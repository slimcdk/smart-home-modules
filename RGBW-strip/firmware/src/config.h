

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
char CHIP_ID[80];
char DEVICE_ID[80];
char DEVICE_ID_TYPE[80];
char DEVICE_ID_AP[80];



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
#define LED_PIN   4
#define LED_COUNT 300
 





/*** NETWORK ***/
bool should_save_config = false;
uint64_t last_reconnect_attempt = 0;
//char deviceLocation[33] = DEVICE_LOCATION;
const char* mqtt_server = MQTT_SERVER;
const char* mqtt_port = MQTT_SERVER_PORT;
const char* mqtt_username = MQTT_USER;
const char* mqtt_password = MQTT_PSK;
//WiFiManagerParameter c_device_name("device_name", "Device name", deviceLocation, 64);
WiFiManagerParameter c_mqtt_server("server", "MQTT server", mqtt_server, 64);
WiFiManagerParameter c_mqtt_port("port", "MQTT port", mqtt_port, 8);
WiFiManagerParameter c_mqtt_username("user", "MQTT username", mqtt_username, 64);
WiFiManagerParameter c_mqtt_password("pass", "MQTT password", mqtt_password, 64, "type='password'");
WiFiClient socket;
PubSubClient mqtt(socket);
WiFiManager wifiManager;


/*** LOAD DIMMING ***/
bool power_state = 0;
bool last_power_state = 0;


/*** NON-BLOCKING EVENT TIMERS  ***/
uint64_t last_broadcast = 0;
