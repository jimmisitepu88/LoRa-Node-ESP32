#include "FS.h"
#include "SD.h"
#include "SPI.h"
SPIClass spiSD(HSPI);
#define SD_CS 27
#define SDSPEED 27000000

void setup(){
  Serial.begin(115200);
  spiSD.begin(14,2,15,27);//SCK,MISO,MOSI,ss // инициализируем HSPI1
  if(!SD.begin( SD_CS, spiSD, SDSPEED)){
  // if(!SD.begin()){
  Serial.println("Card Mount Failed");
  return;
  }
  Serial.println("found SD card");
}

void loop() {
  
}
