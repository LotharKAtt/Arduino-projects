#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

byte pot = A0;

float potHod;

void setup() {
  pinMode(pot, INPUT);
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  potHod = analogRead(pot);
  Serial.println(potHod);
  lcd.setCursor(8, 0);
   // lcd.clear();

  lcd.print(potHod);
  lcd.setCursor(0, 1);
  lcd.print("ahoj svete :)");
  }

