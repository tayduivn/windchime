#ifndef AMBIANCE_H
#define AMBIANCE_H

#include "chime.h"
#include "bluetooth.h"
#include "lightsensor.h"
#include "soundsensor.h"
#include "persist.h"

class Ambiance: public BluetoothInformationProducer,
                public IntentionProvider {
  
  private:
    bool enabled = true;             // play sound from time to time 
    ChimeSoundSensor* soundSensor;
    ChimeLightSensor* lightSensor;
    Persist* persist;

    void storeState();

    virtual void publishBluetoothData();

  public:
    // constructor
    Ambiance();
    void setup(Persist* _persist, ChimeSoundSensor* soundSensor, ChimeLightSensor* lightSensor);
    
    void debugSerial();

    bool isEnabled() { return enabled; }
    
    // inherited
    virtual BluetoothListenerAnswer receivedAmbiance(ble_ambiance content);
    virtual Intention proposeNextMode(Intention currentIntention);


};

#endif // AMBIANCE_H
