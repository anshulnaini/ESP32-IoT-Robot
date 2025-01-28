#ifndef APWEBHANDLER_H
#define APWEBHANDLER_H

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Declare the web server instance
extern AsyncWebServer server;

// Function to initialize the web server in Access Point mode
String initializeWebServer(const char* ssid, const char* password, int ledPin = -1);

// Function to get the last input submitted
const char* getLastInput();

#endif // WEBHANDLER_H
