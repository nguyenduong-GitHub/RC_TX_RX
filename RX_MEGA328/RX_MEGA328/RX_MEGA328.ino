rd#include <SoftwareSerial.h>
#define  M_IN4 4
#define  M_IN3 5
#define  M_IN2 6
#define  M_IN1 9
#define  Front_LED 12
#define  PWM_BAT 6
#define  Vbat_Pin A0


unsigned char rx_payload[36];
int CH0_THR ;  // Drone Throttle - Joystick left - Up/Down
int CH1_YAW ;  // Drone Yaw      - Joystick left - Left/Right
int CH2_FB ;  // Drone Direction FW/BW        - Joystick right - FW/BW
int CH3_LR ;  // Drone Direction Left/Right   - Joystick right - Left/Right  
unsigned char i = 0;
char rx_char_new ;
char rx_char_old ;
String VAL_CH0 = "";
String VAL_CH2 = ""; 
String VAL_CH3 = ""; 
SoftwareSerial mySerial(10, 11); // RX, TX

void setup()
{
  pinMode(Front_LED, OUTPUT);
  digitalWrite(Front_LED, LOW);
  pinMode(PWM_BAT, OUTPUT);
  analogWrite(PWM_BAT, 255);


  pinMode(M_IN1, OUTPUT);
  pinMode(M_IN2, OUTPUT);
  pinMode(M_IN3, OUTPUT);
  pinMode(M_IN4, OUTPUT);
  digitalWrite(M_IN1, HIGH);
  digitalWrite(M_IN2, LOW);
  digitalWrite(M_IN3, LOW);
  digitalWrite(M_IN4, HIGH);
  delay(500);
  digitalWrite(M_IN1, LOW);
  digitalWrite(M_IN2, HIGH);
  digitalWrite(M_IN3, HIGH);
  digitalWrite(M_IN4, LOW);
  delay(500);
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
void wheel_left(char dir)
{
  if(dir == 'U')
  {
    digitalWrite(M_IN1, HIGH);
    digitalWrite(M_IN2, LOW);
  }
  if(dir == 'D')
  {
    digitalWrite(M_IN1, LOW);
    digitalWrite(M_IN2, HIGH);
  }
   if(dir == 'P')
  {
    digitalWrite(M_IN1, LOW);
    digitalWrite(M_IN2, LOW);
  }
}
void wheel_right(char dir)
{
  if(dir == 'U')
  {
    digitalWrite(M_IN3, LOW);
    digitalWrite(M_IN4, HIGH);
  }
  if(dir == 'D')
  {
    digitalWrite(M_IN3, HIGH);
    digitalWrite(M_IN4, LOW);
  }
   if(dir == 'P')
  {
    digitalWrite(M_IN3, LOW);
    digitalWrite(M_IN4, LOW);
  }
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
    { rx_char_new = mySerial.read();
      if(rx_char_new == 'A') 
         { 
           while(rx_char_new !=';')
           {
            if (mySerial.available())
              {
                rx_char_new = mySerial.read();
                if(rx_char_new != ';')
                {
                 VAL_CH0 = VAL_CH0 + rx_char_new;
                }
              }
           }
           Serial.println(VAL_CH0);
           CH0_THR = VAL_CH0.toInt();
           Serial.println(CH0_THR);
           VAL_CH0 = "";
          
         }
       if(rx_char_new == 'C') 
         { 
           while(rx_char_new !=';')
           {
            if (mySerial.available())
              {
                rx_char_new =  mySerial.read();
                if(rx_char_new != ';')
                  {
                  VAL_CH2 = VAL_CH2 + rx_char_new ;
                  }
                  //Serial.println(rx_char_new);
             
              }
           }
           Serial.println(VAL_CH2);
           CH2_FB = VAL_CH2.toInt();
           Serial.println(CH2_FB);
           VAL_CH2 = "";
           
         }
         if(rx_char_new == 'D') 
         { 
           while(rx_char_new !=';')
           {
            if (mySerial.available())
              {
                rx_char_new =  mySerial.read();
                if(rx_char_new != ';')
                  {
                  VAL_CH3 = VAL_CH3 + rx_char_new ;
                  }
                  //Serial.println(rx_char_new);
             
              }
           }
           Serial.println(VAL_CH3);
           CH3_LR = VAL_CH3.toInt();
           Serial.println(CH3_LR);
           VAL_CH3 = "";
           
         }
           //CH0_THR =  rx_payload[1]; CH0_THR=CH0_THR<<8;  CH0_THR = CH0_THR|rx_payload[0]; CH0_THR = CH0_THR & 0x1FFF ;
          // CH1_YAW =  rx_payload[3]; CH1_YAW=CH1_YAW<<8;  CH1_YAW = CH1_YAW|rx_payload[2]; CH1_YAW = CH1_YAW & 0xFFF ;
          // CH2_FB =  rx_payload[5]; CH2_FB=CH2_FB<<8;  CH2_FB = CH2_FB|rx_payload[4]; CH2_FB = CH2_FB & 0xFFF ;
           //CH3_LR =  rx_payload[7]; CH3_LR=CH3_LR<<8;  CH3_LR = CH3_LR|rx_payload[6]; CH3_LR = CH3_LR & 0xFFF ;
          //for(int j=1; j<=2; j++){Serial.write(rx_payload[j]);i= 0;}
          //Serial.print("CH0_THR: ");  Serial.println(CH0_THR); // Center = 2288; Up = 4623, down = 0
         // Serial.print("CH1_YAW: ");  Serial.println(CH1_YAW); //center = 1915, Left = 0, Right = 3848
         // Serial.print("CH2_FB: ");   Serial.println(CH2_FB);   //center = 2204 
         // Serial.print("CH3_LR: ");   Serial.println(CH3_LR);   //center =2222
         // if(CH0_THR >3000){wheel_left('U'); }
         //  if(CH0_THR <500) {wheel_left('D'); }
         // if(CH2_FB >3000) {wheel_right('U');}
         // if(CH2_FB <500)  {wheel_right('D');}
            if(CH2_FB <500){car_move_down();}
            if(CH2_FB >3700){car_move_up();  digitalWrite(Front_LED, HIGH);}
            if(CH3_LR <500){car_turn_left();}
            if(CH3_LR >3700){car_turn_right();}
          //if((CH0_THR >500)&&(CH0_THR <3000)){wheel_left('P');}  
          if((CH2_FB >500)&&(CH2_FB <3000) && (CH3_LR >500)&&(CH3_LR <3700)){car_stop();  digitalWrite(Front_LED, LOW);}
          
             
     
     
     
    
    }  
    
}


