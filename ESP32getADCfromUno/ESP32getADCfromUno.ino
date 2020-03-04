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
}

void loop() {
  // put your main code here, to run repeatedly:
   Serial.println(dataADC(2000));
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
