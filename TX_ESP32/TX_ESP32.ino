
// define ADC channle for analog sticks 
const char CH1 = 2;  // Drone Throttle - Joystick left - Up/Down
const char CH1 = 2;  // Drone Yaw      - Joystick left - Left/Right
const char CH1 = 2;  // Drone Direction FW/BW        - Joystick right - FW/BW
const char CH1 = 2;  // Drone Direction Left/Right   - Joystick right - Left/Right  
const char CH1 = 2;  // Read Internal Battery

void setup() {
  Serial.begin(9600);
}
void loop() {
int sensorValue = analogRead(analogInPin);
  Serial.println(sensorValue);
  delay(200);
}
