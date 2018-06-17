// pin připojen na RCLK registru (12)
int latchPin = 3;
//Pin connected to SRCLK registru (11)
int clockPin = 4;
////Pin připojen na Data pin registu (14)
int dataPin = 2;

// data uložená v poli
// v binární soustavě pro větší
// přehlednost
byte data[] =
{

  B00000000,
  B00011000,
  B00111100,
  B01111110,
  B11111111,
  B11100111,
  B11000011,
  B10000001,
  B00000000,
  B10000001,
  B11000011,
  B11100111,
  B11111111,
  B11100111,
  B11000011,
  B10000001
};


void setup() {
  // nastaví naše piny pro regist na výstupní
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  // funkce projde všechny byte v poli data
  for (int index = 0; index < sizeof(data); index++) {
    // když dáme latchPin na LOW mužeme
    // do registru poslat data
    digitalWrite(latchPin, LOW);
    // a to pomocí funkce shiftOut, která
    shiftOut(dataPin, clockPin, MSBFIRST, data[index]);

    // jakmile dále latchPin na HIGH,
    // data se objeví na výstupu
    digitalWrite(latchPin, HIGH);

    // počká 50ms, aby jsme výsledek viděli
    delay(50);
  }
}
