//Tmp + Humi
#include <DHT.h> 
#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
 Serial.begin(9600);
dht.begin();   
}
 
void loop()
{
float t = dht.readTemperature();                                          
float h = dht.readHumidity();    
 Serial.print("Temp  =");                                        
Serial.println(t);
 Serial.print("Humi =");
Serial.println(h);
delay(1000);
}
