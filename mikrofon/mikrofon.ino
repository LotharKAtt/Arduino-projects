float mikrofon = A0;
float bz = 2;
float mikHod = 0;
float bzhod = 0;

void setup() {
  pinMode(mikrofon, INPUT);
  pinMode(bz,OUTPUT);
  Serial.begin(9600);
}

void loop() {
mikHod=analogRead(mikrofon);
bzhod = map(mikHod,0,1023,0,255);
digitalWrite(bz,bzhod);
Serial.print(mikHod);
Serial.print("     ");
Serial.println(bzhod);
}
