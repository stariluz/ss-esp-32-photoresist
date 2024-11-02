#include <Arduino.h>
#include <esp32-hal-gpio.h>

#define MIN_DUTY_CYCLE 25
#define MAX_DUTY_CYCLE 200

const int ledChannel = 0;
const int transistorPin = GPIO_NUM_13;
const int frequency = 5000;
const int resolution = 8;
volatile int dutyCycle = MIN_DUTY_CYCLE;

void (*updateSpeed)();
void increaseSpeed();
void decreaseSpeed();

void setup()
{
  Serial.begin(9600); 
  ledcSetup(ledChannel, frequency, resolution);
  ledcAttachPin(transistorPin, ledChannel);
  updateSpeed=increaseSpeed;
}

void loop()
{
  updateSpeed();
  Serial.printf("Duty Cycle: %d\n", dutyCycle);
  delay(50);
}
void increaseSpeed()
{
  dutyCycle += 2;
  if (dutyCycle >= MAX_DUTY_CYCLE)
  {
    updateSpeed=decreaseSpeed;
    dutyCycle = MAX_DUTY_CYCLE;
  }
  ledcWrite(ledChannel, dutyCycle);
}

void decreaseSpeed()
{
  dutyCycle -= 2;
  if (dutyCycle <= MIN_DUTY_CYCLE)
  {
    updateSpeed=increaseSpeed;
    dutyCycle = MIN_DUTY_CYCLE;
  }
  ledcWrite(ledChannel, dutyCycle);
}