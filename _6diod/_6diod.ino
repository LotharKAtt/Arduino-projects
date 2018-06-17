byte led11 = 12;
byte led10 = 10;
byte led9 = 9;
byte led6 = 6;
byte led5 = 5;
byte led3 = 3;

byte pot = A0;
int potHod;
int zpozdeni = 0;

void setup() {
  pinMode(led11, OUTPUT);
  pinMode(led10, OUTPUT);
  pinMode(led9, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  potHod = analogRead(pot);
  if (potHod <= 170) {
    int a1 = map(potHod, 0, 170, 0, 255);
    analogWrite(led11, a1);
    delay(zpozdeni);
  }
  else if ((potHod >= 171) && (potHod <= 340)) {
    int a1 = map(potHod, 171, 340, 255, 0);
    analogWrite(led11, a1);
    int a2 = map(potHod, 171, 340, 0, 255);
    analogWrite(led10, a2);
    delay(zpozdeni);
  }
  else if ((potHod >= 341) && (potHod <= 510)) {
    int a1 = map(potHod, 341, 510, 255, 0);
    analogWrite(led10, a1);
    int a2 = map(potHod, 341, 510, 0, 255);
    analogWrite(led9, a2);
    delay(zpozdeni);

  }
  else if ((potHod >= 511) && (potHod <= 680)) {
    int a1 = map(potHod, 511, 680, 255, 0);
    analogWrite(led9, a1);
    int a2 = map(potHod, 511, 681, 0, 255);
    analogWrite(led6, a2);
    delay(zpozdeni);

  }
  else if ((potHod >= 681) && (potHod <= 850)) {
    int a1 = map(potHod, 681, 850, 255, 0);
    analogWrite(led6, a1);
    int a2 = map(potHod, 681, 850, 0, 255);
    analogWrite(led5, a2);
    delay(zpozdeni);

  }
  else if ((potHod >= 851) && (potHod <= 1023)) {
    int a1 = map(potHod, 851, 1023, 255, 0);
    analogWrite(led5, a1);
    int a2 = map(potHod, 851, 1023, 0, 255);
    analogWrite(led3, a2);
    delay(zpozdeni);
  }
}
