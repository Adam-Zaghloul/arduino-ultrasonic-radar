// DC Motor Speed Control with L298N
// Arduino Uno - Enhanced Demo
// Pins
#define ENA 9
#define IN1 7
#define IN2 8

void motorForward(int spd) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, spd);
}

void motorReverse(int spd) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, spd);
}

void motorStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}

void smoothRamp(bool forward, int fromSpeed, int toSpeed, int stepDelay) {
  if (fromSpeed < toSpeed) {
    for (int s = fromSpeed; s <= toSpeed; s++) {
      forward ? motorForward(s) : motorReverse(s);
      delay(stepDelay);
    }
  } else {
    for (int s = fromSpeed; s >= toSpeed; s--) {
      forward ? motorForward(s) : motorReverse(s);
      delay(stepDelay);
    }
  }
}

void pulseDemo() {
  Serial.println("=== PULSE DEMO ===");
  for (int i = 0; i < 5; i++) {
    motorForward(255);
    Serial.println("BURST ON");
    delay(300);
    motorStop();
    Serial.println("BURST OFF");
    delay(300);
  }
}

void oscillateDemo() {
  Serial.println("=== OSCILLATE DEMO ===");
  for (int i = 0; i < 3; i++) {
    smoothRamp(true, 0, 255, 5);   // Forward ramp up
    smoothRamp(true, 255, 0, 5);   // Forward ramp down
    smoothRamp(false, 0, 255, 5);  // Reverse ramp up
    smoothRamp(false, 255, 0, 5);  // Reverse ramp down
  }
}

void stepDemo() {
  Serial.println("=== STEP RESPONSE DEMO ===");
  Serial.println("0% speed");   motorStop();        delay(1000);
  Serial.println("25% speed");  motorForward(64);   delay(1500);
  Serial.println("50% speed");  motorForward(128);  delay(1500);
  Serial.println("75% speed");  motorForward(191);  delay(1500);
  Serial.println("100% speed"); motorForward(255);  delay(1500);
  Serial.println("STOP");       motorStop();        delay(1000);
}

void reverseDemo() {
  Serial.println("=== DIRECTION CHANGE DEMO ===");
  smoothRamp(true, 0, 200, 8);
  Serial.println("Forward at 200");
  delay(1000);
  smoothRamp(true, 200, 0, 8);
  motorStop();
  delay(500);
  smoothRamp(false, 0, 200, 8);
  Serial.println("Reverse at 200");
  delay(1000);
  smoothRamp(false, 200, 0, 8);
  motorStop();
  delay(500);
}

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  Serial.begin(9600);
  Serial.println("=== MOTOR DEMO STARTING ===");
  delay(1000);
}

void loop() {
  stepDemo();
  delay(1000);

  pulseDemo();
  delay(1000);

  oscillateDemo();
  delay(1000);

  reverseDemo();
  delay(1000);
}
