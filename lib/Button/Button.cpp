#include "Button.h"


// Public
Button::Button(uint8_t pin, bool active_mode, bool active_on_release) {
    // Set object properties
    this->pin = pin;
    this->active_logic_level = active_mode;
    this->active_on_release = active_on_release;

    // Configure hardware
    pinMode(this->pin, INPUT);

    this->init();
}

Button::Button() {
    init();
}

bool Button::get_state() {
    bool state = this->active_flag;
    if (state) {
        this->set_flag_inactive();
    }

    return state;
}

void Button::detection_handler() {
    this->detect_state();
    this->state_handler(this->state_is_active());
}

// Private
void Button::init() {
    // Setup initial state
    this->active_flag = false;
    this->current_state = false;
    this->hold_is_active = false;
    this->active_count = 0;
    this->active_time = 0;
}

void Button::detect_state() {
    if (this->state_is_active()) {
        this->current_state = ACTIVE;
    } else {
        this->current_state = INACTIVE;
    }
}

bool Button::state_is_active() {
    return digitalRead(this->pin) && this->active_logic_level;
}

void Button::state_handler(bool current_state) {
    if (this->active_on_release) {
        this->active_on_release_handler(current_state);
    } else {
        this->active_on_press_handler(current_state);
    }
}

void Button::active_on_release_handler(bool current_state) {
    if ((this->last_state == ACTIVE) && (this->current_state == INACTIVE)) {
        this->active_handler();
    } else {
        this->inactive_handler();
    }
}

void Button::active_on_press_handler(bool current_state) {
    if ((this->last_state == INACTIVE) && (this->current_state == ACTIVE)) {
        this->active_handler();
    } else {
        this->inactive_handler();
    }
}

void Button::active_handler() {
    if (!this->active_flag) {
        this->active_flag = true;
        this->active_start_time = millis();
        this->active_time = 0;
    } else {
        this->active_time = millis() - this->active_start_time;
    }
}

void Button::inactive_handler() {
    this->active_start_time = millis();
    this->active_time = 0;
}

void Button::set_flag_inactive() {
    this->active_flag = INACTIVE;
}
