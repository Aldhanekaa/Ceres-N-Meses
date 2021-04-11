#include <imports.h>

#define DHTPIN A1 // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11
#define LED 5

DHT_Unified dht(DHTPIN, DHTTYPE);

float DHT11_Temperature;
unsigned int Sunlight_intensity;
float maksTemperature = 25.0;

sensor_previous_data_union DHT11_PREVIOUS_Temperature_DATA;
sensor_previous_data_union DHT11_PREVIOUS_Humidity_DATA;
sensor_previous_data_union Sunlight_intensity_previous_data;
LED_DATA LED_GROWTH;

arrayOfData<sensor_previous_data_union, 2> DATAS_FOR_LED_GROWTH;

void setup() {
  LED_GROWTH.status = false;
  LED_GROWTH.LED_PIN = 5;

  Serial.begin(9600);
  // Initialize device.
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));

  pinMode(LED_GROWTH.LED_PIN, OUTPUT);
    // pinMode(6, INPUT);

}

void loop() { 

  sensors_event_t humidity;
  sensors_event_t temperature;
  
  // Get temperature event and print its value.
  dht.temperature().getEvent(&temperature);

  // Get humidity event and print its value.
  dht.humidity().getEvent(&humidity);
  Sunlight_intensity = analogRead(A0);
  Serial.println(map(analogRead(A2), 1023, 200, 0, 100));
  // digitalWrite(true, &LED_GROWTH);

    // Serial.print("Sunlight intensity: ");
    // Serial.println(Sunlight_intensity);


  if (Sunlight_intensity != Sunlight_intensity_previous_data.dataInFloat)
  {
    Sunlight_intensity_previous_data.dataInFloat = Sunlight_intensity;
    Serial.print("Sunlight intensity: ");
    Serial.println(Sunlight_intensity);

    // if (Sunlight_intensity >= 1000) {
    //   turn_led(true, &LED_GROWTH);
    // }else if (temperature.temperature >= maksTemperature && Sunlight_intensity < 1000) {
    //   turn_led(false, &LED_GROWTH);
    // }
  }

  if (isnan(temperature.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {

    if (DHT11_PREVIOUS_Temperature_DATA.dataInFloat != temperature.temperature || (DHT11_PREVIOUS_Humidity_DATA.dataInFloat != humidity.relative_humidity && !isnan(humidity.relative_humidity))) {

      Serial.println("=================================================");
      Serial.print("event.temperature: ");
      Serial.print(temperature.temperature);
      Serial.println(" C");
      Serial.print(F("Humidity: "));
      Serial.print(humidity.relative_humidity);
      Serial.println(F("%"));

      Serial.println("=================================================\n\n");

      if (temperature.temperature < maksTemperature) {
        turn_led(true, &LED_GROWTH);
      }
      else if (Sunlight_intensity < 1000)
      {
        turn_led(false, &LED_GROWTH);
      }
    }

    if (DHT11_PREVIOUS_Temperature_DATA.dataInFloat != temperature.temperature) {
      DHT11_PREVIOUS_Temperature_DATA.dataInFloat = temperature.temperature;
    }
  }

  if (isnan(humidity.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    if (DHT11_PREVIOUS_Humidity_DATA.dataInFloat != humidity.relative_humidity) {
      DHT11_PREVIOUS_Humidity_DATA.dataInFloat = humidity.relative_humidity;
    }
  }

  // delay(500);
}
