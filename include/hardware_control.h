#ifndef HARDWARE_CONTROL_H
#define HARDWARE_CONTROL_H

#include <Arduino.h>

#define BUTTON_PIN 0
#define LED_PIN 2
#define LONG_PRESS_TIME 3000

extern bool apMode;

void initializeHardware() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
}

void startAccessPoint() {
    WiFi.disconnect();
    WiFi.mode(WIFI_AP);
    WiFi.softAP("ESP-IR");
    apMode = true;
    Serial.println("Hotspot started");
}

void indicateWiFiConnected() {
    digitalWrite(LED_PIN, HIGH);
}

void handleButtonPress() {
    if (digitalRead(BUTTON_PIN) == LOW) {
        delay(LONG_PRESS_TIME);
        if (digitalRead(BUTTON_PIN) == LOW) {
            startAccessPoint();
        }
    }
}

void handleLEDBlink() {
    if (apMode) {
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
        delay(1000);
    }
}

#endif
