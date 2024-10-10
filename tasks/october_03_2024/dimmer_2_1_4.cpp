#include <esp32-hal-gpio.h> 
 
const int ledChannel = 0; 
const int ledPin = 15; 
const int frequency = 5000; 
const int resolution = 8; 
 
void setup() { 
  ledcSetup(ledChannel, frequency, resolution); 
  ledcAttachPin(ledPin, ledChannel); 
} 
 
void loop() { 
  // Incrementar el ciclo de trabajo gradualmente para aumentar la intensidad del LED 
  for (int dutyCycle = 0; dutyCycle <= 30; dutyCycle++) { 
    ledcWrite(ledChannel, dutyCycle); 
    delay(50); 
  } 
 
  // Disminuir el ciclo de trabajo gradualmente para reducir la intensidad del LED 
  for (int dutyCycle = 30; dutyCycle >= 0; dutyCycle--) { 
    ledcWrite(ledChannel, dutyCycle); 
    delay(50); 
  } 
} 