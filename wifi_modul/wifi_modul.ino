#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
 
const int LED_WIFI_CONN = BUILTIN_LED; 
String html = "";
 
// zde si nastavte jmeno site a heslo, pokud heslo nemá zadejte ""
const char* ssid = "Askeladd";
const char* password = "knih0vna";
 
//vytvori instanci objektu WifiServer na portu 80 
WiFiServer server(80);
 
OneWire oneWire(D8); // inicializace OneWire
DallasTemperature ds18b20(&oneWire); //vytvoření objektu čidla teploty
 
 
void setup() {
  pinMode(LED_WIFI_CONN, OUTPUT); // nastaví vývod pro LED jako výstup
  digitalWrite(LED_WIFI_CONN, HIGH);
  
  Serial.begin(115200);
  delay(10);
 
  // Vypisuje na serial monitor udaje o pripojovani
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid); 
  
  WiFi.begin(ssid, password); // samotný proces pripojeni k siti
  
  while (WiFi.status() != WL_CONNECTED) { // dokud není pripojeno 
    digitalWrite(LED_WIFI_CONN, HIGH);delay(50);digitalWrite(LED_WIFI_CONN, LOW);delay(50);  
  }
  
  
  // zapnni sever
  server.begin();
  Serial.println("Server started");
 
  // vypise pridelenou IP adresu routerem
  Serial.print("Server IP: ");
  Serial.println(WiFi.localIP());
  GenerateHTML();
}
 
 
 
void loop() {
  
  while (WiFi.status() != WL_CONNECTED) { // dokud není pripojeno 
    digitalWrite(LED_WIFI_CONN, HIGH);delay(50);digitalWrite(LED_WIFI_CONN, LOW);delay(50);
  }
  
  
  // kontroluj zda se nekdo pripojil
  WiFiClient client = server.available();
  if (!client) {
    return;
               }
  
  // zobraz z IP adresu za jake prisel pozadavek
  Serial.print("ClientIP: ");
  Serial.println(client.remoteIP());
     
  while(!client.available()){ //dokud neni client dostupny cekej
    delay(1);
    }
  
  ds18b20.requestTemperatures();   // zjisteni teploty ze senzoru
  float teplota = ds18b20.getTempCByIndex(0);
  String color_t = "black";
  String teplota_string = String(teplota, 1);
  if (teplota >= 24.00) color_t = "red";
  if (teplota == -127) teplota_string = "ERROR";  
  InsertDataToHTML(teplota_string, color_t);
  client.print(html); // posli odpoved 
}
 
void GenerateHTML()
{
html="";
html+= "<!DOCTYPE html>";
html+= "<head>";
html+= "<meta http-equiv=\"refresh\" content=\"1\">";
html+= "</head>";
html+= "<html>";
html+= "<body>";
html+= "<table style=\"border-color: lightblue; margin-left: auto; margin-right: auto; background-color: lightblue;\" border=\"3\" cellspacing=\"0\" cellpadding=\"0\">";  
html+= "<tbody>";
html+= "<tr>";
html+= "<td style=\"text-align: center;\"><span style=\"background-color: #3366ff;\"><strong>Temperature sensor 1</strong></span></td>";
html+= "</tr>";
html+= "<tr>";
html+= "<td style=\"text-align: center;\"><span style=\"color: @id_2@;\"><strong>@id_1@&deg;C</strong></span></td>";
html+= "</tr>";
html+= "</tbody>";
html+= "</table>";
html+= "</html>";
html+= "</body>";
}
 
void InsertDataToHTML(String value, String color)
{
  GenerateHTML();
  html.replace("@id_1@", value);
  html.replace("@id_2@", color);
}
