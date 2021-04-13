#ifndef _sensor
#include <data/sensor/sensor.h>
#endif

#define _DHT_SENSOR_H

struct DHT11_DATA {
    float temperature;
    float humidity;
};

class DHT11_SENSOR_INSTANCE: public Sensor <DHT11_DATA,DHT11_DATA> {
    public:
        DHT11_SENSOR_INSTANCE(String SensorName, DHT11_DATA Outside, DHT11_DATA Inside): Sensor<DHT11_DATA,DHT11_DATA>(SensorName, Outside, Inside){
            // this->Outside->
        }
        DHT11_DATA GetOutsideSensorData()
        {
            return this->Inside;
        }

        DHT11_DATA GetInsideSensorData()
        {
            return this->Inside;
        }

        void setInkubatorTemperature(float temperature) {
            this->Inside.temperature = temperature;
            return;
        }
        void setInkubatorHumidity(float humidity) {
            this->Inside.humidity = humidity;
            return;
        }

        void set_outside_InkubatorTemperature(float temperature) {
            this->Outside.temperature = temperature;
            return;
        }
        void set_outside_InkubatorHumidity(float humidity) {
            this->Outside.humidity = humidity;
            return;
        }
};