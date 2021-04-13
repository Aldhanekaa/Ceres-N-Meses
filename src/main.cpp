#include <imports.h>

DateTime Date;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
RTC_DS3231 rtc;

void showDate(void);
void showTime(void);
void showDay(void); 

#define DHTPIN A1 // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11
#define LED 5

DHT_Unified dht(DHTPIN, DHTTYPE);

float DHT11_Temperature;
int Sunlight_intensity;
float maksTemperature = 25.0;

sensor_previous_data_union Sunlight_intensity_previous_data;
sensor_previous_data_union Soil_moisture_previous_data;

arrayOfData<sensor_previous_data_union, 2> DHT_INSIDE;

LED_DATA LED_GROWTH;

DHT11_DATA PPP;
DHT11_DATA PPPP;

DHT11_SENSOR_INSTANCE DHT11_SENSOR("DHT11",PPP,PPPP);

arrayOfData<sensor_previous_data_union, 2> DATAS_FOR_LED_GROWTH;

void setup() {
  // DHT11_SENSOR

  Sunlight_intensity_previous_data.dataInInt = -1;
  LED_GROWTH.status = false;
  LED_GROWTH.LED_PIN = 5;

  Serial.println(F("DHTxx Unified Sensor Example"));

  Serial.begin(9600);
  // Initialize device.
  dht.begin();

  pinMode(LED_GROWTH.LED_PIN, OUTPUT);
  pinMode(4, INPUT);

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
}

void loop() {
  Date = rtc.now();
  int year = Date.year();
  int month = Date.month();
  int dayInInt = Date.day();
  String day = daysOfTheWeek[Date.dayOfTheWeek()];

  // Serial.print("DAY :");
  // Serial.println(DHT11_SENSOR.GetOutsideSensorData().humidity);

  /*
    2021/4/13 (Tue) 15:40:42
    since midnight 1/1/1970 = 1618328442s = 18730d
    Temperature: 29.00 C
  */

  // Date.unixtimex

  // Serial.print(Date.year(), DEC);
  // Serial.print('/');
  // Serial.print(Date.month(), DEC);
  // Serial.print('/');
  // Serial.print(Date.day(), DEC);
  // Serial.print(" (");
  // Serial.print(daysOfTheWeek[Date.dayOfTheWeek()]);
  // Serial.print(") ");
  // Serial.print(Date.hour(), DEC);
  // Serial.print(':');
  // Serial.print(Date.minute(), DEC);
  // Serial.print(':');
  // Serial.print(Date.second(), DEC);
  // Serial.println();

  // Serial.print(" since midnight 1/1/1970 = ");
  // Serial.print(Date.unixtime());
  // Serial.print("s = ");
  // Serial.print(Date.unixtime() / 86400L);
  // Serial.println("d");

  // Serial.print("Temperature: ");
  // Serial.print(rtc.getTemperature());
  // Serial.println(" C");

  // Sunlight_intensity_previous_data.dataInInt = -1;
  sensors_event_t humidity;
  sensors_event_t temperature;
  
  // Get temperature event and print its value.
  dht.temperature().getEvent(&temperature);

  // Get humidity event and print its value.
  dht.humidity().getEvent(&humidity);
  Sunlight_intensity = map(analogRead(A0), 1023, 78, 0, 100);
  int soilMoisture = map(analogRead(A2), 1023, 200, 0, 100);

  if (Sunlight_intensity != Sunlight_intensity_previous_data.dataInInt)
  {
    Sunlight_intensity_previous_data.dataInInt = Sunlight_intensity;
    Serial.print("Sunlight intensity: ");
    Serial.println(Sunlight_intensity);

    if (Sunlight_intensity_previous_data.dataInInt <= 30) {
      turn_led(true, &LED_GROWTH);
    }else{
      turn_led(false, &LED_GROWTH);
    }
  }

  if (soilMoisture != Soil_moisture_previous_data.dataInInt) {
    Soil_moisture_previous_data.dataInInt = soilMoisture;
    Serial.print("Soil Moisture: ");
    Serial.println(Soil_moisture_previous_data.dataInInt);

  }

  if (isnan(temperature.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {

    if (DHT11_SENSOR.GetInsideSensorData().temperature != temperature.temperature || (DHT11_SENSOR.GetInsideSensorData().humidity != humidity.relative_humidity && !isnan(humidity.relative_humidity))) {

      Serial.println("=================================================");
      Serial.print("event.temperature: ");
      Serial.print(temperature.temperature);
      Serial.println(" C");
      Serial.print(F("Humidity: "));
      Serial.print(humidity.relative_humidity);
      Serial.println(F("%"));

      if (humidity.relative_humidity < 60) {
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

    if (DHT11_SENSOR.GetInsideSensorData().temperature != temperature.temperature) {
      DHT11_SENSOR.setInkubatorTemperature(temperature.temperature);
    }
  }

  if (isnan(humidity.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    if (DHT11_SENSOR.GetInsideSensorData().humidity != humidity.relative_humidity) {
      DHT11_SENSOR.setInkubatorHumidity(humidity.relative_humidity);
    }
  }

  delay(1000);
}
