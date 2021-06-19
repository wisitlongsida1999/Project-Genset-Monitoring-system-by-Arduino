
#include <DHT.h>                                                            // dht11 temperature and humidity sensor library



 
#define DHTPIN 2                                                           // what digital pin we're connected to
#define DHTTYPE DHT11                                                       // select dht type as DHT 11 or DHT22
DHT dht(DHTPIN, DHTTYPE);     



  #include<Wire.h>
  
  
void setup() {
  Serial.begin(9600);

  
  dht.begin();                                                               //Start reading dht sensor
  
   Wire.begin(10);
  Wire.onRequest(requestEvent); 

}



void loop() {

    int t = dht.readTemperature();                                           // Read temperature as Celsius (the default)
  int h = dht.readHumidity();                                              // Reading temperature or humidity takes about 250 milliseconds!
Serial.println(t);
Serial.println(h);
delay(1000);
}


void requestEvent(){
 
  int t = dht.readTemperature();                                           // Read temperature as Celsius (the default)
  int h = dht.readHumidity();                                              // Reading temperature or humidity takes about 250 milliseconds!
  Wire.write(t);  
  Wire.write(h);  


      }
