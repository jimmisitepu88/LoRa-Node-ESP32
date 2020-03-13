#include "SPI.h"              // include libraries
#include "LoRa.h"

const long frequency = 915E6;  // LoRa Frequency

const int csPin = 17;          // LoRa radio chip select
const int resetPin = 16;        // LoRa radio reset
const int irqPin = 27;        // change for your board; must be a hardware interrupt pin

String message, buf_message;
int lenId;
int lenAdc0,lenAdc1,lenAdc2,lenAdc3; 
int lenAdc4,lenAdc5,lenAdc6,lenAdc7;

String id, bufId;
String strADC0,strADC1, strADC2,strADC3;
String strADC4,strADC5, strADC6,strADC7;

double startMikros, stopMikros, durMikros; 

void setup() {
  Serial.begin(115200);                   // initialize serial
  while (!Serial);  
  LoRa.setPins(csPin, resetPin, irqPin);
  if (!LoRa.begin(frequency)) {
    Serial.println("LoRa init failed. Check your connections.");
    while (true);                       // if failed, do nothing
  }

  //Serial.println("LoRa init succeeded.");
  LoRa.onReceive(onReceive);
  LoRa_rxMode();
   
}

void loop() {
  if( id != bufId){
	//LoRa_txMode(); //active if will process more time here
    Serial.println(message);
    Serial.print("ADC0: ");Serial.print(strADC0);Serial.print(", ADC1: ");Serial.print(strADC1);
    Serial.print(", ADC2: ");Serial.print(strADC2);Serial.print(", ADC3: ");Serial.println(strADC3);
    Serial.print("ADC4: ");Serial.print(strADC4);Serial.print(", ADC5: ");Serial.print(strADC5);
    Serial.print(", ADC6: ");Serial.print(strADC6);Serial.print(", ADC7: ");Serial.println(strADC7);
    Serial.println();
    bufId = id;
	//LoRa_rxMode(); //active if will process more time here
  }
}

void LoRa_rxMode(){
  LoRa.disableInvertIQ();               // normal mode
  LoRa.receive();                       // set receive mode
}

void LoRa_txMode(){
  LoRa.idle();                          // set standby mode
  LoRa.enableInvertIQ();                // active invert I and Q signals
}

void onReceive(int packetSize) {
  startMikros = micros();
  stopMikros = startMikros;
  while (LoRa.available()) {
    buf_message += (char)LoRa.read();
  }  
  message = buf_message; buf_message = "";
  
  parse_message();
  stopMikros = micros();
  durMikros = stopMikros-startMikros;
  durMikros = durMikros/1000000L;
  //Serial.print("duration: ");
  //Serial.print(durMikros,5);
  //Serial.println(" Second");
}

void LoRa_sendMessage(String _replay) {
  LoRa_txMode();                        // set tx mode
  Serial.println("send id");  
  LoRa.beginPacket();                   // start packet
  LoRa.print(_replay);                  // add payload
  LoRa.endPacket();                     // finish packet and send it
  LoRa_rxMode();                        // set rx mode
}

void parse_message(){
  lenId = message.indexOf('?');
  lenAdc0 = message.indexOf('!');
  lenAdc1 = message.indexOf('@');
  lenAdc2 = message.indexOf('#');
  lenAdc3 = message.indexOf('$');

  lenAdc4 = message.indexOf('%');
  lenAdc5 = message.indexOf('^');
  lenAdc6 = message.indexOf('&');
  lenAdc7 = message.indexOf('*');

  id = message.substring(0, lenId);
  strADC0 = message.substring(lenId+1, lenAdc0);
  strADC1 = message.substring(lenAdc0+1, lenAdc1);
  strADC2 = message.substring(lenAdc1+1, lenAdc2);
  strADC3 = message.substring(lenAdc2+1, lenAdc3);

  strADC4 = message.substring(lenAdc3+1, lenAdc4);
  strADC5 = message.substring(lenAdc4+1, lenAdc5);
  strADC6 = message.substring(lenAdc5+1, lenAdc6);
  strADC7 = message.substring(lenAdc6+1, lenAdc7);
  
  //Serial.print("id: ");
  //Serial.println(id);
  
  //Serial.println(message);
  
  /*Serial.print("ADC0: ");Serial.print(strADC0);Serial.print(", ADC1: ");Serial.print(strADC1);
  Serial.print(", ADC2: ");Serial.print(strADC2);Serial.print(", ADC3: ");Serial.println(strADC3);
  Serial.print("ADC4: ");Serial.print(strADC4);Serial.print(", ADC5: ");Serial.print(strADC5);
  Serial.print(", ADC6: ");Serial.print(strADC6);Serial.print(", ADC7: ");Serial.println(strADC7);
  */
}
