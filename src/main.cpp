// oof too many sripts yea?
#include <imports.h>

void printDHT11_data(sensors_event_t *temperature, sensors_event_t *humidity, int Place);

DateTime Date;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
RTC_DS3231 rtc;

// void showDate(void);
// void showTime(void);
// void showDay(void); 

#define DHTPIN A1 // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11
// #define DHTPIN_OUTSIDE A[X] // Change the X | Digital pin connected to the DHT sensor
#define LED 5

DHT_Unified dht_inside_incubator(DHTPIN, DHTTYPE);
// DHT_Unified dht_outside_incubator(DHTPIN_OUTSIDE, DHTTYPE);

int Sunlight_intensity_inside;
int Sunlight_intensity_outside;
float maksTemperature = 25.0;



LED_DATA LED_GROWTH;
DHT11_DATA Outside;
DHT11_DATA Inside;

DHT11_SENSOR_INSTANCE DHT11_SENSOR("DHT11",Outside,Inside);
Sensor<int, int> SunlightIntensity("sunlight_intensity", -1, -1);

void setup() {
  // DHT11_SENSOR
  Serial.begin(9600);

  // Sunlight_intensity_inside_previous_data.dataInInt = -1;
  LED_GROWTH.status = false;
  LED_GROWTH.LED_PIN = 5;

  Serial.println(F("DHTxx Unified Sensor Example"));
  // Initialize device.
  dht_inside_incubator.begin();

  // INISIALISASI DIGITAL INPUT / OUTPUT
  pinMode(LED_GROWTH.LED_PIN, OUTPUT);
  pinMode(4, INPUT);
  // INISIALISASI DIGITAL INPUT / OUTPUT


  // INISIALISASI RTC (REAL TIME CLOCK)
  if (!rtc.begin()) 
  {
    Serial.println("Couldn't find RTC Module");
    while (1)
      ;
  }

  if (rtc.lostPower()) 
  {
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // INISIALISASI RTC (REAL TIME CLOCK)


}

void loop() {
  Sunlight_intensity_inside = map(analogRead(A0), 1023, 78, 0, 100); // sambungin LDR module ke analog pin A0 ; Map digunakn untuk mengkonversi ke persen
  // Sunlight_intensity_outside = map(analogRead(A[X]), 1023, 78, 0, 100); // sambungin LDR module ke analog pin A[X] ; Map digunakn untuk mengkonversi ke persen
  int soilMoisture = map(analogRead(A2), 1023, 200, 0, 100);  // A0 disambungin ke A2 ; Map digunakn untuk mengkonversi ke persen

  Date = rtc.now();
  int year = Date.year();
  int month = Date.month();
  int dayInInt = Date.day();

  // hari, kamu bisa ganti isinye di pariable daysOfTheWeek
  String day = daysOfTheWeek[Date.dayOfTheWeek()];

  // Sunlight_intensity_inside_inside_previous_data.dataInInt = -1;
  sensors_event_t humidity_of_dht_inside_incubator;
  sensors_event_t temperature_of_dht_inside_incubator;
  
  // uncoment this if you've connected DHT11 outside
  // sensors_event_t humidity_of_dht_outside_incubator;
  // sensors_event_t temperature_of_dht_outside_incubator;

  // Get temperature event and print its value.
  dht_inside_incubator.temperature().getEvent(&temperature_of_dht_inside_incubator);
  // uncoment this code below if you've connected DHT11 outside
  // dht_outside_incubator.temperature().getEvent(&temperature_of_dht_outside_incubator);

  // Get humidity event and print its value.
  dht_inside_incubator.humidity().getEvent(&humidity_of_dht_inside_incubator);
  // uncoment this code below if you've connected DHT11 outside
  // dht_outside_incubator.humidity().getEvent(&humidity_of_dht_inside_incubator);

  if (Sunlight_intensity_inside < 55)
  {
    // jika sinar matahari kurang dari 55% | source : http://1001caramenanam.com/budidaya-anggrek-dendrobium/
    turn_led(true, &LED_GROWTH);
  }else{
    turn_led(false, &LED_GROWTH);
  }

  if (soilMoisture) {
    // Soil_moisture_previous_data.dataInInt = soilMoisture;
    // Serial.print("Soil Moisture: ");
    // Serial.println(Soil_moisture_previous_data.dataInInt);

    int N = 20;

    // if (soilMoisture <= N) {
    //   // maka siram air
    // } else {
    //   // jangan siram air
    // }
  }

  /* saved the DHT11 temperature that placed inside of incubator */
  // if error occurs on the sensor:
  if (isnan(temperature_of_dht_inside_incubator.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    if (DHT11_SENSOR.GetInsideSensorData().temperature != temperature_of_dht_inside_incubator.temperature) {

      DHT11_SENSOR.SetTemperature(&temperature_of_dht_inside_incubator, 1); // 1 means that we want to saved data to the DHT11 Sensor that Inside the incubator
    }
  }
  /* saved the DHT11 temperature that placed inside of incubator */


  /* =============== UNKOMEN INI KETIKA KAMU TELAH MENANAM DHT11 DILUAR INKUBATOR ===============*/
  /* saved the DHT11 temperature that placed outside of incubator */
  // if error occurs on the sensor:
  // if (isnan(temperature_of_dht_outside_incubator.temperature)) {
  //   Serial.println(F("Error reading temperature!"));
  // }
  // else {
  //   printDHT11_data(&temperature_of_dht_outside_incubator, &humidity_of_dht_outside_incubator, 0);

  //   if (DHT11_SENSOR.GetOutsideSensorData().temperature != temperature_of_dht_outside_incubator.temperature) {
  //     DHT11_SENSOR.SetTemperature(&temperature_of_dht_outside_incubator, 0); // 0 means that we want to saved data to the DHT11 Sensor that placed Outside the incubator
  //   }
  // }
  /* saved the DHT11 temperature that placed inside of incubator */
  /* =============== UNKOMEN INI KETIKA KAMU TELAH MENANAM DHT11 DILUAR INKUBATOR ===============*/

  /* saved the DHT11 temperature that placed inside of incubator */
  // if error occurs on the sensor:
  if (isnan(humidity_of_dht_inside_incubator.relative_humidity)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    printDHT11_data(&temperature_of_dht_inside_incubator, &humidity_of_dht_inside_incubator, 1);

    if (DHT11_SENSOR.GetInsideSensorData().humidity != humidity_of_dht_inside_incubator.relative_humidity) {
      DHT11_SENSOR.SetHumidty(&humidity_of_dht_inside_incubator, 1); // 1 means that we want to saved data to the DHT11 Sensor that Inside the incubator
    }
  }
  /* saved the DHT11 temperature that placed inside of incubator */


  // DHT11_SENSOR.SetHumidty(&humidity_of_dht_inside_incubator, 1);
  // DHT11_SENSOR.SetHumidty(&humidity_of_dht_inside_incubator);

  delay(1000);
}


// DO NOT CROSS


void printDHT11_data(sensors_event_t* temperature,sensors_event_t* humidity, int Place) {

  String PlaceInString;

  float DHT11_TEMPERATURE;
  float DHT11_HUMIDITY;

  float temperatureInFloat;
  float humidityInFloat;

  switch (Place)
  {
  case 1:
    PlaceInString = "Inside";
    DHT11_TEMPERATURE = DHT11_SENSOR.GetInsideSensorData().temperature;
    DHT11_HUMIDITY = DHT11_SENSOR.GetInsideSensorData().humidity;
    break;

  default:
    PlaceInString = "Outside";
    DHT11_TEMPERATURE = DHT11_SENSOR.GetOutsideSensorData().temperature;
    DHT11_HUMIDITY = DHT11_SENSOR.GetOutsideSensorData().humidity;

    break;
  }

    if (DHT11_TEMPERATURE != temperature->temperature || (DHT11_HUMIDITY != humidity->relative_humidity && !isnan(humidity->relative_humidity)))
    {
      temperatureInFloat = temperature->temperature;
      humidityInFloat = humidity->relative_humidity;

      Serial.println("=================================================");
      Serial.print("DHT11, POSITION: ");
      Serial.println(PlaceInString);

      Serial.print("\nevent.temperature: ");
      Serial.print(temperatureInFloat);
      Serial.println(" C");
      Serial.print(F("Humidity: "));
      Serial.print(humidityInFloat);
      Serial.println(F("%"));

      if (humidityInFloat < 60) {
        Serial.print("\nKAMI MEMBUTUHKAN KELEMBABAN UDARA! SIRAM TANAMAN INI SEGERA!\n\n");
      }else {
        Serial.print("\nKAMI TIDAK MEMBUTUHKAN KELEMBABAN UDARA!\n\n");
      }
        
      Serial.println("=================================================\n\n");


      // if (temperature.temperature < maksTemperature) {
      //   turn_led(true, &LED_GROWTH);
      // }
      // else if (Sunlight_intensity < 1000)
      // {
      //   turn_led(false, &LED_GROWTH);
      // }
    }

  return;
}