#ifndef Arduino_h
#include <Arduino.h>
#endif

#define _sensor

template<typename OUTSIDE_TYPENAME, typename INSIDE_TYPENAME> 
class Sensor {    
    // protected:

    public:
        OUTSIDE_TYPENAME Outside;
        INSIDE_TYPENAME Inside;

        String SensorName;

        Sensor(String SensorName , OUTSIDE_TYPENAME Outside, INSIDE_TYPENAME Inside) {
            this->SensorName = SensorName;
            this->Outside = Outside;
            this->Inside = Inside;
        }

};