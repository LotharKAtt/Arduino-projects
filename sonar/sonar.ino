#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

#define trig 3
#define echo 4
#define out 5

void setup() {
  lcd.begin();
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(out, INPUT);
  Serial.begin(9600);
  lcd.print("Vzdalenost: ");
  lcd.setCursor(7,1);
  lcd.print("cm");
}

void loop() {
  //Serial.println("posílám implulz");
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  float vzdalenost = pulseIn(echo, HIGH);
  
  vzdalenost = vzdalenost * 0.017315f;
  Serial.println(vzdalenost);
  lcd.setCursor(0,1);
  lcd. print(vzdalenost);    
  delay(1000);
}
