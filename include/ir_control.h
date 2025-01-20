#ifndef IR_CONTROL_H
#define IR_CONTROL_H

#include <IRremoteESP8266.h>
#include <IRsend.h>

#define IR_PIN 4

IRsend irsend(IR_PIN);

void initializeIR() {
    irsend.begin();
}

void sendIRCode(uint64_t code, uint16_t bits) {
    irsend.sendNEC(code, bits);
    Serial.println("IR code sent");
}

#endif
