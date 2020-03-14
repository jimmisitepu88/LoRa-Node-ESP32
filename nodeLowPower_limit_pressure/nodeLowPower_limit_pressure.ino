#include <SPI.h>              // include libraries
#include <LoRa.h>

const long frequency = 923.1E6;  // LoRa Frequency

const int csPin = 21;          // LoRa radio chip select
const int resetPin = 22;        // LoRa radio reset
const int irqPin = 17;          // change for your board; must be a hardware interrupt pin

unsigned long curTime, oldTime;
String bufMessage;

void setup() {
  Serial.begin(115200);                   // initialize serial
  while (!Serial);
  LoRa.setPins(csPin, resetPin, irqPin);

  if (!LoRa.begin(frequency)) {
    Serial.println("LoRa init failed");
    while (true);                       // if failed, do nothing
  }
  Serial.println("LoRa Success");
  LoRa_sendMessage("alarm");
  LoRa.onReceive(onReceive);
  LoRa_rxMode();
  while(!tunggu(2000)){
    Serial.println("kirim lagi");
    LoRa_sendMessage("alarm");
    delay(5000);
  }
}
void loop() {
  
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
  String message = "";

  while (LoRa.available()) {
    message += (char)LoRa.read();
  }
  bufMessage = message;
  Serial.print("Node Receive: ");
  Serial.println(message);
}

bool tunggu(unsigned long waktu){
  bool sts;
  curTime = millis();
  oldTime = curTime;
  while ( curTime - oldTime < waktu){
    curTime = millis();
    if(bufMessage == "OK"){
       sts = 1;
      Serial.println("break");
      break;
    }else{
      sts = 0;
    }
  }
  return sts;
}
