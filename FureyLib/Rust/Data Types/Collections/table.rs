// .rs
// Object Table Type
// by Kyle Furey

use std::any;
use std::any::Any;
use std::boxed::Box;
use std::collections::{HashMap, hash_map::IntoIter};
use std::convert::Into;
use std::fmt::{Debug, Display, Formatter, Result};
use std::iter::IntoIterator;
use std::ops::{Index, IndexMut};
use std::option::Option;
use std::string::String;

// TABLE VARIABLES

/// A collection of named objects of any type.
#[derive(Debug)]
pub struct Table {
    /// Each stored object by name.
    objects: HashMap<String, Box<dyn Any>>,
}

// TABLE METHODS

impl Table {
    // CONSTRUCTORS

    /// Default constructor.
    pub fn new() -> Self {
        Self {
            objects: HashMap::with_capacity(16),
        }
    }

    /// Capacity constructor.
    pub fn with_capacity(capacity: usize) -> Self {
        Self {
            objects: HashMap::with_capacity(capacity),
        }
    }

    // TABLE

    /// Returns the current number of stored objects.
    pub fn count(&self) -> usize {
        self.objects.len()
    }

    /// Returns the object with the given name (or none).
    pub fn get(&self, name: impl Into<String>) -> Option<&Box<dyn Any>> {
        let string = name.into();
        if self.objects.contains_key(&string) {
            return self.objects.get(&string);
        }
        None
    }

    /// Returns the object with the given name (or none).
    pub fn get_mut(&mut self, name: impl Into<String>) -> Option<&mut Box<dyn Any>> {
        let string = name.into();
        if self.objects.contains_key(&string) {
            return self.objects.get_mut(&string);
        }
        None
    }

    /// Returns the object downcasted with the given name and type (or none).
    pub fn find<T: 'static>(&self, name: impl Into<String>) -> Option<&T> {
        let string = name.into();
        let obj = self.objects.get(&string);
        if obj.is_some() {
            return obj.unwrap().downcast_ref::<T>();
        }
        None
    }

    /// Returns the object downcasted with the given name and type (or none).
    pub fn find_mut<T: 'static>(&mut self, name: impl Into<String>) -> Option<&mut T> {
        let string = name.into();
        let obj = self.objects.get_mut(&string);
        if obj.is_some() {
            return obj.unwrap().downcast_mut::<T>();
        }
        None
    }

    /// Returns whether the table contains an object of the given name.
    pub fn contains(&self, name: impl Into<String>) -> bool {
        self.objects.contains_key(&name.into())
    }

    /// Returns whether the table contains an object of the given name and type.
    pub fn contains_a<T: 'static>(&'static self, name: impl Into<String>) -> bool {
        let obj = self.objects.get(&name.into());
        if obj.is_some() {
            return obj.unwrap().is::<T>();
        }
        false
    }

    /// Inserts a new object into the table with the given name and type.
    pub fn insert<T: 'static>(&mut self, name: impl Into<String>, obj: T) -> &mut T {
        let string = name.into();
        let existing = self.objects.get(&string);
        if existing.is_some() && !existing.unwrap().is::<T>() {
            panic!(
                "ERROR: Overwriting table object of name {} and type {} with new object of type {}!",
                string,
                existing.unwrap().type_name(),
                any::type_name::<T>()
            );
        }
        self.objects.insert(string.clone(), Box::new(obj));
        self.objects
            .get_mut(&string)
            .unwrap()
            .downcast_mut::<T>()
            .unwrap()
    }

    /// Erases the object with the given name.
    pub fn erase(&mut self, name: impl Into<String>) -> bool {
        let string = name.into();
        if self.objects.contains_key(&string) {
            self.objects.remove(&string);
            return true;
        }
        false
    }

    /// Clears the table of all its objects.
    pub fn clear(&mut self) {
        self.objects.clear();
    }

    /// Converts this table into a string.
    pub fn to_json(&self, pretty_print: bool) -> String {
        if self.objects.is_empty() {
            return String::from("{}");
        }
        let mut json: String = String::from("{");
        if pretty_print {
            for pair in self.objects.iter() {
                json += "\n\t\"";
                json += pair.0.as_str();
                json += "\" : ";
                json += pair.1.any_to_string().as_str();
                json.push(',');
            }
            json.remove(json.len() - 1);
            json.push('\n');
        } else {
            for pair in self.objects.iter() {
                json += " \"";
                json += pair.0.as_str();
                json += "\" : ";
                json += pair.1.any_to_string().as_str();
                json.push(',');
            }
            json.remove(json.len() - 1);
            json.push(' ');
        }
        json += "}";
        json
    }
}

// TABLE OPERATORS

impl Index<&str> for Table {
    /// The underlying object in this table being indexed by its name.
    type Output = Box<dyn Any>;

