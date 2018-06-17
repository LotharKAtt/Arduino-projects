#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define tlacitkoZapVyp D6
#define tlacitkoSlunMes D7
#define releVypZap D2
#define releSlunMes D3
#define teplomer D5

#define indikaceVypZap D0
#define indikaceSlunMes D1

#define prodleva 50

//priznak minuleho stavu tlacitek
bool minulyStavZapVyp = 0;
bool minulyStavSlunMes = 0;

//ulozeni casu zmen tlacitek
unsigned long casZmenyZapVyp;
unsigned long casZmenySlunMes;

// Nazev Wi-Fi site, do ktere se mam pripojit
const char* ssid = "Askeladd";

// Heslo Wi-Fi site, do ktere se mam pripojit
const char* password = "knih0vna";

String hlaseni;
String teplota_string;
String html = "";

// Webovy server pobezi na portu 80 (HTTP komunikace)
WiFiServer server(80);

//inicializace OneWire
OneWire oneWire(teplomer);

//vytvoreni objektu cidla teploty
DallasTemperature ds18b20(&oneWire);

void setup() {
  //Vstupni a vystupni piny
  pinMode(releVypZap, OUTPUT);
  pinMode(tlacitkoZapVyp, INPUT);

  pinMode(releSlunMes, OUTPUT);
  pinMode(tlacitkoSlunMes, INPUT);

  pinMode(indikaceVypZap, OUTPUT);
  pinMode(indikaceSlunMes, OUTPUT);

  pinMode(teplomer, INPUT);

  digitalWrite(indikaceVypZap, !digitalRead(releVypZap));
  digitalWrite(indikaceSlunMes, !digitalRead(releSlunMes));

  // Zahajeni seriove komunikace
  Serial.begin(115200);

  //Pripojeni k WiFi
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Pripojuji k ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
    Serial.print(".");
  }

  //Spusteni serveru
  server.begin();
  Serial.println();
  Serial.println("Server spusten");

  // Napis IP adresu, kterou mikropocitac dostal
  Serial.print("Pouzij k pripojeni tuto adresu: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());

}

