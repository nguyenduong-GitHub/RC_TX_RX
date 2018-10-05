
/*
 * ESP32
 */
#include "SerialDebug.h"
#define DEBUG true
// define ADC channle for analog sticks 
const char CH0 = 2;  // Drone Throttle - Joystick left - Up/Down
const char CH1 = 2;  // Drone Yaw      - Joystick left - Left/Right
const char CH2 = 2;  // Drone Direction FW/BW        - Joystick right - FW/BW
const char CH3 = 2;  // Drone Direction Left/Right   - Joystick right - Left/Right  
const char CH4 = 2;  // Read Internal Battery

void setup(){
  if (DEBUG){
    //SerialDebugger.begin(2,9600); //can select uart
    SerialDebugger.begin(9600); //if this line is commented out, the binary sketch size will decrease by 332 bytes
  }
  SerialDebugger.enable(NOTIFICATION);
  //SerialDebugger.enable(ERROR);//uncomment if you want to debug ERRORs
}

void loop(){
int sensorValue = analogRead(CH0);
SerialDebugger.print("ADC: ").println(sensorValue);
  
delay(1000);
}
