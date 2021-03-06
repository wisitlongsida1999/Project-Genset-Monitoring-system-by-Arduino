#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#define PIN_WIRE_SDA (4)
#define PIN_WIRE_SCL (5)

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

#define LED_BUILTIN 2

static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t RX   = 3;
static const uint8_t TX   = 1;

#include "../generic/common.h"

#endif /* Pins_Arduino_h */

#include <ESP8266WiFi.h>                                                    // esp8266 library
#include <FirebaseArduino.h>                                                // firebase library
#include <time.h>

#define FIREBASE_HOST "temphumi-3ac1a.firebaseio.com"                          // the project name address from firebase id
#define FIREBASE_AUTH "4rhpUxi7clNpys6e6HieTP8b7kTGGEv51rgP2Ucx"            // the secret key generated from firebase

#define WIFI_SSID "ART"                                             // input your home or public wifi name 
#define WIFI_PASSWORD "123456789"                                            //password of wifi ssid
 


int timezone = 7 * 3600;                                                
int dst = 0;
char ntp_server1[20] = "time1.nimt.or.th";
char ntp_server2[20] = "time2.nimt.or.th";
char ntp_server3[20] = "time3.nimt.or.th";

  #include<Wire.h>

void setup() {
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

  
  configTime(timezone, dst, ntp_server1, ntp_server2, ntp_server3);
  Serial.println("Waiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.println("Now: " + NowString());

  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              // connect to firebase
  
                                                             //Start reading dht sensor
  
  Wire.begin(); 

}



void loop() {

   Wire.requestFrom(9, 1);      // ?????????????????????????????????????????? Slave
    while(Wire.available()){                 // ???????????????????????????????????????????????????
      int d = Wire.read();                  
     
   Wire.requestFrom(10, 2);  
    while(Wire.available()){                 // ???????????????????????????????????????????????????
      int t = Wire.read();                  
      int h = Wire.read();

Serial.println(d);
Serial.println(t);
Serial.println(h);

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["Temperature"] = t;
  root["Humidity"] = h;
  root["Fuel level"] = d;
  root["Time"] = NowString();
  
  // append a new value to /logDHT
  String name = Firebase.push("logDHT", root);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /logDHT/");
  Serial.println(name);

  Firebase.setFloat("Temp",t);
  Firebase.setFloat("Humidity",h);
  Firebase.setFloat("Fuel level",d);
  
}

}
delay(10000);
}

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
