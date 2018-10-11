#include <SoftwareSerial.h>

unsigned char rx_payload[36];
unsigned int CH0_THR ;  // Drone Throttle - Joystick left - Up/Down
unsigned int CH1_YAW ;  // Drone Yaw      - Joystick left - Left/Right
unsigned int CH2_FB ;  // Drone Direction FW/BW        - Joystick right - FW/BW
unsigned int CH3_LR ;  // Drone Direction Left/Right   - Joystick right - Left/Right  
unsigned char i = 0;
unsigned char rx_char;
SoftwareSerial mySerial(10, 11); // RX, TX

void setup()
{
 
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
}

void loop() // run over and over
{
  if (mySerial.available())
    { rx_char = mySerial.read();
      if(rx_char == 0xFF)
      { i = 0;}
      else
      {
        i++;
        rx_payload[i]= rx_char;
      }
      if(i>30)
      {  i= 0;
        //parser rx_payload 
        //Serial.write(rx_payload[1]);
        //Serial.write(rx_payload[2]);
        CH0_THR =  rx_payload[2]; CH0_THR=CH0_THR<<8;  CH0_THR = CH0_THR|rx_payload[1]; CH0_THR = CH0_THR & 0xFFF ;
        CH1_YAW =  rx_payload[4]; CH1_YAW=CH1_YAW<<8;  CH1_YAW = CH1_YAW|rx_payload[3]; CH1_YAW = CH1_YAW & 0xFFF ;
        CH2_FB =  rx_payload[6]; CH2_FB=CH2_FB<<8;  CH2_FB = CH2_FB|rx_payload[5]; CH2_FB = CH2_FB & 0xFFF ;
        CH3_LR =  rx_payload[8]; CH3_LR=CH3_LR<<8;  CH3_LR = CH3_LR|rx_payload[7]; CH3_LR = CH3_LR & 0xFFF ;
       //for(int j=1; j<=2; j++){Serial.write(rx_payload[j]);i= 0;}
        Serial.print("CH0_THR: ");Serial.println(CH0_THR);
        Serial.print("CH1_YAW: "); Serial.println(CH1_YAW);
        Serial.print("CH2_FB: "); Serial.println(CH2_FB);
        Serial.print("CH3_LR: "); Serial.println(CH3_LR);
      }
    }
    
    
    
}

