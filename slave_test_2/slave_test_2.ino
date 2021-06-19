#include <Wire.h>

void setup()
{
 Wire.begin(2);                // join i2c bus with address #2
 Wire.onRequest(requestEvent); // register event
}
byte x=5555;
byte y=6666;
byte z=7777;
void loop()
{
 delay(100);
}


void requestEvent()
{
 Wire.write(x);
                     
 Wire.write(y);
 Wire.write(z);
}
