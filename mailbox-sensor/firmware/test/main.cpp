#include <Arduino.h>
#include <driver/adc.h> 
#include <esp_adc_cal.h>
#include <esp_sleep.h>


/*** BATTERY VOLTAGE LEVEL ***/
bool            _FIRST_RUN                  = true;
const uint8_t   BATT_PIN                    = 39;

const uint64_t  _R1_VALUE                   = 10000;
const uint64_t  _R2_VALUE                   = 10000;
float           _RESISTOR_RATIO             = (float)_R1_VALUE / ((float)_R1_VALUE + (float)_R1_VALUE);
int16_t          BATT_LEVEL                  = 0.0;

const uint16_t  _BATT_MAX                   = 4200;
const uint16_t  _BATT_MIN                   = 3200;
uint16_t        _DAC_P3P_REF                = 3300;
const uint8_t   _ADC_WIDTH                  = 12;

const uint32_t  _DAC_BATT_AVG_SAMPLES        = 10;
uint32_t        _RAW_DAC_BATT[_DAC_BATT_AVG_SAMPLES];
uint32_t        _DAC_BATT_AVG_INDEX          = 0, 
                _DAC_BATT_AVG                = 0, 
                _DAC_BATT_AVG_SUM            = 0,
                _DAC_BATT_MAX_LEVEL          = pow(2, _ADC_WIDTH),
                _DAC_BATT_MIN_LEVEL          = 0;



/*** REED SWITCH ***/
const uint8_t   REEDSW_PIN                   = 26;





void BatteryLevelLoop () {
    _RAW_DAC_BATT[_DAC_BATT_AVG_INDEX] = analogRead(BATT_PIN);                                          // store value at index
    _DAC_BATT_AVG_INDEX = (_DAC_BATT_AVG_INDEX + 1) % _DAC_BATT_AVG_SAMPLES;                            // increase the index and wrap around at max
    _FIRST_RUN = _FIRST_RUN ? (_DAC_BATT_AVG_INDEX + 1 < _DAC_BATT_AVG_SAMPLES) : _FIRST_RUN;           // detect if sample array is still populating
    
    _DAC_BATT_AVG_SUM = 0;
    for (uint8_t i = 0; i < _DAC_BATT_AVG_SAMPLES; i++) _DAC_BATT_AVG_SUM += _RAW_DAC_BATT[i];          // sum up all current values
    _DAC_BATT_AVG = _DAC_BATT_AVG_SUM / (_DAC_BATT_AVG_SAMPLES-1);                                      // find the average value

    BATT_LEVEL =( (float)(_DAC_BATT_AVG - _DAC_BATT_MIN_LEVEL) / (float)(_DAC_BATT_MAX_LEVEL - _DAC_BATT_MIN_LEVEL) ) * 100;   // linear mapping from DAC value to procentage
}



void BatteryLevelSetup() {
    pinMode(BATT_PIN, INPUT);
    adcAttachPin(BATT_PIN);
    analogSetWidth(_ADC_WIDTH);

    _DAC_BATT_MAX_LEVEL = ((_RESISTOR_RATIO * _BATT_MAX) / _DAC_P3P_REF) * pow(2, _ADC_WIDTH);          // maximum sense voltage                      
    _DAC_BATT_MIN_LEVEL = ((_RESISTOR_RATIO * _BATT_MIN) / _DAC_P3P_REF) * pow(2, _ADC_WIDTH);          // minimum sense voltage

    for (uint8_t i = 0; i < _DAC_BATT_AVG_SAMPLES; i++) BatteryLevelLoop();
}


bool ReedSwitchLoop() {
    return digitalRead(REEDSW_PIN);
}



void ReedSwitchSetup() {
    pinMode(REEDSW_PIN, INPUT);
}




void suspend(){
  Serial.println("Process Suspend..");
  esp_deep_sleep_start();
}


void setup(void) {
    Serial.begin(9600);
    Serial.println("\nHello, World!");

    BatteryLevelSetup();
    ReedSwitchSetup(); 
}




void loop(void) {

    // BatteryLevelLoop();


    Serial.println( ReedSwitchLoop() );

    
}