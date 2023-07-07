
// include the SD library:
#include <SPI.h>
#include <SD.h>

File myFile;
// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
// MKRZero SD: SDCARD_SS_PIN
const int chipSelect = 53;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("\nInitializing SD card...");

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* your card is inserted correctly?");
    while (1);
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }
  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    while (1);
  }

  uint32_t volumesize;
  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
  Serial.print("Volume size (Kb):  ");
  Serial.println(volumesize);
  Serial.print("Volume size (Mb):  ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Gb):  ");
  Serial.println((float)volumesize / 1024.0);

  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);

  // open a new file and immediately close it:
  Serial.println("Creating test.txt...");
  myFile = SD.open("test.txt", FILE_WRITE);
  myFile.close();

//test exists filse
  if (SD.exists("test.txt")) {
    Serial.println("test.txt exists.");
  } else {
    Serial.println("test.txt doesn't exist.");
  }

  if (myFile) {// if the file opened okay, write to it:
    Serial.print("Writing to test.txt...");
    myFile.println("abc");
    myFile.close();// close the file:
    Serial.println("done.");
  } else {
    Serial.println("error opening test.txt");// if the file didn't open, print an error:
  }

  myFile = SD.open("test.txt"); // re-open the file for reading:
  if (myFile) {
    Serial.println("test.txt:");
    while (myFile.available()) {  // read from the file until there's nothing else in it:
      Serial.write(myFile.read());
    }
    myFile.close();// close the file:
  } else {
    Serial.println("error opening test.txt");// if the file didn't open, print an error:
  }

  // delete the file:
  Serial.println("Removing test.txt...");
  SD.remove("test.txt");

}


void loop(void) {
}
