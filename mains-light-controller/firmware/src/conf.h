/*
  conf.h
  Created by Christian S. Skjerning, June 18, 2019.
  Released into the public domain.
*/

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
#include <StatusLED.h>



/* DEVICE CONFIGURATION */
#define VERSION_N               "0.0.1"
#define DEVICE_TYPE             "mains-light-controller"
#define DEVICE_ID               "ceiling-light"
#define DEVICE_LOCATION         "living-room"



/* MQTT */
#define MQTT_ADDRESS            "HomeAutoPi.local"
#define MQTT_SERVER_PORT        1883
#define MQTT_USER               "esp-ceiling-light"
#define MQTT_PSK                "DankMemes420"

#define MQTT_CHECKIN_REPORT     "device/checkin"
#define MQTT_ROOT               "home/living/ceiling"
#define MQTT_DEVICE_HEALTH      MQTT_ROOT "/device-health"
#define MQTT_LOAD_PUB           MQTT_ROOT "/get/load"
#define MQTT_LOAD_SUB           MQTT_ROOT "/set/load"
#define MQTT_SWITCH_PUB         MQTT_ROOT "/get/switch"
#define MQTT_LIGHT_LEVEL_PUB    MQTT_ROOT "/get/lightlevel"
#define MQTT_TEMPERATURE_PUB    MQTT_ROOT "/get/temperature"
#define MQTT_BUTTON_PUB         MQTT_ROOT "/get/button"
#define MQTT_HUMIDITY_PUB       MQTT_ROOT "/get/humidity"
#define MQTT_STATUS_LED_SUB     MQTT_ROOT "/set/statusled"


/* HARDWARE CONFIGURATION */    // BB   // PCB config
#define STATUS_LED_PIN          0       // D2
#define OUTPUT_LOAD_PIN         4       // D4
#define MAINS_SWITCH_PIN        2       // D5
#define LIGHT_LEVEL_PIN         A0      // A0
#define BUTTON_PIN              13      // D0
#define TEMPERATURE_PIN         false   // TBD
#define HUMIDITY_PIN            false   // TBD


/* SWITCH SENSING */
uint8_t sense_avg_index = 0;
const uint8_t SENSE_AVG_MAX_SAMPLES = 50;
bool sense_avg[SENSE_AVG_MAX_SAMPLES];
bool lastSwitchState = false;


/* LOAD SWITCHING */
bool powerState = 0;
bool lastPowerState = 0;


/* NON-BLOCKING EVENT TIMERS  */
uint64_t lastBroadcast = 0;
uint32_t startPressDuration = 0;
uint32_t pressDuration = 0;

const uint32_t shortPressDuration = 500;
const uint32_t middlePressDuration = 5000;
const uint32_t longPressDuration = 10000;



WiFiClient socket;
PubSubClient network(socket);
StatusLED LED(STATUS_LED_PIN);
WiFiManager wifiManager;