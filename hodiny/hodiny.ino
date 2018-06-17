#include <DS1302.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

// Init the DS1302
// DS1302 rtc([CE/RST], [I/O], [CLOCK]);
DS1302 rtc(8, 7, 6);

void setup() {
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);

  // Setup Serial connection
  Serial.begin(9600);

  // The following lines can be commented out to use the values already stored in the DS1302
  rtc.setDOW(MONDAY);        // Set Day-of-Week to FRIDAY
  rtc.setTime(20, 14, 0);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(17, 4, 2017);   // Set the date to August 6th, 2010
  lcd.begin();
}
String den() {
  return rtc.getDOWStr();
}
void loop() {

  if (rtc.getDOWStr() == "Monday") {
    lcd.setCursor(0, 0);
    lcd.print("Po");
  }
  else if (rtc.getDOWStr() == "Tuesday") {
    lcd.setCursor(0, 0);
    lcd.print("Ut");
  }
  else if (rtc.getDOWStr() == "Wednesday") {
    lcd.setCursor(0, 0);
    lcd.print("St");
  }
  else if (rtc.getDOWStr() == "Thursday") {
    lcd.setCursor(0, 0);
    lcd.print("Ct");
  }
  else if (rtc.getDOWStr() == "Friday") {
    lcd.setCursor(0, 0);
    lcd.print("Pa");
  }
  else if (rtc.getDOWStr() == "Saturday") {
    lcd.setCursor(0, 0);
    lcd.print("So");
  }
  else if (rtc.getDOWStr() == "Sunday") {
    lcd.setCursor(0, 0);
    lcd.print("Ne");
    Serial.println(den());
  }

  // Send date
  lcd.setCursor(4, 0);
  lcd.print(rtc.getDateStr());
  Serial.println(rtc.getDateStr());
 
  // Send time
  lcd.setCursor(4, 1);
  lcd.print(rtc.getTimeStr());

  delay (1000);
  lcd.clear();

}
