#include <Arduino.h>
#include<lora_adc.h>

#define RXD1 33
#define TXD1 32

const byte pinRST = 25;
unsigned curTime, oldTime;
String str_data;
String buf_str_data;
String sts;

String strADC0,strADC1, strADC2, strADC3;
String strADC4,strADC5, strADC6, strADC7;

int lenADC0,lenADC1, lenADC2, lenADC3;
int lenADC4,lenADC5, lenADC6, lenADC7;
int lenSTS;

void tunggu_data(unsigned long _wkt);
void parsing_str();
char _bufDT[45];

void lora_adc::begin(){
    Serial1.begin(4800, SERIAL_8N1, RXD1, TXD1);
    pinMode(pinRST, OUTPUT);
    digitalWrite(pinRST, HIGH);
}

String lora_adc::_data(){
    String _Data;
    tunggu_data(500);
    _Data = str_data;
    return _Data;
} 

bool lora_adc::getADC(){
    bool _sts;
    tunggu_data(500);
    parsing_str();

    if(sts == "1"){
        _sts = 1;
    }
    else{
        _sts = 0;
    }
    return _sts;
}

int lora_adc::adc0(){
    int _adc0;
    _adc0 = strADC0.toInt();
    return _adc0;
}

int lora_adc::adc1(){
    int _adc1;
    _adc1 = strADC1.toInt();
    return _adc1;
}

int lora_adc::adc2(){
    int _adc2;
    _adc2 = strADC2.toInt();
    return _adc2;
}

int lora_adc::adc3(){
    int _adc3;
    _adc3 = strADC3.toInt();
    return _adc3;
}

int lora_adc::adc4(){
    int _adc4;
    _adc4 = strADC4.toInt();
    return _adc4;
}

int lora_adc::adc5(){
    int _adc5;
    _adc5 = strADC5.toInt();
    return _adc5;
}

int lora_adc::adc6(){
    int _adc6;
    _adc6 = strADC6.toInt();
    return _adc6;
}

int lora_adc::adc7(){
    int _adc7;
    _adc7 = strADC7.toInt();
    return _adc7;
}

void tunggu_data(unsigned long _wkt){
    int i=0;
    digitalWrite(pinRST, LOW); delay(500);
    digitalWrite(pinRST, HIGH);
    curTime = millis();
    oldTime = curTime;
    while(curTime-oldTime<_wkt){
        curTime = millis();
        while (Serial1.available())
        {
            _bufDT[i] = Serial1.read();
            i++;
        }
        
    }
    for(int j = 1; j<i; j++){
        buf_str_data += (_bufDT[j]);
    }
    str_data = buf_str_data;
    buf_str_data = "";
}

void parsing_str(){
    lenADC0 = str_data.indexOf('!');
    lenADC1 = str_data.indexOf('@');
    lenADC2 = str_data.indexOf('#');
    lenADC3 = str_data.indexOf('$');
    lenADC4 = str_data.indexOf('%');
    lenADC5 = str_data.indexOf('^');
    lenADC6 = str_data.indexOf('&');
    lenADC7 = str_data.indexOf('*');
    lenSTS =  str_data.indexOf('?');
    
    strADC0 = str_data.substring(0, lenADC0); 
    strADC1 = str_data.substring(lenADC0+1, lenADC1);
    strADC2 = str_data.substring(lenADC1+1, lenADC2);
    strADC3 = str_data.substring(lenADC2+1, lenADC3);
    strADC4 = str_data.substring(lenADC3+1, lenADC4);
    strADC5 = str_data.substring(lenADC4+1, lenADC5);
    strADC6 = str_data.substring(lenADC5+1, lenADC6);
    strADC7 = str_data.substring(lenADC6+1, lenADC7);
    sts = str_data.substring(lenADC7+1, lenSTS);
}
