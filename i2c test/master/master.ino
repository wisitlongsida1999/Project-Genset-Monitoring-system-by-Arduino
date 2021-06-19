#include <Wire.h> 

/**
 * globals
 */

int esc = 0;
int throttle = 80;    
char i2c_buffer[33];

/**
 * setup & loop
 */

void setup()
{
    Serial.begin(115200);
    Wire.begin();

    esc = throttle * 100 / 180;
    i2c_buffer[32] = '\0';

    Serial.println("I2C Master ready!");
}

void loop()
{
    delay(500);

    Wire.requestFrom(9, 32);

    for (byte i = 0; i < 32 && Wire.available(); ++i)
    {
        i2c_buffer[i] = Wire.read();

        if (i2c_buffer[i] == '#') {
            i2c_buffer[i] = '\0';
            break;
        }
    }

    Serial.print(esc);
    Serial.print(',');
    Serial.println(i2c_buffer);
}
