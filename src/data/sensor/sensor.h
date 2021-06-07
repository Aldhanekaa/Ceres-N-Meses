#ifndef Arduino_h
#include <Arduino.h>
#endif

#define _sensor

template<typename OUTSIDE_TYPENAME, typename INSIDE_TYPENAME> 
class Sensor {    
    protected:
        OUTSIDE_TYPENAME Outside;
        INSIDE_TYPENAME Inside;
        String SensorName;

    public:


        Sensor(String SensorName , OUTSIDE_TYPENAME Outside, INSIDE_TYPENAME Inside) {
            this->SensorName = SensorName;
            this->Outside = Outside;
            this->Inside = Inside;
        }

        INSIDE_TYPENAME& setDataInside() {
            return this->Inside;
        }
        
        OUTSIDE_TYPENAME& setDataOutside() {
            return this->Outside;
        }

        INSIDE_TYPENAME getDataInside() {
            return this->Inside;
        }
        OUTSIDE_TYPENAME getDataOutside() {
            return this->Outside;
        }
};