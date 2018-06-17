byte vystupPotenciometru = A3;
int hodnotaPotenciometru;

void setup() {
  pinMode(vystupPotenciometru, INPUT);
  Serial.begin(57600);
}

void loop() {
  hodnotaPotenciometru = analogRead(vystupPotenciometru);
  Serial.println(hodnotaPotenciometru);
}
