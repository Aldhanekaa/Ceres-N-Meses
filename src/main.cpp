#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h> // minus ke ground, + ke 5V, dan tengah ke A0

#define DHTPIN A0 // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11
#define LED 5

unsigned int Sunlight_intensity;

DHT_Unified dht(DHTPIN, DHTTYPE);

float DHT11_Temperature;

float maksTemperature = 25.0;

// for storing previous data
union sensor_previous_data_union {
  float dataInFloat;
  char dataInChar;
  int dataInInt;
};

// struct for the LED
struct LED_DATA {
  int LED_PIN;
  bool status;
};

template<typename T, int ROWS>
struct arrayOfData {
  T datas[ROWS];
};

void TurnLED(bool status, LED_DATA *previous_data);

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
}

void loop() {

  sensors_event_t humidity;
  sensors_event_t temperature;
  
  // Get temperature event and print its value.
  dht.temperature().getEvent(&temperature);

  // Get humidity event and print its value.
  dht.humidity().getEvent(&humidity);

  Sunlight_intensity = analogRead(A1);
  // Serial.println(Sunlight_intensity);
  // digitalWrite(true, &LED_GROWTH);


  if (Sunlight_intensity != Sunlight_intensity_previous_data.dataInFloat && (Sunlight_intensity == 1022.00 && Sunlight_intensity_previous_data.dataInFloat == 1023.00))
  {
    Sunlight_intensity_previous_data.dataInFloat = Sunlight_intensity;
    Serial.print("Sunlight intensity: ");
    Serial.println(Sunlight_intensity_previous_data.dataInFloat);

    if (Sunlight_intensity >= 1000) {
      TurnLED(true, &LED_GROWTH);
    }else if (temperature.temperature >= maksTemperature && Sunlight_intensity < 1000) {
      TurnLED(false, &LED_GROWTH);
    }
  }

  if (isnan(temperature.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {

    if (DHT11_PREVIOUS_Temperature_DATA.dataInFloat != temperature.temperature || (DHT11_PREVIOUS_Humidity_DATA.dataInFloat != humidity.relative_humidity && !isnan(humidity.relative_humidity))) {

      Serial.println("=================================================");
      Serial.print("event.temperature: ");
      Serial.println(temperature.temperature);
      Serial.print(F("Humidity: "));
      Serial.print(humidity.relative_humidity);
      Serial.println(F("%"));

      Serial.println("=================================================\n\n");

      if (temperature.temperature < maksTemperature) {
        TurnLED(true, &LED_GROWTH);
      }
      else if (Sunlight_intensity < 1000)
      {
        TurnLED(false, &LED_GROWTH);
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

// if status is true, then LED will turn to on, but if status is off LED will turn to off
void TurnLED(bool status, LED_DATA *previous_data) {
  // if the led is off and status is true then turn it on
  if (status)
  {
    digitalWrite(previous_data->LED_PIN, HIGH);
    previous_data->LED_PIN = true;
    Serial.println(previous_data->LED_PIN);

  }
  else if (!status)
  {
    digitalWrite(previous_data->LED_PIN, LOW);
    previous_data->LED_PIN = false;
    Serial.println(previous_data->LED_PIN);
  }
}