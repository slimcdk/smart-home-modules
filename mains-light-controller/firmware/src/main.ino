/*
  main.ino
  Created by Christian S. Skjerning, June 18, 2019.
  Released into the public domain.
*/


#include "conf.h"




void setup() {
  LED.init();

  /* IO CONFIGURATION */
  pinMode(SWITCH_SENSE_PIN, INPUT);
  pinMode(LIGHT_LEVEL_SENSE_PIN, INPUT);
  pinMode(OUTPUT_LOAD_PIN, OUTPUT);

  /* ARDUINO 'OVER THE AIR' CONFIGURATION */
  ArduinoOTA.onStart( []() {
    LED.code(LED.NEUTRAL);
  });

  ArduinoOTA.onProgress( [](unsigned int progress, unsigned int total) {
    LED.code(LED.BUSY);
  });

  ArduinoOTA.onEnd( []() {
    LED.code(LED.GOOD);
  });

  ArduinoOTA.setHostname(DEVICE_ID);
  ArduinoOTA.begin();


  /* WIFI CONNECTION CONFIGURATION */
  WiFiManager wifiManager;
  wifiManager.setAPCallback(configModeCallback);
  if(!wifiManager.autoConnect()) {
    LED.code(LED.WARNING);
    delay(1000);
    ESP.reset();
  }



  /* MQTT CONFIGURATION */
  network.setServer(MQTT_ADDRESS, MQTT_SERVER_PORT);
  network.setCallback(callback);
 
  while (!network.connected()) {
    if (network.connect(DEVICE_ID, MQTT_USER, MQTT_PSK )) {
      LED.code(LED.WARNING);
    } else {
      LED.code(LED.WARNING);
      delay(1000);
      ESP.reset();
    }
  }

  // create checkin report for available topics
  const uint16_t capacity = JSON_OBJECT_SIZE(6+3+2+2+2+2+2) + JSON_ARRAY_SIZE(6);
  
  DynamicJsonDocument report(capacity);
  report["device"] = DEVICE_TYPE;
  report["id"] = DEVICE_ID;
  report["timestamp"] = millis();
  report["status"] = "on";
  report["version"] = VERSION_N;
  
  JsonArray topics = report.createNestedArray("topics");
    
  // output / load
  JsonObject load = topics.createNestedObject();
  load["type"] = "load";
  load["set"] = MQTT_LOAD_SET;
  load["get"] = MQTT_LOAD_GET;
  
  // mains switch
  JsonObject sw = topics.createNestedObject();
  sw["type"] = "switch";
  sw["get"] = MQTT_SWITCH_GET;

  // light level
  JsonObject ll = topics.createNestedObject();
  ll["type"] = "light_level";
  ll["get"] = MQTT_LIGHT_LEVEL_GET;

  // temperature
  JsonObject temperature = topics.createNestedObject();
  temperature["type"] = "temperature";
  temperature["get"] = MQTT_TEMPERATURE_GET;

  // humidity
  JsonObject humidity = topics.createNestedObject();
  humidity["type"] = "humidity";
  humidity["get"] = MQTT_HUMIDITY_GET;

  // button
  JsonObject button = topics.createNestedObject();
  button["type"] = "button";
  button["get"] = MQTT_BUTTON_GET;

  // transmit topic
  char buffer[MQTT_MAX_PACKET_SIZE];
  size_t n = serializeJson(report, buffer);
  network.publish(MQTT_CHECKIN_REPORT, buffer, n);

  // listen to topics
  network.subscribe(MQTT_LOAD_SET);
  network.subscribe(MQTT_ROOT);
}


/* WIFI MANAGER CALLBACK */
void configModeCallback (WiFiManager *myWiFiManager) {
  WiFi.softAPIP();
}






void loop() {
  ArduinoOTA.handle();
  network.loop();
  LED.code(LED.GOOD);

  // stage change event
  bool sw = senseSwitch();
  if (sw != lastSwitchState) {
    lastSwitchState = sw;
    powerState = (powerState + 1) % 2;
  }


  if (powerState != lastPowerState) {
    lastPowerState = powerState;
    setOutput(powerState);
    broadcastOutput(powerState);
  }


}


void setOutput(bool _power) {
  digitalWrite(OUTPUT_LOAD_PIN, _power);
}

bool senseSwitch() {

  // running average
  sense_avg[sense_avg_index] = !digitalRead(SWITCH_SENSE_PIN);
  sense_avg_index = (sense_avg_index + 1) % SENSE_AVG_MAX_SAMPLES;
  
  // sum current measurements
  uint8_t _sense_sum = 0;
  for (int i = 0; i < SENSE_AVG_MAX_SAMPLES; i++) _sense_sum += sense_avg[i];
  
  // determine if power switch is on
  return _sense_sum > 0;
}



/* MQTT BROADCASTS */
void callback(char* topic, byte* payload, unsigned int length) {

  if ( strcmp(topic, MQTT_LOAD_SET) == 0 ) {

    // deserialize JSON message
    const size_t capacity = JSON_OBJECT_SIZE(2) + 20;
    DynamicJsonDocument doc(capacity);
    deserializeJson(doc, payload);

    powerState = doc["output"];; //(powerState + 1) % 2; 
  }
}


void broadcastOutput(bool _power){

  const size_t capacity = JSON_OBJECT_SIZE(1);
  DynamicJsonDocument doc(capacity);

  doc["output"] = _power;

  char buffer[MQTT_MAX_PACKET_SIZE];
  size_t n = serializeJson(doc, buffer);
  network.publish(MQTT_LOAD_GET, buffer, n);
}





/*
void setOutput(uint8_t _percent) {

  // constrain and map values
  uint8_t _p = constrain(_percent, 0, 100);
  uint8_t _l = map(_p, 0, 100, 0, 255);
  uint8_t _level = constrain(_l, 0, 255);

  analogWrite(OUTPUT_LOAD_PIN, _level);
}
*/