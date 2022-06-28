#include <Arduino.h>
#include "Shifter.h"

#define UPSHIFT_PIN 12
#define DOWNSHIFT_PIN 11
#define SHIFTER_SERVO_PIN 9


#define SERVO_PIN 9
#define START 91

Shifter shifter(UPSHIFT_PIN, DOWNSHIFT_PIN);

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  shifter.begin(SHIFTER_SERVO_PIN);
}

void loop() {
  // put your main code here, to run repeatedly:
  shifter.shift_detection();
  shifter.shift_handler();

  //Serial.print("Pos: ");
  //Serial.print(shifter.servo_position);
  //Serial.print("  Real Pos: ");
  //Serial.println(shifter.shifter_servo.read());

  delay(150);
}