# include "RobotHandler.h"

// Constructor
// Sets default maxSpeed = 1000 steps/second and acceleration = steps/second^2
RobotHandler::RobotHandler(int motor1Pins[4], int motor2Pins[4], int motor3Pins[4])
    : motor1(AccelStepper::FULL4WIRE, motor1Pins[0], motor1Pins[2], motor1Pins[1], motor1Pins[3]),
      motor2(AccelStepper::FULL4WIRE, motor2Pins[0], motor2Pins[2], motor2Pins[1], motor2Pins[3]),
      motor3(AccelStepper::FULL4WIRE, motor3Pins[0], motor3Pins[2], motor3Pins[1], motor3Pins[3]) {

        maxSpeed = 1000;
        acceleration = 500;

        motor1.setMaxSpeed(maxSpeed);
        motor1.setAcceleration(acceleration);
        
        motor2.setMaxSpeed(maxSpeed);
        motor2.setAcceleration(acceleration);

        motor3.setMaxSpeed(maxSpeed);
        motor3.setAcceleration(acceleration);
      }

// Set maximum speed for all motors
void RobotHandler::setMaxSpeed(float speed) {
    motor1.setMaxSpeed(speed);
    motor2.setMaxSpeed(speed);
    motor3.setMaxSpeed(speed);
}

// Set acceleration for all motors
void RobotHandler::setAcceleration(float acceleration) {
    motor1.setAcceleration(acceleration);
    motor2.setAcceleration(acceleration);
    motor3.setAcceleration(acceleration);
}


// Move the motors by specified degrees
void RobotHandler::moveMotorsDegrees(float degrees1, float degrees2, float degrees3) {
    // Set target positions for each motor
    motor1.moveTo(motor1.currentPosition() + (degrees1 * STEPS_PER_DEGREE));
    motor2.moveTo(motor2.currentPosition() + (degrees2 * STEPS_PER_DEGREE));
    motor3.moveTo(motor3.currentPosition() + (-degrees3 * STEPS_PER_DEGREE)); // Reverse direction if you need to

    // Run motors until all reach target positions
    while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0) {
        motor1.run();
        motor2.run();
        motor3.run();
    }
}

// Check if motors are still running
bool RobotHandler::motorsAreRunning() {
    return motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0;
}