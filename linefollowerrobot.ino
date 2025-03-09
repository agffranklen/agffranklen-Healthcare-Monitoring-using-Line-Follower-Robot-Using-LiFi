// Define pins for IR sensors
const int leftSensorPin = 2;
const int centerSensorPin = 3;
const int rightSensorPin = 4;

// Define pins for L298N motor driver
const int motorPin1 = 5;
const int motorPin2 = 6;
const int motorPin3 = 7;
const int motorPin4 = 8;
const int enablePinA = 9;
const int enablePinB = 10;

// Define motor speed (0-255)
int motorSpeedA = 80;
int motorSpeedB = 70;

void setup() {
  // Initialize IR sensor pins as input
  pinMode(leftSensorPin, INPUT);
  pinMode(centerSensorPin, INPUT);
  pinMode(rightSensorPin, INPUT);
  
  // Initialize motor driver pins as output
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(enablePinA, OUTPUT);
  pinMode(enablePinB, OUTPUT);

  // Set initial motor speed
  analogWrite(enablePinA, motorSpeedA);
  analogWrite(enablePinB, motorSpeedB);
}

void loop() {
  // Read IR sensor values
  int leftValue = digitalRead(leftSensorPin);
  int centerValue = digitalRead(centerSensorPin);
  int rightValue = digitalRead(rightSensorPin);
  
  // Control logic for line following
  if (centerValue == HIGH && rightValue == LOW && leftValue == LOW) {
    // Move forward
    moveForward();
  } else if (centerValue == HIGH && rightValue == HIGH && leftValue == HIGH) {
    // Stop if no line is detected
    stopMoving();
  } else if (centerValue == LOW && leftValue == LOW && rightValue == LOW) {
    delay(3000);
    moveForward();
  }
  else if (centerValue == LOW && rightValue == LOW) {
    // Turn left
    turnLeft();
  } else if (centerValue == LOW && leftValue == LOW ) {
    // Turn right
    turnRight();
  } 
}

// Function to move forward
void moveForward() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  analogWrite(enablePinA, motorSpeedA);
  analogWrite(enablePinB, motorSpeedB);
}

// Function to turn left
void turnLeft() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  analogWrite(enablePinA, motorSpeedA / 2);
  analogWrite(enablePinB, motorSpeedB);
}

// Function to turn right
void turnRight() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  analogWrite(enablePinA, motorSpeedA);
  analogWrite(enablePinB, motorSpeedB / 2);
}

// Function to stop moving
void stopMoving() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  analogWrite(enablePinA, 0);
  analogWrite(enablePinB, 0);
}