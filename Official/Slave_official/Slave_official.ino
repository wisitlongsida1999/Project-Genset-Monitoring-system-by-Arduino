
//Tmp + Humi
#include <DHT.h> 
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//Fuel Level
#define Trig_PIN 3
#define Echo_PIN 4

//RPM 2 way
int chk11;
int chk12;
int sp1_PIN = 5;
int sp2_PIN = 6;
int count_sp1 = 0;
int count_sp2 = 0;
unsigned long lastmillis = 0;

//i2c
#include<Wire.h> 
float temp,humi,distance,volt,amp,rpm1,rpm2,oilpressure;
char send_temp[8];
char send_humi[8];
char send_distance[8];
char send_volt[8];
char send_amp[8];
char send_rpm1[8];
char send_rpm2[8];
char send_oilpressure[8];

void setup() {
  
Serial.begin(9600);

//Temp + Humi
dht.begin();     

//Fuel Level
pinMode(Trig_PIN, OUTPUT);
pinMode(Echo_PIN, INPUT); 

pinMode(sp1_PIN, INPUT);
pinMode(sp2_PIN, INPUT);
 
Wire.begin(1);
Wire.onRequest(requestEvent); 


}

void loop() {

//Tmp + Humi
float temp = dht.readTemperature();                                          
float humi = dht.readHumidity();                                            
Serial.println(temp);
Serial.println(humi);
delay(1000);

//Fuel Level
digitalWrite(Trig_PIN, LOW);
delayMicroseconds(5);
digitalWrite(Trig_PIN, HIGH);
delayMicroseconds(10);
digitalWrite(Trig_PIN, LOW);
unsigned int PulseWidth = pulseIn(Echo_PIN, HIGH);
float distance = PulseWidth * 0.0173681;
Serial.println(distance);                    
delay(1000);

//RPM 2 way
while(millis() - lastmillis == 1000){     // Limit at 1 sec

while(digitalRead(sp1_PIN) == 1) {        // Check sensor 1
chk11++;
// Serial.println(chk11);
  }

while(chk11 > 0) {                        // Count
count_sp1++;
Serial.print("Round1 = "); Serial.println(count_sp1);
chk11 = 0;
}

while(digitalRead(sp2_PIN) == 1) {        // Check sensor 2
chk12++;
// Serial.println(chk12);
  }

while(chk12 > 0) {                       // Count
count_sp2++;
Serial.print("Round2 = "); Serial.println(count_sp2);
chk12 = 0;
}
}

Serial.print("rpm1 = "); Serial.println(count_sp1*60);
count_sp1=0;

Serial.print("rpm2 = "); Serial.println(count_sp2*60);
count_sp2=0;

lastmillis = millis();                      // Set every 1 sec


}



  



// Data Sending With I2C
void requestEvent(){
  
 //Temp+Humi
float temp = dht.readTemperature();      
dtostrf(temp, 8, 2, send_temp); 
Wire.write(send_temp);                                   
float humi = dht.readHumidity();                                              
dtostrf(humi, 8, 2, send_humi); 
Wire.write(send_humi);

//Fuel lv.
digitalWrite(Trig_PIN, LOW);
delayMicroseconds(5);
digitalWrite(Trig_PIN, HIGH);
delayMicroseconds(10);
digitalWrite(Trig_PIN, LOW);
unsigned int PulseWidth = pulseIn(Echo_PIN, HIGH);
float distance = PulseWidth * 0.0173681;
dtostrf(distance, 8, 2, send_distance); 
Wire.write(send_distance);

//volt
volt = 14.44;
dtostrf(volt, 8, 2, send_volt); 
Wire.write(send_volt);
/*
//amp
amp=0.32;
dtostrf(amp, 8, 2, send_amp); 
Wire.write(send_amp);

//rpm1
rpm1=3000;
dtostrf(rpm1, 8, 2, send_rpm1); 
Wire.write(send_rpm1);

//rpm2
rpm2=1500;
dtostrf(rpm2, 8, 2, send_rpm2); 
Wire.write(send_rpm2);

//oilpressure
oilpressure=1.42;
dtostrf(oilpressure, 8, 2, send_oilpressure); 
Wire.write(send_oilpressure);
*/


      }
