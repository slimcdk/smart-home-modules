#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#ifndef STASSID
  #define STASSID "SuperNetty"
  #define STAPSK  "DankMemes420"
#endif


#define MAINS_SENSE_PIN 2
#define MAINS_SWITCHING_PIN 4

const char* ssid = STASSID;
const char* password = STAPSK;


int sense_avg_index = 0;
const int SENSE_AVG_MAX_SAMPLES = 10;
int sense_avg[SENSE_AVG_MAX_SAMPLES];

bool power = 0;
int power_level = power * 255;




void setup() {
  Serial.begin(115200);
  Serial.println("Booting");


  /* IO CONFIGURATION */
  Serial.println("Setting up IO pins");
  pinMode(MAINS_SENSE_PIN, INPUT);
  pinMode(MAINS_SWITCHING_PIN, OUTPUT);

  Serial.println("IO configured");


  /* VARIABLE ASSIGNMENTS */
    Serial.println("Configuring variables");
  // Setting sensing to 'Off'
  for (int i = 0; i < SENSE_AVG_MAX_SAMPLES; i++) 
  {
    sense_avg[i] = 0;
  }

  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);


  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  ArduinoOTA.setHostname("/home/room/living/light/main");


  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });


  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });


  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });


  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });


  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();


    power = senseMainsLight();
    //Serial.println(power ? "Power: On" : "Power: Off");

    // Slowley adjust output
    int scale = power ? 1 : -1;
    power_level = constrain(power_level += scale, 0, 255);
    analogWrite(MAINS_SWITCHING_PIN, power_level);

    Serial.println(power_level);

}





bool senseMainsLight() {

  // Sense and store value in array with 'running index'
  sense_avg[sense_avg_index] = !digitalRead(MAINS_SENSE_PIN);

  // Calculate average
  int _sense_sum = 0;
  for (int i = 0; i < SENSE_AVG_MAX_SAMPLES; i++) 
  {
    _sense_sum += sense_avg[i];
  }

  // Increment and wrap 'running index'
  sense_avg_index = (sense_avg_index + 1) % SENSE_AVG_MAX_SAMPLES;

  // Determine if power is present
  return _sense_sum > 0;
}