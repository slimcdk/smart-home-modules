/*
  main.cpp
  Created by Christian S. Skjerning, Aug 13, 2019.
  Released into the public domain.
*/


#include "esp32.h"



// running average
bool getMainsSwitch() {
  sense_avg[sense_avg_index] = !digitalRead(MAINS_SWITCH_PIN);
  sense_avg_index = (sense_avg_index + 1) % SENSE_AVG_MAX_SAMPLES;
  uint8_t _sense_sum = 0;
  for (int i = 0; i < SENSE_AVG_MAX_SAMPLES; i++) _sense_sum += sense_avg[i];
  return _sense_sum > 0;
}


uint8_t readLightLevel () {
  uint16_t _raw_value = analogRead(LDR_PIN);

  _light_level_max = _raw_value > _light_level_max ? _raw_value : _light_level_max;
  _light_level_min = _raw_value < _light_level_min ? _raw_value : _light_level_min;

  return map(_raw_value, _light_level_min, _light_level_max, 0, 100);
}

void setOutputDim(uint8_t dim_level) {
  
  uint8_t _dim_level = constrain( 0.1 * pow(dim_level, 1.72), 0, 255);
  dacWrite(DIM_CONTROL_PIN, _dim_level);


  Serial.println(_dim_level);  
}



void setup() {
  Serial.begin(115200);
  pinMode(DIM_MODE_PIN, INPUT_PULLDOWN);
  digitalWrite(DIM_MODE_PIN, LOW);
}
 


void loop() {
  digitalWrite(DIM_MODE_PIN, LOW);
  
  setOutputDim(100);
  

}