#ifndef Arduino_h
#include <Arduino.h>
#endif

#define _sensor

template<typename OUTSIDE_TYPENAME, typename INSIDE_TYPENAME> 
class Sensor {    
    protected:
        OUTSIDE_TYPENAME Outside;
        INSIDE_TYPENAME Inside;
        
    public:

        String SensorName;

        Sensor(String SensorName , OUTSIDE_TYPENAME Outside, INSIDE_TYPENAME Inside) {
            this->SensorName = SensorName;
            this->Outside = Outside;
            this->Inside = Inside;
        }

};