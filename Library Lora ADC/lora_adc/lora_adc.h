#ifndef lora_adc_h
#define lora_adc_h


class lora_adc
{
private:
    byte RST; unsigned int BAUD;
public:
    lora_adc(byte pinRST, unsigned int baud);
    void begin(byte pinRST, unsigned int baud);
    bool getADC();
    int adc0();int adc1();int adc2();int adc3();
    int adc4();int adc5();int adc6();int adc7();
    String _data();
};

#endif