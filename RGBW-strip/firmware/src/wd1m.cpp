

#include <Adafruit_NeoPixel.h>

#include <config.h>


Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


/* WIFI MANAGER CALLBACK */
void configModeCallback (WiFiManager *myWiFiManager) {
  //WiFi.softAPIP();
  should_save_config = true;
}


/* MQTT BROADCASTS */
void callback(char* topic, byte* payload, unsigned int length) {

  if ( strcmp(topic, MQTT_OUTPUT_LOAD) == 0 ) {

    // deserialize JSON message
    const size_t _capacity = JSON_OBJECT_SIZE(1);
    DynamicJsonDocument doc(_capacity);
    deserializeJson(doc, payload);
  }
}

// general method for publishing sensor data
void publishSensorData(const char* topic, uint16_t _data){
  const uint16_t _capacity = JSON_OBJECT_SIZE(3);
  DynamicJsonDocument data(_capacity);

  //data["timestamp"] = 0;
  data["data"] = _data;
  //data["uptime"] = millis();

  char buffer[MQTT_MAX_PACKET_SIZE];
  uint16_t n = serializeJson(data, buffer);
  mqtt.publish(topic, buffer, n);
}

void publishDeviceHealth() {
  const uint16_t _capacity = JSON_OBJECT_SIZE(3);
  DynamicJsonDocument data(_capacity);

  data["uptime"] = millis() / 1000;
  data["current_issue"] = 0;

  char buffer[MQTT_MAX_PACKET_SIZE];
  uint16_t n = serializeJson(data, buffer);
}

void publishAllData() {
  // broadcast device health and sensor readings
  //publishSensorData(MQTT_OUTPUT_LOAD,   readPowerState() );

}

// create checkin report
void mqttCheckin() {
  const uint16_t _capacity = JSON_OBJECT_SIZE(8);
  DynamicJsonDocument report(_capacity);
  
  // structure of data 
  report["type"]        = DEVICE_TYPE;
  report["position"]    = DEVICE_POSIITON;
  report["location"]    = DEVICE_LOCATION;
  report["id"]          = CHIP_ID;
  report["version"]     = VERSION_N;
  report["uptime"]      = millis() / 1000;
  report["base_topic"]  = MQTT_ROOT;
  
  // transmit topic
  char buffer[MQTT_MAX_PACKET_SIZE];
  uint16_t n = serializeJson(report, buffer);
  mqtt.publish(MQTT_CHECKIN_REPORT, buffer, n);
}

// listen to topics
void mqttListen() {
  mqtt.subscribe(MQTT_OUTPUT_LOAD);
  mqtt.subscribe(MQTT_ROOT);
}

// reconnect to broker
boolean mqttReconnect() {
  if (mqtt.connect(DEVICE_ID, c_mqtt_username.getValue(), c_mqtt_password.getValue())) {
    mqttCheckin();
    mqttListen();
  }
  return mqtt.connected();
}


void setup() {


    /* ARDUINO 'OVER THE AIR' CONFIGURATION */
    ArduinoOTA.onStart( []() { });
    ArduinoOTA.onProgress( [](unsigned int progress, unsigned int total) { });
    ArduinoOTA.onEnd( []() { });
    ArduinoOTA.begin();


    // Create identifiers
    sprintf(CHIP_ID,      "ESP%d",        ESP.getChipId() );
    sprintf(DEVICE_ID,    "%s:%s:ESP%d",  DEVICE_LOCATION, DEVICE_POSIITON, CHIP_ID );
    sprintf(DEVICE_ID_AP, "%s-AP",        DEVICE_ID );
    sprintf(DEVICE_ID_TYPE, "%s:%s",      DEVICE_ID, CHIP_ID );

    /* WIFI CONNECTION CONFIGURATION */
    WiFi.hostname( DEVICE_ID );
    wifiManager.setAPCallback(configModeCallback);
    //wifiManager.addParameter(&c_device_location);
    wifiManager.addParameter(&c_mqtt_server);
    wifiManager.addParameter(&c_mqtt_port);
    wifiManager.addParameter(&c_mqtt_username);
    wifiManager.addParameter(&c_mqtt_password);

    if( !wifiManager.autoConnect(DEVICE_ID_AP) ) {

        delay(1000);
        ESP.reset();
    }

    /* MQTT CONFIGURATION */
    String _port = String(c_mqtt_port.getValue());
    mqtt.setServer(c_mqtt_server.getValue(), _port.toInt());
    mqtt.setCallback(callback);
    while ( !mqtt.connected() ) {
    if ( !mqtt.connect(DEVICE_ID, c_mqtt_username.getValue(), c_mqtt_password.getValue()) ) {
        delay(1000);
        ESP.reset();
    }
    }
    mqttCheckin();
    mqttListen();
    last_reconnect_attempt = 0;

    strip.begin();

    for(int i = 0; i < LED_COUNT; i++){
        strip.setPixelColor(i, 0, 0, 0);
    }

    strip.show();
}


void loop() {

}

