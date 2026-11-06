#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void showReady() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RASD SYSTEM");
  lcd.setCursor(0, 1);
  lcd.print("Scan Your Card");
}

void showResult(String result) {
  lcd.clear();

  if (result == "HOLD") {
    lcd.setCursor(0, 0);
    lcd.print("Access Denied");
    lcd.setCursor(0, 1);
    lcd.print("Refer to Staff");
  }
  else if (result == "EXIT_ALLOWED") {
    lcd.setCursor(0, 0);
    lcd.print("Exit Allowed");
    lcd.setCursor(0, 1);
    lcd.print("Good Bye");
  }
  else if (result == "TRIP_ACTIVE") {
    lcd.setCursor(0, 0);
    lcd.print("Trip Active");
    lcd.setCursor(0, 1);
    lcd.print("Welcome");
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print("Scan Error");
    lcd.setCursor(0, 1);
    lcd.print("Try Again");
  }

  delay(3000);
  showReady();
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(5000);

  SPI.begin();
  rfid.PCD_Init();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("RASD SYSTEM");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");

  delay(1500);

  byte version = rfid.PCD_ReadRegister(rfid.VersionReg);

  Serial.print("RFID Reader Version: 0x");
  Serial.println(version, HEX);
  Serial.println("RASD System Ready");

  showReady();
}

void loop() {

  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Card Detected!");
  lcd.setCursor(0, 1);
  lcd.print("Checking...");

  Serial.print("RFID_UID=");

  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) {
      Serial.print("0");
    }
    Serial.print(rfid.uid.uidByte[i], HEX);
  }

  Serial.println();

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  // Wait for the Python bridge/backend decision.
  unsigned long startTime = millis();

  while (millis() - startTime < 10000) {

    if (Serial.available()) {
      String response = Serial.readStringUntil('\n');
      response.trim();

      if (response.startsWith("RASD_RESULT=")) {
        String result = response.substring(12);
        showResult(result);
        return;
      }
    }
  }

  // No response received from the bridge.
  showResult("SCAN_ERROR");
}