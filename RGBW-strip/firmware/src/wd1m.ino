
/*
  wd1m.cpp
  Created by Christian S. Skjerning, Aug 18, 2019.
  Released into the public domain.
*/


#include <config.h>



void configModeCallback (WiFiManager *myWiFiManager) {
  should_save_config = true;
}


void callback(char* topic, byte* payload, unsigned int length) {

    if ( strcmp(topic, MQTT_RGBW_POWER.c_str() ) == 0 ) {
        const size_t _capacity = JSON_OBJECT_SIZE(1);
        DynamicJsonDocument doc(_capacity);
        deserializeJson(doc, payload);


        doc["power"] 


    }
}


// create checkin report
void mqttCheckin() {
  const uint16_t _capacity = 4*JSON_OBJECT_SIZE(4) + 3*JSON_OBJECT_SIZE(7);  
  DynamicJsonDocument _report(_capacity);
  
  // data structure
  _report["device"]       = DEVICE_TYPE.c_str();
  _report["mac"]          = MAC_ADDRESS.c_str();
  _report["fw_version"]   = FW_VERSION;
  _report["ip"]           = WiFi.localIP().toString();

  JsonObject _topics      = _report.createNestedObject("topics");
  _topics["base"]         = MQTT_ROOT.c_str();

  JsonObject _suffix      = _topics.createNestedObject("suffix");
  _suffix["command"]      = MQTT_COMMAND_SUFFIX.c_str();
  _suffix["status"]       = MQTT_STATUS_SUFFIX.c_str();

  JsonObject _power       = _topics.createNestedObject("power");
  _power["type"]          = "switch";
  _power["topic"]         = MQTT_RGBW_POWER.c_str() + String(":<suffix>");

  JsonObject _color       = _topics.createNestedObject("color");
  _color["type"]          = "hue";
  _color["topic"]         = MQTT_RGBW_COLOR.c_str() + String(":<suffix>");

  JsonObject _brightness  = _topics.createNestedObject("brightness");
  _brightness["type"]     = "dimming";
  _brightness["topic"]    = MQTT_RGBW_BRIGHTNESS.c_str() + String(":<suffix>");

  // transmit topic
  char buffer[MQTT_MAX_PACKET_SIZE];
  uint16_t n = serializeJson(_report, buffer);
  mqtt.publish(MQTT_CHECKIN_REPORT.c_str(), buffer, n);
}



// listen to topics
void mqttListen() {
  mqtt.subscribe( (MQTT_RGBW_POWER + "/" + MQTT_COMMAND_SUFFIX).c_str() );
  mqtt.subscribe( (MQTT_RGBW_COLOR + "/" + MQTT_COMMAND_SUFFIX).c_str() );
  mqtt.subscribe( (MQTT_RGBW_BRIGHTNESS + "/" + MQTT_COMMAND_SUFFIX).c_str() );
}



// reconnect to broker
boolean mqttReconnect() {
  if (mqtt.connect(MAC_ADDRESS.c_str(), c_mqtt_username.getValue(), c_mqtt_password.getValue())) {
    mqttCheckin();
    mqttListen();
  }
  return mqtt.connected();
}


void setup() {

  Serial.begin(115200);
  

  /* ARDUINO 'OVER THE AIR' CONFIGURATION */
/*
  ArduinoOTA.onStart( []() { 

  });
  ArduinoOTA.onProgress( [](unsigned int progress, unsigned int total) { 

  });
  ArduinoOTA.onEnd( []() { 

  });
  ArduinoOTA.begin();
 */

  MAC_ADDRESS = ( "ESP" + String( ESP.getChipId()) ).c_str();
  DEVICE_AP   = ( DEVICE_TYPE + ":" + MAC_ADDRESS + "-AP" ).c_str();

  /* WIFI CONNECTION CONFIGURATION */
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.addParameter(&c_mqtt_server);
  wifiManager.addParameter(&c_mqtt_port);
  wifiManager.addParameter(&c_mqtt_username);
  wifiManager.addParameter(&c_mqtt_password);

  if( !wifiManager.autoConnect(DEVICE_AP.c_str()) ) {
      delay(1000);
      ESP.reset();
  }


  /* MQTT CONFIGURATION */
  String _port = String(c_mqtt_port.getValue());
  mqtt.setServer(c_mqtt_server.getValue(), _port.toInt());
  mqtt.setCallback(callback);

  while ( !mqtt.connected() ) {
      if ( !mqtt.connect( MAC_ADDRESS.c_str(), c_mqtt_username.getValue(), c_mqtt_password.getValue()) ) {
          delay(1000);
          ESP.reset();
      }
  }

  mqttListen();
  mqttCheckin();
  last_reconnect_attempt = 0;


  strip.begin();
  for(int i = 0; i < LED_COUNT; i++){
      strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
}




void loop() {
  //ArduinoOTA.handle();

  if (!mqtt.connected()) {
    if (millis() - last_reconnect_attempt > 5000) {
      if (mqttReconnect()) {
        last_reconnect_attempt = 0;
      }
    }
  } else {
    mqtt.loop();
  }


  strip.setPixelColor((int)n, random(255), random(255), random(255), 10);
  strip.show();

}


