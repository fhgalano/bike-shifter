#include "Shifter.h"

#define BASE_SHIFT_FACTOR 10
#define SHIFT_STARTING_POSITION 90

#define MAX_SHIFT_POSITION 180
#define MIN_SHIFT_POSITION 0

#define BUTTON_ACTIVE_STATE 0


// PUBLIC
Shifter::Shifter(int upshift_pin, int downshift_pin) {
    this->upshift_pin = upshift_pin;
    this->downshift_pin = downshift_pin;
    init();
}

void Shifter::begin(uint8_t shifter_servo_pin) {
    this->shifter_servo.attach(shifter_servo_pin, 500, 2500);
}

void Shifter::init() {
    this->shift_factor = BASE_SHIFT_FACTOR;

    // Setup Pin Modes
    pinMode(this->upshift_pin, INPUT);
    pinMode(this->downshift_pin, INPUT);

    // Set servo to starting position
    this->shifter_servo.write(SHIFT_STARTING_POSITION);
    this->servo_position = SHIFT_STARTING_POSITION;
}

void Shifter::upshift() {
    // detect direction and update position
    this->servo_position += this->shift_factor;

    // checking for upper limit exceedance 
    this->max_position_correction();

    // write position
    this->shifter_servo.write(this->servo_position);
}

void Shifter::downshift() {
    // detect direction and update position
    this->servo_position -= this->shift_factor;

    // checking for upper limit exceedance 
    this->min_position_correction();

    // write position
    this->shifter_servo.write(this->servo_position);
}

void Shifter::shift_detection() {
    // get pin states and shift
    if (this->shift_button_is_active(this->downshift_pin)) {
        this->downshift_flag = true;
    } else if (this->shift_button_is_active(this->upshift_pin)) {
        this->upshift_flag = true;
    }
}

void Shifter::shift_handler() {
    this->downshift_handler();
    this->upshift_handler();
    this->shifter_servo.write(this->servo_position);
}

// PRIVATE
bool Shifter::shift_button_is_active(int pin) {
    int state = digitalRead(pin);

    if ( state == BUTTON_ACTIVE_STATE) {
        return true;
    } else {
        return false;
    }
}

void Shifter::max_position_correction() {
    this->servo_position = min(this->servo_position, MAX_SHIFT_POSITION);
}

void Shifter::min_position_correction() {
    this->servo_position = max(this->servo_position, MIN_SHIFT_POSITION);
}

void Shifter::upshift_handler() {
    if (this->upshift_flag) {
        this->upshift();
    }
    this->upshift_flag = false;
}

void Shifter::downshift_handler() {
    if (this->downshift_flag) {
        this->downshift();
    }
    this->downshift_flag = false;
}