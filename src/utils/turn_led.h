#ifdef Arduino_h
#ifndef _LED_DATA
  #include <data/LED_DATA.h>
#endif

// if status is true, then LED will turn to on, but if status is off LED will turn to off
void turn_led(bool status, LED_DATA *previous_data) {
  // if the led is off and status is true then turn it on
  if (status)
  {
    digitalWrite(previous_data->LED_PIN, HIGH);
    previous_data->status = true;    // Serial.println(previous_data->LED_PIN);

  }
  else 
  {
    digitalWrite(previous_data->LED_PIN, LOW);
    previous_data->status = false;
    // Serial.println(previous_data->LED_PIN);
  }
}

#endif 