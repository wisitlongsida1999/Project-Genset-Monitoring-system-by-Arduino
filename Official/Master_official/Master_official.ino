
 
 
//Set WiFi
#include <ESP8266WiFi.h>                                                    // esp8266 library
#define WIFI_SSID "ART"                                             // input your home or public wifi name 
#define WIFI_PASSWORD "123456789"                                            //password of wifi ssid

//Set firebase cloud
#include <FirebaseArduino.h>                                                // firebase library
#define FIREBASE_HOST "temphumi-3ac1a.firebaseio.com"                          // the project name address from firebase id
#define FIREBASE_AUTH "4rhpUxi7clNpys6e6HieTP8b7kTGGEv51rgP2Ucx"            // the secret key generated from firebase

//Set time
#include <time.h>
int timezone = 7 * 3600;                                                
int dst = 0;
char ntp_server1[20] = "time1.nimt.or.th";
char ntp_server2[20] = "time2.nimt.or.th";
char ntp_server3[20] = "time3.nimt.or.th";



//i2c
#include<Wire.h>
String string,string1, string2, string3, string4, string5, string6, string7, string8;
float temp,humi,distance,volt,amp,rpm1,rpm2,oilpressure;
void setup() {
    Serial.begin(9600);
  delay(1000);

  //WiFi
  Serial.begin(9600);
  delay(1000);                
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address

  //Firebase  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              // connect to firebase
  
  //time                                                         
  configTime(timezone, dst, ntp_server1, ntp_server2, ntp_server3);
  Serial.println("Waiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.println("Now: " + NowString());

  //i2c
  Wire.begin(); 

}



void loop() {
//Slave 1
  Wire.requestFrom(1, 32);    

  do   
  {
    char c = Wire.read();
    string = string + c; 
    string1 = string.substring(0, 8);
    string2 = string.substring(9,16); 
    string3 = string.substring(17,24); 
    string4 = string.substring(25,32); /*
    string5 = string.substring(33,40);
    string6 = string.substring(41,48);
    string7 = string.substring(49,56);    
    string8 = string.substring(57,64);*/
    temp=string1.toFloat();
    humi=string2.toFloat();
    distance=string3.toFloat();
    volt=string4.toFloat();/*
    amp=string5.toFloat();
    rpm1=string6.toFloat();
    rpm2=string7.toFloat();
    oilpressure=string8.toFloat();*/
    
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
  Serial.print(" RPM 1 : " );
  Serial.println(rpm1);
  Serial.print(" RPM 2 : " );
  Serial.println(rpm2);
  Serial.print(" Oil Pressure : " );
  Serial.println(oilpressure);
  
delay(10000);
}

//Slave 2


//Firebase
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["Temperature"] = temp;
  root["Humidity"] = humi;
  root["Fuel level"] = distance;
  root["Battery Voltage"] = volt;
  root["Battery Current"] = amp;
  root["RPM 1"] = rpm1;
  root["RPM 2"] = rpm2;
  root["Oil Pressure"] = oilpressure;
  root["Time"] = NowString();
  
  
  String name = Firebase.push("Slave 1 ", root);
  if (Firebase.failed()) {
      Serial.print("pushing /Slave 1 failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: Slave 1 ");
  Serial.println(name);

  Firebase.setFloat("Temp",temp);
  Firebase.setFloat("Humidity",humi);
  Firebase.setFloat("Fuel level",distance);
  Firebase.setFloat("Battery Voltage",volt);
  Firebase.setFloat("Battery Current",amp);
  Firebase.setFloat("RPM 1",rpm1);
  Firebase.setFloat("RPM 2",rpm2);
  Firebase.setFloat("Oil Pressure",oilpressure);
}

}
delay(10000);


}


//Time
String NowString() {
  time_t now = time(nullptr);
  struct tm* newtime = localtime(&now);

  String tmpNow = "";
  tmpNow += String(newtime->tm_year + 1900);
  tmpNow += "-";
  tmpNow += String(newtime->tm_mon + 1);
  tmpNow += "-";
  tmpNow += String(newtime->tm_mday);
  tmpNow += " ";
  tmpNow += String(newtime->tm_hour);
  tmpNow += ":";
  tmpNow += String(newtime->tm_min);
  tmpNow += ":";
  tmpNow += String(newtime->tm_sec);
  return tmpNow;
}
