# ESP32 Air Mouse 🖱️

A wireless Bluetooth BLE Air Mouse built using an **ESP32** microcontroller
and **MPU6050** 6-axis gyroscope/accelerometer sensor.
Move your hand to control the cursor — no surface needed!

## 🔧 Hardware Required
- ESP32 Development Board
- MPU6050 Gyroscope/Accelerometer Module
- 2x Push Buttons (Left Click & Right Click)
- 4 Jumper Wires

## 📦 Required Libraries
Install these via Arduino IDE Library Manager:
1. **ESP32 BLE Mouse** by T-vK download from https://github.com/T-vK/ESP32-BLE-Mouse
2. **MPU6050_tockn** by tockn downlod from arduiono (pres ctrl+shift+i and in board manager search for MPU6050_tockn and install

## How to Install Board Manager:
Open Arduino IDE
Go to File → Preferences
In "Additional Board Manager URLs" paste:

https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

Click OK
Go to Tools → Board → Boards Manager
Search "ESP32"
Install "esp32 by Espressif Systems" download 2.0.17 version
After install → Go to Tools → Board → ESP32 Arduino → Select your board
Most common: "ESP32 Dev Module"

## 📌 Pin Configuration
| Component        | ESP32 Pin |
|------------------|-----------|
| MPU6050 SDA      | GPIO 21   |
| MPU6050 SCL      | GPIO 22   |
| MPU6050 vcc      | GPIO 3v3  |
| MPU6050 GND      | GPIO GND  |
| Left Click Btn   | GPIO 4    |
| Right Click Btn  | GPIO 5    |
| ground wire for left and right click | GND  |

when you have to right click use right click btn and gnd wire button and for left click use left click btn and gnd wire

## ⚙️ How It Works
- Gyroscope X/Y axes control cursor movement
- Deadzone filtering prevents cursor drift
- BLE HID protocol emulates a real mouse

## How to upload on the esp32 
-copy ESP32_AIRMouse.ino and past and upload

-use the 
## 🚀 Getting Started
1. Clone the repo
2. Install required libraries
3. Flash to ESP32 using Arduino IDE
4. Pair via Bluetooth as `ESP32_AirMouse`
