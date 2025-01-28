#include <OLEDHandler.h>
#include <APWebHandler.h>

// Create an instance of a web server
AsyncWebServer server(80);

// Store the last input that the user gave
static String lastInput = "";

String initializeWebServer(const char* ssid, const char* password, int ledPin) {

    // If the ledPin is specified, set it up
    if (ledPin != -1) {
        pinMode(ledPin, OUTPUT);
        digitalWrite(ledPin, LOW);
    }

    Serial.begin(115200);

    // Start ESP32 as an access point
    WiFi.softAP(ssid);

    // Print the AP IP address
    Serial.println("Access Point Started!");
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());

    // Serve the HTML page with text input and buttons
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        String html = R"rawliteral(
            <!DOCTYPE html>
            <html>
            <head>
                <title>IoT Robot</title>
                <style>
                    body {
                        font-family: Arial, sans-serif;
                        background-color: #222;
                        color: white;
                        text-align: center;
                        padding: 20px;
                    }
                    button {
                        margin: 10px;
                        padding: 10px 20px;
                        font-size: 16px;
                        cursor: pointer;
                    }
                    input {
                        padding: 10px;
                        font-size: 16px;
                        margin-right: 10px;
                    }
                </style>
            </head>
            <body>
                <h1>WiFi Robot</h1>
                
                <h2>Text Input</h2>
                <form action="/submit" method="GET">
                    <input type="text" name="inputText" placeholder="Enter instructions:" required>
                    <button type="submit">Submit</button>
                </form>
                
                <h2>Last Received Instructions:</h2>
        )rawliteral";
        html += "<p>" + lastInput + "</p>";
        html += R"rawliteral(
            </body>
            </html>
        )rawliteral";
        request->send(200, "text/html", html);
    });

    // Handle form submissions
    server.on("/submit", HTTP_GET, [](AsyncWebServerRequest* request) {
        if (request->hasParam("inputText")) {
            lastInput = request->getParam("inputText")->value(); // Save the input
            Serial.println("Received text: " + lastInput);
        }
        request->redirect("/");
    });

    server.begin();

    // Return the AP IP address
    return WiFi.softAPIP().toString();
}

// Get the last input submitted
const char* getLastInput() {
    return lastInput.c_str();
}
