// Public libraries
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include <Adafruit_NeoPixel.h>

// Custom libaries
#include <StatusLED.h>


// Nwtwork configuration
#define WIFI_SSID               "SuperNetty"
#define WIFI_PSK                "DankMemes420"
#define MQTT_ADDRESS            "192.168.123.17"
#define MQTT_SERVER_PORT        1883
#define MQTT_USER               "esp-ceiling-light"
#define MQTT_PSK                "DankMemes420"

// Structure                    "{bulding}/{room}/{location}/{type}"
#define MQTT_TOPIC              "home/living/ceiling/light"



// Hardware configuration
#define SWITCH_SENSE_PIN        2
#define MAINS_SWITCHING_PIN     4
#define STATUS_LED_PIN          0
#define LIGHT_LEVEL_SENSE_PIN   A0


// Data structure for publishing information
struct publish_data {
  //int temperature;
  int light_level;
  int switch_state;
  int power_level;
};


WiFiClient socket;
PubSubClient network(socket);
StatusLED statusLED(STATUS_LED_PIN);


// Switch sensing
#ifdef SWITCH_SENSE_PIN
  uint8_t sense_avg_index = 0;
  const uint8_t SENSE_AVG_MAX_SAMPLES = 50;
  bool sense_avg[SENSE_AVG_MAX_SAMPLES];
#endif


// Load power switching
#ifdef MAINS_SWITCHING_PIN
  bool power = 0;
  int power_level = power * 255;
#endif


// For flashing status LED
unsigned long previousMillis = 0;
const long FLASH_INTERVAL = 80;
bool flash = false;



void setup() {
  Serial.begin(115200);
  statusLED.init();

  /* IO CONFIGURATION */
  pinMode(SWITCH_SENSE_PIN, INPUT);
  pinMode(LIGHT_LEVEL_SENSE_PIN, INPUT);
  pinMode(MAINS_SWITCHING_PIN, OUTPUT);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PSK);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    //// Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }


  network.setServer(MQTT_ADDRESS, MQTT_SERVER_PORT);
  network.setCallback(callback);
 
  while (!network.connected()) {
    // Serial.println("Connecting to MQTT...");
 
    if (network.connect("ESP8266Client", MQTT_USER, MQTT_PSK )) {
      // Serial.println("connected");
    } else {
      delay(2000);
      ESP.restart();
    }
  }
 
  network.subscribe(MQTT_TOPIC);


  /* Arduino OAT 'Over The Air' handlers */
  //ArduinoOTA.setHostname("ESP:ceiling-light");

  ArduinoOTA.onStart([]() {
    statusLED.code(4);
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
    // Serial.println("\nEnd");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    statusLED.code(3);
  });

  ArduinoOTA.onError([](ota_error_t error) {
    statusLED.code(0);

    // Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      // Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      // Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      // Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      // Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      // Serial.println("End Failed");
    }
  });

  ArduinoOTA.begin();
  // Serial.println("Ready");
  // Serial.print("IP address: ");
  // Serial.println(WiFi.localIP());
  statusLED.code(2);
}



void callback(char* topic, byte* payload, unsigned int length) {
 
  // Serial.print("Message arrived in topic: ");
  // Serial.println(topic);
 
  // Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    // Serial.print((char)payload[i]);
  }
 
  // Serial.println();
  // Serial.println("-----------------------");
 
}


void loop() {
  ArduinoOTA.handle();
  network.loop();
  statusLED.code(2);


  power = senseSwitch();
  int8_t scale = power ? 1 : -1;
  power_level = constrain(power_level += scale, 0, 255);
  analogWrite(MAINS_SWITCHING_PIN, power_level);

  publishData();
}



bool senseSwitch() {

  // Sense and store value in array with 'running index'
  sense_avg[sense_avg_index] = !digitalRead(SWITCH_SENSE_PIN);

  // Calculate average
  uint8_t _sense_sum = 0;
  for (int i = 0; i < SENSE_AVG_MAX_SAMPLES; i++) 
  {
    _sense_sum += sense_avg[i];
  }

  // Increment and wrap 'running index'
  sense_avg_index = (sense_avg_index + 1) % SENSE_AVG_MAX_SAMPLES;

  // Determine if power is present
  return _sense_sum > 0;
}


uint16_t previousPublish = 0;

void publishData() {


  uint64_t currentMillis = millis();

  if (currentMillis - previousPublish >= 5000) {
    previousPublish = currentMillis;


    publish_data data = {};
    data.switch_state = power;
    data.power_level = power_level;
    data.light_level = analogRead(LIGHT_LEVEL_SENSE_PIN);

    char* my_s_bytes = reinterpret_cast<char*>(&data);
    network.publish(MQTT_TOPIC, String(analogRead(LIGHT_LEVEL_SENSE_PIN)).c_str(), true);
  }
}