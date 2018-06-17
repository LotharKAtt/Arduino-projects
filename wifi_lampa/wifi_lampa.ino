#define svetlo1 2
#define svetlo2 0


#include <ESP8266WiFi.h>

// Nazev Wi-Fi site, do ktere se mam pripojit
const char* ssid = "Askeladd";

// Heslo Wi-Fi site, do ktere se mam pripojit
const char* password = "knih0vna";

// Ma svitit lampicka?
bool svetlo1Maska = false;
bool svetlo2Maska = false;


// Webovy server pobezi na portu 80 (HTTP komunikace)
WiFiServer server(80);

void setup() {
  // Nastartuj seriovou linku, do ktere budu vypisovat provozni informace
  Serial.begin(115200);

  // Nastav pin D1 na zapis a nastav nizkou hodnotu (LED dioda nesviti)
  pinMode(svetlo1, OUTPUT);
  digitalWrite(svetlo1, LOW);
  pinMode(svetlo2, OUTPUT);
  digitalWrite(svetlo2, LOW);

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
  // Pokud ma promenna svetlo hodnotu pravda, posli na pin D1 napeti a rozsvit LED diodu
  if (svetlo1Maska == true) digitalWrite(svetlo1, HIGH);
  else digitalWrite(svetlo1, LOW);

  if (svetlo2Maska == true) digitalWrite(svetlo2, HIGH);
  else digitalWrite(svetlo2, LOW);

  // Cekej, dokud se nepripoji nejaky klient
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Cekej, dokud klient neposle nejaka data
  Serial.println("Novy klient!");
  while (!client.available()) {
    delay(1);
  }

  // Precti a vypis prvni radek od klienta s URL dotazem
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Pokud je v radku vyraz ZapnoutSvetlo, nastav promennou svetlo na pravdu
  if (request.indexOf("ZapnoutSvetlo1") > -1) svetlo1Maska = true;
  // Pokud je v radku vyraz VypnoutSvetlo, nastav promennou svetlo na nepravdu
  if (request.indexOf("VypnoutSvetlo1") > -1) svetlo1Maska = false;

  // Pokud je v radku vyraz ZapnoutSvetlo2., nastav promennou svetlo2 na pravdu
  if (request.indexOf("ZapnoutSvetlo2") > -1) svetlo2Maska = true;
  // Pokud je v radku vyraz VypnoutSvetlo2, nastav promennou svetlo2 na nepravdu
  if (request.indexOf("VypnoutSvetlo2") > -1) svetlo2Maska = false;

  // Posli pripojenemu klientu HTML kod stranky s tlacitky
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE html>");
  client.println("<html><body>");
  client.print("<h1>Wi-Fi lampicka</h2>");
  // Tlacitko pro zapnuti lampicky1 vede na adresu /ZapnoutSvetlo1
  client.println("<a href=\"/ZapnoutSvetlo1\"><button>Zapni svetlo 1</button></a>");
  // Tlacitko pro vypnuti lampicky1 vede na adresu /VypnoutSvetlo1
  client.println("<a href=\"/VypnoutSvetlo1\"><button>Vypni svetlo 1</button></a><br />");

  // Tlacitko pro zapnuti lampicky2 vede na adresu /ZapnoutSvetlo2
  client.println("<a href=\"/ZapnoutSvetlo2\"><button>Zapni svetlo 2</button></a>");
  // Tlacitko pro vypnuti lampicky2 vede na adresu /VypnoutSvetlo2
  client.println("<a href=\"/VypnoutSvetlo2\"><button>Vypni svetlo 2</button></a><br />");
  client.println("</body></html>");

  // To je vse, ted jeste 1 ms pockam a cela smycka se muze zopakovat
  delay(1);
  Serial.println("Klient odpojen");
  Serial.println("");
}
