#include <SPI.h>
#include <Ethernet.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// zde si upravte podle sebe
byte mac[] = { 0xD4, 0xAD, 0xBE, 0xEF, 0xFE, 0x7D };

// IP adresa
IPAddress ip(192, 168, 1, 190);
// port
EthernetServer server(80);

OneWire oneWire(A0);
DallasTemperature teplomer(&oneWire);

void setup()
{
  // inicalizace sítě
  Ethernet.begin(mac, ip);
  // inicializace serveru
  server.begin();
  //Serial.begin(115200);
}

void loop()
{
  //Serial.println(Ethernetc.loalIP());

  // když je připojen klient, zjistíme, zda jsou odeslána data
  // od klienta směrem k nám
  EthernetClient client = server.available();

  // dokud je klient připojen
  while (client.connected()) {
    // čti data od něj dokud nenarazíš na znak nového řádku
    if (client.available()) {
      teplomer.requestTemperatures();
      char c = client.read();
      if (c == '\n') {


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
        client.println("<title>Arduinio Server</title>");
         client.println("<meta http-equiv='refresh' content='2' >");
        client.println("</head>");
        client.println("<body>");
        // vypíše text
        client.print("Teplota je ");
        client.print(teplomer.getTempCByIndex(0));
        client.println(" stupnu Celsia.");

        client.println("</body>");
        client.println("</html>");

        //ukončí přenos
        client.stop();
      }
    }
  }
}
