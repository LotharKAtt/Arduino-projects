// RFID čtečka - ukázka čtení adres tagů

// připojení knihoven SPI a MFRC522
#include <SPI.h>
#include <MFRC522.h>

// definování pinů pro SDA a RST
#define SDA_PIN 10
#define RST_PIN 9

// vytvoření instance RFID čtečky z knihovny
MFRC522 rfid(SDA_PIN, RST_PIN);

void setup() {
  // komunikace přes sériovou linku rychlostí 9600 baud
  Serial.begin(9600);
  // inicializace komunikace přes SPI
  SPI.begin();
  // inicializace komunikace s RFID čtečkou
  rfid.PCD_Init();
}

void loop() {
  // kontrola RFID tagů v okolí modulu,
  // pokud není žádný tag v okolí, volá se loop funkce od začátku,
  // celá část s RFID by tedy měla být na konci programu
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  // kontrola správného přečtení RFID tagu
  if ( ! rfid.PICC_ReadCardSerial())
    return;
  // výpis informace o verzi RFID tagu
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.print("RFID tag typu: ");
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // kontrola podporovaných typů RFID tagu
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println("Tento RFID tag neni podporovany (typ MIFARE Classic).");
    return;
  }
  // výpis adresy RFID tagu v hexa formátu
  Serial.print("Adresa RFID tagu: ");
  vypisHex(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();

  if(rfid.uid.uidByte[0] == 0xB3 & rfid.uid.uidByte[1] == 0xDB & rfid.uid.uidByte[2] == 0x2D & rfid.uid.uidByte[3] == 0x5B) {
    Serial.println("Detekovana bila karta!");
  }
  else if(rfid.uid.uidByte[0] == 0xB0 & rfid.uid.uidByte[1] == 0xAA & rfid.uid.uidByte[2] == 0x69 & rfid.uid.uidByte[3] == 0x89) {
    Serial.println("Detekovan modry privesek!");
  }
  /* ukázka přidání dalšího tagu
  else if(rfid.uid.uidByte[0] == 0x?? & rfid.uid.uidByte[1] == 0x?? & rfid.uid.uidByte[2] == 0x?? & rfid.uid.uidByte[3] == 0x??) {
    Serial.println("Detekovan novy tag ..!");
  } 
   */
  else {
    Serial.println("Detekovan neznamy RFID tag!");
  }
  Serial.println();
  // ukončení komunikace a jejího zabezpečení
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
// podprogram pro výpis adresy RFID tagu v hexa formátu
void vypisHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
