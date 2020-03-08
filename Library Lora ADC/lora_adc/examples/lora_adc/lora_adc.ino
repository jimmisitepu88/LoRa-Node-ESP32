#include<lora_adc.h>

lora_adc lora;
String txt; 
int ADC0,ADC1,ADC2, ADC3;
int ADC4,ADC5,ADC6, ADC7;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  lora.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  if(lora.getADC()){
    ADC0 = lora.adc0();
    ADC1 = lora.adc1();
    ADC2 = lora.adc2();
    ADC3 = lora.adc3();

    ADC4 = lora.adc4();
    ADC5 = lora.adc5();
    ADC6 = lora.adc6();
    ADC7 = lora.adc7();

    Serial.print("ADC :");
    Serial.print(ADC0);Serial.print(",");
    Serial.print(ADC1);Serial.print(",");
    Serial.print(ADC2);Serial.print(",");
    Serial.print(ADC3);Serial.print(",");
    Serial.print(ADC4);Serial.print(",");
    Serial.print(ADC5);Serial.print(",");
    Serial.print(ADC6);Serial.print(",");
    Serial.print(ADC7);Serial.println();
  }else{
    Serial.println("fail get ADC");
  }
}
