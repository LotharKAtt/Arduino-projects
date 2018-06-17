// created  28 Mar 2011
// by Limor Fried
// modified 9 Apr 2012
// by Tom Igoe
// modifed 23.3.2013
// by Pavel Putna

#include <SD.h>

// nastaví proměné pro info karty
Sd2Card card;
SdVolume volume;
SdFile root;

// nastavte správně
// Arduino Ethernet shield: pin 4 - náš případ
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
const int chipSelect = 4;

void setup()
{
  Serial.begin(115200);

  Serial.print("\nInicializace SD karty...");
  pinMode(4, OUTPUT);

  // inicializace
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("\nPametova karta nebyla detekovana");
    return;
  } else {
    Serial.println("\nPametova karta nalezena.");
  }

  // Určí typ karty
  Serial.print("\nTyp karty: ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Neznama");
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println("System souboru FAT16/FAT32 nenalezen.\nZkuste naformatovat kartu");
    return;
  }

  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("\nVolume type is FAT");
  Serial.println(volume.fatType(), DEC);
  Serial.println();

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize *= 512;                            // SD card blocks are always 512 bytes
  Serial.print("Volume size (bytes): ");
  Serial.println(volumesize);
  Serial.print("Volume size (Kbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Mbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);


  Serial.println("\nNalezene soubory na karte (nazev, datum a velikost v bajtech): ");
  root.openRoot(volume);

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
}

void loop(void) {
}
