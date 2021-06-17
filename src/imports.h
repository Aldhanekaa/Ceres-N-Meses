#include <Arduino.h>

#ifndef degreeIconDef
#include <characters/degree.hpp>
#endif


// Include the libraries:
// LiquidCrystal_I2C.h: https://github.com/johnrickman/LiquidCrystal_I2C
// Include the libraries:
// LiquidCrystal_I2C.h: https://github.com/johnrickman/LiquidCrystal_I2C

#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD

// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4); // Change to (0x27,16,2) for 16x2 LCD.my address is (0x3F)

// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h> // minus ke ground, + ke 5V, dan tengah ke A0


#include <RTClib.h>

#ifndef _LED_DATA
  #include <data/LED_DATA.h>
#endif

#ifndef _sensor_previous_data_union
  #include <data/sensor_previous_data_union.h>
#endif

#ifndef _sensor
  #include <data/sensor/sensor.h>
#endif

#ifndef _DHT_SENSOR_H
  #include <sensors/DHT11_SENSOR.h>
#endif

#ifndef _triggers 
  #include <utils/triggers.h>
#endif

#include <utils/turn_led.h>

#ifndef _printLCD
#include <utils/printLCD.hpp>
#endif
