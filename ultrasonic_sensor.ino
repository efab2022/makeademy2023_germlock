/*
 * Created by ArduinoGetStarted, https://arduinogetstarted.com
 *
 * Arduino - Ultrasonic Sensor HC-SR04
 *
 * Wiring: Ultrasonic Sensor -> Arduino:
 * - VCC  -> 5VDC
 * - TRIG -> Pin 9
 * - ECHO -> Pin 8
 * - GND  -> GND
 *
 * Tutorial is available here: https://arduinogetstarted.com/tutorials/arduino-ultrasonic-sensor
 */

int trigPin = 9;  // TRIG pin
int echoPin = 8;  // ECHO pin
int ledPin = 13;  // transmit LED
int redLed = 12;
int greenLed = 11;
int threshold_distance = 20;

float duration_us, distance_cm;

void setup() {


  // begin serial port
  Serial.begin(9600);

  // configure the trigger pin to output mode
  pinMode(trigPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  // configure the echo pin to input mode
  pinMode(echoPin, INPUT);
}

void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(trigPin, HIGH);
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(trigPin, LOW);
  digitalWrite(ledPin, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(echoPin, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;

  // print the value to Serial Monitor
  Serial.println(distance_cm);

  if (distance_cm < threshold_distance) {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
  } else {
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
  }

  delay(100);
}
