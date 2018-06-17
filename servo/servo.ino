#include <Servo.h>
#define vystupNaServo 6
Servo mojeServo;
byte posun = 10;

void setup() {
  pinMode(vystupNaServo, OUTPUT);
}



void loop() {
  mojeServo.attach(vystupNaServo);
  mojeServo.write(0);
  delay(1000);

  mojeServo.write(180);
  delay(1000);
  mojeServo.detach();
//  //  //Serial.println(hod);
}
