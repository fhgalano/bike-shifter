#ifndef SHIFTER_H
#define SHIFTER_H

#include <Arduino.h>
#include <Servo.h>

class Shifter {
    private:
        int upshift_pin;
        int downshift_pin;
        int shift_factor;
        bool shift_button_is_active(int pin);
        void max_position_correction();
        void min_position_correction();
        void upshift_handler();
        void downshift_handler();
        void relative_position_handler();

    public:
        Shifter(int upshift_pin, int downshift_pin);
        void init();
        void upshift();
        void downshift();
        void shift_detection();
        void shift_handler();
        void begin(uint8_t shifter_servo_pin);
        int servo_position;
        bool upshift_flag;
        bool downshift_flag;
        Servo shifter_servo;

        

};

#endif