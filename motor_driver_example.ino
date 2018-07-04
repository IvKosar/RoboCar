/* L9110 driver example.
 *  
 *  Driver A-1A → Arduino D10
 *  Driver A-1B → Arduino D12
 *  Driver B-1A → Arduino D11
 *  Driver B-1B → Arduino D13
 *  Driver VCC -> Arduino 5V
 *  Driver GND -> Arduino GND
*/

// Defining Arduino pins for driver control
#include <NewPing.h>

#define MAX_DISTANCE 200

const int right_A = 10; // driver pin A-1A
const int right_B = 12; // driver pin A-1B
const int left_A = 11; // driver pin B-1A
const int left_B = 13; // driver pin B-1B

//const float WHEEL_COEFFICIENT = 0.9;

// defines pins numbers for UHsensor
//struct UHsensor{
//  int trigPin;
//  int echoPin;
//};
//UHsensor sonicL;
//UHsensor sonicR;
int leftTrigPin = A3;
int leftEchoPin = A2;
int rightTrigPin = 9;
int rightEchoPin = 8;
int leftDistance, rightDistance;

// defines variables
void setup() 
{  
  // setting the motor pins as OUTPUT
  pinMode(left_A,OUTPUT);
  pinMode(left_B,OUTPUT);
  pinMode(right_A,OUTPUT);
  pinMode(right_B,OUTPUT);
 
  motors(0,0); // Stopping the motors
  delay(1000); // A little delay, so the robot will not start moving immediately.

  pinMode(leftTrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(leftEchoPin, INPUT); // Sets the echoPin as an Input
  pinMode(rightTrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(rightEchoPin, INPUT); // Sets the echoPin as an Input

  Serial.begin(9600);
}
void loop()
 {delay(1000);
  leftDistance = get_distance(leftTrigPin, leftEchoPin);
  // Prints the distance on the Serial Monitor
  Serial.print("Distance from left: ");
  delay(10);
  Serial.println(leftDistance);
  delay(100);
  rightDistance = get_distance(rightTrigPin, rightEchoPin);
  Serial.print("Distance from right: ");
  delay(10);
  Serial.println(rightDistance);
  delay(100);

  // Start moving
  motors(150,150); // Robot will move straight ahead slowly
  delay(5000); // Delay - robot will keep moving as told
  motors(0,0); // Stopping the motors
  delay(500); // A little delay, so the robot will not start moving immediately.
  motors(-150,-150); // Robot will go back
  delay(5000); // Delay - robot will keep moving as told
  motors(0,0);
  delay(500);
  
}
 
// This is the function will setting robots moving direction and speed. The first operand will set the moving speed and direction for the left motor.
// And the second for the right motor.
void motors(int left, int right)
 {
  right=right*1; //FIXING SYNCHRONOUS
  
  // left motor
  if(left > 0 && left <= 255)
  { // left motor straight ahead
    analogWrite(left_A,left);
    digitalWrite(left_B,LOW);
  }
  else if(left < 0 && left >= -255)
  { // left motor reverse
    analogWrite(left_A,255+left);
    digitalWrite(left_B,HIGH);
  }
  else
  { // left motor stop
    digitalWrite(left_A,LOW);
    digitalWrite(left_B,LOW);
  }
 
  // right motor
  if(right > 0 && right <= 255)
  { // right motor straight ahead
    analogWrite(right_A,right);
    digitalWrite(right_B,LOW);
  }
  else if(right < 0 && right >= -255)
  { // right motor reverse
    analogWrite(right_A,255+right);
    digitalWrite(right_B,HIGH);
  }
  else
  { // right motor stop
    digitalWrite(right_A,LOW);
    digitalWrite(right_B,LOW);
  }
}

int get_distance(int trigPin, int echoPin){
  NewPing sonar(trigPin, echoPin, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
  return sonar.ping_cm();
}

