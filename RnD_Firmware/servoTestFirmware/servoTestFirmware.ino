/*
  #############################################################
  #Firmware:           Servo Test Firmware                    #
  #Hardware:           Arduino Mega 2560?                     #
  #Eerste opzet:       05-02-2020                             #
  #Auteurs: E. Hammer                                         #
  #Laatst gewijzigd:   06-02-2020                             #
  #Versie:             0.0.1                                  #
  #############################################################
*/

#include <Servo.h>

//ARDUINO PINS
const int s0Pin = 9;
const int s1Pin = 10;
const int s2Pin = 11;

//SERVOS
Servo servo0;  // create servo object to control a servo
Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo

//STRUCTS
struct setpoint_servowaarde {
  int s0Pos;    //Max 180
  int s1Pos;    //Max 180
  int s2Pos;    //Max 180
};

//FUNCTION PROTOTYPS
void stuur_servo_aan (struct setpoint_servowaarde var);
String serialInput();
//VARIABLES
String incomingByte; // for incoming serial data

void setup() {
  Serial.begin(9600);
  servo0.attach(s0Pin);  // attaches servo0 on pin 9 to the servo object
  servo1.attach(s1Pin);  // attaches servo0 on pin 19 to the servo object
  servo2.attach(s2Pin);  // attaches servo0 on pin 11 to the servo object
  Serial.println("Voer servo posities in (max 180d!): s0s1s2");
}

void loop() {
       String serialInputReturn;
  // send data only when you receive data:
  if (Serial.available() > 0) {


  serialInputReturn = serialInput(); // k now contains 6

   
  }
  
struct setpoint_servowaarde var;                                         //Call struct
var.s0Pos = serialInputReturn.substring(0,3).toInt();                    //Servo0 position in degress | Max 180
var.s1Pos = serialInputReturn.substring(3,6).toInt();                    //Servo1 position in degress | Max 180
var.s2Pos = serialInputReturn.substring(6,9).toInt();                    //Servo2 position in degress | Max 180
stuur_servo_aan(var);                                                    //Call function with struc variables

}

String serialInput(){
  // read the incoming byte:
    incomingByte = Serial.readString();
  String result;
  result = incomingByte;
  return result;
}

void stuur_servo_aan (struct setpoint_servowaarde var){
  Serial.println("Server0 pos:");    //DEBUG
  Serial.println(var.s0Pos);         //DEBUG
  servo0.write(var.s0Pos);           //Servo0 aansturen
  Serial.println("Server1 pos:");    //DEBUG
  Serial.println(var.s1Pos);         //DEBUG
  servo1.write(var.s1Pos);           //Servo1 aansturen
  Serial.println("Server2 pos:");    //DEBUG
  Serial.println(var.s2Pos);         //DEBUG
  servo1.write(var.s2Pos);           //Servo2 aansturen
  delay(1500);                       //DEBUG

}