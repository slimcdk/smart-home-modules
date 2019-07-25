/*
  main.ino
  Created by Christian S. Skjerning, June 18, 2019.
  Released into the public domain.
*/


#include "conf.h"


void setup() {
  LED.init();


  /* IO CONFIGURATION */
  pinMode(MAINS_SWITCH_PIN, INPUT);
  pinMode(LIGHT_LEVEL_PIN, INPUT);
  pinMode(OUTPUT_LOAD_PIN, OUTPUT);


  /* ARDUINO 'OVER THE AIR' CONFIGURATION */
  ArduinoOTA.onStart( []() {
    //LED.code(LED.NEUTRAL);
  });
  ArduinoOTA.onProgress( [](unsigned int progress, unsigned int total) {
    //LED.code(LED.BUSY);
  });
  ArduinoOTA.onEnd( []() {
    //LED.code(LED.GOOD);
  });
  // ArduinoOTA.setHostname( DEVICE_ID + String(ESP.getChipId()) );
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
    LED.code(LED.WARNING);
    delay(1000);
    ESP.reset();
  }

  /* MQTT CONFIGURATION */
  String _port = String(c_mqtt_port.getValue());
  mqtt.setServer(c_mqtt_server.getValue(), _port.toInt());
  mqtt.setCallback(callback);
  while ( !mqtt.connected() ) {
    if ( !mqtt.connect(DEVICE_ID, c_mqtt_username.getValue(), c_mqtt_password.getValue()) ) {
      //LED.code(LED.WARNING);
      delay(1000);
      ESP.reset();
    }
  }
  mqttCheckin();
  mqttListen();
  lastReconnectAttempt = 0;
}


/* WIFI MANAGER CALLBACK */
void configModeCallback (WiFiManager *myWiFiManager) {
  //WiFi.softAPIP();
  shouldSaveConfig = true;
}

void loop() {
  //LED.code(LED.GOOD);
  ArduinoOTA.handle();

  // check MQTT network status
  if (!mqtt.connected()) {
    if (millis() - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = millis();
      if (mqttReconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    mqtt.loop();
  }


  bool sw = readMainsSwitch();

  // stage change event
  if (sw != lastSwitchState) {
    lastSwitchState = sw;
    powerState = (powerState + 1) % 2;
    publishSensorData(MQTT_OUTPUT_LOAD, readPowerState());
  }

  setOutput(powerState);

  // broadcast every 1 min interval
  if ( (millis() - lastBroadcast) > 1000*5 ) {
    lastBroadcast = millis();
    publishAllData();
  }

/*
  if (readButton()) {
    //LED.code(LED.WARNING);
    if ( millis() - startPressDuration > 5000) {
      wifiManager.resetSettings();
      ESP.restart();
      delay(1000);
    }
  } else {
    startPressDuration = millis();
  }
  */
}


/* IO INTERACTIONS */
bool readMainsSwitch() {

  // running average
  sense_avg[sense_avg_index] = !digitalRead(MAINS_SWITCH_PIN);
  sense_avg_index = (sense_avg_index + 1) % SENSE_AVG_MAX_SAMPLES;
  
  // sum current measurements
  uint8_t _sense_sum = 0;
  for (int i = 0; i < SENSE_AVG_MAX_SAMPLES; i++) _sense_sum += sense_avg[i];

  // determine if power switch is on
  return _sense_sum > 0;
}

uint8_t readLightLevel () {
  return map(analogRead(LIGHT_LEVEL_PIN), 0, 1023, 0, 100);
}

uint8_t readTemperature () {
  return analogRead(TEMPERATURE_PIN);
}

uint8_t readHumidity () {
  return analogRead(HUMIDITY_PIN);
}

uint8_t readPowerState () {
  return powerState;
}

bool readButton() {
  return digitalRead(BUTTON_PIN);
}

// open for mains current
void setOutput(bool _power) {
  digitalWrite(OUTPUT_LOAD_PIN, _power);
}



/* MQTT BROADCASTS */
void callback(char* topic, byte* payload, unsigned int length) {

  if ( strcmp(topic, MQTT_OUTPUT_LOAD) == 0 ) {

    // deserialize JSON message
    const size_t _capacity = JSON_OBJECT_SIZE(1);
    DynamicJsonDocument doc(_capacity);
    deserializeJson(doc, payload);

    powerState = doc["data"];
    publishAllData();
  }

  if ( strcmp(topic, MQTT_DEVICE_HEALTH) == 0 ) {
    
  }

  if ( strcmp(topic, MQTT_STATUS_LED) == 0 ) {

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
  mqtt.publish(MQTT_DEVICE_HEALTH, buffer, n);
}

void publishAllData() {
  // broadcast device health and sensor readings
  publishDeviceHealth();
  publishSensorData(MQTT_SWITCH,        readMainsSwitch() );
  publishSensorData(MQTT_LIGHT_LEVEL,   readLightLevel() );
  //publishSensorData(MQTT_OUTPUT_LOAD,   readPowerState() );
  publishSensorData(MQTT_TEMPERATURE,   readTemperature() );
  publishSensorData(MQTT_HUMIDITY,      readHumidity() );
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
  mqtt.subscribe(MQTT_DEVICE_HEALTH);
}

// reconnect to broker
boolean mqttReconnect() {
  if (mqtt.connect(DEVICE_ID, c_mqtt_username.getValue(), c_mqtt_password.getValue())) {
    mqttCheckin();
    mqttListen();
  }
  return mqtt.connected();
}