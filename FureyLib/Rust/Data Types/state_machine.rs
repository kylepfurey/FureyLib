// .rs
// State Machine Interface and Structure
// by Kyle Furey

use std::any::{Any, TypeId};
use std::boxed::Box;
use std::ops::{Deref, DerefMut};
use std::option::Option;
use std::time::Instant;

// STATE

/** An interface defining a structure that can be used as a state within a state machine. */
pub trait State<Type: 'static>: Any {
    // INTERFACE

    /** Called when a state machine instantiates this state. */
    fn on_state_enter(&mut self, previous_state: Option<&mut Box<dyn State<Type>>>);

    /** Called when a state machine updates this state. */
    fn on_state_update(&mut self, delta_time: f64);

    /** Called when a state machine switches off this state. */
    fn on_state_exit(&mut self, next_state: Option<&mut Box<dyn State<Type>>>);

    /** Returns the state machine that owns this state. */
    fn get_state_machine(&mut self) -> &mut StateMachine<Type>;

    /** Sets the state machine that owns this state. */
    fn set_state_machine(&mut self, state_machine: &mut StateMachine<Type>);
}

// STATE MACHINE VARIABLES

/** A structure that manages its data within different states of code. */
pub struct StateMachine<Type> {
    /** The data this state machine is managing. */
    data: Type,

    /** The current state of this state machine. */
    state: Option<Box<dyn State<Type>>>,

    /** The time of this state machine's last update. */
    last_update: Instant,

    /** The time in seconds since the state machine's last update. */
    delta_time: f64,
}

// STATE MACHINE METHODS

/** A structure that manages its data within different states of code. */
impl<Type: 'static> StateMachine<Type> {
    /** Default constructor. */
    pub fn new(data: Type) -> StateMachine<Type> {
        StateMachine {
            data,
            state: None,
            last_update: Instant::now(),
            delta_time: 0.0,
        }
    }

    /** State constructor. */
    pub fn new_from_state(data: Type, state: Option<Box<dyn State<Type>>>) -> StateMachine<Type> {
        StateMachine {
            data,
            state,
            last_update: Instant::now(),
            delta_time: 0.0,
        }
    }

    /** Returns the data this state machine is managing. */
    pub fn get_data_ref(&self) -> &Type {
        &self.data
    }

    /** Returns the data this state machine is managing. */
    pub fn get_data_mut(&mut self) -> &mut Type {
        &mut self.data
    }

    /** Returns the current state of this state machine. */
    pub fn get_state_ref(&self) -> Option<&Box<dyn State<Type>>> {
        self.state.as_ref()
    }

    /** Returns the current state of this state machine. */
    pub fn get_state_mut(&mut self) -> Option<&mut Box<dyn State<Type>>> {
        self.state.as_mut()
    }

    /** Returns the type of the state machine's current state. */
    pub fn get_state_type(&self) -> Option<TypeId> {
        if self.state.is_none() {
            return None;
        }
        Some(self.state.type_id())
    }

    /** Returns whether the state machine's current state is not empty. */
    pub fn is_state_valid(&self) -> bool {
        self.state.is_some()
    }

    /** Returns whether the state machine's current state is the given type. */
    pub fn state_is<StateType: State<Type> + 'static>(&self) -> bool {
        if self.state.is_none() {
            return false;
        }
        let any: &dyn Any = self.state.as_ref().unwrap().deref();
        any.is::<StateType>()
    }

    /** Returns the state machine's current state as the given type. */
    pub fn state_as_ref<StateType: State<Type> + 'static>(&self) -> Option<&StateType> {
        if self.state.is_none() {
            return None;
        }
        let any: &dyn Any = self.state.as_ref().unwrap().deref();
        any.downcast_ref::<StateType>()
    }

    /** Returns the state machine's current state as the given type. */
    pub fn state_as_mut<StateType: State<Type> + 'static>(&mut self) -> Option<&mut StateType> {
        if self.state.is_none() {
            return None;
        }
        let any: &mut dyn Any = self.state.as_mut().unwrap().deref_mut();
        any.downcast_mut::<StateType>()
    }

    /** Returns the time of this state machine's last update. */
    pub fn get_last_update(&self) -> Instant {
        self.last_update
    }

    /** Returns the time in seconds since the state machine's last update. */
    pub fn get_delta_time(&self) -> f64 {
        self.delta_time
    }

    /** Sets the data this state machine is managing. */
    pub fn set_data(&mut self, data: Type) {
        self.data = data;
    }

    /** Switches the state machine's current state to a new state. */
    pub fn switch_state(
        &mut self,
        mut new_state: Option<Box<dyn State<Type>>>,
    ) -> Option<&mut Box<dyn State<Type>>> {
        let mut current_state = self.state.take();
        if current_state.is_some() {
            current_state
                .as_mut()
                .unwrap()
                .on_state_exit(new_state.as_mut());
        }
        if new_state.is_some() {
            new_state.as_mut().unwrap().set_state_machine(self);
            self.state = new_state;
            self.state
                .as_mut()
                .unwrap()
                .on_state_enter(current_state.as_mut());
        } else {
            self.state = None;
        }
        self.state.as_mut()
    }

    /** Updates the state machine's current state and returns the state machine's current or new state. */
    pub fn update(&mut self) -> Option<&mut Box<dyn State<Type>>> {
        let now = Instant::now();
        self.delta_time = f64::max((now - self.last_update).as_secs_f64(), 0.000001);
        self.last_update = now;
        if self.state.is_some() {
            self.state
                .as_mut()
                .unwrap()
                .on_state_update(self.delta_time);
        }
        self.state.as_mut()
    }

    /** Updates the state machine until its current state is null. */
    pub fn unwrap(&mut self) {
        while self.update().is_some() {}
    }
}
