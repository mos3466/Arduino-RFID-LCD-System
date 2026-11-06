# Arduino RFID & LCD System

An Arduino-based RFID card reading system integrated with a 16×2 LCD display.

## Project Overview

This project uses an Arduino Uno, an RC522 RFID reader, and a 16×2 I2C LCD display to create a simple card-scanning system.

The system reads RFID cards, displays instructions on the LCD, and sends card scan data through Serial communication.

## Features

- RFID card detection using the RC522 module.
- LCD display for instructions and status messages.
- Serial communication at 115200 baud.
- Support for integration with external applications.
- Simple hardware setup using Arduino Uno.

## Hardware Components

| Component | Description |
|---|---|
| Arduino Uno | Main microcontroller |
| RC522 RFID Reader | Reads RFID cards |
| 16×2 I2C LCD | Displays system messages |
| Jumper Wires | Connects the components |
| USB Cable | Connects Arduino to a computer |

## Technologies Used

- Arduino IDE
- C/C++ (Arduino)
- SPI Communication
- I2C Communication
- RFID Technology
- Serial Communication

## Required Libraries

- MFRC522
- SPI
- Wire
- LiquidCrystal_I2C

## How It Works

1. The Arduino initializes the RFID reader and LCD.
2. The LCD displays a message asking the user to scan a card.
3. The RFID reader detects the card.
4. The Arduino reads the card UID.
5. The system sends scan information through Serial communication.
6. The LCD displays a status message.

## Setup Instructions

1. Connect the RFID reader and LCD to the Arduino Uno according to the wiring configuration.
2. Install the required libraries in Arduino IDE.
3. Open `arduino_rfid_rc522.ino`.
4. Select **Arduino Uno** and the correct COM port.
5. Upload the code to the Arduino.
6. Open Serial Monitor at **115200 baud**.
7. Scan an RFID card to test the system.

## Project Structure

```text
Arduino-RFID-LCD-System/
├── arduino_rfid_rc522.ino
├── README.md
└── images/
    ├── circuit.jpg
    └── lcd-display.jpg
```

*The images folder is optional. Add your own hardware photos when available.*

## Future Improvements

- Add support for more RFID card operations.
- Improve LCD status messages.
- Integrate the system with a web dashboard.
- Add a database for authorized card records.

## Project Status

Working hardware prototype with RFID reading and LCD integration.
