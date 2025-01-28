#include "OLEDHandler.h" 
#include "APWebHandler.h"

// Custom UART1 pins for ESP32-1
#define TXD1_PIN 21
#define RXD1_PIN 20
#define BAUD_RATE 115200

// create OLEDHandler object
// argument (int SDA, int SCL)
OLEDHandler oled(9, 10);

// Stores the previous input
String previousInput = "";


void setup() {

    Serial1.begin(BAUD_RATE, SERIAL_8N1, RXD1_PIN, TXD1_PIN);
    Serial.begin(115200);

    oled.initializeOLED();
    oled.displayText(initializeWebServer("Robot WiFi", "12345", 8).c_str());
}

void loop() {

    const char* input  = getLastInput();

    if (previousInput != input) {
    previousInput = input;
    std::string text = std::string("Moving to: ") + input;
    oled.displayText(text.c_str());
    Serial1.println(input);
    }

    delay(500);
}

