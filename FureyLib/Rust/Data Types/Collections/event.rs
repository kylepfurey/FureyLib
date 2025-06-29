// .rs
// Multicast Event Type
// by Kyle Furey

use std::any::Any;
use std::clone::Clone;
use std::convert::Into;
use std::hash::{DefaultHasher, Hash, Hasher};
use std::iter::IntoIterator;
use std::ops::{AddAssign, FnMut, SubAssign};
use std::option::Option;
use std::string::String;
use std::vec::{IntoIter, Vec};

// EVENT VARIABLES

/// A collection of functions that can be bound, unbound, and invoked all at once.
pub struct Event<'a, T, A: Clone> {
    /// Each bound function and its ID.
    bindings: Vec<(String, Box<dyn FnMut(A) -> T + 'a>)>,
}

// EVENT METHODS

impl<'a, T, A: Clone> Event<'a, T, A> {
    // CONSTRUCTORS

    /// Default constructor.
    pub fn new() -> Self {
        Event {
            bindings: Vec::with_capacity(8),
        }
    }

    /// Capacity constructor.
    pub fn with_capacity(capacity: usize) -> Self {
        Event {
            bindings: Vec::with_capacity(capacity),
        }
    }

    // EVENT

    /// Creates a string ID from the given function.
    fn make_id<F: FnMut(A) -> T + 'static>(&self, callback: &F) -> String {
        let mut hasher = DefaultHasher::new();
        callback.type_id().hash(&mut hasher);
        hasher.finish().to_string()
    }

    /// Returns the total number of bound functions.
    pub fn count(&self) -> usize {
        self.bindings.len()
    }

    /// Returns the maximum number of functions that can be bound before resizing.
    pub fn capacity(&self) -> usize {
        self.bindings.capacity()
    }

    /// Binds a new function to this event.
    pub fn bind<F: FnMut(A) -> T + 'static>(&mut self, callback: F) {
        self.bind_id(self.make_id(&callback), callback);
    }

    /// Binds a new function and its ID to this event.
    pub fn bind_id<F: FnMut(A) -> T + 'a>(&mut self, id: impl Into<String>, callback: F) {
        self.bindings.push((id.into(), Box::new(callback)));
    }

    /// Unbinds the first bound function that matches the given function from this event.
    pub fn unbind<F: FnMut(A) -> T + 'static>(&mut self, callback: F) -> bool {
        self.unbind_id(self.make_id(&callback))
    }

    /// Unbinds the first bound function that matches the given ID from this event.
    pub fn unbind_id(&mut self, id: impl Into<String>) -> bool {
        let string = id.into();
        for i in 0..self.bindings.len() {
            if self.bindings[i].0 == string {
                drop(self.bindings.remove(i));
                return true;
            }
        }
        false
    }

    /// Returns whether at least one bound function matches the given function.
    pub fn is_bound<F: FnMut(A) -> T + 'static>(&self, callback: F) -> bool {
        self.is_bound_id(self.make_id(&callback))
    }

    /// Returns whether at least one bound function matches the given ID.
    pub fn is_bound_id(&self, id: impl Into<String>) -> bool {
        let string = id.into();
        for i in 0..self.bindings.len() {
            if self.bindings[i].0 == string {
                return true;
            }
        }
        false
    }

    /// Invokes each bound function with the given arguments and returns the most recent function's returned value.
    pub fn invoke(&mut self, args: A) -> Option<T> {
        let mut result = None;
        for i in 0..self.bindings.len() {
            result = Some(self.bindings[i].1(args.clone()));
        }
        result
    }

    /// Unbinds all functions from this event.
    pub fn clear(&mut self) {
        self.bindings.clear();
    }
}

// EVENT OPERATORS

impl<'a, T, A: Clone, F: FnMut(A) -> T + 'static> AddAssign<F> for Event<'a, T, A> {
    /// Binds a new function to this event.
    fn add_assign(&mut self, callback: F) {
        self.bind(callback)
    }
}

impl<'a, T, A: Clone, F: FnMut(A) -> T + 'static> SubAssign<F> for Event<'a, T, A> {
    /// Unbinds the first instance of the given function from this event.
    fn sub_assign(&mut self, callback: F) {
        self.unbind(callback);
    }
}

impl<'a, T, A: Clone> IntoIterator for Event<'a, T, A> {
    /// Each function stored within this event.
    type Item = (String, Box<dyn FnMut(A) -> T + 'a>);

    /// An iterator to this event's bound functions.
    type IntoIter = IntoIter<Self::Item>;

    /// Returns an iterator to the event's bindings.
    fn into_iter(self) -> Self::IntoIter {
        self.bindings.into_iter()
    }
}

// ID

/// Creates a string ID from the given data's address.
pub fn make_id<T>(data: &T) -> String {
    format!("{:p}", &*data)
}
