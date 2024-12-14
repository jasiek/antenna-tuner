#include <Arduino.h>

#define MOTOR_STEPS 200
#define RPM 120

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

#define FINE_STEP_DELAY 200

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
    stepper.setMicrostep(16); // A4988 is hard wired to 16 microsteps (MS2=HIGH)

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
    delay(10);

    // fine controls, one step per push
    if (digitalRead(LEFT_FINE) == LOW)
    {
        digitalWrite(LED, HIGH);
        stepper.move(1);
        delay(FINE_STEP_DELAY);
    }
    if (digitalRead(RIGHT_FINE) == LOW)
    {
        digitalWrite(LED, HIGH);
        stepper.move(-1);
        delay(FINE_STEP_DELAY);
    }

    // coarse controls, continuous movement
    if (digitalRead(LEFT) == LOW)
    {
        digitalWrite(LED, HIGH);
        stepper.move(1);
    }
    if (digitalRead(RIGHT) == LOW)
    {
        digitalWrite(LED, HIGH);
        stepper.move(-1);
    }
}
