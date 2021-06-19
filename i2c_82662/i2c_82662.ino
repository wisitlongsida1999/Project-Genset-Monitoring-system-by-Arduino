#include <Wire.h>

#include <DHT.h>
#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define Trig_PIN 3
#define Echo_PIN 4

float REV = 0;
int RPM_VALUE;
int PREVIOUS = 0;
int TIME;

int vb_1;
float vb_2;
float calb_vb;
int vb_pin = 1;

int ThermistorPin = 2;
int Vo;
float R1 = 10000;
float logR2, R2, T_NTC;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

int ib_sensitive = 66;
int ib_offset = 2525;
int ib_pin = 0;


int slave_address = 0x53;

float t, h, distance, ib_result, rpm, lb_pr;

char send_temp[3];
char send_humi[3];
char send_distance[3];
char send_volt[4];
char send_amp[4];
char send_temp_c[3];
char send_rpm[4];
char send_oilpressure[3];


void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(Trig_PIN, OUTPUT);
  pinMode(Echo_PIN, INPUT);
  attachInterrupt(0, INTERRUPT, RISING);
  Wire.begin(slave_address);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

void loop() {
  float t = dht.readTemperature() * 10;
  dtostrf(t, 3, 0, send_temp);

  float h = dht.readHumidity() * 10;
  dtostrf(h, 3, 0, send_humi);

  digitalWrite(Trig_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(Trig_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_PIN, LOW);
  unsigned int PulseWidth = pulseIn(Echo_PIN, HIGH);
  float distance = PulseWidth * 0.0173681 * 10;
  dtostrf(distance, 3, 0, send_distance);

  vb_1 = analogRead(vb_pin);
  calb_vb = vb_1 / 4.092;
  vb_1 = (int)calb_vb; //
  vb_2 = ((vb_1 % 100) / 10.0) * 100;
  dtostrf(vb_2, 4, 0, send_volt);

  double ib_result = abs(cal_i_avg()) * 100;
  dtostrf(ib_result, 4, 0, send_amp);

  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T_NTC = ((1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2)) - 273.15) * 10;
  dtostrf(T_NTC, 3, 0, send_temp_c);

  float lub_pr = 315;
  dtostrf(lub_pr, 3, 0, send_oilpressure);

  detachInterrupt(0);
  TIME = millis() - PREVIOUS;
  RPM_VALUE = (REV / TIME) * 60000;
  PREVIOUS = millis();
  REV = 0;
  Serial.println(RPM_VALUE);
  dtostrf(RPM_VALUE, 4, 0, send_rpm);
  attachInterrupt(0, INTERRUPT, RISING);

//  Serial.print("Temp  =");
//  Serial.println(t);
//  Serial.print("Humi =");
//  Serial.println(h);
//  Serial.print("Fuel Lv =");
//  Serial.println(distance);
//  Serial.print("Vb =");
//  Serial.println(vb_2);
//  Serial.print("NTC =");
//  Serial.print( T_NTC);
//  Serial.println(" C");
//  Serial.println(ib_result);


  Serial.print(send_temp);
  Serial.print(send_humi);
  Serial.print(send_distance);
  Serial.print(send_volt);
  Serial.print(send_amp);
  Serial.print(send_temp_c);
  Serial.print(send_oilpressure);
  Serial.print(send_rpm);
  Serial.println("---------------------------------");
}



void requestEvent() {
  float t = dht.readTemperature() * 10;
  dtostrf(t, 3, 0, send_temp);

  float h = dht.readHumidity() * 10;
  dtostrf(h, 3, 0, send_humi);

  digitalWrite(Trig_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(Trig_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_PIN, LOW);
  unsigned int PulseWidth = pulseIn(Echo_PIN, HIGH);
  float distance = PulseWidth * 0.0173681 * 10;
  dtostrf(distance, 3, 0, send_distance);

  vb_1 = analogRead(vb_pin);
  calb_vb = vb_1 / 4.092;
  vb_1 = (int)calb_vb; //
  vb_2 = ((vb_1 % 100) / 10.0) * 100;
  dtostrf(vb_2, 4, 0, send_volt);

  double ib_result = abs(cal_i_avg()) * 100;
  dtostrf(ib_result, 4, 0, send_amp);

  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T_NTC = ((1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2)) - 273.15) * 10;
  dtostrf(T_NTC, 3, 0, send_temp_c);

  float lub_pr = 315;
  dtostrf(lub_pr, 3, 0, send_oilpressure);

  detachInterrupt(0);
  TIME = millis() - PREVIOUS;
  RPM_VALUE = (REV / TIME) * 60000;
  PREVIOUS = millis();
  REV = 0;
  Serial.println(RPM_VALUE);
  dtostrf(RPM_VALUE, 4, 0, send_rpm);
  attachInterrupt(0, INTERRUPT, RISING);

  Wire.write(send_temp);
  Wire.write(send_humi);
  Wire.write(send_distance);
  Wire.write(send_volt);
  Wire.write(send_amp);
  Wire.write(send_temp_c);
  Wire.write(send_oilpressure);
  Wire.write(send_rpm);
}


void receiveEvent(int bytes)
{

}
