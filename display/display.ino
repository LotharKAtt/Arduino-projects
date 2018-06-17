
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2); //display (adresa, pocet znaku na radek, pocet radku)

int potenciometr = A0; //pripojeni potenciometru na analogovy port A0
int odporVyst = 3;

int odporHod = 0; //odpor na digitalnim vystupu
float odporOhm = 0;
int hodnotaOdporu = 0;
float odpor = 0;

void setup()
{
  lcd.begin(); //inicializace displaye
  lcd.backlight(); // zapnutí podsvicení

  pinMode(potenciometr, INPUT); //nastaveni potenciometru jako vstupu
  pinMode(odporVyst, OUTPUT);
  Serial.begin(9600); //komunikace
  lcd.print("ODPOR = ");
}

void loop()
{
  hodnotaOdporu = analogRead(potenciometr); //nacteni hodnoty odporu potenciometru
  odpor = map(hodnotaOdporu, 0, 1023, 0, 255);
  odporOhm = (odpor*9200/255);
  Serial.print("Hodnota potenciometru = ");
  Serial.print(odpor);
  Serial.print("\t Odpor potenciometru = ");
  Serial.print(odporOhm);
  Serial.println(" Ω");
  delay(2);

  
  // nastavení kurzoru na devátý znak, druhý řádek
  lcd.setCursor(8, 0);
  // vytisknutí počtu sekund od začátku programu
  lcd.print(odporOhm);
  lcd.setCursor(10,1);
  lcd.print("[Ohm]");
}
