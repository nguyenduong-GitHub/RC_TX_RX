#include <SoftwareSerial.h>

unsigned int rx_payload[18]; 
unsigned char i = 0;
unsigned char rx_c;
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
    { rx_c = mySerial.read();
      if(rx_c == 0xFF)
      { i = 0;}
      else
      {
        i++;
        rx_payload[i]= rx_c;
        
      }
      if(rx_c == 0xEE)
      {
       for(int j=0; j<=10; j++){Serial.write(rx_payload[j]);Serial.write(rx_payload[j]>>8);}
      }
    }
    
    
    
}

