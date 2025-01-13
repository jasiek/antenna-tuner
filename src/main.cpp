#include <Arduino.h>

#define MOTOR_STEPS 200 // 1.8 degree per step
#define RPM 120

// This uses the MH-Tiny board with an ATtiny88
// ![https://user-images.githubusercontent.com/68873801/89062312-803fa100-d366-11ea-9142-69c36b0ca764.png]

#define DIR PD3
#define STEP PD4

#include "A4988.h"
A4988 stepper(MOTOR_STEPS, DIR, STEP);

#define LEFT_FINE A5
#define LEFT A4
#define RIGHT A3
#define RIGHT_FINE A2
#define ZERO_SENSOR PD5
#define LED PD0

#define FINE_STEP_DELAY 300
#define MAIN_LOOP_DELAY 10

int debounce(uint8_t pin)
{
    int state = digitalRead(pin);
    delay(1);
    if (state == digitalRead(pin))
    {
        return state;
    }
    else
    {
        return LOW;
    }
}

void calibrate()
{
    digitalWrite(LED, HIGH);
    while (digitalRead(ZERO_SENSOR) == HIGH)
    {
        stepper.move(1);
        delay(5);
    }
    digitalWrite(LED, LOW);
}

void setup()
{
    stepper.begin(RPM);
    stepper.enable();

    pinMode(LEFT_FINE, INPUT_PULLUP);
    pinMode(LEFT, INPUT_PULLUP);
    pinMode(RIGHT, INPUT_PULLUP);
    pinMode(RIGHT_FINE, INPUT_PULLUP);
    pinMode(LED, OUTPUT);
    pinMode(ZERO_SENSOR, INPUT);
    digitalWrite(LED, LOW);
    calibrate();
}

void loop()
{
    digitalWrite(LED, LOW);
    delay(MAIN_LOOP_DELAY);

    // fine controls, one step per push
    if (debounce(LEFT_FINE) == LOW)
    {
        digitalWrite(LED, HIGH);
        stepper.move(1);
        delay(FINE_STEP_DELAY);
    }
    if (debounce(RIGHT_FINE) == LOW)
    {
        digitalWrite(LED, HIGH);
        stepper.move(-1);
        delay(FINE_STEP_DELAY);
    }

    // coarse controls, continuous movement
    if (debounce(LEFT) == LOW)
    {
        digitalWrite(LED, HIGH);
        stepper.move(1);
    }
    if (debounce(RIGHT) == LOW)
    {
        digitalWrite(LED, HIGH);
        stepper.move(-1);
    }
}
