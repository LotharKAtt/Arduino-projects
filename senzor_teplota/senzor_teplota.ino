#include <dht11.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

//vytvoří objekt DHT11 s názvem MojeCidlo
dht11 Senzor;

void setup() {
  // nastaví typ displeje na 20 znaků a 4 řádky (upravte dle sebe)
  lcd.begin();
  lcd.backlight();
}

void loop() {

  Senzor.read(0); // přečte údaje z čidla DTH11 připojeného na pin 0
  int hodnota = Senzor.temperature;  // přečte hodnotu z A0
  int vlhkost = Senzor.humidity;
lcd.setCursor(0, 0); 
  lcd.print("t = ");           // napíše text t =
  lcd.print(hodnota);          // napíše hodnotu teploty
  lcd.print(" oC");              // napíše oC

  lcd.setCursor(0, 1);         // nastaví kurzor na čtvrtý řádek a první znak
  lcd.print("v = ");           // napíše text v =
  lcd.print(vlhkost);          // napíše hodnotu teploty
  lcd.print(" %   ");          // napíše %

  delay(1000);                       // čekej 1000ms
}
