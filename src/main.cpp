#include <Arduino.h>

#define MOTOR_STEPS 200
#define RPM 120

#define DIR PD3
#define STEP PD4
#define SLEEP 13

#include "A4988.h"
#define MS1 10
#define MS2 11
#define MS3 12
A4988 stepper(MOTOR_STEPS, DIR, STEP, SLEEP, MS1, MS2, MS3);

#define LEFT PD5
#define RIGHT PD6

void setup()
{
    stepper.begin(RPM);
    stepper.enable();
    stepper.setMicrostep(32);

    pinMode(LEFT, INPUT);
    pinMode(RIGHT, INPUT);
    pinMode(PD0, OUTPUT);
    digitalWrite(PD0, LOW);
}

void loop()
{
    digitalWrite(PD0, LOW);
    delay(30);
    if (digitalRead(LEFT) == LOW)
    {
        digitalWrite(PD0, HIGH);
        stepper.move(1);
        return;
    }
    if (digitalRead(RIGHT) == LOW)
    {
        digitalWrite(PD0, HIGH);
        stepper.move(-1);
        return;
    }
}