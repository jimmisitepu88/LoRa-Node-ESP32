#include "LowPower.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);

String strADC, strBufAdC;
int adc0,adc1,adc2,adc3;
int adc4,adc5,adc6,adc7;
char data;
 
void setup(){
  Serial.begin(115200);
  mySerial.begin(9600);
  Serial.println("mulai adc");
  baca_adc();
  mySerial.print(strBufAdC);
}

void loop(){
   LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
}

void baca_adc(){
  adc0 = analogRead(A0);
  adc1 = analogRead(A1);
  adc2 = analogRead(A2);
  adc3 = analogRead(A3);
  adc4 = analogRead(A4);
  adc5 = analogRead(A5);
  adc6 = analogRead(A6);
  adc7 = analogRead(A7);
  strADC = String(adc0)+ "!";
  strADC += String(adc1)+ "@";
  strADC += String(adc2)+ "#";
  strADC += String(adc3)+ "$";
  strADC += String(adc4)+ "%";
  strADC += String(adc5)+ "^";
  strADC += String(adc6)+ "&";
  strADC += String(adc7)+ "*";
  strBufAdC = strADC; 
  strADC = "";
}