void loop() {
  WiFiClient client = server.available();

  String buffer = "";

  //zjisteni teploty ze senzoru
  ds18b20.requestTemperatures();
  float teplota = ds18b20.getTempCByIndex(0);


  //Ovladani fyzickeho tlacitka zapnuti/vyputi topeni s osetrenim debouncingu
  if (digitalRead(tlacitkoZapVyp) == 1) {
    if (minulyStavZapVyp == 0 && abs(millis() - casZmenyZapVyp) > prodleva) {
      minulyStavZapVyp = 1;
      digitalWrite(releVypZap, !digitalRead(releVypZap));
      digitalWrite(indikaceVypZap, !digitalRead(releVypZap));
    }
  }
  else
  {
    casZmenyZapVyp = millis();
    minulyStavZapVyp = 0;
  }
  Serial.println(digitalRead(releVypZap));


  //Ovladani fyzickeho tlacitka slunicko/mesicek s osetrenim debouncingu
  if (digitalRead(tlacitkoSlunMes) == 1 && digitalRead(releVypZap) == 0) {
    if (minulyStavSlunMes == 0 && abs(millis() - casZmenySlunMes) > prodleva) {
      minulyStavSlunMes = 1;
      digitalWrite(releSlunMes, !digitalRead(releSlunMes));
      digitalWrite(indikaceSlunMes, !digitalRead(releSlunMes));

    }
  }
  else
  {
    casZmenySlunMes = millis();
    minulyStavSlunMes = 0;
  }

  //vypnuti slunicka pri vypnuti vypinace VypZap
  if (digitalRead(releSlunMes) == 0 && digitalRead(releVypZap) == 1) {
    digitalWrite(releSlunMes, HIGH);
    digitalWrite(indikaceSlunMes, !digitalRead(releVypZap));

  }

  // dokud je klient připojen
  while (client.connected()) {

    // čti data od něj dokud nenarazíš na znak nového řádku a ukladej je do bufferu
    if (client.available()) {

      char c = client.read();
      buffer = buffer + c;
      if (c == '\n') {

        if (buffer.indexOf("releVypZap=1") >= 0) {
          digitalWrite(releVypZap, HIGH);
          digitalWrite(indikaceVypZap, !digitalRead(releVypZap));
          if (digitalRead(releSlunMes) == 0) {
            digitalWrite(releSlunMes, HIGH);
            digitalWrite(indikaceSlunMes, !digitalRead(releSlunMes));
          }
        }

        if (buffer.indexOf("releVypZap=0") >= 0) {
          digitalWrite(releVypZap, LOW);
          digitalWrite(indikaceVypZap, !digitalRead(releVypZap));
        }
        if (buffer.indexOf("releSlunMes=1") >= 0) {
          digitalWrite(releSlunMes, HIGH);
          digitalWrite(indikaceSlunMes, !digitalRead(releSlunMes));
        }
        if (buffer.indexOf("releSlunMes=0") >= 0 && digitalRead(releVypZap) == 0) {
          digitalWrite(releSlunMes, LOW);
          digitalWrite(indikaceSlunMes, !digitalRead(releSlunMes));
        }

        // odešle klasickou hlavičku HTML stránky
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println();
        client.println("<!DOCTYPE HTML>");

        // zde již klasická html data
        client.println("<html>");
        client.println("<head>");
        // Název stránky
        client.println("<title>NodeMCU - Termostat</title>");
        client.println("</head>");
        client.println("<body>");
        client.println("<h1>Wi-Fi TERMOSTAT A TEPLOMER</h1>");

        if (digitalRead(releVypZap)) {
          client.println("<a href='http://192.168.1.184?releVypZap=0'><button style='background:lightred;width:100%;height:150px'> Zapnuto/Vypnuto</button></a> ");
          if (digitalRead(releSlunMes)) {
            client.println("<a href='http://192.168.1.184?releSlunMes=0'><button style='background:lightred;width:100%;height:150px'> Slunicko/Mesicek</button></a> ");
            client.println("<a href='http://192.168.1.184'><button style='background:lightred;width:100%;height:150px'>Obnovit</button></a>");
          }
          else {
            client.println("<a href='http://192.168.1.184?releSlunMes=1'><button style='background:yellow;width:100%;height:150px'>Slunicko/Mesicek</button></a>");
            client.println("<a href='http://192.168.1.184'><button style='background:lightred;width:100%;height:150px'>Obnovit</button></a>");
          }
        }
        else {
          client.println("<a href='http://192.168.1.184?releVypZap=1'><button style='background:lightgreen;width:100%;height:150px'>Zapnuto/Vypnuto</button></a>");
          if (digitalRead(releSlunMes)) {
            client.println("<a href='http://192.168.1.184?releSlunMes=0'><button style='background:lightred;width:100%;height:150px'> Slunicko/Mesicek</button></a> ");
            client.println("<a href='http://192.168.1.184'><button style='background:lightred;width:100%;height:150px'>Obnovit</button></a>");
          }
          else {
            client.println("<a href='http://192.168.1.184?releSlunMes=1'><button style='background:yellow;width:100%;height:150px'>Slunicko/Mesicek</button></a>");
            client.println("<a href='http://192.168.1.184'><button style='background:lightred;width:100%;height:150px'>Obnovit</button></a>");
          }
        }
        hlaseni = "teplota je: @teplota@ ";
        teplota_string = String(teplota);
        hlaseni.replace("@teplota@", teplota_string);

        client.print(hlaseni);

        client.println("</br>");
        client.println("</body>");
        client.println("</html>");

        //ukončí přenos
        client.stop();
        //Serial.println(buffer);
      }
    }
  }
}
