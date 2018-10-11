
/*
 * ESP32
 * LC12S - 2.4GHZ Setting: NET ID->1234; NODE ID -> 0001; BAUDRATE->9600; Channel-> 100; PW 12dbm
 */
#include "SerialDebug.h"
#define DEBUG true
// define ADC channle for analog sticks 
const char CH0 = 4;  // Drone Throttle - Joystick left - Up/Down
const char CH1 = 15;  // Drone Yaw      - Joystick left - Left/Right
const char CH2 = 13;  // Drone Direction FW/BW        - Joystick right - FW/BW
const char CH3 = 12;  // Drone Direction Left/Right   - Joystick right - Left/Right  
const char CH4 = 2;  // Read Internal Battery

unsigned int payload[18]; // 1 byte start, 8 bytes of Channles, 8 bytes of functions, 1 byte stop
unsigned char payload_leng;
void setup(){
 /*if (DEBUG){
    //SerialDebugger.begin(2,9600); //can select uart
    SerialDebugger.begin(9600); //if this line is commented out, the binary sketch size will decrease by 332 bytes
  }
  SerialDebugger.enable(NOTIFICATION);*/
  Serial.begin(9600);
  Serial2.begin(9600);
  //SerialDebugger.enable(ERROR);//uncomment if you want to debug ERRORs
}

void loop(){
 // Serial2.write('a');
unsigned int VAL_CH0 = 4095-analogRead(CH0); payload[1] = VAL_CH0;

//SerialDebugger.print("Throttle_CH0: ").println(VAL_CH0);

unsigned int VAL_CH1 = analogRead(CH1);payload[2] = VAL_CH1;
//SerialDebugger.print("YAW_CH1: ").println(VAL_CH1);

unsigned int VAL_CH2 = 4095-analogRead(CH2);payload[3] = VAL_CH2;
//SerialDebugger.print("DIR_FB_CH2: ").println(VAL_CH2);

unsigned int VAL_CH3 = 4095 - analogRead(CH3);payload[4] = VAL_CH3;
//SerialDebugger.print("DIR_LR_CH3: ").println(VAL_CH3);

payload[0]= 0xFFFF;
payload[18]= 0xEEEE;;

for(int i=0; i<=18; i++){Serial2.write(payload[i]);Serial2.write(payload[i]>>8);} // Send payload to uart
for(int i=0; i<=18; i++){Serial.write(payload[i]);Serial.write(payload[i]>>8);}
delay(1000);
}
