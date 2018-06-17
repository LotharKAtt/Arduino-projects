
byte x = 5;
byte y = 5;
byte rady[8] = {2, 7, 19, 5, 13, 18, 12, 16};
byte sloupce[8] = {6, 11, 10, 3, 17, 4, 8, 9};
bool pixely[8][8];

void setup() {

  for (byte i = 0; i <= 7; i = i + 1) {
    pinMode(rady[i], OUTPUT);
    pinMode(sloupce[i], OUTPUT);
  }
  for (byte x = 0; x <= 7; x = x + 1) {
    for (byte y = 0; y <= 7; y = y + 1) {
      pixely[x][y] = HIGH;
    }
  }

}



void loop() {
  nacti();
  kresli();

}

void nacti() {
  pixely[x][y] = HIGH;
  x = map(analogRead(A0), 0, 1023, 0, 7);
  y = map(analogRead(A1), 0, 1023, 0, 7);
  pixely[x][y] = LOW;
}

void kresli() {
  for (byte i = 0; i <= 7; i = i + 1) {
    digitalWrite(rady[i], HIGH);
    for (byte j = 0; j <= 7; j = j + 1) {
      byte pixel = pixely[i][j];
      digitalWrite(sloupce[j], pixel);
      if (pixel == LOW) {
        digitalWrite(sloupce[j], HIGH);
      }
    }
    digitalWrite(rady[i], LOW);
  }
}