    /// Returns the object that matches the given name.
    fn index(&self, index: &str) -> &Self::Output {
        self.get(index).expect(
            format!(
                "ERROR: Object of name {} was not found in the table!",
                index
            )
            .as_str(),
        )
    }
}

impl IndexMut<&str> for Table {
    /// Returns the object that matches the given name.
    fn index_mut(&mut self, index: &str) -> &mut Self::Output {
        self.get_mut(index).expect(
            format!(
                "ERROR: Object of name {} was not found in the table!",
                index
            )
            .as_str(),
        )
    }
}

impl IntoIterator for Table {
    /// Each object pair stored in this table.
    type Item = (String, Box<dyn Any>);

    /// An iterator to this table's object pairs.
    type IntoIter = IntoIter<String, Box<dyn Any>>;

    /// Returns an iterator to this table's object pairs.
    fn into_iter(self) -> Self::IntoIter {
        self.objects.into_iter()
    }
}

impl Display for Table {
    fn fmt(&self, f: &mut Formatter<'_>) -> Result {
        write!(f, "{}", self.to_json(true))
    }
}

// TO STRING

/// Converts an Any reference into a string if it is a primitive type.
pub trait AnyToString {
    /// Returns this instance as a string if it is a primitive type.
    fn any_to_string(&self) -> String;

    /// Returns the name of this type as a string if it is a primitive type.
    fn type_name(&self) -> &str;
}

impl AnyToString for dyn Any {
    /// Returns this instance as a string if it is a primitive type.
    fn any_to_string(&self) -> String {
        if let Some(var) = self.downcast_ref::<i8>() {
            return var.to_string();
        }
        if let Some(var) = self.downcast_ref::<i16>() {
            return var.to_string();
        }
        if let Some(var) = self.downcast_ref::<i32>() {
            return var.to_string();
        }
        if let Some(var) = self.downcast_ref::<i64>() {
            return var.to_string();
        }
        if let Some(var) = self.downcast_ref::<isize>() {
            return var.to_string();
        }
        if let Some(var) = self.downcast_ref::<u8>() {
            return var.to_string();
        }
        if let Some(var) = self.downcast_ref::<u16>() {
            return var.to_string();
        }
        if let Some(var) = self.downcast_ref::<u32>() {
            return var.to_string();
        }
        if let Some(var) = self.downcast_ref::<u64>() {
            return var.to_string();
        }
        if let Some(var) = self.downcast_ref::<usize>() {
            return var.to_string();
        }
        if let Some(var) = self.downcast_ref::<f32>() {
            return var.to_string();
        }
        if let Some(var) = self.downcast_ref::<f64>() {
            return var.to_string();
        }
        if let Some(var) = self.downcast_ref::<bool>() {
            return var.to_string();
        }
        if let Some(var) = self.downcast_ref::<char>() {
            let mut result = String::from('\'');
            result.push(*var);
            result.push('\'');
            return result;
        }
        if let Some(var) = self.downcast_ref::<&str>() {
            let mut result = String::from('"');
            result += var;
            result.push('"');
            return result;
        }
        if let Some(var) = self.downcast_ref::<String>() {
            let mut result = String::from('"');
            result += var.as_str();
            result.push('"');
            return result;
        }
        String::from("???")
    }

    /// Returns the name of this type as a string if it is a primitive type.
    fn type_name(&self) -> &str {
        if self.downcast_ref::<i8>().is_some() {
            return any::type_name::<i8>();
        }
        if self.downcast_ref::<i16>().is_some() {
            return any::type_name::<i16>();
        }
        if self.downcast_ref::<i32>().is_some() {
            return any::type_name::<i32>();
        }
        if self.downcast_ref::<i64>().is_some() {
            return any::type_name::<i64>();
        }
        if self.downcast_ref::<isize>().is_some() {
            return any::type_name::<isize>();
        }
        if self.downcast_ref::<u8>().is_some() {
            return any::type_name::<u8>();
        }
        if self.downcast_ref::<u16>().is_some() {
            return any::type_name::<u16>();
        }
        if self.downcast_ref::<u32>().is_some() {
            return any::type_name::<u32>();
        }
        if self.downcast_ref::<u64>().is_some() {
            return any::type_name::<u64>();
        }
        if self.downcast_ref::<usize>().is_some() {
            return any::type_name::<usize>();
        }
        if self.downcast_ref::<f32>().is_some() {
            return any::type_name::<f32>();
        }
        if self.downcast_ref::<f64>().is_some() {
            return any::type_name::<f64>();
        }
        if self.downcast_ref::<bool>().is_some() {
            return any::type_name::<bool>();
        }
        if self.downcast_ref::<char>().is_some() {
            return any::type_name::<char>();
        }
        if self.downcast_ref::<&str>().is_some() {
            return any::type_name::<&str>();
        }
        if self.downcast_ref::<String>().is_some() {
            return any::type_name::<String>();
        }
        "???"
    }
}
