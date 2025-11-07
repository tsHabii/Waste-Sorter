#include <WiFi.h>
#include <esp_now.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>

// ---------------- OLED CONFIG ----------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---------------- LED PINS ----------------
#define LED_WHITE 18   // Power indicator
#define LED_YELLOW 19  // Blinks when message received

// ---------------- SERVO PINS ----------------
#define SERVO_PAPER_PIN     14
#define SERVO_PLASTIC_PIN   12
#define SERVO_CARDBOARD_PIN 13

String detectedWaste = "";

Servo servoPaper;
Servo servoPlastic;
Servo servoCardboard;

// ---------------- MESSAGE STRUCT ----------------
typedef struct struct_message {
  char binType[32];
} struct_message;

struct_message incomingMessage;

// ---------------- HELPER FUNCTIONS ----------------
void blinkActivityLED() {
  digitalWrite(LED_YELLOW, HIGH);
  delay(150);
  digitalWrite(LED_YELLOW, LOW);
}

void displayBin(String bin) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println("Bin:");
  display.setTextSize(2);
  display.setCursor(0, 40);
  display.println(bin);
  display.display();
}

void moveServo(Servo &servo) {
  servo.write(180);
  delay(2000);
  servo.write(0);
  delay(2000);
}

// ---------------- CALLBACK FUNCTION ----------------
void OnDataRecv(const esp_now_recv_info *info, const uint8_t *incomingData, int len) {
  memcpy(&incomingMessage, incomingData, sizeof(incomingMessage));
  String bin = String(incomingMessage.binType);

  Serial.print("Received from: ");
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X", info->src_addr[i]);
    if (i < 5) Serial.print(":");
  }
  Serial.println();

  Serial.print("Received bin type: ");
  Serial.println(bin);

  displayBin(bin);
  blinkActivityLED();

  // Move corresponding servo
  if (bin.equalsIgnoreCase("Paper")) {
    moveServo(servoPaper);
  } else if (bin.equalsIgnoreCase("Plastic")) {
    moveServo(servoPlastic);
  } else if (bin.equalsIgnoreCase("Cardboard")) {
    moveServo(servoCardboard);
  }
}

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  // LED setup
  pinMode(LED_WHITE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  digitalWrite(LED_WHITE, HIGH); // Power ON indicator

  // Servo setup
  servoPaper.attach(SERVO_PAPER_PIN);
  servoPlastic.attach(SERVO_PLASTIC_PIN);
  servoCardboard.attach(SERVO_CARDBOARD_PIN);
  servoPaper.write(0);
  servoPlastic.write(0);
  servoCardboard.write(0);


  // OLED setup
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed to initialize!");
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println("ESP32 Receiver Ready");
  display.display();

  // ESP-NOW initialization
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register callback
  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("ESP-NOW Receiver Initialized.");
  Serial.print("Receiver MAC Address: ");
  Serial.println(WiFi.macAddress());
}

// ====== Loop ======
void loop() {
  // Simulate a detected waste type for testing
  // Replace this section with your ESP32-CAM detection input
  if (Serial.available()) {
    detectedWaste = Serial.readStringUntil('\n');
    detectedWaste.trim();
  }

  if (detectedWaste == "paper") {
    Serial.println("🧾 Paper detected! Opening paper bin...");
    openBin(servoPaper);
  } 
  else if (detectedWaste == "plastic") {
    Serial.println("🧴 Plastic detected! Opening plastic bin...");
    openBin(servoPlastic);
  } 
  else if (detectedWaste == "cardboard") {
    Serial.println("📦 Cardboard detected! Opening cardboard bin...");
    openBin(servoCardboard);
  }

  delay(100); // small delay for serial stability
}

// ====== Function: Open and close bin ======
void openBin(Servo &binServo) {
  binServo.write(90);   // open position
  delay(2000);          // keep bin open for 2 seconds
  binServo.write(0);    // close bin
  delay(500);           // brief pause
}
