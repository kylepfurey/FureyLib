// .rs
// Slab Type
// by Kyle Furey

use std::collections::VecDeque;
use std::iter::IntoIterator;
use std::ops::{Index, IndexMut};
use std::option::Option;
use std::vec::{IntoIter, Vec};

// SLAB TYPES

/// A unique ID used to lookup an object in a slab.
type ID = usize;

// SLAB VARIABLES

/// A collection that manages the memory of each object it contains by providing handles to access the objects.
pub struct Slab<T> {
    /// The underlying array of objects in the slab.
    objects: Vec<Option<T>>,

    /// Each ID that can be reused in the slab.
    next_ids: VecDeque<ID>,

    /// The current number of objects in the slab.
    count: usize,
}

// SLAB METHODS

impl<T> Slab<T> {
    // CONSTRUCTORS

    /// Default constructor.
    pub fn new() -> Self {
        let mut slab = Self {
            objects: Vec::with_capacity(16),
            next_ids: VecDeque::with_capacity(16),
            count: 0,
        };
        for i in 0..16 {
            slab.next_ids.push_back(i);
            slab.objects.push(None);
        }
        slab
    }

    /// Capacity constructor.
    pub fn with_capacity(capacity: usize) -> Self {
        let mut slab = Self {
            objects: Vec::with_capacity(capacity),
            next_ids: VecDeque::with_capacity(capacity),
            count: 0,
        };
        for i in 0..capacity {
            slab.next_ids.push_back(i);
            slab.objects.push(None);
        }
        slab
    }

    // SLAB

    /// Returns the number of objects currently in the slab.
    pub fn count(&self) -> usize {
        self.count
    }

    /// The maximum number of objects that can be stored before resizing the slab.
    pub fn capacity(&self) -> usize {
        self.objects.len()
    }

    /// Adds the object to the slab and returns its unique ID.
    pub fn insert(&mut self, object: T) -> ID {
        if self.next_ids.is_empty() {
            let size = self.objects.len();
            let capacity = if size == 0 { 16 } else { size * 2 };
            for i in size..capacity {
                self.next_ids.push_back(i);
                self.objects.push(None);
            }
        }
        let id = self.next_ids.pop_front().unwrap();
        self.objects[id] = Some(object);
        self.count += 1;
        id
    }

    /// Removes the object that matches the given ID from the slab, and returns whether it was successful.
    pub fn erase(&mut self, id: ID) -> bool {
        if id >= self.objects.len() || self.objects[id].is_none() {
            return false;
        }
        self.objects[id] = None;
        self.next_ids.push_back(id);
        self.count -= 1;
        true
    }

    /// Returns whether the slab contains an object with the given ID.
    pub fn contains(&self, id: ID) -> bool {
        if id >= self.objects.len() {
            return false;
        }
        self.objects[id].is_some()
    }

    /// Returns the object with the given ID if it exists, or none if it does not.
    pub fn find(&self, id: ID) -> Option<&T> {
        if id >= self.objects.len() {
            return None;
        }
        self.objects[id].as_ref()
    }

    /// Returns the object with the given ID if it exists, or none if it does not.
    pub fn find_mut(&mut self, id: ID) -> Option<&mut T> {
        if id >= self.objects.len() {
            return None;
        }
        self.objects[id].as_mut()
    }

    /// Clears the slab of all its objects.
    pub fn clear(&mut self) {
        self.objects.clear();
        self.next_ids.clear();
        self.count = 0;
        for i in 0..16 {
            self.next_ids.push_back(i);
            self.objects.push(None);
        }
    }

    /// Clears the slab of all its objects and resizes to the given capacity.
    pub fn reset(&mut self, capacity: usize) {
        self.objects.clear();
        self.next_ids.clear();
        self.count = 0;
        for i in 0..capacity {
            self.next_ids.push_back(i);
            self.objects.push(None);
        }
    }
}

// SLAB OPERATORS

impl<T> Index<ID> for Slab<T> {
    /// The underlying object in this table being indexed by its name.
    type Output = T;

    /// Finds the object with the specified ID if it is valid.
    fn index(&self, index: ID) -> &Self::Output {
        self.find(index)
            .expect(format!("ERROR: ID {} was not valid!", index).as_str())
    }
}

impl<T> IndexMut<ID> for Slab<T> {
    /// Finds the object with the specified ID if it is valid.
    fn index_mut(&mut self, index: ID) -> &mut Self::Output {
        self.find_mut(index)
            .expect(format!("ERROR: ID {} was not valid!", index).as_str())
    }
}

impl<T> IntoIterator for Slab<T> {
    /// Each object slot in this slab.
    type Item = Option<T>;

    /// An iterator to this slab's object slots.
    type IntoIter = IntoIter<Option<T>>;

    /// Returns an iterator to this slab's objects.
    fn into_iter(self) -> Self::IntoIter {
        self.objects.into_iter()
    }
}
