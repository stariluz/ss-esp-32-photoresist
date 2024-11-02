#include <Arduino.h>
#include <esp32-hal-gpio.h>

#define MIN_DUTY_CYCLE 80
#define MAX_DUTY_CYCLE 180

const int ledChannel = 0;
const int transistorPin = GPIO_NUM_15;
const int encoderPin = GPIO_NUM_2;
const int frequency = 5000;
const int resolution = 8;

// Variables for the timer and clock
hw_timer_t *timer = NULL;
volatile bool updateTime = false; // Flag to signal when to update time
volatile int seconds = 0;
volatile int minutes = 0;
volatile int hours = 0;
volatile int dutyCycle = MIN_DUTY_CYCLE;
volatile bool isIncreasing = true;

volatile int counter, previousCounter = 0;
volatile int counterPerSecond = 0;

void IRAM_ATTR onTimer();
void updateClock();
void updateSpeed();

void setup()
{
  Serial.begin(9600);
  ledcSetup(ledChannel, frequency, resolution);
  ledcAttachPin(transistorPin, ledChannel);
  pinMode(encoderPin, INPUT);

  // Configurar el temporizador 0, que cuenta hasta 1 segundo (1 Hz)
  timer = timerBegin(0, 80, true);             // Temporizador 0, prescaler 80 (80 MHz / 80 = 1 MHz, 1 microsegundo por tick)
  timerAttachInterrupt(timer, &onTimer, true); // Conectar la función de interrupción
  timerAlarmWrite(timer, 1000000, true);       // 1000000 ticks = 1 segundo
  timerAlarmEnable(timer);                     // Habilitar la alarma del temporizador
}
volatile int lastEncoderValue = 0;
void loop()
{
  updateClock();
  int encoderValue = digitalRead(encoderPin);
  // Serial.println(encoderValue);
  if (encoderValue != lastEncoderValue)
  {
    lastEncoderValue = encoderValue;
    if (encoderValue == 1)
    {
      counter++;
    }
  }
}

// Interrupt handler function
void IRAM_ATTR onTimer()
{
  updateTime = true; // Set the flag to true (keep the ISR short)
}

void updateClock()
{
  // Check if the time needs to be updated (set by the interrupt)
  if (updateTime)
  {
    updateTime = false; // Reset the flag

    // Update the time
    seconds++;
    if (seconds >= 60)
    {
      seconds = 0;
      minutes++;
    }

    if (minutes >= 60)
    {
      minutes = 0;
      hours++;
    }

    if (hours >= 24)
    {
      hours = 0;
    }
    updateSpeed();
    counterPerSecond = counter - previousCounter;
    previousCounter = counter;
    Serial.printf("Time: %02d:%02d:%02d\n", hours, minutes, seconds);
    Serial.printf("Encoder turns: %d\n", counterPerSecond / 12);
    Serial.printf("Tics: %d\n", counterPerSecond);
  }
}
void updateSpeed()
{

  if (isIncreasing)
  {
    dutyCycle+=2;
  }
  else
  {
    dutyCycle-=2;
  }

  if (dutyCycle <= MIN_DUTY_CYCLE)
  {
    isIncreasing = true;
    dutyCycle = MIN_DUTY_CYCLE;
  }
  else if (dutyCycle >= MAX_DUTY_CYCLE)
  {
    isIncreasing = false;
    dutyCycle = MAX_DUTY_CYCLE;
  }

  ledcWrite(ledChannel, dutyCycle);
  Serial.printf("Duty Cycle: %d\n", dutyCycle);
}