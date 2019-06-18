/*
  StatusLED.h - Library for controlling status LED.
  Created by Christian S. Skjerning, June 18, 2019.
  Released into the public domain.
*/

#include <StatusLED.h>

// Constructor
StatusLED::StatusLED(const uint8_t STATUS_LED_PIN) : WS2812(1, STATUS_LED_PIN, NEO_GRB + NEO_KHZ800) {}


void StatusLED::init() {
  WS2812.begin();
  WS2812.show();
}


void StatusLED::code(uint8_t code) {
  WS2812.clear();

  uint32_t color;

  switch(code) {
    // ERROR
    case 0:
      color = WS2812.Color(255, 0, 0);
      blink(100, 20);
      break;
    
    // WARNING
    case 1:
      color = WS2812.Color(255, 255, 0);
      blink(1000, 20);
      break;
    
    // GOOD
    case 2:
      color = WS2812.Color(0, 255, 0);
      blink(10000, 20);
      break;
    
    // BUSY
    case 3:
      color = WS2812.Color(0, 255, 255);
      blink(50, 20);
      break;
    
    // NEUTAL
    case 4:
      color = WS2812.Color(255, 255, 255);
      blink(0, 20);
      break;

    // NONE
    default: 
      color = WS2812.Color(0, 0, 0);
      blink(0, 20);
  }

  if (blinkState) {
    WS2812.setPixelColor(0, color);
  }

  WS2812.show();
}


void StatusLED::blink(uint32_t interval) {

  uint64_t currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    blinkState = !blinkState;
  }

}

void StatusLED::blink(uint32_t interval, uint32_t duration) {


  uint64_t currentMillis = millis();
  uint64_t deltaTime = currentMillis - previousMillis;

  if((blinkState == true) && (deltaTime >= duration))
  {
    blinkState = false;
    previousMillis = currentMillis;
  }
  else if ((blinkState == false) && (deltaTime >= interval))
  {
    blinkState = true;
    previousMillis = currentMillis;
  }
}
