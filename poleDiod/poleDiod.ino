
byte rady[8] = {2, 7, 19, 5, 13, 18, 12, 16};
byte sloupce[8] = {6, 11, 10, 3, 17, 4, 8, 9};
int sourX1;
int sourY1;
int sourX2;
int sourY2;
int sourX3;
int sourY3;

void setup() {

  for (byte i = 0; i <= 7; i = i + 1) {
    pinMode(rady[i], OUTPUT);
    pinMode(sloupce[i], OUTPUT);
    digitalWrite(sloupce[i], HIGH);
    digitalWrite(rady[i], LOW);
  }
  //rozsvitBod(3,3);
  // rozsvitBod(3,4);
  //rozsvitBod(5,6);
  //zhasniKolem(3,3,3,1,3,5);
  sourX1 = map(analogRead(A1), 0, 1023, 0, 7);
  sourY1 = map(analogRead(A0), 0, 1023, 0, 7);
  sourX2 = sourX1;
  sourY2 = sourY1;
  sourX3 = sourX1;
  sourY3 = sourY1;
  Serial.begin(9600);
}


void rozsvitBod(byte x, byte y) {
  for (int i = 0; i <= 7; i++) {
    if (i == x) {
      digitalWrite(sloupce[i], LOW);
    }
    if (i == y) {
      digitalWrite(rady[i], HIGH);
    }
  }
}


void zhasniKolem(byte x1, byte y1, byte x2, byte y2, byte x3, byte y3) {
  for (byte i = 0; i <= 7; i++) {
    for (byte j = 0; j <= 7; j++) {
      if ((i != y1) && (i != y2) && (i != y3)) {
        if ((j != x1) && (j != x2) && (j != x3)) {
          digitalWrite(rady[i], LOW);
          digitalWrite(sloupce[j], HIGH);
        }
      }
    }
  }
}


void loop() {
  rozsvitBod(sourX2, sourY2);
  rozsvitBod(sourX3, sourY3);
  sourX1 = map(analogRead(A1), 0, 1023, 0, 7);
  sourY1 = map(analogRead(A0), 0, 1023, 0, 7);
  if ((sourX1 != sourX2) || (sourY1 != sourY2)) {
    rozsvitBod(sourX1, sourY1);

    zhasniKolem(sourX1, sourY1, sourX2, sourY2, sourX3, sourY3);
    //delay(500);
    Serial.print(sourX1);
    Serial.print("   ");
    Serial.print(sourY1);
    Serial.print("   ");
    Serial.print(sourX2);
    Serial.print("   ");
    Serial.print(sourY2);
    Serial.print("   ");
    Serial.print(sourX3);
    Serial.print("   ");
    Serial.println(sourY3);
    sourX3 = sourX2;
    sourY3 = sourY2;
    sourX2 = sourX1;
    sourY2 = sourY1;


  }
}




