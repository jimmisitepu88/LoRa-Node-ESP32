#include <SPI.h>
#include <LoRa.h>

int counter = 0;

SPIClass spiLoRa(HSPI);
#define SCK_LORA 14
#define MISO_LORA 2
#define MOSI_LORA 15
#define SS_LORA 5

#define FREQ_LORA 923E6

#define resetPin 18
#define irqPin 19


void setup() {
  Serial.begin(9600);
  while (!Serial);
  //spiLoRa.begin(14,2,15,5);//SCK,MISO,MOSI,ss
  spiLoRa.begin(SCK_LORA,MISO_LORA,MOSI_LORA,SS_LORA);
  LoRa.setSPI(spiLoRa);
  LoRa.setPins(SS_LORA, resetPin, irqPin);
  if (!LoRa.begin(FREQ_LORA)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  
  Serial.println("LoRa success init");
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(5000);
}
