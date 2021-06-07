
// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include <imports.h>


#define DHTPIN 2     // Digital pin connected to the DHT sensor 
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

// 
DHT11_DATA Outside;
DHT11_DATA Inside;
DHT11_SENSOR_INSTANCE DHT11_SENSOR("DHT11",Outside,Inside);

Sensor<int, int> SunlightIntensity("sunlight_intensity", -1, -1);
Sensor<int, int> SoilMoisture("soil_moisture", -1, -1);

void setup() {
  Serial.begin(9600);
  // Initialize device.
  dht.begin();
  Serial.println(F("Using DHTxx Unified Sensor"));

}

void loop() {
  int Sunlight_intensity_inside = map(analogRead(A0), 1023, 78, 0, 100); // sambungin LDR module ke analog pin A0 ; Map digunakn untuk mengkonversi ke persen
  int soilMoisture = map(analogRead(A1), 1023, 200, 0, 100);  // A0 disambungin ke A2 ; Map digunakn untuk mengkonversi ke persen

  // Get temperature event and print its value.
  sensors_event_t DHT11_INSIDE_INCUBATOR;

  // ================== Sunlight Intensity ==================
    if (SunlightIntensity.getDataInside() != Sunlight_intensity_inside) {
    SunlightIntensity.setDataInside() = Sunlight_intensity_inside;
    // Serial.print("Sunlight_intensity_inside: ");
    // Serial.println(Sunlight_intensity_inside);

  }
  // ================== End of Sunlight Intensity ==================



  // ================== Soil Moisture ==================

if (SoilMoisture.getDataInside() != soilMoisture) {
    SoilMoisture.setDataInside() = soilMoisture;
    // Serial.print("soil moisture: ");
    // Serial.println(SoilMoisture.getDataInside());

  }

  // ================== End of soil Moisture ==================



  // ================== UTAK ATIK DHT DISINI ==================

  dht.temperature().getEvent(&DHT11_INSIDE_INCUBATOR);

  if (isnan(DHT11_INSIDE_INCUBATOR.temperature)) {
    Serial.println(F("Error reading temperature!"));  
    // Serial.println("hey");
  }
  else {
    if (DHT11_SENSOR.GetInsideSensorData().temperature != DHT11_INSIDE_INCUBATOR.temperature) {
      // Serial.print(F("Temperature: "));
      // Serial.print(DHT11_INSIDE_INCUBATOR.temperature);
      // Serial.println(F("°C"));

      DHT11_SENSOR.SetTemperature(&DHT11_INSIDE_INCUBATOR, 1); // 1 means that we want to saved data to the DHT11 Sensor that Inside the incubator
    }
  }

  
  // Get humidity event and print its value.
  dht.humidity().getEvent(&DHT11_INSIDE_INCUBATOR);
  if (isnan(DHT11_INSIDE_INCUBATOR.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    if (DHT11_SENSOR.GetInsideSensorData().humidity != DHT11_INSIDE_INCUBATOR.relative_humidity) {
      // Serial.print(F("Humidity: "));
      // Serial.print(DHT11_INSIDE_INCUBATOR.relative_humidity);
      // Serial.println(F("%"));
      DHT11_SENSOR.SetHumidty(&DHT11_INSIDE_INCUBATOR, 1); // 1 means that we want to saved data to the DHT11 Sensor that Inside the incubator
    }
  }

  // ================== END OF DHT ==================


}
