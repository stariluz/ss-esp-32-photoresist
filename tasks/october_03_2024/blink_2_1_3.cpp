#include <Arduino.h>

const int Led = 15; 
const int TIME = 1000; 
 
void setup(void) { 
  pinMode(Led, OUTPUT); 
  digitalWrite(Led, HIGH); 
 //  Serial.begin(115200); 
} 
void loop(void) { 
  digitalWrite(Led, LOW); 
  delay(TIME); 
  digitalWrite(Led, HIGH); 
  delay(TIME); 
}
