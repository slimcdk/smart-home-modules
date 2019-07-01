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
#define VERSION_N               001
#define DEVICE_TYPE             "mains-light-controller"
#define DEVICE_ID               "ceiling-light"
#define DEVICE_LOCATION         "living-room"


/* WIFI */
#define WIFI_AP_NAME            DEVICE_ID "-AP"
#define WIFI_HOSTNAME           DEVICE_TYPE ":" DEVICE_ID

/* MQTT */
#define MQTT_SERVER             "hassio.local"
#define MQTT_SERVER_PORT        "1883"
#define MQTT_USER               "esp-device"
#define MQTT_PSK                "DankMemes420"

#define MQTT_CHECKIN_REPORT     "device/checkin"
#define MQTT_ROOT               "home/living/ceiling"
#define MQTT_DEVICE_HEALTH      MQTT_ROOT "/device-health"
#define MQTT_OUTPUT_LOAD        MQTT_ROOT "/output"
#define MQTT_SWITCH             MQTT_ROOT "/switch"
#define MQTT_LIGHT_LEVEL        MQTT_ROOT "/lightlevel"
#define MQTT_TEMPERATURE        MQTT_ROOT "/temperature"
#define MQTT_BUTTON             MQTT_ROOT "/button"
#define MQTT_HUMIDITY           MQTT_ROOT "/humidity"
#define MQTT_STATUS_LED         MQTT_ROOT "/statusled"


/* HARDWARE CONFIGURATION */    // BB   // PCB config
#define STATUS_LED_PIN          0       // D2
#define OUTPUT_LOAD_PIN         4       // D4
#define MAINS_SWITCH_PIN        2       // D5
#define LIGHT_LEVEL_PIN         A0      // A0
#define BUTTON_PIN              13      // D0
#define TEMPERATURE_PIN         false   // TBD
#define HUMIDITY_PIN            false   // TBD




/* NETWORK */
WiFiClient socket;
PubSubClient network(socket);
WiFiManager wifiManager;
bool shouldSaveConfig = false;
uint64_t lastReconnectAttempt = 0;
char mqtt_server[64] = MQTT_SERVER;
char mqtt_port[64] = MQTT_SERVER_PORT;
char mqtt_username[64] = MQTT_USER;
char mqtt_password[64] = MQTT_PSK;
WiFiManagerParameter custom_mqtt_server("server", "MQTT server", mqtt_server, 64);
WiFiManagerParameter custom_mqtt_port("port", "MQTT port", mqtt_port, 64);
WiFiManagerParameter custom_mqtt_username("user", "MQTT username", mqtt_username, 64);
WiFiManagerParameter custom_mqtt_password("pass", "MQTT password", mqtt_password, 64, "type='password'");



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



/* MISC */
StatusLED LED(STATUS_LED_PIN);