#include <SPI.h>
#include <Ethernet.h>

// zde si upravte podle sebe
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// IP adresa
IPAddress ip(192, 168, 1, 190);
// port
EthernetServer server(80);

void setup()
{
  // inicalizace sítě
  Ethernet.begin(mac, ip);
  // inicializace serveru
  server.begin();
  // nastavíme pin 2 jako výstup pro LED
  pinMode(2, OUTPUT);

  Serial.begin(115200);

}

void loop()
{
  // když je připojen klient, zjistíme, zda jsou odeslána data
  // od klienta směrem k nám
  EthernetClient client = server.available();
  String buffer = "";
  // dokud je klient připojen
  while (client.connected()) {

    // čti data od něj dokud nenarazíš na znak nového řádku
    if (client.available()) {
      char c = client.read();
      buffer = buffer + c;
      if (c == '\n') {

        if (buffer.indexOf("led1=1") >= 0)
          digitalWrite(2, HIGH);

        if (buffer.indexOf("led1=0") >= 0)
          digitalWrite(2, LOW);
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
        client.println("<title>Arduinio Server - LED control</title>");
        client.println("</head>");
        client.println("<body>");
        // vygeneruje formulář
        if (digitalRead(2)) {
          client.print("<a href='http://192.168.1.190?led1=0'><button style='background:green;width:50%;height:40px'>LED 1</button></a>");
        } else {
          client.print("<a href='http://192.168.1.190?led1=1'><button style='background:grey;width:50%;height:40px'>LED 1</button></a>");
        }

      
        client.println("</br>");



        client.println("</body>");
        client.println("</html>");

        //ukončí přenos
        client.stop();
        Serial.println(buffer);
      }
    }
  }
}
