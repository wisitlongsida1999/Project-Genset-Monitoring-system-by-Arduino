
//i2c
#include<Wire.h>
String string,string_2,string1, string2, string3, string4, string5, string6, string7, string8;
float temp,humi,distance,volt,amp,temp_c,rpm2,oilpressure;


int count = 0;
char byteArray[32]={}; 


void setup() {
    Serial.begin(9600);
  delay(1000);

  //i2c
  Wire.begin(); 

}



void loop() {
Serial.println("Start");
  int i=0;
//Slave 1
  Wire.requestFrom(1, 32);    
Serial.println("Request");

  do   
  {
    //char c = Wire.read();
    string = Wire.read();//string + c; 
    string1 = string.substring(0, 3);
    string2 = string.substring(3,6); 
    string3 = string.substring(6,9); 
    string4 = string.substring(9,13); 
    string5 = string.substring(13,17);
    string6 = string.substring(17,20);
    string7 = string.substring(20,23);    
    string8 = string.substring(23,27);
    temp=string1.toFloat()/10;
    humi=string2.toFloat()/10;
    distance=string3.toFloat()/10;
    volt=string4.toFloat()/100;
    amp=string5.toFloat()/100;
    temp_c=string6.toFloat()/10;
    oilpressure=string7.toFloat()/100;
    rpm2=string8.toFloat();
    
}

    while(Wire.available());{              

  Serial.println("Recieving float as String...");
  Serial.print("Full String: ");
  Serial.println(string);
   string = "";
 
  Serial.print(" Temp : " );
  Serial.println(temp);
  Serial.print(" Humi : " );
  Serial.println(humi);
  Serial.print(" Fuel Level : " );
  Serial.println(distance);
  Serial.print(" Battery Voltage : " );
  Serial.println(volt);
  Serial.print(" Battery Current : " );
  Serial.println(amp);
  Serial.print(" NTC : " );
  Serial.println(temp_c);
  Serial.print(" RPM 2 : " );
  Serial.println(rpm2);
  Serial.print(" Oil Pressure : " );
  Serial.println(oilpressure);
  
delay(5000);
}


}
