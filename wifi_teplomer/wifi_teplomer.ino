#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
 
const char* ssid = "Askeladd";
const char* password = "knih0vna";
 
OneWire oneWire(D8);
DallasTemperature sensor(&oneWire);
String myHTML = "";
ESP8266WebServer server(80);
 
 
const int led = LED_BUILTIN;
float teplota;
 
void handleRoot() {
  
  digitalWrite(led, 1);  
  Serial.println();
  String message = "";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  Serial.println(message);
  if (server.args()==0)
  {
    generateHTML();
    server.send(200, "text/html", myHTML);
  }
  else
  {}
  digitalWrite(led, 0);
}
 
void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}
 
void setup(void){
  sensor.begin();
  
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
 
  server.on("/", handleRoot);
  server.on("/inline", [](){server.send(200, "text/plain", "this works as well");});
  server.onNotFound(handleNotFound);
 
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
    
  server.handleClient();
}
 
 
void generateHTML(){
myHTML="";
myHTML+="<html>";
myHTML += "  <head> ";
myHTML += "<script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script>";
myHTML += "   <script type=\"text/javascript\">";
myHTML += "      google.charts.load('current', {'packages':['gauge']});";
myHTML += "      google.charts.setOnLoadCallback(drawChart);";
myHTML += "      function drawChart() {";
myHTML += "";
myHTML += "        var data = google.visualization.arrayToDataTable([";
myHTML += "          ['Label', 'Value'],";
myHTML += "          ['Teplota', @id_1@]";
myHTML += "        ";
myHTML += "        ]);";
myHTML += "";
myHTML += "        var options = {";
myHTML += "          width: 600, height: 600,";
//myHTML += "          redFrom: 90, redTo: 100,";
myHTML += "          yellowFrom:20, yellowTo: 30,";
myHTML += "          minorTicks: 5";
//myHTML += "          majorTicks: 1";
myHTML += "        };";
myHTML += "";
myHTML += "        var chart = new google.visualization.Gauge(document.getElementById('chart_div'));";
myHTML += "";
myHTML += "        chart.draw(data, options);      ";
myHTML += "        ";
myHTML += "      }";
myHTML += "    </script>";
myHTML += "  </head>";
myHTML += "  <body>";
myHTML += "    <div id=\"chart_div\" style=\"width: 600px; height: 600px;\"></div>";
myHTML += "  </body>";
myHTML += "</html>";
sensor.requestTemperatures(); 
myHTML.replace("@id_1@", String(sensor.getTempCByIndex(0), 1));
}
