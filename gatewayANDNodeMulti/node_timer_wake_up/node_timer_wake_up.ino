uint64_t chipid;
String id, buf_id;
char ssid[13];

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  5        /* Time ESP32 will go to sleep (in seconds) */

#include"lora_adc.h"
lora_adc lora;
String strADC;
int ADC0,ADC1,ADC2, ADC3;
int ADC4,ADC5,ADC6, ADC7;
  
#include "SPI.h"
#include "LoRa.h"

const int csPin = 5;          // LoRa radio chip select
const int resetPin = 26;        // LoRa radio reset
const int irqPin = 13;          // change for your board; must be a hardware interrupt pin

unsigned long curWaitReplay, oldWaitReplay;

void setup(){
  Serial.begin(115200);
  delay(1000); //Take some time to open up the Serial Monitor
  get_id();
  lora.begin();
  
  Serial.println("LoRa Sender");
  LoRa.setPins(csPin, resetPin, irqPin);
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("found LoRa");
  send_LoRa();
  
  LoRa.onReceive(onReceive);
  //LoRa_rxMode();
  
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Going to sleep now");
  Serial.flush(); 
  esp_deep_sleep_start();
}

void loop(){
  //This is not going to be called
}

bool send_LoRa(){
  bool sts_send;

  while(!lora.getADC()){
    delay(1000);
    Serial.println("coba baca adc");
  }
    ADC0 = lora.adc0();
    ADC1 = lora.adc1();
    ADC2 = lora.adc2();
    ADC3 = lora.adc3();

    ADC4 = lora.adc4();
    ADC5 = lora.adc5();
    ADC6 = lora.adc6();
    ADC7 = lora.adc7();
    strADC = id + "?";
    strADC += String(ADC0)+"!";
    strADC += String(ADC1)+"@";
    strADC += String(ADC2)+"#";
    strADC += String(ADC3)+"$";
    strADC += String(ADC4)+"%";
    strADC += String(ADC5)+"^";
    strADC += String(ADC6)+"&";
    strADC += String(ADC7)+"*";
    Serial.println(strADC);  
  // send packet
  LoRa_sendMessage(strADC);
  //waitReplay(2000);
  return sts_send;
}

void get_id(){
  chipid=ESP.getEfuseMac();//The chip ID is essentially its MAC address(length: 6 bytes).
  uint16_t chip = (uint16_t)(chipid >> 32);
  snprintf(ssid, 13, "%04X%08X", chip, (uint32_t)chipid);
  for ( int i=0; i < 12; i++){
    buf_id += String(ssid[i]);
  }
  id = buf_id; buf_id="";
}

void LoRa_rxMode(){
  LoRa.enableInvertIQ();                // active invert I and Q signals
  LoRa.receive();                       // set receive mode
}

void LoRa_txMode(){
  LoRa.idle();                          // set standby mode
  LoRa.disableInvertIQ();               // normal mode
}

void LoRa_sendMessage(String message) {
  LoRa_txMode();                        // set tx mode
  LoRa.beginPacket();                   // start packet
  LoRa.print(message);                  // add payload
  LoRa.endPacket();                     // finish packet and send it
  LoRa_rxMode();                        // set rx mode
}

void onReceive(int packetSize) {
  String strIdReplay = "";
  while (LoRa.available()) {
    strIdReplay += (char)LoRa.read();
  }

  Serial.print("Node Receive: ");
  Serial.println(strIdReplay);

}

void waitReplay(unsigned long _Wait){
  Serial.println("tunggu");
  LoRa_rxMode();
  curWaitReplay = millis();
  oldWaitReplay = curWaitReplay;
  while (curWaitReplay - oldWaitReplay < _Wait){
    curWaitReplay = millis();
    
  }
}
