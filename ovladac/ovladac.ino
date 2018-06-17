// Dálkové ovládání infračervené s HX1838

// připojení knihovny
#include"IRremote2.h"

// nastavení čísla pinu pro propojení s Arduinem
#define pinIN 6

// vytvoření instance dalkoveOvl z knihovny IRremote2
// a proměnné vysledek pro ukládání výsledků
IRrecv dalkoveOvl(pinIN);
decode_results vysledek;

void setup() {
  // komunikace přes sériovou linku rychlostí 9600 baud
  Serial.begin(9600);
  // start komunikace s IR přijímačem
  dalkoveOvl.enableIRIn();
}

void loop() {
  // v if podmínce je volána funkce decode
  // pro načtení dat z přijímače - pokud přišel
  // signál, provede se obsah if podmínky
  if (dalkoveOvl.decode(&vysledek)) {
    // pro zkoušení nového ovladače stačí odkomentovat
    // následující řádek a číst data po sériové lince
     Serial.println(vysledek.value, HEX);

    // volání podprogramu detekceKlaves pro
    // zjištění názvu klávesy
    detekceKlaves();
    // pokračování v detekci nových stisků
    dalkoveOvl.resume();
  }  
}
// podprogram s překladem syrových hodnot na
// jednotlivá tlačítka
void detekceKlaves() {
  switch(vysledek.value) {
    // u každé stisknuté klávesy se vždy vypíše
    // její název po sériové lince
    case 0xFFA25D:  
      Serial.println("Stisknuto CH-");
      break;
    case 0xFF629D:  
      Serial.println("Stisknuto CH");
      break;
    case 0xFFE21D:  
      Serial.println("Stisknuto CH+");
      break;
    case 0xFF22DD:  
      Serial.println("Stisknuto PREV");
      break;
    case 0xFF02FD:  
      Serial.println("Stisknuto NEXT");
      break;
    case 0xFFC23D:  
      Serial.println("Stisknuto PLAY/PAUSE");
      break;
    case 0xFFE01F:  
      Serial.println("Stisknuto VOL-");
      break;
    case 0xFFA857:  
      Serial.println("Stisknuto VOL+");
      break;
    case 0xFF906F:  
      Serial.println("Stisknuto EQ");
      break;
    case 0xFF6897:  
      Serial.println("Stisknuto 0");
      break;
    case 0xFF9867:  
      Serial.println("Stisknuto 100+");
      break;
    case 0xFFB04F:  
      Serial.println("Stisknuto 200+");
      break;
    case 0xFF30CF:  
      Serial.println("Stisknuto 1");
      break;
    case 0xFF18E7:  
      Serial.println("Stisknuto 2");
      break;
    case 0xFF7A85:  
      Serial.println("Stisknuto 3");
      break;
    case 0xFF10EF:  
      Serial.println("Stisknuto 4");
      break;
    case 0xFF38C7:  
      Serial.println("Stisknuto 5");
      break;
    case 0xFF5AA5:  
      Serial.println("Stisknuto 6");
      break;
    case 0xFF42BD:  
      Serial.println("Stisknuto 7");
      break;
    case 0xFF4AB5:  
      Serial.println("Stisknuto 8");
      break;
    case 0xFF52AD:  
      Serial.println("Stisknuto 9");
      break;
    default: 
      Serial.println("Stisknuta jina klavesa");
  }
  // pauza pro přehlednější výpis
  delay(500);
}
