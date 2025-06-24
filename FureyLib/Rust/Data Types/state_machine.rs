// .rs
// State Machine Interface and Structure
// by Kyle Furey

use std::boxed::Box;
use std::option::Option;
use std::time::Instant;

// STATE

/// An interface defining a structure that can be used as a state within a state machine.
pub trait State<'a, Type: 'a> {
    // INTERFACE

    /// Called when a state machine instantiates this state.
    fn on_state_enter(
        &mut self,
        state_machine: &mut StateMachine<'a, Type>,
        previous_state: Option<&mut Box<dyn State<'a, Type>>>,
    );

    /// Called when a state machine updates this state.
    fn on_state_update(&mut self, state_machine: &mut StateMachine<'a, Type>, delta_time: f64);

    /// Called when a state machine switches off this state.
    fn on_state_exit(
        &mut self,
        state_machine: &mut StateMachine<'a, Type>,
        next_state: Option<&mut Box<dyn State<'a, Type>>>,
    );
}

// STATE MACHINE VARIABLES

/// A structure that manages its data within different states of code.
pub struct StateMachine<'a, Type: 'a> {
    /// The data this state machine is managing.
    data: Type,

    /// The current state of this state machine.
    state: Option<Box<dyn State<'a, Type>>>,

    /// The time of this state machine's last update.
    last_update: Instant,

    /// The time in seconds since the state machine's last update.
    delta_time: f64,
}

// STATE MACHINE METHODS

impl<'a, Type: 'a> StateMachine<'a, Type> {
    // CONSTRUCTORS

    /// Default constructor.
    pub fn new(data: Type) -> Self {
        StateMachine {
            data,
            state: None,
            last_update: Instant::now(),
            delta_time: 0.0,
        }
    }

    /// State constructor.
    pub fn new_from_state(data: Type, state: Option<Box<dyn State<'a, Type>>>) -> Self {
        StateMachine {
            data,
            state,
            last_update: Instant::now(),
            delta_time: 0.0,
        }
    }

    // GETTERS

    /// Returns the data this state machine is managing.
    pub fn get_data_ref(&self) -> &Type {
        &self.data
    }

    /// Returns the data this state machine is managing.
    pub fn get_data_mut(&mut self) -> &mut Type {
        &mut self.data
    }

    /// Returns the current state of this state machine.
    pub fn get_state_ref(&self) -> Option<&Box<dyn State<'a, Type>>> {
        self.state.as_ref()
    }

    /// Returns the current state of this state machine.
    pub fn get_state_mut(&mut self) -> Option<&mut Box<dyn State<'a, Type>>> {
        self.state.as_mut()
    }

    /// Returns whether the state machine's current state is not empty.
    pub fn is_state_valid(&self) -> bool {
        self.state.is_some()
    }

    /// Returns the time of this state machine's last update.
    pub fn get_last_update(&self) -> Instant {
        self.last_update
    }

    /// Returns the time in seconds since the state machine's last update.
    pub fn get_delta_time(&self) -> f64 {
        self.delta_time
    }

    // SETTERS

    /// Sets the data this state machine is managing.
    pub fn set_data(&mut self, data: Type) {
        self.data = data;
    }

    /// Switches the state machine's current state to a new state.
    pub fn switch_state(
        &mut self,
        mut new_state: Option<Box<dyn State<'a, Type>>>,
    ) -> Option<&mut Box<dyn State<'a, Type>>> {
        let mut current_state = self.state.take();
        if current_state.is_some() {
            current_state
                .as_mut()
                .unwrap()
                .on_state_exit(self, new_state.as_mut());
        }
        if new_state.is_some() {
            new_state
                .as_mut()
                .unwrap()
                .on_state_enter(self, current_state.as_mut());
            self.state = new_state;
        } else {
            self.state = None;
        }
        self.state.as_mut()
    }

    /// Updates the state machine's current state and returns the state machine's current or new state.
    pub fn update(&mut self) -> Option<&mut Box<dyn State<'a, Type>>> {
        let now = Instant::now();
        self.delta_time = f64::max((now - self.last_update).as_secs_f64(), 0.000001);
        self.last_update = now;
        if self.state.is_some() {
            let mut unboxed = self.state.take().unwrap();
            unboxed.on_state_update(self, self.delta_time);
            self.state = Some(unboxed);
        }
        self.state.as_mut()
    }

    /// Updates the state machine until its current state is null.
    pub fn unwrap(&mut self) {
        while self.update().is_some() {}
    }
}
