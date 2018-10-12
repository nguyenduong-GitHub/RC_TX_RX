#include <SoftwareSerial.h>
#define  M_IN4 3
#define  M_IN3 5
#define  M_IN2 6
#define  M_IN1 9


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
  pinMode(M_IN1, OUTPUT);
  pinMode(M_IN2, OUTPUT);
  pinMode(M_IN3, OUTPUT);
  pinMode(M_IN4, OUTPUT);
  digitalWrite(M_IN1, HIGH);
  digitalWrite(M_IN2, LOW);
  digitalWrite(M_IN3, LOW);
  digitalWrite(M_IN4, HIGH);
  delay(1000);
  digitalWrite(M_IN1, LOW);
  digitalWrite(M_IN2, HIGH);
  digitalWrite(M_IN3, HIGH);
  digitalWrite(M_IN4, LOW);
  delay(1000);
  digitalWrite(M_IN1, LOW);
  digitalWrite(M_IN2, LOW);
  digitalWrite(M_IN3, LOW);
  digitalWrite(M_IN4, LOW);
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
}
void car_motor_intial()
{
  pinMode(M_IN1, OUTPUT);
  pinMode(M_IN2, OUTPUT);
  pinMode(M_IN3, OUTPUT);
  pinMode(M_IN4, OUTPUT);
  digitalWrite(M_IN1, LOW);
  digitalWrite(M_IN2, LOW);
  digitalWrite(M_IN3, LOW);
  digitalWrite(M_IN4, LOW);
}
void car_move_up()
{
  digitalWrite(M_IN1, HIGH);
  digitalWrite(M_IN2, LOW);
  digitalWrite(M_IN3, LOW);
  digitalWrite(M_IN4, HIGH);
}
void car_move_down()
{
  digitalWrite(M_IN1, LOW);
  digitalWrite(M_IN2, HIGH);
  digitalWrite(M_IN3, HIGH);
  digitalWrite(M_IN4, LOW);
}
void car_turn_left()
{
  digitalWrite(M_IN1, HIGH);
  digitalWrite(M_IN2, LOW);
  digitalWrite(M_IN3, HIGH);
  digitalWrite(M_IN4, LOW);
}
void car_turn_right()
{
  digitalWrite(M_IN1, LOW);
  digitalWrite(M_IN2, HIGH);
  digitalWrite(M_IN3, LOW);
  digitalWrite(M_IN4, HIGH);
}
void car_stop()
{
  digitalWrite(M_IN1, LOW);
  digitalWrite(M_IN2, LOW);
  digitalWrite(M_IN3, LOW);
  digitalWrite(M_IN4, LOW);
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
        CH0_THR =  rx_payload[2]; CH0_THR=CH0_THR<<8;  CH0_THR = CH0_THR|rx_payload[1]; CH0_THR = CH0_THR & 0x1FFF ;
        CH1_YAW =  rx_payload[4]; CH1_YAW=CH1_YAW<<8;  CH1_YAW = CH1_YAW|rx_payload[3]; CH1_YAW = CH1_YAW & 0xFFF ;
        CH2_FB =  rx_payload[6]; CH2_FB=CH2_FB<<8;  CH2_FB = CH2_FB|rx_payload[5]; CH2_FB = CH2_FB & 0xFFF ;
        CH3_LR =  rx_payload[8]; CH3_LR=CH3_LR<<8;  CH3_LR = CH3_LR|rx_payload[7]; CH3_LR = CH3_LR & 0xFFF ;
       //for(int j=1; j<=2; j++){Serial.write(rx_payload[j]);i= 0;}
        Serial.print("CH0_THR: ");Serial.println(CH0_THR); // Center = 2288; Up = 4623, down = 0
        Serial.print("CH1_YAW: "); Serial.println(CH1_YAW); //center = 1915, Left = 0, Right = 3848
        Serial.print("CH2_FB: "); Serial.println(CH2_FB);   //center = 2204 
        Serial.print("CH3_LR: "); Serial.println(CH3_LR);   //center =2222
        if(CH0_THR >3000){car_move_up();}
        if(CH0_THR <500){car_move_down();}
        if(CH1_YAW <500){car_turn_left();}
        if(CH1_YAW >3700){car_turn_right();}
        if((CH0_THR >500)&&(CH0_THR <3000)&&(CH1_YAW >500)&&(CH1_YAW<3700)){car_stop();}
      
    }
    
    }  
    
}

