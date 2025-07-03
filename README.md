# Smart-Classroom-Temperature--Time--System-Project
## Overview
This project is an IoT-based **Smart Classroom Temperature & Time Display System** designed to monitor real-time temperature and time inside a classroom. The system provides visual and sound alerts if the temperature exceeds a certain threshold, ensuring a comfortable and safe environment for young students.

## Features
- Real-time temperature monitoring using **DHT11 Sensor**
- Accurate time display using **DS3231 Real-Time Clock (RTC)**
- Visual display on a **16x2 LCD**
- Alert system with **LEDs** and a **passive buzzer** when temperature exceeds safe limits

## Hardware Used
- **Arduino Uno** (or compatible board)
- **DHT11 Temperature & Humidity Sensor**
- **DS3231 RTC Module**
- **16x2 LCD Display**
- **LEDs** (Red, Green)
- **Passive Buzzer**
- **Breadboard & Jumper Wires**
- **Power Source (Laptop)**

## Software & Libraries
- **Arduino IDE**
- Required Libraries:
  - `DHT.h` - for reading temperature and humidity
  - `RTClib.h` - for handling the RTC module
  - `LiquidCrystal.h` - for the LCD display
    
## How It Works
1. The **DHT11 sensor** continuously reads the temperature and humidity.
2. The **DS3231 RTC module** keeps and provides the current time.
3. The **Arduino** processes the data and updates the **16x2 LCD** display in real time.
4. If the measured temperature exceeds a predefined limit, the system activates:
   - **Red LED** and **buzzer** as warning signals.
   - Otherwise, the **Green LED** indicates normal conditions.

##  How to Use
1. Open the Arduino IDE and install the following libraries if not already installed:
   - `DHT.h`
   - `RTClib.h`
   - `LiquidCrystal.h`
2. Upload the provided `.ino` file to your Arduino board.
3. Connect the components as per the schematic.
4. Power the system and monitor the LCD display and alerts.
   
## Future Improvements
- Add Wi-Fi capability for remote temperature monitoring.
- Log data to SD card or upload to IoT platforms like ThingSpeak.
- Display humidity alongside temperature.
- Adjustable temperature thresholds.

## Author
Imran Mulindwa 
GitHub: [Imra198](https://github.com/Imra198)
