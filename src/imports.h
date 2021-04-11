#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h> // minus ke ground, + ke 5V, dan tengah ke A0

#ifndef _LED_DATA
  #include <data/LED_DATA.h>
#endif

#ifndef _sensor_previous_data_union
  #include <data/sensor_previous_data_union.h>
#endif

#ifndef _arrayOfData
  #include <data/arrayOfDatas.h>
#endif

#include <utils/turn_led.h>