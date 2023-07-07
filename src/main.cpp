#include <SPI.h>
#include <SD.h>
File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");



  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);
if (SD.exists("test.txt")) {
    Serial.println("test.txt exists.");
  } else {
    Serial.println("test.txt doesn't exist.");
  }




  if (myFile) {  // if the file opened okay, write to it:
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    myFile.close();    // close the file:
    Serial.println("done.");
  } else {
    Serial.println("error opening test.txt");} // if the file didn't open, print an error:



  myFile = SD.open("test.txt");  // re-open the file for reading:
  if (myFile) {
    Serial.println("test.txt:");
    while (myFile.available()) {// read from the file until there's nothing else in it:
      Serial.write(myFile.read());
    }
    myFile.close();
  } else {
    Serial.println("error opening test.txt");    // if the file didn't open, print an error:
    }


  // Check to see if the file exists:
  if (SD.exists("test.txt")) {
    Serial.println("test.txt exists.");
  } else {
    Serial.println("test.txt doesn't exist.");
  }

    
  // delete the file:
  Serial.println("Removing example.txt...");
  SD.remove("test.txt");
}

void loop() {
}
