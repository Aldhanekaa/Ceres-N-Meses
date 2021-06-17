#ifndef Arduino_h
#include <Arduino.h>
#endif

#ifndef _printLCD
#define _printLCD
#endif

#ifndef _sensor
  #include <data/sensor/sensor.h>
#endif

#ifndef _DHT_SENSOR_H
  #include <sensors/DHT11_SENSOR.h>
#endif

DHT11_DATA Outside;
DHT11_DATA Inside;
DHT11_SENSOR_INSTANCE DHT11_SENSOR("DHT11",Outside,Inside);

Sensor<int, int> SunlightIntensity("sunlight_intensity", -1, -1);
Sensor<int, int> SoilMoisture("soil_moisture", -1, -1);


enum LCD_Tasks
{
  temperature_humidity = 'th',
  soil_sun = 'ss'
};

LCD_Tasks lastShow = soil_sun;
int lastShowInUnixTime = 1000;

void printLCD(int unixTime) {
    // Serial.println(unixTime);
    //     Serial.println(lastShowInUnixTime);

    //     Serial.println(unixTime - lastShowInUnixTime);

    // lcd.setCursor(0, 0); // Set the cursor on the first column and first row.(7->column, 0->row)

    //     lcd.print("Ceres N Meses        "); // Print the string "Hello World!"
        
    //     lcd.setCursor(0, 1); //Set the cursor on the third column and the second row (counting starts at 0!).row 1
    //     for (int i = 1; i <= 20; i++)
    //     {
    //         lcd.print("-");
    //     }

    //     lcd.setCursor(0, 2); //Set the cursor on the third column and the second row (counting starts at 0!).row 1
    //     lcd.print("Temperature: 20");
    //     lcd.write(1);
    if (unixTime - lastShowInUnixTime >= 1 * 1)
    {
        switch (lastShow)
        {
        case soil_sun:
            // Serial.println("soil_sun");

            lcd.setCursor(0, 0); 

            lcd.print("Ceres N Meses        "); 

            lcd.setCursor(0, 1);
            for (int i = 1; i <= 20; i++)
            {
                lcd.print("-");
            }

            lcd.setCursor(0, 2);
            lcd.print("Temperature: ");
            lcd.print(String(DHT11_SENSOR.getDataInside().temperature));
            lcd.write(0);
            lcd.print("C");

            lcd.setCursor(0, 3);
            lcd.print("Humidity: ");
            lcd.print(String(DHT11_SENSOR.getDataInside().humidity));
            lcd.print("%");

            // DHT11_SENSOR.getDataInside().humidity;
        lastShow = temperature_humidity;
            /* code */
            break;
        
        case temperature_humidity: 

          // Print 'Hello World!' on the first line of the LCD:
            lcd.setCursor(0, 0); // Set the cursor on the first column and first row.(7->column, 0->row)

            lcd.print("ceres-n-meses.now.sh        "); // Print the string "Hello World!"
            
            lcd.setCursor(0, 1); //Set the cursor on the third column and the second row (counting starts at 0!).row 1
            for (int i = 1; i <= 20; i++)
            {
                lcd.print("-");
            }

            lcd.setCursor(0, 2); //Set the cursor on the third column and the second row (counting starts at 0!).row 1
            lcd.print("Soil Moisture: ");
            lcd.print(String(SoilMoisture.getDataInside()));
            lcd.print("%");

            lcd.setCursor(0, 3); //Set the cursor on the third column and the second row (counting starts at 0!).row 1
            lcd.print("Sunlight: ");
            lcd.print(String(SunlightIntensity.getDataInside()));
            lcd.print("%");

                // DHT11_SENSOR.getDataInside().humidity;
            lastShow = soil_sun;
            /* code */
            break;
        default:
            break;
        }

        lastShowInUnixTime = unixTime;
    }
}