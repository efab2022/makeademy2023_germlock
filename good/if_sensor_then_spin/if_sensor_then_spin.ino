#include <Stepper.h>
const int stepsPerRevolution_default = 1500;
const int rpm = 15;
Stepper stepper1 = Stepper(stepsPerRevolution_default, 4, 5, 6, 7);

const int trigPin = 9;  // TRIG pin
const int echoPin = 8;  // ECHO pin
const int ledPin = 13;  // transmit LED
const int redLed = 12;
const int greenLed = 11;
const int threshold_distance = 20;

const int nemaStepPin = 1;
const int nemaDirectionPin = 0;
const int stepsPerRevolution_nema = 200;

float duration_us, distance_cm;


void setup() {
  Serial.begin(9600);
  enable_io_pins();
  enable_stepper_motors();
}

void enable_io_pins() {
  pinMode(trigPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(nemaStepPin, OUTPUT);
  pinMode(nemaDirectionPin, OUTPUT);

}

void enable_stepper_motors() {
  stepper1.setSpeed(rpm);
  digitalWrite(nemaDirectionPin, HIGH);
}

int hands_distance() {
  digitalWrite(trigPin, HIGH);
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(trigPin, LOW);
  digitalWrite(ledPin, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(echoPin, HIGH);

  distance_cm = 0.017 * duration_us;
  return distance_cm;
}


void loop(){
  int distance_cm = hands_distance();
  // print the value to Serial Monitor
  Serial.println(distance_cm);

  if (distance_cm < threshold_distance) {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    dispense_sanitiser();
  } else {
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
    delay(100);
  }
  delay(100);
}

void dispense_sanitiser(){
  stepper1.step(stepsPerRevolution_default);
  delay(1000);
  stepNema(1000);
}

void stepNema(int numSteps){
  const int pause_in_microseconds = 1000;
  for(int x = 0; x < numSteps; x++){
    digitalWrite(nemaStepPin, HIGH);
    delayMicroseconds(pause_in_microseconds);
    digitalWrite(nemaStepPin, LOW);
    delayMicroseconds(pause_in_microseconds);
  } 
}

