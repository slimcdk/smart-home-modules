/*
  esp32.h
  Created by Christian S. Skjerning, Aug 13, 2019.
  Released into the public domain.
*/


#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include <StatusLED.h>
#include <driver/adc.h>
#include <Arduino.h>


/*** DEVICE CONFIGURATION ***/
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define VERSION_MAJOR           1
#define VERSION_MINOR           1
#define VERSION_PATCH           0
#define VERSION_N               STR(VERSION_MAJOR) "." STR(VERSION_MINOR) "." STR(VERSION_PATCH)

#define DEVICE_TYPE             "light"
#define DEVICE_POSIITON         "ceiling"
#define DEVICE_LOCATION         "living-room"


/*** MQTT ***/
#define MQTT_SERVER             "hassio.local"
#define MQTT_SERVER_PORT        "1883"
#define MQTT_USER               "esp-device"
#define MQTT_PSK                "0123456789"

// TOPICS
#define MQTT_CHECKIN_REPORT     "device/checkin"
#define MQTT_ROOT               "home/" DEVICE_LOCATION "/" DEVICE_POSIITON
#define MQTT_OUTPUT_LOAD        MQTT_ROOT "/OUTPUT"
#define MQTT_SWITCH             MQTT_ROOT "/SWITCH"
#define MQTT_LIGHT_LEVEL        MQTT_ROOT "/LIGHTLEVEL"



/*** HARDWARE CONFIGURATION ***/    
#define LED_PIN                 04
#define DIM_MODE_PIN            22
#define DIM_CONTROL_PIN         25
#define MAINS_SWITCH_PIN        23
#define LDR_PIN                 34
#define BUTTON_PIN              00
#define PCB_TEMP_PIN            35




/*** NETWORK ***/
WiFiClient socket;
PubSubClient mqtt(socket);


/*** SWITCH SENSING ***/
uint8_t sense_avg_index = 0;
const uint8_t SENSE_AVG_MAX_SAMPLES = 50;
bool sense_avg[SENSE_AVG_MAX_SAMPLES];
bool last_switch_state = false;


/*** LOAD DIMMING ***/
bool power_state = 0;
bool last_power_state = 0;


/*** LIGHT LEVEL ***/
uint16_t _light_level_max = 2050;
uint16_t _light_level_min = 2040;


/*** NON-BLOCKING EVENT TIMERS  ***/
uint64_t last_broadcast = 0;
uint32_t start_press_duration = 0;



/*** MISC ***/
StatusLED LED(LED_PIN);