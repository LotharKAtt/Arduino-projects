//hraci kostka
//pri stisku tlacitka se na ledkach rozsviti "hozene" cislo

byte tlacitko = 9; //vstup tlacitka na pin 9

//dioda2--------------dioda6 ||rozlozeni diod na kostce||
//dioda3----dioda5----dioda7
//dioda4--------------dioda8

byte cisla[6][7] = {{0, 0, 0, 1, 0, 0, 0}, //1
  {1, 0, 0, 0, 0, 0, 1}, //2
  {1, 0, 0, 1, 0, 0, 1}, //3
  {1, 0, 1, 0, 1, 0, 1}, //4
  {1, 0, 1, 1, 1, 0, 1}, //5
  {1, 1, 1, 0, 1, 1, 1} //6
};

byte ledky[7] {2, 3, 4, 5, 6, 7, 8}; //vystupy ledek na pinech 2 -8
byte randn; //promena pro generaci nahodneho cisla (pro vrh kostkou)

bool aktualniStavTlacitka; //promenna pro ulozeni aktualniho stavu tlacitka
bool minulyStavTlacitka = 0; //promenna pro ulozeni predchoziho stavu tlacitka

void setup() {
  randomSeed(analogRead(A0)); //nahodne cislo bude generovano z sumu na anal. pinu A0
  pinMode(tlacitko, INPUT); //vstup tlacitka na pin 9
  //Serial.begin(9600); //zahajeni seriove komunikace

  for (int i = 0; i <= 6; i = i + 1) {
    pinMode(ledky[i], OUTPUT); //vystupy ledek na pinech 2 -8
  }
}

void loop() {
  aktualniStavTlacitka = digitalRead(tlacitko); //zjisteni aktualniho stavu tlacitka

  if (aktualniStavTlacitka == 1 && minulyStavTlacitka == 0) {
    for (int i = 0; i <= 6; i = i + 1) {
      digitalWrite(ledky[i], LOW); //pokud prisla kladna hrana signalu, ledky zhasnou
    }

    randn = random(0, 6); //vygenerovani nahodneho cisla od 0 do 6, tedy cele cislo od 0 do 5

    for (int i = 0; i <= 6; i = i + 1) {
      if (cisla[randn][i] == 1) {
        digitalWrite(ledky[i], HIGH); //rozsviceni hozeneho cisla na ledkach
      }
    }
    delay(300);
  }
  //Serial.println(randn);
  minulyStavTlacitka = aktualniStavTlacitka; //zmena stavu tlacitka

}
