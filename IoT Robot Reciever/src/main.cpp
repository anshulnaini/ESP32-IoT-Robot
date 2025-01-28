#include <Arduino.h>
#include <RobotHandler.h>

// Define UART pins
#define TXD2_PIN 22
#define RXD2_PIN 23
#define BAUD_RATE 115200

// Motor pins
int motor1Pins[] = {25, 26, 27, 14};
int motor2Pins[] = {32, 33, 15, 4};
int motor3Pins[] = {16, 17, 18, 19};

// Create RobotHandler object
RobotHandler robot(motor1Pins, motor2Pins, motor3Pins);

String inputBuffer = "";

// Demo function
void runDemo() {
    Serial.println("Demo motor movements initiated.");

    robot.moveMotorsDegrees(-90, -134, 330);
    robot.moveMotorsDegrees(90, 134, -330);
    robot.moveMotorsDegrees(0, -150, 90);
    robot.moveMotorsDegrees(90, 0, 0);
    robot.moveMotorsDegrees(-180, 0, 0);
    robot.moveMotorsDegrees(90, 0, 0);
    robot.moveMotorsDegrees(0, 150, -90);

    Serial.println("Demo motor movements completed.");
}


void setup() {
    // Initialize UART2 with custom pins
    Serial2.begin(BAUD_RATE, SERIAL_8N1, RXD2_PIN, TXD2_PIN);
    Serial.begin(115200); // Debugging via USB
    Serial.println("ESP32-2 Receiver ready");
}

void loop() {
    // Read and process user input
    if (Serial2.available() > 0) {
        char receivedChar = Serial2.read();

        if (receivedChar == '\n') {
            inputBuffer.trim();

            if (inputBuffer.equalsIgnoreCase("run demo")) {
                // demo run
                runDemo();
                Serial.println("Running demo sequence.");
            } else {
                float degrees1, degrees2, degrees3;

                if (sscanf(inputBuffer.c_str(), "%f %f %f", &degrees1, &degrees2, &degrees3) == 3) {
                    Serial.print("Moving motors to: ");
                    Serial.print(degrees1);
                    Serial.print(", ");
                    Serial.print(degrees2);
                    Serial.println(", ");
                    Serial.println(degrees3);

                    robot.moveMotorsDegrees(degrees1, degrees2, degrees3);

                    Serial.println("Motors have reached their target positions.");
                } else {
                    Serial.println("Invalid input. Enter three degree values (e.g., 90 180 45).");
                }
            }

            inputBuffer = "";
            Serial.println("Enter new degrees:");
        } else {
            inputBuffer += receivedChar;
            Serial.print(receivedChar);
        }
    }
}
