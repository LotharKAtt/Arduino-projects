#include <ESP8266WiFi.h>

#define tlacitkoZapVyp D6
#define tlacitkoSlunMes D7
#define releVypZap D2
#define releSlunMes D3
#define LEDZapVyp D0
#define LEDSlunMes D1
#define prodleva 50

// Nazev Wi-Fi site, do ktere se mam pripojit
const char* ssid = "Askeladd";

// Heslo Wi-Fi site, do ktere se mam pripojit
const char* password = "knih0vna";

// IP adresa
IPAddress ip(192, 168, 1, 184);

// Webovy server pobezi na portu 80 (HTTP komunikace)
WiFiServer server(80);

//vypinace na termostatu
bool zapnoutVypnout = false; //false=vypnuto, true=zapnuto
bool slunickoMesicek = false; //false=mesicek, true=slunicko

//vypinace wifi
bool wifiZapVyp = false;
bool wifiSlunMes = false;

//ulozeni casu zmen tlacitek
unsigned long casZmenyZapVyp;
unsigned long casZmenySlunMes;

//priznak minuleho stavu tlacitek
bool minulyStavZapVyp = 0;
bool minulyStavSlunMes = 0;

void setup() {
  pinMode(releVypZap, OUTPUT);
  pinMode(tlacitkoZapVyp, INPUT);
  pinMode(LEDZapVyp, OUTPUT);

  pinMode(releSlunMes, OUTPUT);
  pinMode(tlacitkoSlunMes, INPUT);
  pinMode(LEDSlunMes, OUTPUT);

  Serial.begin(115200);

  WiFi.config(ip);
  WiFi.begin(ssid, password);

  // Pripojeni k Wi-Fi
  Serial.println();
  Serial.print("Pripojuji k ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
    Serial.print(".");
  }

  // Spusteni serveru
  server.begin(); Serial.println(digitalRead(tlacitkoZapVyp));
  Serial.println();
  Serial.println("Server spusten");

  // Napis IP adresu, kterou mikropocitac dostal
  Serial.print("Pouzij k pripojeni tuto adresu: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());

}
void loop() {
  // Cekej, dokud se nepripoji nejaky klient
  WiFiClient client = server.available();
  if (!client) {
    //ovladani rele vypinani a zapinani, tlacitko VypZap je na termostatu
    if (digitalRead(tlacitkoZapVyp) == 1)        // je-li nejake tlacitko stisknuto

    {
      if (minulyStavZapVyp == 0 && abs(millis() - casZmenyZapVyp) > prodleva) // neni-li nastaven priznak
      { // tlacitko stisknuto a uplynul-li vetsi cas
        // od zmeny stavu tlacitka nez je mez (50ms)
        minulyStavZapVyp = 1;                             // nastav priznak tlacitko stisknuto
        digitalWrite(releVypZap, !digitalRead(releVypZap));       // zmen hodnotu vystupu LED
        digitalWrite(LEDZapVyp, !digitalRead(releVypZap));
      }

    }
    else                                      // neni-li stisknuto tlacitko
    {
      casZmenyZapVyp = millis();                       // zapamatuj si posledni cas, kdy bylo nestisknuto
      minulyStavZapVyp = 0;                            // nuluj priznak, tlacitko stisknuto

    }

    if (digitalRead(tlacitkoSlunMes) == 1)        // je-li nejake tlacitko stisknuto

    {
      if (minulyStavSlunMes == 0 && abs(millis() - casZmenySlunMes) > prodleva) // neni-li nastaven priznak
      { // tlacitko stisknuto a uplynul-li vetsi cas
        // od zmeny stavu tlacitka nez je mez (50ms)
        minulyStavSlunMes = 1;                             // nastav priznak tlacitko stisknuto
        digitalWrite(releSlunMes, !digitalRead(releSlunMes));       // zmen hodnotu vystupu LED
        digitalWrite(LEDSlunMes, !digitalRead(releSlunMes));
      }
    }
    else                                      // neni-li stisknuto tlacitko
    {
      casZmenySlunMes = millis();                       // zapamatuj si posledni cas, kdy bylo nestisknuto
      minulyStavSlunMes = 0;                            // nuluj priznak, tlacitko stisknuto
    }
    return;
  }


  // Cekej, dokud klient neposle nejaka data
  Serial.println("Novy klient!");
  while (!client.available()) {
    delay(1);
  }
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if (request.indexOf("ZapnoutVypnoutTopeni") > -1) {
    wifiZapVyp = !wifiZapVyp;
    digitalWrite(releVypZap, !digitalRead(releVypZap));
    digitalWrite(LEDZapVyp, !digitalRead(releVypZap));
  }

  if (request.indexOf("slunickoMesicek") > -1) {
    wifiSlunMes = !wifiSlunMes;
    digitalWrite(releSlunMes, !digitalRead(releSlunMes));
    digitalWrite(LEDZapVyp, !digitalRead(releVypZap));
  }

  if (!digitalRead(releVypZap) == 1 && !digitalRead(releSlunMes) == 1) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE html>");
    client.println("<html><body>");
    client.print("<h1>Wi-Fi TERMOSTAT</h2>");
    // Tlacitko pro zapnuti topeni vede na adresu /ZapnoutVypnoutTopeni
    client.println("<a href=\"/ZapnoutVypnoutTopeni\"><button>Zapnout/Vypnout Topeni</button></a>");
    // Tlacitko pro prepnuti slunicko/mesicek vede na adresu /slunickoMesicek
    client.println("<a href=\"/slunickoMesicek\"><button>Slunicko/Mesicek</button></a><br />");
    client.println("<h1>Topeni Zapnuto</h2>");
    client.println("<h1>Slunicko Zapnuto</h2>");
  }
  else if (!digitalRead(releVypZap) == 0 && !digitalRead(releSlunMes) == 0) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE html>");
    client.println("<html><body>");
    client.print("<h1>Wi-Fi TERMOSTAT</h2>");
    // Tlacitko pro zapnuti topeni vede na adresu /ZapnoutVypnoutTopeni
    client.println("<a href=\"/ZapnoutVypnoutTopeni\"><button>Zapnout/Vypnout Topeni</button></a>");
    // Tlacitko pro prepnuti slunicko/mesicek vede na adresu /slunickoMesicek
    client.println("<a href=\"/slunickoMesicek\"><button>Slunicko/Mesicek</button></a><br />");
    client.print("<h1>Topeni Vypnuto</h2>");
    client.println("<h1>Slunicko Vypnuto</h2>");
  }
  else if (!digitalRead(releVypZap) == 1 && !digitalRead(releSlunMes) == 0) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE html>");
    client.println("<html><body>");
    client.print("<h1>Wi-Fi TERMOSTAT</h2>");
    // Tlacitko pro zapnuti topeni vede na adresu /ZapnoutVypnoutTopeni
    client.println("<a href=\"/ZapnoutVypnoutTopeni\"><button>Zapnout/Vypnout Topeni</button></a>");
    // Tlacitko pro prepnuti slunicko/mesicek vede na adresu /slunickoMesicek
    client.println("<a href=\"/slunickoMesicek\"><button>Slunicko/Mesicek</button></a><br />");
    client.print("<h1>Topeni Zapnuto</h2>");
    client.println("<h1>Slunicko Vypnuto</h2>");
  }
  else  {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE html>");
    client.println("<html><body>");
    client.print("<h1>Wi-Fi TERMOSTAT</h2>");
    // Tlacitko pro zapnuti topeni vede na adresu /ZapnoutVypnoutTopeni
    client.println("<a href=\"/ZapnoutVypnoutTopeni\"><button>Zapnout/Vypnout Topeni</button></a>");
    // Tlacitko pro prepnuti slunicko/mesicek vede na adresu /slunickoMesicek
    client.println("<a href=\"/slunickoMesicek\"><button>Slunicko/Mesicek</button></a><br />");
    client.print("<h1>Topeni Vypnuto</h2>");
    client.println("<h1>Slunicko Zapnuto</h2>");
  }

}

