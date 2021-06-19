// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3

#include "EmonLib.h"                   // Include Emon Library
EnergyMonitor emon1;                   // Create an instance
int b;
float a,x=0;
int d;
float c,y=0;
int f;
float e,z=0;
void setup()
{  
  pinMode(A0,INPUT); // set pin a0 as input pin
  pinMode(A1,INPUT); // set pin a0 as input pin
  pinMode(A2,INPUT); // set pin a0 as input pin
  Serial.begin(9600);
  
  emon1.current(A3, 5);             // Current: input pin, calibration.
  emon1.current(A4, 5);             // Current: input pin, calibration.
  emon1.current(A5, 5);             // Current: input pin, calibration.
}

void loop()
{
  b=analogRead(A0);// read analog values from pin A0 across capacitor
a=(b* 0.304177);// converts analog value(x) into input ac supply value using this formula ( explained in woeking section)
delay(100);
if(x!=a)
{
Serial.print(" analaog input 1 " ) ; // specify name to the corresponding value to be printed
Serial.print(b) ; // print input analog value on serial monitor
Serial.print(" ac voltage 1 ") ; // specify name to the corresponding value to be printed
Serial.print(a/sqrt(2)) ; // prints the ac value on Serial monitor
Serial.println();
x=a;
}

else
{
delay(100);
}
  d=analogRead(A1);// read analog values from pin A0 across capacitor
c=(d* 0.304177);// converts analog value(x) into input ac supply value using this formula ( explained in woeking section)
delay(100);
if(y!=c)
{
Serial.print(" analaog input 2 " ) ; // specify name to the corresponding value to be printed
Serial.print(d) ; // print input analog value on serial monitor
Serial.print(" ac voltage 2 ") ; // specify name to the corresponding value to be printed
Serial.print(c/sqrt(2)) ; // prints the ac value on Serial monitor
Serial.println();
y=c;
}
else
{
delay(100);
}
  f=analogRead(A2);// read analog values from pin A0 across capacitor
e=(f* 0.304177);// converts analog value(x) into input ac supply value using this formula ( explained in woeking section)
delay(100);
if(z!=e)
{
Serial.print(" analaog input 3 " ) ; // specify name to the corresponding value to be printed
Serial.print(f) ; // print input analog value on serial monitor
Serial.print(" ac voltage 3 ") ; // specify name to the corresponding value to be printed
Serial.print(e/sqrt(2)) ; // prints the ac value on Serial monitor
Serial.println();
z=e;
}
else
{
delay(100);
}
  double Irms = emon1.calcIrms(1480);  // Calculate Irms only
  

  Serial.print("Current 1 : ");
  Serial.print(Irms);         // Irms
    Serial.println(" mA");


    
}
