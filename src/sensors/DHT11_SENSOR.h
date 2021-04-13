#ifndef _sensor
#include <data/sensor/sensor.h>
#endif

#define _DHT_SENSOR_H
template<typename OUTSIDE_TYPENAME, typename INSIDE_TYPENAME>
class DHT11_SENSOR_INSTANCE: public Sensor <OUTSIDE_TYPENAME,INSIDE_TYPENAME> {
    public:
        DHT11_SENSOR_INSTANCE(String SensorName, OUTSIDE_TYPENAME Outside, INSIDE_TYPENAME Inside): Sensor<OUTSIDE_TYPENAME,INSIDE_TYPENAME>(SensorName, Outside, Inside){
        }
            void GetOutsideSensorData()
            {
                return;
            }
};