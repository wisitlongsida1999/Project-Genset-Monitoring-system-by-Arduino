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


Wire.begin(1);
Wire.onRequest(requestEvent); 
//Wire.onRequest(requestEvent2); 

}

void loop() {
oilpressure=1.42;
rpm2=1500;
rpm1=3000;
volt = 14.44;
distance = 29.54;
amp=0.32;
return distance;
}


// Data Sending With I2C
void requestEvent(){
Serial.println("Start");
 int i=0;
 Serial.println(i);
 while(i==0) {
 //Temp+Humi
float temp = 33.45;
dtostrf(temp, 8, 2, send_temp); 
Wire.write(send_temp);                                   
float humi = 45.66;                                
dtostrf(humi, 8, 2, send_humi); 
Wire.write(send_humi);

//Fuel lv.


dtostrf(distance, 8, 2, send_distance); 
Wire.write(send_distance);

//volt

dtostrf(volt, 8, 2, send_volt); 
Wire.write(send_volt);



dtostrf(amp, 8, 2, send_amp); 
Wire.write(send_amp);

//rpm1

dtostrf(rpm1, 8, 2, send_rpm1); 
Wire.write(send_rpm1);

//rpm2

dtostrf(rpm2, 8, 2, send_rpm2); 
Wire.write(send_rpm2);

//oilpressure

dtostrf(oilpressure, 8, 2, send_oilpressure); 
Wire.write(send_oilpressure);
i++;

      }
      Serial.println(i);
 }
/*
// Data Sending With I2C2
void requestEvent2(){


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


      }
      
 
*/
 
