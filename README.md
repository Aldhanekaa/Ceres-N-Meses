library: Adafruit DHT SENSOR

kamu membutuhkan: vscode dan plugin platfromIO

```c++

  Serial.print("DAY :");
  Serial.println(DHT11_SENSOR.GetOutsideSensorData().humidity);

  /*
    2021/4/13 (Tue) 15:40:42
    since midnight 1/1/1970 = 1618328442s = 18730d
    Temperature: 29.00 C
  */

//   Date.unixtimex

  Serial.print(Date.year(), DEC);
  Serial.print('/');
  Serial.print(Date.month(), DEC);
  Serial.print('/');
  Serial.print(Date.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[Date.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(Date.hour(), DEC);
  Serial.print(':');
  Serial.print(Date.minute(), DEC);
  Serial.print(':');
  Serial.print(Date.second(), DEC);
  Serial.println();

  Serial.print(" since midnight 1/1/1970 = ");
  Serial.print(Date.unixtime());
  Serial.print("s = ");
  Serial.print(Date.unixtime() / 86400L);
  Serial.println("d");

  Serial.print("Temperature: ");
  Serial.print(rtc.getTemperature());
  Serial.println(" C");
```

```
A0 -> sunlight intensity (using D0)
A1 -> Soil Moisture
2  -> DHT11
3 -> relay solenoid
4 -> relay LED
```

```
clock 24 H ; e.g 21:29:6
```
