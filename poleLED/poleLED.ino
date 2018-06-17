byte rady[8] = {2, 7, 19, 5, 13, 18, 12, 16};
byte sloupce[8] = {6, 11, 10, 3, 17, 4, 8, 9};
byte maska[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};
byte Xh = 3;
byte Yh = 3;

byte Xt = 3;
byte Yt = 2;

byte Xo = 3;
byte Yo = 1;


void setup() {
  for (byte i = 0; i <= 7; i++) {
    pinMode(rady[i], OUTPUT);
    pinMode(sloupce[i], OUTPUT);

    digitalWrite(rady[i], LOW);
    digitalWrite(sloupce[i], HIGH);
  }
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void loop() {
  byte X = map(analogRead(A0), 0, 1023, 0, 7);
  byte Y = map(analogRead(A1), 0, 1023, 0, 7);
  for (byte i = 0; i < 8; i++) {
    digitalWrite(rady[i], HIGH);
    for (byte j = 0; j < 8; j++) {
      if (maska[i][j] == 1) {
        digitalWrite(sloupce[j], LOW);
      }

    }
    delay(1);
    for (byte j = 0; j < 8; j++) {
      digitalWrite(sloupce[j], HIGH);
    }
    digitalWrite(rady[i], LOW);
  }
  if (((X != Xh) || (Y != Yh)) && ((X != Xt) || (Y != Yt))&& ((X != Xo) || (Y != Yo))) {
    maska[X][Y] = 1;
    maska[Xh][Yh] = 1;
    maska[Xt][Yt] = 1;
    maska[Xo][Yo] = 0;
    Xo = Xt;
    Yo = Yt;
    Xt = Xh;
    Yt = Yh;
    Xh = X;
    Yh = Y;
  }
  else {
    maska[Xh][Yh] = 1;
    maska[Xt][Yt] = 1;
    maska[Xo][Yo] = 1;
  }
}
