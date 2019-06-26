/*
StatusLED.h - Library for controlling using WS2812 RGB LED.
Created by Christian S. Skjerning, June 18, 2019.
Released into the public domain.
*/

#ifndef StatusLED_h
#define StatusLED_h

	#include "Arduino.h"
	#include <Adafruit_NeoPixel.h>

	class StatusLED 
	{

		public:
			StatusLED(const uint8_t STATUS_LED_PIN);
			void code(uint8_t code);
			void init();

			// status codes
			// static enum CODES {ERROR, WARNING, GOOD, BUSY, NEUTRAL };
			static const uint8_t ERROR = 0;
			static const uint8_t WARNING = 1;
			static const uint8_t GOOD = 2;
			static const uint8_t BUSY = 3;
			static const uint8_t NEUTRAL = 4;

		private:
			Adafruit_NeoPixel WS2812;
			unsigned long previousMillis = 0; 
			bool blinkState = false;

			void blink(uint32_t interval);
			void blink(uint32_t interval, uint32_t duration);
	};

#endif