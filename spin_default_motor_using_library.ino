   /*
  ULN2003-Stepper-Motor-Driver
  modified on 25 Nov 2020
  by Amir Mohammad Shojaee @ Electropeak
  Home
  
  based on Arduino library Example
*/

#include <Stepper.h>
const int stepsPerRevolution = 1500;
const int rpm = 15;
Stepper stepper1 = Stepper(stepsPerRevolution, 4, 5, 6, 7);

void setup() {
  stepper1.setSpeed(rpm);
}

void loop() {
  stepper1.step(stepsPerRevolution);
  delay(1000);
}
