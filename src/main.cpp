#include <Arduino.h>
#include <TimeLib.h> // Para manejar el tiempo
#include <Wire.h>

// Pines y valores
const int sensorPin = GPIO_NUM_15; // Pin GPIO15 donde conectas la fotoresistencia
const float resistance = 10000;    // Resistencia fija en ohmios

int dataIndex = 0; // Cambiado de "index" a "dataIndex" para evitar conflictos

void setup()
{
  Serial.begin(9600);
  delay(2000);
  setTime(0, 0, 0, 1, 1, 2024);
  pinMode(sensorPin, INPUT);
}

void loop()
{
  // Obtener la hora actual
  time_t current = now();

  // Leer el valor del sensor en GPIO15 (ADC2_3)
  int sensorValue = analogRead(sensorPin);

  Serial.print(numberOfMinutes(current));
  Serial.print(",");
  Serial.println(sensorValue);

  // Esperar un minuto antes de la siguiente medición
  delay(60000);
}
