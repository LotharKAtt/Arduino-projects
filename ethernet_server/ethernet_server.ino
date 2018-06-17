#include<SPI.h>
#include<Ethernet.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//přidělení mac adresy shieldu
byte mac[] = {0x90, 0xA2, 0xDA, 0x00, 0x9C, 0xB7 };

//přidělení IP adresy vytvářeného serveru
IPAddress ip(192, 168, 1, 150);

//vytvoření serveru na portu 80
EthernetServer mujServer(80);

//OneWire oneWire(D8); // inicializace OneWire
DallasTemperature ds18b20(&oneWire); //vytvoření objektu čidla teploty

void setup() {
  //spuštění shieldu
  Ethernet.begin(mac);

  //spuštění serveru
  mujServer.begin();

  pinMode(8, OUTPUT);
}

void loop() {
 // kontroluj zda se nekdo pripojil
  EthernetClient client = mujServer.available();
  if (!client) {
    return;
               }
  
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

