
const int analogInPin = 2;  // Analog input pin that the potentiometer is attached to
void setup() {
  Serial.begin(9600);
}
void loop() {
int sensorValue = analogRead(analogInPin);
  Serial.println(sensorValue);
  delay(200);
}
