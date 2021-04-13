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

        DHT11_DATA getDHT_Data(int Place = 0) {
            switch (Place)
            {
            case 1:
                return this->Inside;
                break;

            default:
                return this->Outside;
                break;
            }
        }

        void SetHumidty(sensors_event_t* humidity, int Place = 1) {
            // jika ada error pada sensor
            if (isnan(humidity->relative_humidity)) {
                Serial.println(F("Error reading humidity!"));
            }
            // mengganti Humidity
            else {
                if (getDHT_Data(Place).humidity != humidity->relative_humidity) {
                    if (Place) {
                        this->Inside.humidity = humidity->relative_humidity;
                    }
                    else
                    {
                        this->Outside.humidity = humidity->relative_humidity;
                    }
                }
            }
        }

        void SetTemperature(sensors_event_t* temperature, int Place = 0) {
            // jika ada error pada sensor
            if (isnan(temperature->temperature)) {
                Serial.println(F("Error reading humidity!"));
            }
            // mengganti Humidity
            else {
                DHT11_DATA Data = getDHT_Data(Place);

                if (Data.temperature != temperature->temperature) {
                    if (Place) {
                        this->Inside.temperature = temperature->temperature;
                    }
                    else {
                        this->Outside.temperature = temperature->relative_humidity;
                    }
                }
            }
        }
};