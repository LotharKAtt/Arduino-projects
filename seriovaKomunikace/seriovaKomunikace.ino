byte tlac = 3;

void setup() {
  pinMode(tlac, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(tlac) == 1) {
    Serial.print("H");
  }
  else {
    Serial.print("L");
  }
  delay(100);
}
