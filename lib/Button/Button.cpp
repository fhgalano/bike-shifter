#include "Button.h"


Button::Button(uint8_t pin, bool active_mode, bool active_on_release) {
    // Set object properties
    this->pin = pin;
    this->active_logic_level = active_mode;
    this->active_on_release = active_on_release;

    this->init();
}

void Button::init() {
    // Configure hardware
    pinMode(this->pin, INPUT);

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
    } else if (!(this->last_state && this->current_state && ACTIVE)) {
        this->inactive_handler();
    }
}

void Button::active_on_press_handler(bool current_state) {
    if ((this->last_state == INACTIVE) && (this->current_state == ACTIVE)) {
        this->active_handler();
    } else if (!(this->last_state && this->current_state && INACTIVE)) {
        this->inactive_handler();
    }
}

bool Button::state_is_active() {
    return digitalRead(this->pin) && this->active_logic_level;
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
    this->active_flag = true;
    this->active_start_time = 0;
    this->active_time = 0;
}
