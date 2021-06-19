#include <Wire.h>

void setup()
{
 Wire.begin();        // join i2c bus (address optional for master)
 Serial.begin(9600);  // start serial for output
}

void loop()
{
 Wire.requestFrom(2, 32);    
 
   byte a = Wire.read();
   Serial.print(a);        
 byte b = Wire.read();
   Serial.print(b);  
   byte c = Wire.read();
   Serial.print(c);  

 delay(500);
}
