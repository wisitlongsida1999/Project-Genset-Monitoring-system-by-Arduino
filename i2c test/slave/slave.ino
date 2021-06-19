#include <Wire.h>

/**
 * globals
 */

const byte DATA_SIZE = 32;
float a = 15.999;
String data[];

/**
 * setup & loop
 */

void setup()
{
    Serial.begin(115200);
    Wire.begin(9);
    Wire.onRequest(requestEvent); // data request from Master

    Serial.println("I2C Slave ready!");
}

void loop()
{
    delay(50);
}

/**
 * help functions
 */

void requestEvent()
{

    float n = 15.99;
    n = data[1];
    static byte req_number = 0;

    Wire.write(reinterpret_cast<const unsigned char*>(data[req_number].c_str()),
               data[req_number].length());

    req_number = (req_number + 1) % DATA_SIZE;
}
