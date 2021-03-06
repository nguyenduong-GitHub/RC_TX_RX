
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
String new_payload = "";
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
unsigned int VAL_CH0 = 4095-analogRead(CH0); 
if (VAL_CH0>4000){VAL_CH0 = 4000;}
//Serial.print("Throttle_CH0: "); Serial.print(VAL_CH0);

unsigned int VAL_CH1 = analogRead(CH1);

unsigned int VAL_CH2 = 4095-analogRead(CH2);
if (VAL_CH2>4000){VAL_CH2 = 4000;}
unsigned int VAL_CH3 = 4095 - analogRead(CH3);

new_payload = 'A' + String(VAL_CH0, DEC)+ ';' + 'B' +String(VAL_CH1, DEC) + ';' + 'C' +String(VAL_CH2, DEC) + ';' + 'D' +String(VAL_CH3, DEC) + ';'; 
Serial.println(new_payload);
Serial2.println(new_payload);

//for(int i=0; i<=18; i++){Serial2.write(payload[i]);Serial2.write(payload[i]>>8);} // Send payload to uart
//for(int i=0; i<=18; i++){Serial.write(payload[i]);Serial.write(payload[i]>>8);}
delay(100);
}
