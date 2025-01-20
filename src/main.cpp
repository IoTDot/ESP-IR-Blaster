#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include "wifi_config.h"
#include "web_ui.h"
#include "server_handlers.h"
#include "hardware_control.h"

AsyncWebServer server(80);
bool apMode = false;

void setup() {
    Serial.begin(115200);
    initializeHardware();

    if (!LittleFS.begin()) {
        Serial.println("Failed to mount LittleFS");
        return;
    }

    char ssid[32] = "";
    char password[32] = "";
    loadWiFiConfig(ssid, password);

    if (strlen(ssid) == 0 || strlen(password) == 0) {
        Serial.println("No Wi-Fi credentials found. Starting AP mode...");
        startAccessPoint();
        apMode = true;
        configureServer(server);
        server.begin();
    } else {
        const unsigned long connectTimeout = 5000;
        if (connectToWiFi(connectTimeout)) {
            Serial.println("Connected to Wi-Fi!");
            indicateWiFiConnected();
            apMode = false;
        } else {
            Serial.println("Failed to connect to Wi-Fi. Starting AP mode...");
            startAccessPoint();
            apMode = true;
            configureServer(server);
            server.begin();
        }
    }
}

void loop() {
    handleButtonPress();
    if (apMode) {
        handleLEDBlink();
    }
}
