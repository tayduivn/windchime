
#ifndef CHIME_SOUNDSENSOR_H
#define CHIME_SOUNDSENSOR_H

// in milliseconds
#define CHIME_SOUNDSENSOR_MEASURES_FREQUENCY 100 
#define CHIME_SOUNDSENSOR_MEASURES_ETA 0.5 

#define CHIME_SOUNDSENSOR_ENVELOPE_ETA_SLOW 0.01
#define CHIME_SOUNDSENSOR_ENVELOPE_ETA_QUICK 0.9

#include "sensors_filtering.h"
#include "chime_bluetooth.h"

#include <Arduino.h>

class ChimeSoundSensor: public BluetoothCommandListener {
  
  private:
  
    // hardware config
    byte pin;

    // 
    LowPassFilterSensorWithMinMax sensor;                                                // the sensor plugged on the pin
      
    // state
    unsigned short quietThreshold = 20;                  // the silence / noise threshold

    byte factorThreshold = 50;                // the quiet / noisy threshold will be defined as min+(max-min)*factor; so a factor of 0 will always lead to noisy, a factor of 1 will alwats lead to quiet
    
    // measures the current level of sound
    unsigned short measureSoundLevel();
    
  public:
    
    ChimeSoundSensor(const byte pin);
    
    void setup();
    
    // reads sound level from the environment
    void perceive();
    
    // prints debug information in the Serial port
    void debugSerial();

    // returns a filtered and averaged sound level
    unsigned short getSoundLevel();

    // returns true if it is quiet now
    bool isQuiet();
    
    // inherited
    virtual BluetoothListenerAnswer processBluetoothGet(char* str, SoftwareSerial* BTSerial);
    virtual BluetoothListenerAnswer processBluetoothSet(char* str, SoftwareSerial* BTSerial);
    virtual BluetoothListenerAnswer processBluetoothDo(char* str, SoftwareSerial* BTSerial);

};


#endif // CHIME_SOUNDSENSOR_H





