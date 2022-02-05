#include <Ultrasonic.h>
const int trigger = 1;
const int echo = 2; 

Ultrasonic ultrasonic_left(left_trigger, left_echo);

void setup() {
  Serial.begin(9600); 
    
  pinMode(trigger, OUTPUT); 
  pinMode(echo, INPUT); 

}

void loop() { 
  Serial.print("Sensor: ");
  Serial.print(ultrasonic_left.read());
  Serial.println("cm");
  delay(1000);
}






