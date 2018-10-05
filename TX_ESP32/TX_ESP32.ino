
/*
 * ESP32
 * LC12S - 2.4GHZ Setting: NET ID->1234; NODE ID -> 0001; BAUDRATE->19200; Channel-> 100; PW 12dbm
 */
#include "SerialDebug.h"
#define DEBUG true
// define ADC channle for analog sticks 
const char CH0 = 4;  // Drone Throttle - Joystick left - Up/Down
const char CH1 = 15;  // Drone Yaw      - Joystick left - Left/Right
const char CH2 = 13;  // Drone Direction FW/BW        - Joystick right - FW/BW
const char CH3 = 12;  // Drone Direction Left/Right   - Joystick right - Left/Right  
const char CH4 = 2;  // Read Internal Battery

void setup(){
  if (DEBUG){
    //SerialDebugger.begin(2,9600); //can select uart
    SerialDebugger.begin(9600); //if this line is commented out, the binary sketch size will decrease by 332 bytes
  }
  SerialDebugger.enable(NOTIFICATION);
  Serial2.begin(9600);
  //SerialDebugger.enable(ERROR);//uncomment if you want to debug ERRORs
}

void loop(){
int VAL_CH0 = 4095-analogRead(CH0);
SerialDebugger.print("Throttle_CH0: ").println(VAL_CH0);

int VAL_CH1 = analogRead(CH1);
SerialDebugger.print("YAW_CH1: ").println(VAL_CH1);

int VAL_CH2 = 4095-analogRead(CH2);
SerialDebugger.print("DIR_FB_CH2: ").println(VAL_CH2);

int VAL_CH3 = 4095 - analogRead(CH3);
SerialDebugger.print("DIR_LR_CH3: ").println(VAL_CH3);
  
delay(1000);
}
