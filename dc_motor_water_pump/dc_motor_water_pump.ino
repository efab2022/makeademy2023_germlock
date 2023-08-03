
// constants won't change
const int ENA_PIN = 9; // the Arduino pin connected to the EN1 pin L298N
const int IN1_PIN = 8; // the Arduino pin connected to the IN1 pin L298N
const int IN2_PIN = 7; // the Arduino pin connected to the IN2 pin L298N
const int pump_speed = 0.5; // set between 0 and 1 (stopped to full speed)

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins as outputs.
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(ENA_PIN, OUTPUT);

  digitalWrite(IN1_PIN, HIGH); // control motor A spins clockwise
  digitalWrite(IN2_PIN, LOW);  // control motor A spins clockwise
}

void loop() {
  analogWrite(ENA_PIN, 100);
}
