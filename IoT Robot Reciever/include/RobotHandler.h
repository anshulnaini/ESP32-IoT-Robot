#ifndef ROBOTHANDLER_H
#define ROBOTHANDLER_H

#include <AccelStepper.h>
#include <Arduino.h>

class RobotHandler {
private:
    AccelStepper motor1;
    AccelStepper motor2;
    AccelStepper motor3;

    // Standard for 28byj48 steppers
    const float STEPS_PER_REV = 2048;
    const float STEPS_PER_DEGREE = STEPS_PER_REV / 360.0;

    // Default values
    float acceleration; // steps/second^2
    float maxSpeed; // steps/second

public:
    // Constructor
    // Must pass pointer to array (define the arrays before and pass the variable)
    RobotHandler(int motor1Pins[4], int motor2Pins[4], int motor3Pins[4]);

    void setMaxSpeed(float speed);

    void setAcceleration(float acceleration);

    void moveMotorsDegrees(float degrees1, float degrees2, float degrees3);

    bool motorsAreRunning();
};


#endif