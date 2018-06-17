#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define tl1 2
#define tl2 3
#define tl3 4
#define tl4 5
#define tl5 6
#define tl6 7

#define bzz A3
#define modra A0
#define modra2 13
#define cerv A1
#define cerv2 8
#define cerv3 11
#define servo A2

Servo ser;
LiquidCrystal_I2C disp(0x3F, 16, 2);

void setup() {
  //spravne: 7, 4,3,2
  pinMode(tl1, INPUT);
  pinMode(tl2, INPUT);
  pinMode(tl3, INPUT);
  pinMode(tl4, INPUT);
  pinMode(tl5, INPUT);
  pinMode(tl6, INPUT);

  pinMode(bzz, OUTPUT);
  pinMode(modra, OUTPUT);
  pinMode(cerv, OUTPUT);
  pinMode(cerv2, OUTPUT);
  pinMode(cerv3, OUTPUT);
  pinMode(servo, OUTPUT);

  disp.begin();

}

void loop() {
  if (digitalRead(tl1) && digitalRead(tl2) && digitalRead(tl3) && digitalRead(tl6) && digitalRead(tl4) == 0 && digitalRead(tl5) == 0) {
    digitalWrite(modra, HIGH);
    digitalWrite(modra2, HIGH);
    digitalWrite(bzz, LOW);
    digitalWrite(cerv, LOW);
    digitalWrite(cerv2, LOW);
    digitalWrite(cerv3, LOW);
    disp.setCursor(0, 0);
    disp.print("!!VEM SI KLIC!! ");
    disp.setCursor(0, 1);
    disp.print("                ");

  }
  else if (digitalRead(tl1) == 0 && digitalRead(tl2) == 0 && digitalRead(tl3) == 0 && digitalRead(tl6) == 0 && digitalRead(tl4) == 0 && digitalRead(tl5) == 0) {
    digitalWrite(modra, LOW);
    digitalWrite(modra2, LOW);
    digitalWrite(bzz, LOW);
    digitalWrite(cerv, LOW);
    digitalWrite(cerv2, LOW);
    digitalWrite(cerv3, LOW);

    disp.setCursor(0, 0);
    disp.print("   !!MACKEJ!!   ");
    disp.setCursor(0, 1);
    disp.print("                ");

    ser.attach(servo);
    ser.write(180);
    delay(1000);
    ser.detach();

  }
  else {
    digitalWrite(bzz, HIGH);
    digitalWrite(cerv, HIGH);
    digitalWrite(cerv2, HIGH);
    digitalWrite(cerv3, HIGH);
    disp.setCursor(0, 0);
    disp.print("SPATNE TY TROUBO");
    disp.setCursor(0, 1);
    disp.print("!ZKUS TO JINAK! ");

    ser.attach(servo);
    ser.write(180);
    delay(1000);
    ser.detach();

  }
}
