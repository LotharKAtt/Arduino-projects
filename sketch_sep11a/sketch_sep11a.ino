#define LED 13
int interval = 1000;
unsigned int minulyCas = 0;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
 
}

void loop() {
  unsigned int aktualniCas = millis();
      //Serial.println((unsigned int)(aktualniCas - minulyCas));

  if ((unsigned int)(aktualniCas - minulyCas) >= interval) {
    digitalWrite(LED, !digitalRead(LED));
    //Serial.println(digitalRead(LED));    
    minulyCas = aktualniCas;
  }
}
