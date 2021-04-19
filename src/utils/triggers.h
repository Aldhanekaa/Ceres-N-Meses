#ifndef _DHT_SENSOR_H 
#include <sensors/DHT11_SENSOR.h>
#endif

#define _triggers

void triggerLEDGrowth(DHT11_SENSOR_INSTANCE *DHT11_SENSOR) {
    if (DHT11_SENSOR->GetInsideSensorData().temperature < 24 ) {
      // nyalakan lampu
    }else {
        // matikan lampu
    }
}

void triggerHumidy() {
  
}