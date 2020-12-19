/**
 * Program for obstacle avoiding robot
 */
#include <Servo.h>

// change below pins based on your connections
#define leftFwdPin 2
#define leftRevPin 3
#define rightFwdPin 4
#define rightRevPin 5
#define servoPin 7
#define echoPin 8
#define trigPin 9
#define RED_LED 11
#define YELLOW_LED 12
#define GREEN_LED 13

// servo motor class
Servo servo;

/**
 * set sensor's trigger Pin to output and echo pin to input
 */
void setupSensor() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
}

/**
 * set pins where LEDs are connected to output
 */
void setupLEDIndicators() {
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}

/**
 * setup motor pins
 */
void setupMotors() {
  pinMode(leftFwdPin, OUTPUT);
  pinMode(leftRevPin, OUTPUT);
  pinMode(rightFwdPin, OUTPUT);
  pinMode(rightFwdPin, OUTPUT);
}

/**
 * attach servo motor to servo pin
 */
void setupServo() {
  servo.attach(servoPin);
}

/**
 * setup 
 */
void setup() {
  setupSensor();
  setupMotors();
  setupServo();
  setupLEDIndicators();
}

/**
 * Turn on RED LED only
 */
void stopSign() {
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
}

/**
 * Turn on YELLOW LED only
 */
void readyToGoSign() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, HIGH);
}

/**
 * Turn on GREEN LED only
 */
void goSign() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(YELLOW_LED, LOW);
}

/**
 * Set robot in forward motion and glow GO Sign
 */
void moveFwd() {
  goSign();
  digitalWrite(leftFwdPin, HIGH);
  digitalWrite(leftRevPin, LOW);
  digitalWrite(rightFwdPin, HIGH);
  digitalWrite(rightRevPin, LOW);
}

/**
 * Stop the robot and glow RED sign
 */
void makeStop() {
  stopSign();
  digitalWrite(leftFwdPin, LOW);
  digitalWrite(leftRevPin, LOW);
  digitalWrite(rightFwdPin, LOW);
  digitalWrite(rightRevPin, LOW);
}

/**
 * Set robot in backward motion and glow GO sign
 */
void moveBwrd() {
  goSign();
  digitalWrite(leftFwdPin, LOW);
  digitalWrite(leftRevPin, HIGH);
  digitalWrite(rightFwdPin, LOW);
  digitalWrite(rightRevPin, HIGH);  
}

/**
 * Turn Robot in left direction and glow YELLO Sign
 */
void turnLeft() {
  readyToGoSign();
  digitalWrite(leftFwdPin, LOW);
  digitalWrite(leftRevPin, HIGH);
  digitalWrite(rightFwdPin, HIGH);
  digitalWrite(rightRevPin, LOW);  
}

/**
 * Turn robot in right direction and glow YELLOW sign
 */
void turnRight() {
  readyToGoSign();
  digitalWrite(leftFwdPin, HIGH);
  digitalWrite(leftRevPin, LOW);
  digitalWrite(rightFwdPin, LOW);
  digitalWrite(rightRevPin, HIGH);  
}

/**
 * returns distance on left
 */
int checkLeftDistance() {
  servo.write(30);
  delay(100);
  int distance = getDistance();
  return distance;
}

/**
 * returns distance on right
 */
int checkRightDistance() {
  servo.write(150);
  delay(100);
  int distance = getDistance();
  return distance;
}

/**
 * returns distance in front
 */
int checkFwdDistance() {
  servo.write(90);
  delay(100);
  int distance = getDistance();
  return distance;
}

/**
 * sends ultra sonic waves to sense distance
 */
int getDistance() {
  int duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  return distance;
}

/**
 * Main program loop
 */
void loop() {
  int distance = checkFwdDistance();
  int lDistance;
  int rDistance;
  if(distance > 19) {
    moveFwd();
  } else {
    makeStop();
    delay(500);
    moveBwrd();
    delay(500);
    makeStop();
    delay(100);
    lDistance = checkLeftDistance();
    rDistance = checkRightDistance();
    if(rDistance < lDistance) {
      turnRight();
    } else {
      turnLeft();
    }
    delay(500);
  }
  
}
