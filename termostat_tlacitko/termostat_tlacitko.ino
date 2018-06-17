#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
//#include "U8glib.h"
Servo SERVO;
LiquidCrystal_I2C DISP(0x3F, 16, 2);
//U8GLIB_SSD1306_128X64 OLED(U8G_I2C_OPT_NONE);


#define RELE        2
#define TLACITKO1   8
#define TLACITKO2   6
#define TLACITKO3   5
// casova prodleva v niz ignorujeme zmenu stavu tlacitka
#define PRODLEVA   50
#define POTENC1 A7
#define VYSTUPNASERVO 7

bool  MinulyStav = 0;               // priznak predchoziho stavu tlacitka (0 .. stisknuto)
unsigned long CasZmeny;             // promenna pro ulozeni casu zmeny stavu tlacitka
int StavPotenc1;
byte NastavenyStavPotenc;

void setup()
{
  pinMode(RELE, OUTPUT);             // nastaveni pinu 2 jako vystup
  pinMode(TLACITKO1, INPUT);  // nastaveni pinu 5 jako vstup
  pinMode(TLACITKO2, INPUT);  // nastaveni pinu 6 jako vstup
  pinMode(TLACITKO3, INPUT);
  pinMode(POTENC1, INPUT);
  pinMode(VYSTUPNASERVO, OUTPUT);
  SERVO.attach(VYSTUPNASERVO);
  DISP.begin(); //inicializace displaye
  //DISP.backlight(); // zapnutí podsvicení
  DISP.print("nastaveno: ");
  DISP.setCursor(0, 1);
  DISP.print("aktualne: ");
}

void loop()
{

  //ovladani rele1, tlactko1 je na termostatu, tlacitko2 jde pres wifi
  if ((digitalRead(TLACITKO1) == 1) || (digitalRead(TLACITKO2) == 1))         // je-li tlacitko stisknuto
  {
    if (MinulyStav == 0 && abs(millis() - CasZmeny) > PRODLEVA) // neni-li nastaven priznak
    { // tlacitko stisknuto a uplynul-li vetsi cas
      // od zmeny stavu tlacitka nez je mez (50ms)
      MinulyStav = 1;                             // nastav priznak tlacitko stisknuto
      digitalWrite(RELE, !digitalRead(RELE));       // zmen hodnotu vystupu LED
    }
  }
  else                                      // neni-li stisknuto tlacitko
  {
    CasZmeny = millis();                       // zapamatuj si posledni cas, kdy bylo nestisknuto
    MinulyStav = 0;                            // nuluj priznak, tlacitko stisknuto
  }


  //ovladani teploty pres servo
  StavPotenc1 = analogRead(POTENC1); //nacte hodnotu z potenciometru
  StavPotenc1 = map(StavPotenc1, 0, 1023, 0, 180); //preskaluje na 0-180 pro servo

  if ((digitalRead(TLACITKO3) == 1) || (NastavenyStavPotenc == 0)) {
    NastavenyStavPotenc = StavPotenc1; //pri stisku tlacitka 3 se nastavi promenna pro vypis na display a otoci se servo
    SERVO.write(StavPotenc1);
  }

  DISP.setCursor(11, 0);
  DISP.print(String(StavPotenc1));
  DISP.print("   ");
  DISP.setCursor(11, 1);
  DISP.print(String(NastavenyStavPotenc));
  DISP.print("   ");

  //  OLED.firstPage();
  //  do {
  //    vypis();
  //  } while (OLED.nextPage());

}


//
//void vypis(void) {
//  OLED.setFont(u8g_font_unifont);
//  OLED.setPrintPos(0, 10);
//  OLED.print("Nastaveno: ");
//  OLED.setPrintPos(0, 25);
//  OLED.print(StavPotenc1);
//  OLED.setPrintPos(0, 30);
//  OLED.print("______________");
//  OLED.setPrintPos(0, 45);
//  OLED.print("Aktualne ");
//  OLED.setPrintPos(0, 60);
//  OLED.print(NastavenyStavPotenc);
//}

