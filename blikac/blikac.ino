
int dio1 = 13;


void setup() {
  pinMode(dio1, OUTPUT);
  digitalWrite(dio1, HIGH);
}

void loop() {
  digitalWrite(dio1,HIGH);
  delay(500);
  digitalWrite(dio1,LOW);
  delay(500);
}

