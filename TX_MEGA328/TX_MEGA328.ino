
/*
 * ESP32
 * LC12S - 2.4GHZ Setting: NET ID->1234; NODE ID -> 0001; BAUDRATE->9600; Channel-> 100; PW 12dbm
 */
#include "PS2X_lib.h"
#include <SoftwareSerial.h>
#define DEBUG true
// for PS2 Gamepad
PS2X ps2x;
int error = 0; 
byte type = 0;
byte vibrate = 0;
// define ADC channle for analog sticks 
const char CH0 = 4;  // Drone Throttle - Joystick left - Up/Down
const char CH1 = 15;  // Drone Yaw      - Joystick left - Left/Right
const char CH2 = 13;  // Drone Direction FW/BW        - Joystick right - FW/BW
const char CH3 = 12;  // Drone Direction Left/Right   - Joystick right - Left/Right  
const char CH4 = 2;  // Read Internal Battery
String new_payload = "";
SoftwareSerial mySerial(3, 2); // RX, TX

unsigned int VAL_CH2  = 2000;
unsigned int VAL_CH3  = 2000;
unsigned int VAL_CH0  = 2000;
unsigned int VAL_CH1  = 2000;

void setup(){
 /*if (DEBUG){
    //SerialDebugger.begin(2,9600); //can select uart
    SerialDebugger.begin(9600); //if this line is commented out, the binary sketch size will decrease by 332 bytes
  }
  SerialDebugger.enable(NOTIFICATION);*/
  Serial.begin(9600);
  mySerial.begin(9600);

  setup_ps2_gamepad();
  //SerialDebugger.enable(ERROR);//uncomment if you want to debug ERRORs
}

void loop(){
VAL_CH2  = 2000;
VAL_CH3  = 2000;
VAL_CH0  = 128; // speed 0-> 255;
VAL_CH1  = 2000;
ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
if(ps2x.Button(PSB_PAD_UP)) 
  {         //will be TRUE as long as button is pressed
   VAL_CH2 = 4000;
  //Serial.print("Up held this hard: "); Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC); 
  }
if(ps2x.Button(PSB_PAD_RIGHT))
  {
   VAL_CH3 = 4000;
   //Serial.print("Right held this hard: "); Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
   }
if(ps2x.Button(PSB_PAD_LEFT))
  {
    VAL_CH3 = 0;
   //Serial.print("LEFT held this hard: "); Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC); 
  }
if(ps2x.Button(PSB_PAD_DOWN))
  {
   VAL_CH2 = 0;
   //Serial.print("DOWN held this hard: "); Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC); 
  }
 update_speed();
  
new_payload = 'A' + String(VAL_CH0, DEC)+ ';' + 'B' +String(VAL_CH1, DEC) + ';' + 'C' +String(VAL_CH2, DEC) + ';' + 'D' +String(VAL_CH3, DEC) + ';'; 
Serial.println(new_payload);
mySerial.print(new_payload);


//for(int i=0; i<=18; i++){Serial2.write(payload[i]);Serial2.write(payload[i]>>8);} // Send payload to uart
//for(int i=0; i<=18; i++){Serial.write(payload[i]);Serial.write(payload[i]>>8);}
delay(100);

//test_ps2_game_pad();
}

void setup_ps2_gamepad(){

 //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
  
 error = ps2x.config_gamepad(13,11,10,12, true, true);   //setup pins and settnings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error 
 if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
   Serial.println("holding L1 or R1 will print out the analog stick values.");
   Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   //Serial.print(ps2x.Analog(1), HEX);
   
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
       break;
     }
  
}

void test_ps2_game_pad(){
   /* You must Read Gamepad to get new values
   Read GamePad and set vibration values
   ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
   if you don't enable the rumble, use ps2x.read_gamepad(); with no values
   
   you should call this at least once a second
   */
   
   
   
 if(error == 1) //skip loop if no controller found
  return; 
  
 if(type == 2){ //Guitar Hero Controller
   
   ps2x.read_gamepad();          //read controller 
   
   if(ps2x.ButtonPressed(GREEN_FRET))
     Serial.println("Green Fret Pressed");
   if(ps2x.ButtonPressed(RED_FRET))
     Serial.println("Red Fret Pressed");
   if(ps2x.ButtonPressed(YELLOW_FRET))
     Serial.println("Yellow Fret Pressed");
   if(ps2x.ButtonPressed(BLUE_FRET))
     Serial.println("Blue Fret Pressed");
   if(ps2x.ButtonPressed(ORANGE_FRET))
     Serial.println("Orange Fret Pressed");
     

    if(ps2x.ButtonPressed(STAR_POWER))
     Serial.println("Star Power Command");
    
    if(ps2x.Button(UP_STRUM))          //will be TRUE as long as button is pressed
     Serial.println("Up Strum");
    if(ps2x.Button(DOWN_STRUM))
     Serial.println("DOWN Strum");
  
 
    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
         Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
         Serial.println("Select is being held");

    
    if(ps2x.Button(ORANGE_FRET)) // print stick value IF TRUE
    {
        Serial.print("Wammy Bar Position:");
        Serial.println(ps2x.Analog(WHAMMY_BAR), DEC); 
    } 
 }

 else { //DualShock Controller
  
    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
    
    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
         Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
         Serial.println("Select is being held");
         
         
     if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
       Serial.print("Up held this hard: ");
       Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
      }
      if(ps2x.Button(PSB_PAD_RIGHT)){
       Serial.print("Right held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
      }
      if(ps2x.Button(PSB_PAD_LEFT)){
       Serial.print("LEFT held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
      }
      if(ps2x.Button(PSB_PAD_DOWN)){
       Serial.print("DOWN held this hard: ");
     Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
      }   
  
    
      vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on 
                                              //how hard you press the blue (X) button    
    
    if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
    {
     
       
         
        if(ps2x.Button(PSB_L3))
         Serial.println("L3 pressed");
        if(ps2x.Button(PSB_R3))
         Serial.println("R3 pressed");
        if(ps2x.Button(PSB_L2))
         Serial.println("L2 pressed");
        if(ps2x.Button(PSB_R2))
         Serial.println("R2 pressed");
        if(ps2x.Button(PSB_GREEN))
         Serial.println("Triangle pressed");
         
    }   
         
    
    if(ps2x.ButtonPressed(PSB_RED))             //will be TRUE if button was JUST pressed
         Serial.println("Circle just pressed");
         
    if(ps2x.ButtonReleased(PSB_PINK))             //will be TRUE if button was JUST released
         Serial.println("Square just released");     
    
    if(ps2x.NewButtonState(PSB_BLUE))            //will be TRUE if button was JUST pressed OR released
         Serial.println("X just changed");    
    
    
    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
    {
        Serial.print("Stick Values:");
        Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_LX), DEC); 
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_RY), DEC); 
        Serial.print(",");
        Serial.println(ps2x.Analog(PSS_RX), DEC); 
    } 
    
    
 }
 
 
 delay(50);
     
}
void update_speed()
{
    if(ps2x.ButtonPressed(PSB_RED)){ VAL_CH0++; if(VAL_CH0 >= 254){VAL_CH0 = 254;} }  // Circle button ++
    if(ps2x.ButtonReleased(PSB_PINK)){VAL_CH0--; if(VAL_CH0 <=1){VAL_CH0 = 1;}}  // Square button--          
   
}

