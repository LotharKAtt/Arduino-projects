void setup() {
  pinMode(6, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  while (Serial.available()) {
    char pismeno = Serial.read();
    Serial.print(pismeno);
    if (pismeno == 'H') {
      digitalWrite(6, HIGH);
    }
    else if (pismeno == 'L') {
      digitalWrite(6, LOW);
    }
  }
}
