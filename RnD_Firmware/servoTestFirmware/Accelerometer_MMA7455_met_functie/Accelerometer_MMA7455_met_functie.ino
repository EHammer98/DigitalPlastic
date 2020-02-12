#include <Wire.h> //Include the Wire library
#include <MMA_7455.h> //Include the MMA_7455 library

MMA_7455 accel = MMA_7455(i2c_protocol); // Make an instance of MMA_7455
float xg, yg, zg; // Variables for the values from the sensor
int setsensitivity = 8; // Sensitivity chosen: 8g

float lees_accel_uit(int as); // Prototype of the wanted function to read g values of the Accelerometer
float lees_accel_uit_raw(int as); // Prototype for reading the raw values of the Accelerometer

void setup() {
  Serial.begin(9600); // Ability to write to serial monitor
  accel.begin(); // Start accelerometer
  
  // Set the sensitivity you want to use
  // 2 = 2g, 4 = 4g, 8 = 8g
  accel.setSensitivity(setsensitivity); // Good for "Tilt" measurements
  
  accel.setMode(measure); // Set accelerometer mode
  accel.setAxisOffset(-6, 36, -22); // Defined thanks to the auto-calibration example
}

void loop() {
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
    
//    if (xVal < -50) Serial.println("Tilted FAR LEFT");
//    else if (xVal < -20) Serial.println("Tilted LEFT");
//    else if (xVal > 50) Serial.println("Tilted FAR RIGHT");
//    else if (xVal >  20) Serial.println("Tilted RIGHT");
//    if (yVal < -50) Serial.println("Tilted FAR TOWARDS");
//    else if (yVal < -20) Serial.println("Tilted TOWARDS");
//    else if (yVal > 50) Serial.println("Tilted FAR AWAY");
//    else if (yVal >  20) Serial.println("Tilted AWAY"); 
//    if (zVal < -100 ) Serial.println("UPSIDE DOWN!"); 
   
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


