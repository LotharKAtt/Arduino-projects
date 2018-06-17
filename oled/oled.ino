#include "DHT.h"
#include "U8glib.h"

#define DHTPIN 2
#define DHTTYPE DHT22

float teplota;
float vlhkost;

DHT Senzor(DHTPIN, DHTTYPE);
U8GLIB_SSD1306_128X64 disp(U8G_I2C_OPT_NONE);

void setup() {
  Serial.begin(9600);
  Senzor.begin();
}

void loop(void) {

  vlhkost = Senzor.readHumidity();
  teplota = Senzor.readTemperature();

  Serial.print("Vlhokost: ");
  Serial.print(vlhkost);
  Serial.print(" %\t");
  Serial.print("Teplota: ");
  Serial.print(teplota);
  Serial.println(" °C ");

  disp.firstPage();
  do {
    vypis();
  } while (disp.nextPage());

  delay(10);
}

void vypis(void) {
  disp.setFont(u8g_font_unifont);
  disp.setPrintPos(0, 10);
  disp.print("Teplota: ");
  disp.setPrintPos(0, 25);
  disp.print(teplota);
  disp.print(" oC");
  disp.setPrintPos(0, 30);
  disp.print("______________");
  disp.setPrintPos(0, 45);
  disp.print("Vlhkost: ");
  disp.setPrintPos(0, 60);
  disp.print(vlhkost);
  disp.print(" %");


}

