#ifndef SERVER_HANDLERS_H
#define SERVER_HANDLERS_H

#include <ESPAsyncWebServer.h>
#include <Ticker.h>
#include "web_ui.h"
#include "wifi_config.h"

extern bool apMode;
Ticker restartTimer;

void configureServer(AsyncWebServer &server) {
    if (!apMode) {
        Serial.println("Server configuration skipped: not in AP mode.");
        return;
    }

    // Strona główna (formularz do ustawienia Wi-Fi)
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", INDEX_HTML);
    });

    // Obsługa zapisu ustawień Wi-Fi
    server.on("/setwifi", HTTP_POST, [](AsyncWebServerRequest *request) {
        if (request->hasParam("ssid", true) && request->hasParam("password", true)) {
            String ssid = request->getParam("ssid", true)->value();
            String password = request->getParam("password", true)->value();

            // Zapis ustawień Wi-Fi
            saveWiFiConfig(ssid.c_str(), password.c_str());
            Serial.println("WiFi settings saved:");
            Serial.printf("SSID: %s\n", ssid.c_str());
            Serial.printf("Password: %s\n", password.c_str());

            // Wysłanie odpowiedzi z potwierdzeniem
            request->send_P(200, "text/html", SETWIFI_HTML);

            // Restart urządzenia po 5 sekundach
            restartTimer.once(5, []() {
                Serial.println("Restarting ESP...");
                ESP.restart();
            });
        } else {
            request->send(400, "text/plain", "Invalid data");
        }
    });
}

#endif
