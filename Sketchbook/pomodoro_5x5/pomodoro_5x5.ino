/* https://www.banggood.com/ESP32-C3-Development-Board-RISC-V-WiFi-Bluetooth-IoT-Development-Board-Compatible-with-Python-p-1914005.html?cur_warehouse=CN
 *  
 *  GPIO09  button
 *  GPIO08  neopixels
 *  GPIO10 status led 
 *  
  */

#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

#define LED_PIN 8
#define LED_COUNT 25

unsigned long oneMinute = 60000;
unsigned long fifthOfMinute = 12000;
unsigned long clockMillis;

uint8_t LEDsTurnedOff = 0;

boolean isOn[25];
boolean toggleLED = true;
uint8_t onBoardLED = 10;

uint8_t red = 0;
uint8_t green = 255;

char state = 0;
char state_pomodoro = 0;
char state_cooldown = 1;
char state_waitForReset = 2;


Adafruit_NeoPixel strip(
  LED_COUNT,
  LED_PIN,
  NEO_GRB + NEO_KHZ800
);

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(20);

  clockMillis = millis();

  state = state_pomodoro;
  resetValues();

  randomSeed(analogRead(0));

  pinMode(onBoardLED, OUTPUT);
}


void loop() {
  if (state == state_pomodoro) {
    pomodoro();
  }
  else if (state == state_cooldown) {
    cooldown();
  }
  else {
    waitForReset();
  }
}

void waitForReset() {
  if (millis() - clockMillis > 500) {

      if (toggleLED) {
        digitalWrite(onBoardLED, LOW);
        draw(255, 0, 127);
      }
      else {
        digitalWrite(onBoardLED, HIGH);
        draw(0, 0, 0);
      }
      clockMillis = millis();
      toggleLED = !toggleLED;
  }
}

void cooldown() {
  if (millis() - clockMillis > fifthOfMinute) {
    clockMillis = millis();
    turnOffRandom();
    draw(0, 0, 255);
    LEDsTurnedOff++;
    if (LEDsTurnedOff == 25) {
      state = state_waitForReset;
      resetValues();
    }
  }
}

void pomodoro() {
  if (millis() - clockMillis > oneMinute) {

    clockMillis = millis();

    LEDsTurnedOff++;

    if (LEDsTurnedOff == 25) {
      state = state_cooldown;
      resetValues();
      draw(0, 0, 255);
      return;
    }

    if (LEDsTurnedOff < 10) {
      red = 0;
      green = 255;
    }
    else if (LEDsTurnedOff < 20) {

      uint8_t factor = LEDsTurnedOff - 10;

      red = 255 * (factor) / 10;
      green = 255 * (10 - factor) / 10;
    }
    else {
      red = 255;
      green = 0;
    }

    turnOffRandom();
  }

  draw(red, green, 0);
}

void draw(uint8_t r,uint8_t g,uint8_t b) {
  for (uint8_t i = 0; i < 25; i++) {
    if (isOn[i]) {
      strip.setPixelColor(i, strip.Color(r, g, b));
    }
    else {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
  }
  strip.show();
}

void turnOffRandom() {
  uint8_t r = random(25);
  if (isOn[r]) {
    isOn[r] = false;
  }
  else {
    turnOffRandom();
  }
}

void resetValues() {
  for (uint8_t i = 0; i < 25; i++) {
    isOn[i] = true;
  }
  LEDsTurnedOff = 0;
}
