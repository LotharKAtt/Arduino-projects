#define cervena 4
#define zelena 3
#define senzor A0
#define bzu 11

void setup() {
  pinMode(senzor, INPUT);
  pinMode(cervena, OUTPUT);
  pinMode(zelena, OUTPUT);
  pinMode(bzu,OUTPUT);
  Serial.begin(9600);
}
void loop() {
  unsigned int hodnotaSenzoru = analogRead(senzor);
  Serial.println(hodnotaSenzoru);
  if (hodnotaSenzoru < 1000) {
    digitalWrite(zelena, LOW);
    digitalWrite(cervena, HIGH);
    digitalWrite(bzu, HIGH);
    delay(2000);
  }
  else {
    digitalWrite(zelena, HIGH);
    digitalWrite(cervena, LOW);
    digitalWrite(bzu, LOW);
  }

}
