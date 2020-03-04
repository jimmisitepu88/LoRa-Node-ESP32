#include "FS.h"
#include "SD.h"
#include "RTClib.h"
#include "SPI.h"
#include "LoRa.h"
RTC_DS3231 rtc;

SPIClass spiSD(HSPI);
#define SD_CS 27
#define SDSPEED 27000000
File root;

const int csPin = 5;          // LoRa radio chip select
const int resetPin = 26;        // LoRa radio reset
const int irqPin = 13;

#define RXD1 33
#define TXD1 32
unsigned long cur_time, old_time;
const byte pinRST = 25;
unsigned long cur_time_wait, old_time_wait;
String str_data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, RXD1, TXD1);
  pinMode(pinRST, OUTPUT);
  digitalWrite(pinRST, HIGH);
  Serial.println("init LoRa");
  LoRa.setPins(csPin, resetPin, irqPin); // set config pin LoRa ESP32
  if (!LoRa.begin(923E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa success");delay(1000);
  Serial.println("init RTC DS3231");
   if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  Serial.println("RTC Success");delay(1000);

  Serial.println("init SD Card");
  spiSD.begin(14,2,15,27);//SCK,MISO,MOSI,ss // инициализируем HSPI1
  if(!SD.begin( SD_CS, spiSD, SDSPEED)){
  // if(!SD.begin()){
  Serial.println("Card Mount Failed");
  return;
  }
  Serial.println("found SD card");
  
  root = SD.open("/");
  printDirectory(root, 0);
  Serial.println("SD card Done");
  
  Serial.println("test ADC");
  Serial.println(dataADC(2000));

}

void loop() {
  // put your main code here, to run repeatedly:
   
}

String dataADC(unsigned long wkt){
    String buf_str_data, strADC;
    digitalWrite(pinRST, LOW); delay(500);
    digitalWrite(pinRST, HIGH);
    Serial.println("tunggu");
    cur_time_wait = millis();
    old_time_wait = cur_time_wait;
    while(cur_time_wait - old_time_wait < wkt){
      cur_time_wait = millis();
      while(Serial1.available()){
          buf_str_data = Serial1.readString();
       }
    }
    strADC = buf_str_data; buf_str_data = "";
    Serial.println(str_data);
    return strADC;
  }


void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
