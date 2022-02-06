#include <Ultrasonic.h>
const int trigger = 12;
const int echo = 13; 

Ultrasonic ultrasonic(trigger, echo);

void setup() {
  Serial.begin(9600); 
  pinMode(trigger, OUTPUT); 
  pinMode(echo, INPUT); 

}

void loop() { 
  int distance = ultrasonic.read();
  Serial.println(distance);
  if(distance < 50) {
    Serial.println("Pause");
  }
  delay(100);
}






