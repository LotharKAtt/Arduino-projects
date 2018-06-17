byte pot = A1;

int potHod;

void setup() {
  pinMode(pot, INPUT);
  Serial.begin(9600);
}

void loop() {
  potHod = analogRead(pot);
  Serial.println(potHod);
  delay(100);
}

