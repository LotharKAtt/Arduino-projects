#define laser 2
#define fotoodpor A7
#define zelena A5
#define cervena A4
#define bzzz 5

void setup() {
  pinMode(laser, OUTPUT);
  pinMode(fotoodpor, INPUT);
  pinMode(zelena, OUTPUT);
  pinMode(cervena, OUTPUT);
  pinMode(bzzz, OUTPUT);

}

void loop() {
  unsigned int odpor = analogRead(fotoodpor);
  //Serial.println(odpor);
  if (odpor >= 1015) {
    digitalWrite(zelena, HIGH);
    digitalWrite(cervena, LOW);
    digitalWrite(bzzz, LOW);

  }
  else {
    digitalWrite(zelena, LOW);
    digitalWrite(cervena, HIGH);
    digitalWrite(bzzz, HIGH);

  }

}
