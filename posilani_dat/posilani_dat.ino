
#include <ESP8266WiFi.h>

/** Ethernet client instance */
WiFiClient client;

/** Default local IP address, in case of DHCP IP assignement fails */
const IPAddress eth_default_ip( 192,  168,  1,  221);

/** MAC Address of the ethernet shield */
//byte eth_mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0xCD, 0xB8 };

/** Server address wich runs InfluxDB */
const byte eth_server[] = {192, 168, 1, 189};

/** InfluxDB HTTP port */
const int eth_port = 8086;


/** Size of the buffer for HTTP content */
const int bufferSize = 2048;

/** An character array filled with null terminate chars */
char buf[bufferSize] = {'\0'};

//some variables for generating places
const char kitchen[] = "kitchen";
const char garage[] = "garage";
const char living_room[] = "living_room";
const char basement[] = "basement";
int lastGivenPlace = 0;

const char* nazevWifi = "Askeladd";
const char* hesloWifi = "knih0vna";

/**
   @brief: Returns a place out of 4 places we have!
*/
const char* get_place() {
  switch (lastGivenPlace) {
    case 0:
      lastGivenPlace = 1;
      return &kitchen[0];

    case 1:
      lastGivenPlace = 2;
      return &garage[0];

    case 2:
      lastGivenPlace = 3;
      return &living_room[0];

    case 3:
      lastGivenPlace = 0;
      return &basement[0];
  }

  return "unknown_place";
}

/**
   @brief Starts the ethernet shield as client
*/
bool eth_start() {
  WiFi.begin(nazevWifi, hesloWifi);
  delay(2000); //delay to allow connection to be done

  //do a fast test if we can connect to server
  int conState = client.connect(eth_server, eth_port);

  if (conState > 0) {
    Serial.println("Connected to InfluxDB server");
    client.stop();
    return true;
  }

  //print the error number and return false
  Serial.print("Could not connect to InfluxDB Server, Error #");
  Serial.println(conState);
  return false;
}

/**
   @brief Send  HTTP data to InfluxDB
   @param data  Pointer to the beginning of the buffer
   @param dataSize  Number of valid characters to send
*/
void eth_send_data(char* data, int dataSize) {
  //first we need to connect to InfluxDB server
  int conState = client.connect(eth_server, eth_port);

  if (conState <= 0) { //check if connection to server is stablished
    Serial.print("Could not connect to InfluxDB Server, Error #");
    Serial.println(conState);
    return;
  }

  //Send HTTP header and buffer
  client.println("POST /write?db=embedonix HTTP/1.1");
  client.println("Host: www.embedonix.com");
  client.println("User-Agent: Arduino/1.0");
  client.println("Connection: close");
  client.println("Content-Type: application/x-www-form-urlencoded");
  client.print("Content-Length: ");
  client.println(dataSize);
  client.println();
  client.println(data);

  delay(50); //wait for server to process data

  //Now we read what server has replied and then we close the connection
  Serial.println("Reply from InfluxDB");
  while (client.available()) { //receive char
    Serial.print((char)client.read());
  }
  Serial.println(); //empty line

  client.stop();
}

/**
   @brief Setups the peripherals
*/
void setup() {
  //Serial interface for debugging purposes
  Serial.begin(115200);
  delay(1000);
  eth_start();
}



/**
   @brief Main loop
*/
void loop() {

  //A loop to send some data
  for (int i = 30; i < 50  ; i++) {

    //this will be number of chars written to buffer, return value of sprintf
    int numChars = 0;

    //First of all we need to add the name of measurement to beginning of the buffer
    numChars = sprintf(buf, "my_house_data,");

    //tag should have an space at the end
    numChars += sprintf(&buf[numChars], "SOURCE=arduino_1,PLACE=%s ", get_place());

    //after tags, comes the values!
    numChars += sprintf(&buf[numChars], "TEMP=%d,", i);
    numChars += sprintf(&buf[numChars], "HUMIDITY=%.2f,", i * 1.03);
    numChars += sprintf(&buf[numChars], "LIGHT=%.2f", i * 10.5);

    //Print the buffer on the serial line to see how it looks
    Serial.print("Sending following dataset to InfluxDB: ");
    Serial.println(buf);

    //send to InfluxDB
    eth_send_data(buf, numChars);

    //we have to reset the buffer at the end of loop
    memset(buf, '\0', bufferSize);
    delay(1000); //some small delay!
  }

}

