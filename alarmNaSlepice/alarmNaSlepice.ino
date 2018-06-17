void setup() {
  pinMode(6, OUTPUT);
  pinMode(4, INPUT);

  Serial.begin(9600);
}

void loop() {
 bool senzor = digitalRead(4);
 if(senzor){
  digitalWrite(6,HIGH);
 }
 else digitalWrite(6,LOW);
}
