
/*
  config.h
  Created by Christian S. Skjerning, Aug 18, 2019.
  Released into the public domain.
*/

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

/*
const char* getMac(){
  return ( "ESP" + String( ESP.getChipId()) ).c_str();
}*/


/** DEVICE CONFIGURATION **/
#define VERSION_MAJOR               0
#define VERSION_MINOR               0
#define VERSION_PATCH               0
#define FW_VERSION                  STR(VERSION_MAJOR) "." STR(VERSION_MINOR) "." STR(VERSION_PATCH)

std::string DEVICE_TYPE             = "slimc-rgbw";
std::string MAC_ADDRESS             = "ESP11674575";  
std::string DEVICE_AP;


/** MQTT **/
std::string MQTT_SERVER             = "hassio.local";
std::string MQTT_SERVER_PORT        = "1883";
std::string MQTT_USER               = "slimc-device";
std::string MQTT_PSK                = "0123456789";
WiFiManagerParameter                c_mqtt_server   ("Server",  "server",      MQTT_SERVER.c_str(), 64);
WiFiManagerParameter                c_mqtt_port     ("Port",    "port",        MQTT_SERVER_PORT.c_str(), 8);
WiFiManagerParameter                c_mqtt_username ("Username",    "username",    MQTT_USER.c_str(), 64);
WiFiManagerParameter                c_mqtt_password ("Password",    "password",    MQTT_PSK.c_str(), 64, "type='password'");

std::string MQTT_COMMAND_SUFFIX     = "cmnd";
std::string MQTT_STATUS_SUFFIX      = "stat";
std::string MQTT_CHECKIN_REPORT     = "device/checkin";
std::string MQTT_ROOT               = DEVICE_TYPE + "/" + MAC_ADDRESS;
std::string MQTT_RGBW_POWER         = MQTT_ROOT + "/" + "POWER";
std::string MQTT_RGBW_COLOR         = MQTT_ROOT + "/" + "COLOR";
std::string MQTT_RGBW_BRIGHTNESS    = MQTT_ROOT + "/" + "BRIGHTNESS";



/** NETWORK **/
WiFiClient                          socket;
PubSubClient                        mqtt(socket);
WiFiManager                         wifiManager;
bool should_save_config             = false;
uint64_t last_reconnect_attempt     = 0;


/** HARDWARE **/    
#define LED_PIN                     4
#define LED_COUNT                   230
Adafruit_NeoPixel                   strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


/** TIMERS  **/
uint64_t last_broadcast             = 0;
float n = 0;