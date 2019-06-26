/*
  conf.h
  Created by Christian S. Skjerning, June 18, 2019.
  Released into the public domain.
*/

// public libraries
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

// custom libaries
#include <StatusLED.h>


#define VERSION_N                 "0.0.1"


// device conf
#define DEVICE_TYPE             "mains_light_controller"
#define DEVICE_ID               "ceiling_light"
#define DEVICE_LOCATION         "living_room"


#define MQTT_ADDRESS            "192.168.123.17"
#define MQTT_SERVER_PORT        1883
#define MQTT_USER               "esp-ceiling-light"
#define MQTT_PSK                "DankMemes420"

#define MQTT_CHECKIN_REPORT     "device/checkin"
#define MQTT_ROOT               "home/living/ceiling"


// hardware configuration               // PCB config
#define STATUS_LED_PIN          0       // D2
#define OUTPUT_LOAD_PIN         4       // D4

#define SWITCH_SENSE_PIN        2       // D5
#define LIGHT_LEVEL_SENSE_PIN   A0      // A0
#define BUTTON_SENSE_PIN        false   // D0
#define TEMPERATURE_SENSE_PIN   false   // TBD
#define HUMIDITY_SENSE_PIN      false   // TBD


// switch sensing
#ifdef SWITCH_SENSE_PIN
  uint8_t sense_avg_index = 0;
  const uint8_t SENSE_AVG_MAX_SAMPLES = 50;
  bool sense_avg[SENSE_AVG_MAX_SAMPLES];
  bool lastSwitchState = false;
  #define MQTT_SWITCH_GET       MQTT_ROOT "/get/switch"
#endif


// load switching
#ifdef OUTPUT_LOAD_PIN
  #define ANALOGUE_LAMP         false
  #define MQTT_LOAD_SET       MQTT_ROOT "/set/load"
  #define MQTT_LOAD_GET       MQTT_ROOT "/get/load"
  bool powerState = 0;
  bool lastPowerState = 0;
#endif


// light level sensor
#ifdef LIGHT_LEVEL_SENSE_PIN
  #define MQTT_LIGHT_LEVEL_GET  MQTT_ROOT "/get/lightlevel"
#endif


// temperature sensor
#ifdef TEMPERATURE_SENSE_PIN
  #define MQTT_TEMPERATURE_GET  MQTT_ROOT "/get/temperature"
#endif


// button
#ifdef BUTTON_SENSE_PIN
  #define MQTT_BUTTON_GET       MQTT_ROOT "/get/button"
#endif


// humidity sensor
#ifdef HUMIDITY_SENSE_PIN
  #define MQTT_HUMIDITY_GET     MQTT_ROOT "/get/humidity"
#endif


WiFiClient socket;
PubSubClient network(socket);
StatusLED LED(STATUS_LED_PIN);