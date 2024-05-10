# FlashMemory_ESP32
FlashMemory_ESP32
Project to write to and read from Winbond W25Q128FV flash memory with an ESP32 Arduino using its VSPI.
  This sketch demonstrates how to interact with SPI flash such as the:
  128mb W25Q128JV
  4mbit AT25SF041
  16mbit GD25Q16C
  64mbit AT45DB641E
  32mbit IS25WP032D

  If you are using (e.g.) the W25Q128JV - as used on the SparkX Serial Flash Breakout -
  you will need to pull the WP/IO2 and HOLD/IO3 pins high otherwise the chip will not communicate.

* **In order for this program to work the frequency of the SPI needs to be lowered from 50MHz to 5MHz or even lower (lib/SerialFlash/SerialFlashChip.cpp line 33 SPICONFIG)**
## Pin layout
This is how the ESP32 should be connected to the W25Q128FV chip


| ESP32 | W25Q128FV |
| ------------- | ------------- |
| 3.3V  | VCC |
|  GPIO4 | CS  |
|  GPIO18 | CLK |
|  GPIO19 | MISO  |
| GPIO23  | MOSI  |

