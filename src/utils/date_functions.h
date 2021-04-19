#ifndef _RTCLIB_H_
#include <RTClib.h>
#endif

#define _date_functions_h

DateTime Date;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

 void showDate()
 {
  lcd.print(now.day());
  lcd.print('/');
  lcd.print(now.month());
  lcd.print('/');
  lcd.print(now.year());
 }
 void showDay()
 {
  lcd.setCursor(11,0);
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
 }
 void showTime()
 {
  lcd.setCursor(0,1);
  lcd.print("Time:");
  lcd.print(now.hour());
  lcd.print(':');
  lcd.print(now.minute());
  lcd.print(':');
  lcd.print(now.second());
  lcd.print("    ");
 } 
