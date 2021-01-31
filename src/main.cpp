#include <Arduino.h>
#include "FastLED.h"

// LEDs
#define DATA_PIN 2
#define NUM_LEDS 5
#define MAX_CURRENT 500

// Moisture Sensor
#define SENSOR_POWER 10
#define SENSOR_SIGNAL A0

CRGB leds[NUM_LEDS];

void setup() {
  delay(1000);
  Serial.begin(9600);

  pinMode(SENSOR_POWER, OUTPUT);

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5,MAX_CURRENT);

  FastLED.setBrightness(30);

  leds[0] = CHSV(0,255,255);
  leds[1] = CHSV(40,255,255);
  leds[2] = CHSV(80,255,255);
  leds[3] = CHSV(120,255,255);
  leds[4] = CHSV(160,255,255);

  FastLED.show();
}

void loop() {
  delay(2000);  
  digitalWrite(SENSOR_POWER, HIGH);
  delay(300);
  int sens = analogRead(SENSOR_SIGNAL);  
  digitalWrite(SENSOR_POWER, LOW);

  sens = 1023-sens;  
  Serial.println("Sensor Value: " + String(sens));
  if (sens<200) sens = 200;
  if (sens>800) sens = 800;
  
  int color = map(sens,200,800,0,160);
  for(int i=0; i<NUM_LEDS; i++) leds[i] = CHSV(color,255,255);
  FastLED.show();
}
