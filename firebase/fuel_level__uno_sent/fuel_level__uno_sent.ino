#define Trig_PIN 3
#define Echo_PIN 4
#include<Wire.h>


void setup() {
pinMode(Trig_PIN, OUTPUT);
pinMode(Echo_PIN, INPUT);
Serial.begin(9600);

  Wire.begin(9);
  Wire.onRequest(requestEvent); 
}

void loop() {
digitalWrite(Trig_PIN, LOW);
delayMicroseconds(5);
digitalWrite(Trig_PIN, HIGH);
delayMicroseconds(10);
digitalWrite(Trig_PIN, LOW);
unsigned int PulseWidth = pulseIn(Echo_PIN, HIGH);
unsigned int distance = PulseWidth * 0.0173681;
Serial.print("Distance is ");
Serial.print(distance);
Serial.println(" cm.");
delay(1000);
requestEvent(distance,5);
}

void requestEvent(int d,int x){
Wire.write(d); 
Wire.write(x);
}
