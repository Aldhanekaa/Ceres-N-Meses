
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

// DHT Sensor instance, SunlightIntensity, and SoilMoisture of Sensor Instances were moved to printLCD.hpp

RTC_DS3231 rtc;
DateTime Date;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};


void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);

  // Initialize device.
  dht.begin();
  Serial.println(F("Using DHTxx Unified Sensor"));

  lcd.init();
  lcd.backlight();
  
  // pinMode(3, OUTPUT);

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

  Serial.println("Setup Done!");

  
}

void loop() {

  lcd.begin(20, 4);
  lcd.createChar(0, degreeIcon);
  lcd.createChar(1, christ);

  Date = rtc.now();
  int hour = Date.hour();
  int minute = Date.minute();
  int unixTime = Date.unixtime();

  int Sunlight_intensity_inside = map(analogRead(A0), 755, 40, 0, 100); // sambungin LDR module ke analog pin A0 ; Map digunakn untuk mengkonversi ke persen
  int soilMoisture = map(analogRead(A1), 1023, 0, 0, 100); // A0 disambungin ke A2 ; Map digunakn untuk mengkonversi ke persen
  // Serial.println(minute);

  // Get temperature event and print its value.
  sensors_event_t DHT11_INSIDE_INCUBATOR;
  // ================== Sunlight Intensity ==================
    if (SunlightIntensity.getDataInside() != Sunlight_intensity_inside) {
    SunlightIntensity.setDataInside() = Sunlight_intensity_inside;
    // Serial.print("Sunlight_intensity: ");
    // Serial.print(analogRead(A0));
    // Serial.print(", ");
    // Serial.println(Sunlight_intensity_inside);

    /*
     * Cahaya yang dibutuhkan oleh anggrek berkisaran 50-70% sehingga tempat tumbuh anggrek harus memiliki atap yang terbuat dari paranet sehingga cahaya yang dibutuhk
     */

    if (SunlightIntensity.getDataInside() < 50) {
      // nyalakan lampu
      // analogWrite(4, 100);
      digitalWrite(4, HIGH);

    }
    else if (

        (DHT11_SENSOR.getDataInside().temperature > 21 && (hour >= 18 && hour <= 5)) ||
        (DHT11_SENSOR.getDataInside().temperature > 24 && (hour >= 6 && hour <= 17))

    )
    {
      // matikan lampu
      // analogWrite(4, 0);
      digitalWrite(4, LOW);


    }
  }
  // ================== End of Sunlight Intensity ==================



  // ================== Soil Moisture ==================
    // Serial.print("soil moisture: ");
    // Serial.println(soilMoisture);
  if (SoilMoisture.getDataInside() != soilMoisture) {
    SoilMoisture.setDataInside() = soilMoisture;
    Serial.print("soil moisture: ");
    Serial.println(SoilMoisture.getDataInside());

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
      Serial.print(F("Temperature: "));
      Serial.print(DHT11_INSIDE_INCUBATOR.temperature);
      Serial.println(F("°C"));

      DHT11_SENSOR.SetTemperature(&DHT11_INSIDE_INCUBATOR, 1); // 1 means that we want to saved data to the DHT11 Sensor that Inside the incubator


      /*
       * Anggrek tipe hangat, suhu malam hari 21-24 C
       * sedang siang hari 24-30OC
       * source :  http://balithi.litbang.pertanian.go.id/berita-144-budidaya-anggrek.html
       */
      // if (
      //   (DHT11_SENSOR.getDataInside().temperature<21 && (hour >= 18 && hour <= 5)) || 
      //   (DHT11_SENSOR.getDataInside().temperature<24 && (hour >= 6 && hour <= 17))
      // ) {
      //   // nyalakan lampu
      // }else {
      //   // matikan lampu
      // }
    }
  }

  
  // Get humidity event and print its value.
  dht.humidity().getEvent(&DHT11_INSIDE_INCUBATOR);
  if (isnan(DHT11_INSIDE_INCUBATOR.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    if (DHT11_SENSOR.GetInsideSensorData().humidity != DHT11_INSIDE_INCUBATOR.relative_humidity) {
      Serial.print(F("Humidity: "));
      Serial.print(DHT11_INSIDE_INCUBATOR.relative_humidity);
      Serial.println(F("%"));
      DHT11_SENSOR.SetHumidty(&DHT11_INSIDE_INCUBATOR, 1); // 1 means that we want to saved data to the DHT11 Sensor that Inside the incubator

      /*
       * Umumnya kelembaban yang dibutuhkan tanaman anggrek adalah kelembaban ninbi (RH) yang berkisar antara 60-85%. source : http://balithi.litbang.pertanian.go.id/berita-144-budidaya-anggrek.html
       */
      if (DHT11_SENSOR.getDataInside().humidity < 60) {
        // siram air
      }else {
        // matikan air
      }

    }
  }


  // ================== END OF DHT ==================
// lcd.setCursor(0, 0); // Set the cursor on the first column and first row.(7->column, 0->row)

//         lcd.print("Ceres N Meses        "); // Print the string "Hello World!"
        
//         lcd.setCursor(0, 1); //Set the cursor on the third column and the second row (counting starts at 0!).row 1
//         for (int i = 1; i <= 20; i++)
//         {
//             lcd.print("-");
//         }

//         lcd.setCursor(0, 2); //Set the cursor on the third column and the second row (counting starts at 0!).row 1
//         lcd.print("Temperature: 20");
//         lcd.write(0);
        // lcd.print(String(hour));
  printLCD(unixTime);
  // Serial.print("unixTime: ");
  // Serial.println(unixTime);
}
