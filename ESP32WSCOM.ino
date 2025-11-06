#include "Arduino.h"

#define RXD2 16  // RX2
#define TXD2 17  // TX2

void setup() {
  Serial.begin(115200);       // Debug monitor
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); // UART2 for communication

  Serial.println("ESP32 Dev Board UART Receiver Started");
}

void loop() {
  if (Serial2.available()) {
    String incoming = Serial2.readStringUntil('\n');
    Serial.println("Received: " + incoming);
  }
}
