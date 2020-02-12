/*
  #############################################################
  #Firmware:           Servo Test Firmware                    #
  #Hardware:           Arduino Nano                           #
  #Eerste opzet:       05-02-2020                             #
  #Auteurs: E. Hammer      N.Benhaddou O. Cekem               #
  #Laatst gewijzigd:   12-02-2020                             #
  #Versie:             0.0.5                                  #
  #############################################################
*/

#include <Servo.h>
#include <Wire.h> //Include the Wire library
#include <MMA_7455.h> //Include the MMA_7455 library

//ARDUINO PINS
const int s0Pin = 9;
const int s1Pin = 10;
const int s2Pin = 11;

//SERVOS
Servo servo0;  // create servo object to control a servo
Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo

//SENSOREN
MMA_7455 accel = MMA_7455(i2c_protocol); // Make an instance of MMA_7455

//STRUCTS
struct setpoint_servowaarde {
  int s0Pos;    //Range: 65-165
  int s1Pos;    //Range: 65-165
  int s2Pos;    //Range: 65-165
};

//FUNCTION PROTOTYPS
void stuur_servo_aan (struct setpoint_servowaarde var);
void serialInput();
void demo(void);
void accSensor();

//VARIABLES
String incomingByte;        // for incoming serial data
const int servoMax = 165;   // Max. degrees before the deltarobot destroys it zelf
const int servoMin = 65;    // Min. degrees before the deltarobot destroys it zelf
int servoGuard;             //0=OK | 1=Wrong input (not in range)
float xg, yg, zg; // Variables for the values from the sensor

int setsensitivity = 8; // Sensitivity chosen: 8g

float lees_accel_uit(int as); // Prototype of the wanted function to read g values of the Accelerometer
float lees_accel_uit_raw(int as); // Prototype for reading the raw values of the Accelerometer

void setup() {
  Serial.begin(9600);
  servo0.attach(s0Pin);  // attaches servo0 on pin 9 to the servo object
  servo1.attach(s1Pin);  // attaches servo0 on pin 19 to the servo object
  servo2.attach(s2Pin);  // attaches servo0 on pin 11 to the servo object 
  accel.begin(); // Start accelerometer
  // Set the sensitivity you want to use
  // 2 = 2g, 4 = 4g, 8 = 8g
  accel.setSensitivity(setsensitivity); // Good for "Tilt" measurements
  
  accel.setMode(measure); // Set accelerometer mode
  accel.setAxisOffset(-6, 36, -22); // Defined thanks to the auto-calibration example
  Serial.println("START POSITIE");
  struct setpoint_servowaarde var; 
  var.s0Pos = 65;        //165-65 degrees as range
  var.s1Pos = 65;        //165-65 degrees as range
  var.s2Pos = 65;        //165-65 degrees as range
  stuur_servo_aan(var);  
  Serial.println("Voer servo posities in  of '2' voor demo. (Range 65d-165d): s0s1s2"); 
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    serialInput();    //Go to function to get input data     
  }
  accSensor();
}

void serialInput(){
  incomingByte = Serial.readString();                           // read the incoming byte
  String result;
  result = incomingByte;
  Serial.println("Input: ");                                      //DEBUG
  Serial.println(result);                                         //DEBUG
  if (result.toInt() == 2){
    Serial.println("Automatische demo wordt gestart");            
    demo();   //Start demo function
  }else{

    struct setpoint_servowaarde var;                              //Call struct
    if (result.substring(0,3).toInt() >= servoMin and result.substring(0,3).toInt() <= servoMax){
       var.s0Pos = result.substring(0,3).toInt();
        servoGuard = 0;
    }else{
        servoGuard = 1;
    }
    if (result.substring(3,6).toInt() >= servoMin and result.substring(3,6).toInt() <= servoMax){
       var.s1Pos = result.substring(3,6).toInt();
       servoGuard = 0;
    }else{
         servoGuard = 1;
    }
    if (result.substring(6,9).toInt() >= servoMin and result.substring(6,9).toInt() <= servoMax){
       var.s2Pos = result.substring(6,9).toInt(); 
       servoGuard = 0;
    }else{
         servoGuard = 1;
    }

    if(servoGuard == 1){
      Serial.println("Voer servo posities in  of '2' voor demo. (Range 65d-165d): s0s1s2");
    }else{
     stuur_servo_aan(var);                                         //Call function with struc variables
     Serial.println("Voer servo posities in  of '2' voor demo. (Range 65d-165d): s0s1s2");
    }
  }
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
  servo2.write(var.s2Pos);           //Servo2 aansturen
  accSensor();
  delay(1000);                       //DEBUG
}

void demo(void){
  struct setpoint_servowaarde var; 
  var.s0Pos = 170;                 //Servo0 position in degress | Max 180
  var.s1Pos = 170;                 //Servo1 position in degress | Max 180
  var.s2Pos = 170;                 //Servo2 position in degress | Max 180
  stuur_servo_aan(var);   
                                      
  var.s0Pos = 65;
  var.s1Pos = 65;
  var.s2Pos = 65;
  stuur_servo_aan(var);  
                                         
  var.s0Pos = 65;
  var.s1Pos = 165;
  var.s2Pos = 165;
  stuur_servo_aan(var);  
                                           
  var.s0Pos = 165;
  var.s1Pos = 65;
  var.s2Pos = 165;
  stuur_servo_aan(var);  
                                           
  var.s0Pos = 165;
  var.s1Pos = 165;
  var.s2Pos = 65;
  stuur_servo_aan(var); 
  Serial.println("Voer servo posities in  of '2' voor demo. (Range 65d-165d): s0s1s2"); 
}


void accSensor(){
   // the Axis variables make use of the function to receive their corresponding Axis values
  xg = lees_accel_uit(1);
  yg = lees_accel_uit(2);
  zg = lees_accel_uit(3);
    Serial.print ("X = ");
    Serial.print (xg, 6); // Print x with 6 decimals
    Serial.print ("\t");
    Serial.print ("Y = ");
    Serial.print (yg, 6); // Print y with 6 decimals
    Serial.print ("\t");
    Serial.print ("Z = ");
    Serial.println (zg, 6); // Print z with 6 decimals
    delay(500);
}

// Read accelerometer Axis g with this function.
// Parameters: X=1, Y=2, Z=3.
float lees_accel_uit(int as){
  float value = 0;
  // X = 1
  if (as == 1){
    value = accel.readAxis10g('x'); // Read out the 'x' Axis
  }
  // Y = 2
  else if (as == 2){
    value = accel.readAxis10g('y'); // Read out the 'y' Axis
  }
  // Z = 3
  else if (as == 3){
    value = accel.readAxis10g('z'); // Read out the 'z' Axis
  }
  else{}
  return value;
}

// Read accelerometer Axis raw value with this function
// Parameters: X=1, Y=2, Z=3
float lees_accel_uit_raw(int as){
  float value = 0;
  // X = 1
  if (as == 1){
    value = accel.readAxis10('x'); // Read out the 'x' Axis
  }
  // Y = 2
  else if (as == 2){
    value = accel.readAxis10('y'); // Read out the 'y' Axis
  }
  // Z = 3
  else if (as == 3){
    value = accel.readAxis10('z'); // Read out the 'z' Axis
  }
  else{}
  return value;
}

// int grange = sensitivity*2;
// LSB = grange / 256 counts ~~ 0,016 g/count
// 1g = 9,81 m/s^2 (gravity)
