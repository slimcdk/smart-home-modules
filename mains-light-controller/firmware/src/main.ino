/*
  main.ino
  Created by Christian S. Skjerning, June 18, 2019.
  Released into the public domain.
*/


#include "conf.h"


void setup() {
  Serial.begin(9600);
  LED.init();

  /* IO CONFIGURATION */
  pinMode(MAINS_SWITCH_PIN, INPUT);
  pinMode(LIGHT_LEVEL_PIN, INPUT);
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

  ArduinoOTA.setHostname(DEVICE_TYPE DEVICE_ID);
  ArduinoOTA.begin();

 
  /* WIFI CONNECTION CONFIGURATION */
  WiFi.hostname(WIFI_HOSTNAME /*":"+ESP.getChipId()*/);
  //wifiManager.resetSettings();
  wifiManager.setAPCallback(configModeCallback);

  wifiManager.addParameter(&custom_mqtt_server);
  wifiManager.addParameter(&custom_mqtt_port);
  wifiManager.addParameter(&custom_mqtt_username);
  wifiManager.addParameter(&custom_mqtt_password);

  if(!wifiManager.autoConnect(WIFI_AP_NAME /*":" + String(ESP.getChipId())*/ )) {
    LED.code(LED.WARNING);
    delay(1000);
    ESP.reset();
  }

  String _port = String( custom_mqtt_port.getValue() );

  Serial.println("GOT INFO");
  Serial.println( custom_mqtt_server.getValue() );
  Serial.println( custom_mqtt_port.getValue() );
  Serial.println( _port.toInt() );
  Serial.println( custom_mqtt_username.getValue() );
  Serial.println( custom_mqtt_password.getValue() );


  /* MQTT CONFIGURATION */
  network.setServer(custom_mqtt_server.getValue(), _port.toInt());
  //network.setServer(MQTT_SERVER, MQTT_SERVER_PORT);
  network.setCallback(callback);
 
  while (!network.connected()) {
    if (network.connect(DEVICE_ID, custom_mqtt_username.getValue(), custom_mqtt_password.getValue())) {
      LED.code(LED.WARNING);
    } else {
      LED.code(LED.WARNING);
      delay(1000);
      ESP.reset();
    }
  }

  // create checkin report for available topics
  const uint16_t _capacity = JSON_OBJECT_SIZE(6+3+2+2+2+2+2) + JSON_ARRAY_SIZE(6);
  DynamicJsonDocument report(_capacity);

  report["device"] = DEVICE_TYPE;
  report["id"] = DEVICE_ID;
  report["timestamp"] = 0;
  report["status"] = "on";
  report["version"] = VERSION_N;
  
  JsonArray topics = report.createNestedArray("topics");
    
  // output / load
  JsonObject load = topics.createNestedObject();
  load["type"] = "load";
  load["set"] = MQTT_LOAD_SUB;
  load["get"] = MQTT_LOAD_PUB;
  
  // mains switch
  JsonObject sw = topics.createNestedObject();
  sw["type"] = "switch";
  sw["get"] = MQTT_SWITCH_PUB;

  // light level
  JsonObject ll = topics.createNestedObject();
  ll["type"] = "light_level";
  ll["get"] = MQTT_LIGHT_LEVEL_PUB;

  // temperature
  JsonObject temperature = topics.createNestedObject();
  temperature["type"] = "temperature";
  temperature["get"] = MQTT_TEMPERATURE_PUB;

  // humidity
  JsonObject humidity = topics.createNestedObject();
  humidity["type"] = "humidity";
  humidity["get"] = MQTT_HUMIDITY_PUB;

  // button
  JsonObject button = topics.createNestedObject();
  button["type"] = "button";
  button["get"] = MQTT_BUTTON_PUB;

  // transmit topic
  char buffer[MQTT_MAX_PACKET_SIZE];
  uint16_t n = serializeJson(report, buffer);
  network.publish(MQTT_CHECKIN_REPORT, buffer, n);

  // listen to topics
  network.subscribe(MQTT_LOAD_SUB);
  network.subscribe(MQTT_ROOT);
  network.subscribe(MQTT_DEVICE_HEALTH);
}


/* WIFI MANAGER CALLBACK */
void configModeCallback (WiFiManager *myWiFiManager) {
  WiFi.softAPIP();
  shouldSaveConfig = true;
}



void loop() {
  ArduinoOTA.handle();
  network.loop();
  LED.code(LED.GOOD);

  bool sw = senseSwitch();

  
    // stage change event
  if (sw != lastSwitchState) {
    lastSwitchState = sw;
    powerState = (powerState + 1) % 2;
  }


  // toggle output and MQTT broadcast event
  if (powerState != lastPowerState) {
    lastPowerState = powerState;
    setOutput(powerState);
    //broadcastOutput(powerState);
    publishSensorData(MQTT_LOAD_PUB, powerState);
  }


  // broadcast every 1 min interval
  if ( (millis() - lastBroadcast) > 1000*10 ) {
    lastBroadcast = millis();
    publishAllData();
  }

/*
  startPressDuration = millis();
  while ( readButton() ) { 
    Serial.println(millis() - startPressDuration); 
    network.loop();  
  }
  pressDuration = millis() - startPressDuration;


  if ( pressDuration > 1 ) {
    if (pressDuration <= shortPressDuration)
    {
      
    } 
    else if (pressDuration <= middlePressDuration)
    {
      Serial.println("reset");
      ESP.reset();
    } 
    else if (pressDuration <= longPressDuration)
    {      
      Serial.println("restart");
      wifiManager.resetSettings();
      ESP.restart();
    }
    else 
    {
    }
  }
  else 
  {
  }
*/
}





/* IO INTERACTIONS */
bool senseSwitch() {

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

  if ( strcmp(topic, MQTT_LOAD_SUB) == 0 ) {

    // deserialize JSON message
    const size_t _capacity = JSON_OBJECT_SIZE(1);
    DynamicJsonDocument doc(_capacity);
    deserializeJson(doc, payload);

    powerState = doc["data"];
    publishAllData();
  }

  if ( strcmp(topic, MQTT_DEVICE_HEALTH) == 0 ) {
    
  }

  if ( strcmp(topic, MQTT_STATUS_LED_SUB) == 0 ) {

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
  network.publish(topic, buffer, n);
}

void publishDeviceHealth() {
  const uint16_t _capacity = JSON_OBJECT_SIZE(2);
  DynamicJsonDocument data(_capacity);

  data["timestamp"] = 0;

  char buffer[MQTT_MAX_PACKET_SIZE];
  uint16_t n = serializeJson(data, buffer);
  network.publish(MQTT_DEVICE_HEALTH, buffer, n);
}

void publishAllData() {
  // broadcast device health and sensor readings
  publishDeviceHealth();
  publishSensorData(MQTT_SWITCH_PUB,        senseSwitch() );
  publishSensorData(MQTT_LIGHT_LEVEL_PUB,   readLightLevel() );
  publishSensorData(MQTT_LOAD_PUB,          readPowerState() );
  publishSensorData(MQTT_TEMPERATURE_PUB,   readTemperature() );
  publishSensorData(MQTT_HUMIDITY_PUB,      readHumidity() );
}




/* UNUSED
void setOutput(uint8_t _percent) {

  // constrain and map values
  uint8_t _p = constrain(_percent, 0, 100);
  uint8_t _l = map(_p, 0, 100, 0, 255);
  uint8_t _level = constrain(_l, 0, 255);

  analogWrite(OUTPUT_LOAD_PIN, _level);
}
*/