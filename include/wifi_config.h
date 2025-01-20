#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#include <LittleFS.h>
#include <ESP8266WiFi.h>

void saveWiFiConfig(const char* ssid, const char* password) {
    File configFile = LittleFS.open("/wifi_config.txt", "w");
    if (!configFile) {
        Serial.println("Failed to open config file for writing");
        return;
    }
    configFile.printf("%s\n%s", ssid, password);
    configFile.close();
    Serial.println("Wi-Fi configuration saved to LittleFS");
}

void loadWiFiConfig(char* ssid, char* password) {
    File configFile = LittleFS.open("/wifi_config.txt", "r");
    if (!configFile) {
        Serial.println("Wi-Fi configuration file not found");
        ssid[0] = '\0';
        password[0] = '\0';
        return;
    }
    String ssidStr = configFile.readStringUntil('\n');
    String passStr = configFile.readStringUntil('\n');
    configFile.close();

    ssidStr.trim();
    passStr.trim();

    strncpy(ssid, ssidStr.c_str(), 32);
    strncpy(password, passStr.c_str(), 32);

    Serial.printf("Loaded Wi-Fi configuration: SSID=%s\n", ssid);
}

bool connectToWiFi(unsigned long timeoutMs) {
    char ssid[32] = "";
    char password[32] = "";
    loadWiFiConfig(ssid, password);

    if (strlen(ssid) == 0 || strlen(password) == 0) {
        Serial.println("WiFi credentials not set.");
        return false;
    }

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    Serial.printf("Connecting to Wi-Fi: %s\n", ssid);
    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startTime < timeoutMs) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    return WiFi.status() == WL_CONNECTED;
}

#endif
