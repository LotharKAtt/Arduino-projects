#include <ESP8266WiFi.h>

// Nazev Wi-Fi site, do ktere se mam pripojit
const char* ssid = "Askeladd";

// Heslo Wi-Fi site, do ktere se mam pripojit
const char* password = "knih0vna";

// Ma svitit lampicka?
bool svetlo = false;

// Webovy server pobezi na portu 80 (HTTP komunikace)
WiFiServer server(80);

void setup() {
  // Nastartuj seriovou linku, do ktere budu vypisovat provozni informace
  Serial.begin(115200);

  // Nastav pin D1 na zapis a nastav nizkou hodnotu (LED dioda nesviti)
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  // Pripojeni k Wi-Fi
  Serial.println();
  Serial.print("Pripojuji k ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // Dokud nejsem pripojeny k Wi-Fi,zapisuj do seriove linky tecky progressbaru
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  // Jsem pripojeny k Wi-Fi a mohu pokracovat
  Serial.println();
  Serial.println("WiFi pripojena!");

  // Spusteni serveru
  server.begin();
  Serial.println("Server spusten");

  // Napis IP adresu, kterou mikropocitac dostal
  Serial.print("Pouzij k pripojeni tuto adresu: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
}

// Smycka loop se opakuje stale dokola
void loop() {
 
} 
