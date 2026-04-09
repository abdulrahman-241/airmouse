#include <BleMouse.h>
#include <Wire.h>
#include <MPU6050_tockn.h>
// Create instances
BleMouse bleMouse("ESP32_AirMouse", "Espressif", 100);
MPU6050 mpu6050(Wire);
// Define Button Pins
#define LEFT_CLICK_PIN 4
#define RIGHT_CLICK_PIN 5
// Variables for mouse movement logic
long lastMouseUpdate = 0;
int updateInterval = 20; // Update mouse every 20ms (smoothness control)
// Sensitivity: Higher number = faster cursor movement
// You may need to adjust this based on your preference
float sensitivity = 8.0; 

// Gyro Deadzone: Ignores tiny movements to prevent drift
float deadzone = 4.0; 

void setup() {
  Serial.begin(115200);
  
  // Initialize I2C
  Wire.begin();
  
  // Initialize MPU6050
  mpu6050.begin();
  
  // Start Bluetooth Mouse
  bleMouse.begin();
  
  // Setup Buttons with Internal Pull-up Resistors
  pinMode(LEFT_CLICK_PIN, INPUT_PULLUP);
  pinMode(RIGHT_CLICK_PIN, INPUT_PULLUP);
  
  Serial.println("Starting...");
  Serial.println("Waiting for Bluetooth connection...");
}

void loop() {
  // 1. Update MPU6050 data
  mpu6050.update();

  // 2. Handle Bluetooth Connection Status
  if(bleMouse.isConnected()) {
    
    // --- MOUSE MOVEMENT LOGIC ---
    // We use a timer to control how often we move the mouse
    if (millis() - lastMouseUpdate > updateInterval) {
      
      // Read Gyroscope data (angle velocity)
      // getGyroX() corresponds to tilting forward/backward (Y axis on screen)
      // getGyroY() corresponds to tilting left/right (X axis on screen)
      float gyroX = mpu6050.getGyroX();
      float gyroY = mpu6050.getGyroY();

      int moveX = 0;
      int moveY = 0;

      // Calculate movement if outside deadzone
      // Note: You might need to invert signs (-) if movement is backwards
      if (abs(gyroY) > deadzone) {
        moveX = (int)(gyroY * sensitivity / 100.0);
      }
      
      if (abs(gyroX) > deadzone) {
        moveY = (int)(gyroX * sensitivity / 100.0);
      }

      // Only move if there is actual movement calculated
      if (moveX != 0 || moveY != 0) {
        bleMouse.move(moveX, moveY);
      }
      
      lastMouseUpdate = millis();
    }

    // --- CLICK LOGIC ---
    // Left Click (Active LOW because of INPUT_PULLUP)
    if (digitalRead(LEFT_CLICK_PIN) == LOW) {
      // Press and hold logic usually requires debouncing, 
      // but press/release is simpler for basic usage.
      // We send "press" and then immediately check for release in next loop.
      bleMouse.press(MOUSE_LEFT);
    } else {
      bleMouse.release(MOUSE_LEFT);
    }

    // Right Click
    if (digitalRead(RIGHT_CLICK_PIN) == LOW) {
      bleMouse.press(MOUSE_RIGHT);
    } else {
      bleMouse.release(MOUSE_RIGHT);
    }
  }
}