// This is a test program to write/read files onto the flash
#include "Arduino.h"
#include <SPI.h>
#include <SparkFun_SPI_SerialFlash.h>

const byte PIN_FLASH_CS = 4; // Change this to match the Chip Select pin on your board

#include <SPI.h>

#include <SparkFun_SPI_SerialFlash.h> //Click here to get the library: http://librarymanager/All#SparkFun_SPI_SerialFlash
SFE_SPI_FLASH myFlash;

void setup()
{
  Serial.begin(115200);
  Serial.println(F("SparkFun SPI SerialFlash Example"));

  //pinMode(2, OUTPUT); digitalWrite(2, HIGH); // Uncomment this line to use pin 2 to pull up (e.g.) the WP/IO2 pin
  //pinMode(3, OUTPUT); digitalWrite(3, HIGH); // Uncomment this line to use pin 3 to pull up (e.g.) the HOLD/IO3 pin

  //myFlash.enableDebugging(); // Uncomment this line to enable helpful debug messages on Serial
// Begin the flash using the chosen CS pin. Default to: spiPortSpeed=2000000, spiPort=SPI and spiMode=SPI_MODE0
  if (myFlash.begin(PIN_FLASH_CS) == false)
  {
    Serial.println(F("SPI Flash not detected. Check wiring. Maybe you need to pull up WP/IO2 and HOLD/IO3? Freezing..."));
    while (1);
  }

  Serial.println(F("SPI Flash detected"));

  sfe_flash_manufacturer_e mfgID = myFlash.getManufacturerID();
  if (mfgID != SFE_FLASH_MFG_UNKNOWN)
  {
    Serial.print(F("Manufacturer: "));
    Serial.println(myFlash.manufacturerIDString(mfgID));
  }
  else
  {
    uint8_t unknownID = myFlash.getRawManufacturerID(); // Read the raw manufacturer ID
    Serial.print(F("Unknown manufacturer ID: 0x"));
    if (unknownID < 0x10) Serial.print(F("0")); // Pad the zero
    Serial.println(unknownID, HEX);
  }

  Serial.print(F("Device ID: 0x"));
  Serial.println(myFlash.getDeviceID(), HEX);
}

void loop()
{
  Serial.println();
  Serial.println("r)ead HEX values, 1k bytes");
  Serial.println("v)iew ASCII values, 1k bytes");
  Serial.println("d)ump raw values, 1k bytes");
  Serial.println("w)rite test values, 1k bytes");
  Serial.println("e)rase entire chip");
  Serial.println();

  while (Serial.available()) Serial.read(); //Clear the RX buffer
  while (Serial.available() == 0); //Wait for a character

  byte choice = Serial.read();
// To read and print the flash memory
  if (choice == 'r')
  {
    Serial.println("Read raw values for 1024 bytes");

    for (int x = 0 ; x < 0x0400 ; x++)
    {
      if (x % 16 == 0) {
        Serial.println();
        Serial.print("0x");
        if (x < 0x100) Serial.print("0");
        if (x < 0x10) Serial.print("0");
        Serial.print(x, HEX);
        Serial.print(": ");
      }

      byte val = myFlash.readByte(x);
      if (val < 0x10) Serial.print("0");
      Serial.print(val, HEX);
      Serial.print(" ");
    }

    Serial.println();

  }
//   View ASCII for 1024 bytes
  else if (choice == 'v')
  {
    Serial.println("View ASCII for 1024 bytes");

    for (int x = 0 ; x < 0x0400 ; x++)
    {
      if (x % 16 == 0) Serial.println();

      byte val = myFlash.readByte(x);
      if (isAlphaNumeric(val))
        Serial.write(val);
    }
  }
// to   dump raw data 
  else if (choice == 'd')
  {
    for (int x = 0 ; x < 0x0400 ; x++)
    {
      byte val = myFlash.readByte(x);
      Serial.write(val);
    }
  }
//   Erasing entire chip
  else if (choice == 'e')
  {
    Serial.println("Erasing entire chip");
    myFlash.erase();
  }
// to Write test HEX values to first 1024 bytes
  else if (choice == 'w')
  {
    Serial.println("Writing test HEX values to first 1024 bytes");
    uint8_t myVal[4] = {0xDE, 0xAD, 0xBE, 0xEF};
    for (int x = 0 ; x < 0x0400 ; x += 4)
    {
      myFlash.writeBlock(x, myVal, 4); //Address, pointer, size
    }
  }
// Unknown choice  
  else
  {
    Serial.print("Unknown choice: ");
    Serial.write(choice);
    Serial.println();
  }
}