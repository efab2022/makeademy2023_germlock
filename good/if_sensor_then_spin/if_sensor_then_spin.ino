#include <AccelStepper.h>;

#define STEPPER_SPEED 100
#define STEPPER_MAX_SPEED 1000

AccelStepper stepper(1, 2, 3); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
//(::driver, step, dir)


const int trigPin = 6;  // TRIG pin
const int echoPin = 5;  // ECHO pin
const int redLed = 13;
const int greenLed = 12;
const int threshold_distance = 20;

float duration_us, distance_cm;
bool hand_detected = false;


void setup() {
  Serial.begin(9600);
  enable_io_pins();
  enable_stepper_motors();
}

void enable_io_pins() {
  pinMode(trigPin, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(echoPin, INPUT);
}

void enable_stepper_motors() {
   stepper.setMaxSpeed(STEPPER_MAX_SPEED);
   stepper.setSpeed(STEPPER_SPEED); 
}

int hands_distance() {
  if(!hand_detected){
    digitalWrite(trigPin, HIGH);
    delay(100);
    digitalWrite(trigPin, LOW);
  }else{
    digitalWrite(trigPin, HIGH);
    digitalWrite(redLed, HIGH);
    delay(100);
    digitalWrite(trigPin, LOW);
    digitalWrite(redLed, LOW);
  }

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(echoPin, HIGH);

  distance_cm = 0.017 * duration_us;
  return distance_cm;
}


void loop(){
  int distance_cm = hands_distance();
  // print the value to Serial Monitor
  Serial.println(distance_cm);

  if (distance_cm > 0 && distance_cm < threshold_distance) {
    green_led();
    dispense_sanitiser();
  } else {
    red_led();
  }
  delay(100);
}

void dispense_sanitiser(){
  stepper.runSpeed();
}

void red_led(){
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
}

void green_led(){
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    delay(5000);
}
