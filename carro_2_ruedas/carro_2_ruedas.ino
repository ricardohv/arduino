/*
  Author: Ricardo Herrera (ricardo.herreravargas@ucr.ac.cr)
  This is Open Sourece Code, released under the terms of the "MIT License"
  Copyright Universidad de Costa Rica 2017
*/

//https://arduino.stackexchange.com/questions/33137/how-to-fix-compilation-error-for-tone-using-same-timer-as-other-function

#include <IRremote.h>
#include <TonePlayer.h>

#define trig_pin              4
#define echo_pin              7
#define ir_pin                8
#define piezo_pin             9
#define board_led            13
#define left_speed_pin        5
#define right_speed_pin       6
#define left_direction_pin   10
#define right_direction_pin  11
#define MOTOR_LEFT           "L"
#define MOTOR_RIGHT          "R"
#define MOTOR_DIRECTION_FORWARD  1
#define MOTOR_DIRECTION_BACKWARDS 0

#define ARRIBA1 0x5656481C
#define ARRIBA2 0xE5545229
#define ABAJO1 0xCD2F8CC0
#define ABAJO2 0x5C2D96CD
#define IZQ1 0xDF96D4
#define IZQ2 0x8FDDA0E1
#define DER1 0xF813E99E
#define DER2 0xAB5DF0F7
#define PLAY1 0x5F565CB8
#define PLAY2 0xEE5466C5
#define MENU1 0xFC3A874
#define MENU2 0x9EC1B281

IRrecv irrecv(ir_pin);
decode_results results;
TonePlayer tone1 (TCCR1A, TCCR1B, OCR1AH, OCR1AL, TCNT1H, TCNT1L);  // pin D9 (Uno), D11 (Mega)
long duration;
int distance;

void setup() {
  pinMode(trig_pin, OUTPUT); // Sets the trig_pin as an Output
  pinMode(echo_pin, INPUT); // Sets the echo_pin as an Input
  pinMode(piezo_pin, OUTPUT);
  pinMode(board_led, OUTPUT);
  pinMode(left_speed_pin, OUTPUT);
  pinMode(right_speed_pin, OUTPUT);
  pinMode(left_direction_pin, OUTPUT);
  pinMode(right_direction_pin, OUTPUT);
  irrecv.enableIRIn(); // enable input from IR receiver
  Serial.begin(9600);
}

void loop() {

// Clears the trig_pin
digitalWrite(trig_pin, LOW);
delayMicroseconds(2);
// Sets the trig_pin on HIGH state for 10 micro seconds
digitalWrite(trig_pin, HIGH);
delayMicroseconds(10);
digitalWrite(trig_pin, LOW);
// Reads the echo_pin, returns the sound wave travel time in microseconds
duration = pulseIn(echo_pin, HIGH);
// Calculating the distance
distance= duration*0.034/2;

      if (distance <= 20) {
          stopMotors();
          tone1.tone (880);
          delay (200);
          tone1.noTone ();
          delay (200);
          tone1.tone (880);
          delay (200);
          tone1.noTone ();
          delay(1000);
          rotateRight();
          delay(950);
          stopMotors();
          tone1.tone (880);
          delay (200);
          tone1.noTone ();
      }


    if (irrecv.decode( & results)) {

      if (results.value == ARRIBA1 || results.value == ARRIBA2) {
        Serial.println("+");
        moveForward();
      }

      if (results.value == ABAJO1 || results.value == ABAJO2) {
        Serial.println("-");
        moveBackwards();
      }

      if (results.value == IZQ1 || results.value == IZQ2) {
        Serial.println("<<");
        rotateLeft();
      }

      if (results.value == DER1 || results.value == DER2) {
        Serial.println(">>");
        rotateRight();
      }

      if (results.value == PLAY1 || results.value == PLAY2) {
        Serial.println(">||");
        stopMotors();
      }

      if (results.value == MENU1 || results.value == MENU2) {
        Serial.println("MENU");
        doBlink(2,100);
      }
      irrecv.resume();
    } 

/*  
  moveForward();
  doBlink(4,500);
  stopMotors();
  doBlink(3, 50);
  moveBackwards();
  doBlink(2,100);
  rotateLeft();
  doBlink(2, 250);
  
  moveForward();
  doBlink(4,500);
  stopMotors();
  doBlink(3, 50);
  moveBackwards();
  doBlink(2,100);
  rotateRight();
  doBlink(2, 250);
  */
}

/* 
 * motor: "L" for left and "R" for Right
 * direction: 1 for Forward, 0 for Backwards
 * speed: percentage 0-100 for speed of the motor
 */

void setMotor(String motor, int motorDirection, int motorSpeed){
  if(motor==MOTOR_RIGHT){
    digitalWrite(right_direction_pin, motorDirection);
    analogWrite(right_speed_pin, motorSpeed);
  }

  if(motor==MOTOR_LEFT){
    digitalWrite(left_direction_pin, motorDirection);
    analogWrite(left_speed_pin, motorSpeed);
  }
}

void moveForward(){
  setMotor(MOTOR_LEFT, MOTOR_DIRECTION_FORWARD, 80);
  setMotor(MOTOR_RIGHT, MOTOR_DIRECTION_FORWARD, 70);  
}

void moveBackwards(){
  setMotor(MOTOR_LEFT, MOTOR_DIRECTION_BACKWARDS, 80);
  setMotor(MOTOR_RIGHT, MOTOR_DIRECTION_BACKWARDS, 70);  
}

void rotateRight(){
  setMotor(MOTOR_LEFT,  MOTOR_DIRECTION_FORWARD, 50);
  setMotor(MOTOR_RIGHT, MOTOR_DIRECTION_BACKWARDS, 60);  
}
void rotateLeft(){
  setMotor(MOTOR_LEFT,  MOTOR_DIRECTION_BACKWARDS, 50);
  setMotor(MOTOR_RIGHT, MOTOR_DIRECTION_FORWARD, 60);  
}

void stopMotors(){
  setMotor(MOTOR_LEFT, MOTOR_DIRECTION_FORWARD, 0);
  setMotor(MOTOR_RIGHT, MOTOR_DIRECTION_FORWARD, 0);  
}

//USE THIS AS HUMANCOMMUNICATION MECHANISM 
void doBlink(int times, int delayTime){
  for(int i=0; i<times; i++){
    digitalWrite(board_led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(delayTime);              // wait for a second
    digitalWrite(board_led, LOW);    // turn the LED off by making the voltage LOW
    delay(delayTime);              // wait for a second    
  }
}
