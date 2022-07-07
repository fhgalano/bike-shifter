#ifndef LIB_BUTTON_BUTTON_H_
#define LIB_BUTTON_BUTTON_H_

#include <Arduino.h>

#define ACTIVE true
#define INACTIVE false

class Button {
 private:
    // Setup Vars
    uint8_t pin;
    bool active_logic_level;
    bool active_on_release;

    // Usage Vars
    bool current_state;
    bool last_state;
    bool active_flag;
    uint8_t active_count;
    int32_t active_start_time;
    int32_t active_time;
    bool hold_is_active;

    // Functions
    void init();
    void detect_state();
    void detection_handler();
    void state_handler(bool current_state);
    void active_on_release_handler(bool current_state);
    void active_on_press_handler(bool current_state);
    void active_handler();
    void inactive_handler();
    void set_flag_inactive();
    bool state_is_active();

 public:
    Button(uint8_t pin, bool active_mode, bool active_on_release);
    bool get_state();
    void add_hold(int32_t hold_target_time);
};

class Hold {
 private:
    int32_t hold_target_time;
    int32_t hold_current_time;
    int32_t hold_time;

 public:
    explicit Hold(int32_t hold_time);
    void init();
    bool hold_flag;
};

#endif  // LIB_BUTTON_BUTTON_H_
