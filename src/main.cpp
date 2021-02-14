#include <Arduino.h>
#include <esp_camera.h>
#include <WifiSettings.h>
#include <Wire.h>

// Using the Grove SDA pin to trigger a ULN2803 driver to light a LED lamp.
#define LED_PIN 12

void setup() {
  // put your setup code here, to run once:

  pinMode(LED_PIN, OUTPUT);  
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(LED_PIN, HIGH);
  delay(50);
  digitalWrite(LED_PIN, LOW);
  delay(950);
}