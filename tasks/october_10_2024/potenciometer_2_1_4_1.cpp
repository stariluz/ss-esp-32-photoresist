#include <Arduino.h>
#include <esp32-hal-gpio.h>

const int sensorPin = GPIO_NUM_15;
const int ledPin = GPIO_NUM_2;
const int ledChannel = 0;
const int frequency = 5000;
const int resolution = 8;

void setup()
{
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);

  ledcSetup(ledChannel, frequency, resolution);
  ledcAttachPin(ledPin, ledChannel);
}

void loop()
{

  // Leer el valor del sensor en GPIO15 (ADC2_3)
  int sensorValue = analogRead(sensorPin);

  // Calcular el voltaje
  float voltage = (sensorValue / 4095.0) * 3.3; 

  Serial.print(sensorValue);
  Serial.print(", ");
  Serial.println(voltage, 2);

  // Establecer el ciclo de trabajo según el valor leído por el adc
  float dutyCycle = sensorValue / 160;
  ledcWrite(ledChannel, dutyCycle);
}