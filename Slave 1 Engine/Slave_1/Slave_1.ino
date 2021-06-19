//Tmp + Humi
#include <DHT.h>
#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//Fuel Level
#define Trig_PIN 3
#define Echo_PIN 4

//RPM 2 way
float REV = 0;
int RPM_VALUE;
int PREVIOUS = 0;
int TIME;




//Vb
int vb_1;
float vb_2;
float calb_vb;
int vb_pin = 1;

//NTC Tmp
int ThermistorPin = 2;
int Vo;
float R1 = 10000;
float logR2, R2, T_NTC;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

//Ib
int ib_sensitive = 66; // สำหรับ 30A
int ib_offset = 2500; // ค่าเริ่มต้น 2500 ปรับค่าตรงนี้เพื่อให้ค่ายังไม่มีโหลดเป็น 0.00
int ib_pin = 0;

//Lub Pr



//i2c
#include<Wire.h>
float t, h, distance, ib_result, rpm, lb_pr;
char send_temp[15];
char send_humi[15];
char send_distance[15];
char send_volt[15];
char send_amp[15];
char send_temp_c[15];
char send_rpm[15];
char send_oilpressure[15];





void setup() {

  Serial.begin(9600);

  //Tmp + Humi
  dht.begin();

  //Fuel Level
  pinMode(Trig_PIN, OUTPUT);
  pinMode(Echo_PIN, INPUT);

  //RPM 2 way
  attachInterrupt(0, INTERRUPT, RISING);

  //Vb



  //NTC Tmp





  //I2c
  Wire.begin(1);
  Wire.onRequest(requestEvent);


}

void loop() {

// random ทศนิยม
float a = random(0,9);
float b =random(0,9);
float c =random(0,9);


//Tmp + Humi
  float t =  (random(30,50)+a/10)*10;//dht.readTemperature() * 10;
  dtostrf(t, 3, 0, send_temp);

  float h =  (random(40,80)+b/10)*10;//dht.readHumidity() * 10;
  dtostrf(h, 3, 0, send_humi);


  //Fuel Level
  digitalWrite(Trig_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(Trig_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_PIN, LOW);
  unsigned int PulseWidth = pulseIn(Echo_PIN, HIGH);
  float distance =   (random(1,20)+c/10)*10;//PulseWidth * 0.0173681 * 10;
  dtostrf(distance, 3, 0, send_distance);


  //Vb
  vb_1 = analogRead(vb_pin);
  calb_vb = vb_1 / 4.092;
  vb_1 = (float)calb_vb; 
  vb_2 = (random(10,16)+a/10+b/100)*100; //(((vb_1 % 100) / 10.0)+a/100 )* 100;
  if(vb_2<10){
    vb_2=0;
  }
  dtostrf(vb_2, 4, 0, send_volt);


  //Ib
  double ib_result = (random(6,20)+b/10+a/100)*100; //abs(cal_i_avg())* 100;
  dtostrf(ib_result, 4, 0, send_amp);
  


  //NTC Temp
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T_NTC = (random(80,99)+c/10)*10;// abs(((1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2)) - 273.15) * 10);
  dtostrf(T_NTC, 3, 0, send_temp_c);
   

  //Lub_pr
  float lub_pr =(random(1,6)+c/10+b/100)*100; //315;
  dtostrf(lub_pr, 3, 0, send_oilpressure);




  //RPM 2 way
  detachInterrupt(0);
  TIME = millis() - PREVIOUS;
  RPM_VALUE = random(2900,3000);//(REV / TIME) * 60000;
  PREVIOUS = millis();
  REV = 0;
  dtostrf(RPM_VALUE, 4, 0, send_rpm);
  attachInterrupt(0, INTERRUPT, RISING);



  


Serial.println("+++++++++++++++++++++++++++++++++");
  Serial.print("Panel Temperature : ");
  Serial.println(send_temp);
  Serial.print("Cooling Water Temperature : ");
  Serial.println(send_temp_c);
  Serial.print("Panel Humidity : ");
  Serial.println(send_humi);
  Serial.print("Fuel Level : ");
  Serial.println(send_distance);
  Serial.print("Battery Voltage : ");
  Serial.println(send_volt);
  Serial.print("Battery Current : ");
  Serial.println(send_amp);
  Serial.print("Engine Speed : ");
  Serial.println(send_rpm);
  Serial.print("Lubricant Pressure : ");
  Serial.println(send_oilpressure);
  delay(3000);
  
  }

//Func Temp



//Func Humi




//Func Fuel LV




//Func Vb




//Func Ib

// หาค่ากระแสเฉลี่ย
double cal_i_avg() {
  int count = 200;
  double sum = 0;
  for (int i = 0; i < count; i++) {
    sum += ib_input();
  }
  double val = sum / count;
  return val;
}
// อ่านค่ากระแส
double ib_input() {
  int a = analogRead(ib_pin);
  double v = (a / 1024.0) * 5000;
  double ib_result = (v - ib_offset) / ib_sensitive;
  return ib_result;
}



//Func NTC



//Func Lub_Pr




//Func RPM
void INTERRUPT()
{
  REV++;
}






















// Data Sending With I2C
void requestEvent() {

  Wire.write(send_temp);

  Wire.write(send_humi);

  Wire.write(send_distance);

  Wire.write(send_volt);

  Wire.write(send_amp);

  Wire.write(send_temp_c);

  Wire.write(send_oilpressure);

  Wire.write(send_rpm);
}
