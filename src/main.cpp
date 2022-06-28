// Include
#include <Arduino.h>
#include <TaskScheduler.h>

#include "Shifter.h"


// Define
#define UPSHIFT_PIN 12
#define DOWNSHIFT_PIN 11
#define SHIFTER_SERVO_PIN 9

#define SERVO_PIN 9
#define START 91


// Global
Shifter shifter(UPSHIFT_PIN, DOWNSHIFT_PIN);
Scheduler scheduler;


// Function Prototypes
void monitor_inputs_callback();
void shifter_manager_callback();


// Task Definitions
Task monitor_inputs(10, TASK_FOREVER, &monitor_inputs_callback);
Task shifter_manager(500, TASK_FOREVER, &shifter_manager_callback);


// Task Callbacks
void monitor_inputs_callback() {
  shifter.shift_detection();
}

void shifter_manager_callback() {
  shifter.shift_handler();
  // TODO: Make a logger function in shifter.cpp to capture system data on shift
}


// Setup
void setup() {
  // Serial Coms Setup
  Serial.begin(9600);
  Serial.println("Serial Communication Initialized...\n");

  Serial.println("Start System Initialization");

  // Initialize Scheduler
  Serial.print("Initialize Scheduler...");
  scheduler.init();
  Serial.println("Done");

  // Initialize Shifter
  Serial.print("Initialize Shifter...");
  shifter.begin(SHIFTER_SERVO_PIN);
  delay(500);
  Serial.println("Done");

  // Add Tasks
  Serial.print("Add Tasks to Scheduler...");
  scheduler.addTask(monitor_inputs);
  scheduler.addTask(shifter_manager);
  delay(1000);
  Serial.println("Done");

  // Enable Tasks
  Serial.print("Enable Tasks...");
  monitor_inputs.enable();
  shifter_manager.enable();
  Serial.println("Done");

}

// Loop
void loop() {
  // put your main code here, to run repeatedly:
  scheduler.execute();
}