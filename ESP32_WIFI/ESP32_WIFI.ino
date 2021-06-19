//Set WiFi
#include<WiFi.h>
#define WIFI_STA_NAME "ART"
#define WIFI_STA_PASS "123456789"
int wifi_count=0;

//Line Notify
#include <ESP_Line_Notify.h>
  /* Define the LineNotifyClient object */
  LineNotiFyClient client;
  //Sticker Source : http://cons-robotics.com/LINEAPI/sticker.pdf
  
//Set firebase cloud
#include <IOXhop_FirebaseESP32.h>                                           // firebase library
#define FIREBASE_HOST "test-app-android-studio.firebaseio.com"              // the project name address from firebase id
#define FIREBASE_AUTH "UAsnKUjoH48RnvMqx8GQrhcp5GsuUK8bByvHFnzf"            // the secret key generated from firebase

//Set time
#include <time.h>
int timezone = 7 * 3600;                                                
int dst = 0;
char ntp_server1[20] = "time1.nimt.or.th";
char ntp_server2[20] = "time2.nimt.or.th";
char ntp_server3[20] = "time3.nimt.or.th";



//i2c
#include<Wire.h>
String string,string_2,string1, string2, string3, string4, string5, string6, string7, string8;
float temp,humi,fuel_lv,vb,ib,cw_temp,rpm,lub_pr;
float vg1,vg2,vg3,ig1,ig2,ig3,f,pf,s,p;


//SD Card
#include "FS.h"
#include "SD.h"
#include <SPI.h>
#include <RTClib.h>
#define SD_CS 5
RTC_DS1307 rtc;
String dataMessage;



void setup() {

  //WiFi
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_STA_NAME);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_STA_NAME, WIFI_STA_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    wifi_count+=1;
    Serial.print(wifi_count);
    if(wifi_count==15){
    Serial.print("  >>>>>>>>>>>>>>>>  Restart ESP 32");
    ESP.restart();
     }
  }
    wifi_count=0;
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
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


    
   //Line
  client.token = "aAMbETXqFN3BV9tv346MOWuOUMEnx82ibB3ZiQDuLuR";
  client.reconnect_wifi = true;
  client.message = "Generator Set Operating System is ONLINE !!!";
  client.sticker.package_id = 1;
  client.sticker.id = random(136,139);
  LineNotify.send(client);


  /*
  // setup for the RTC
  while(!Serial); // for Leonardo/Micro/Zero
    if(! rtc.begin()) {
      Serial.println("Couldn't find RTC");
      while (1);
    }
    else {
      // following line sets the RTC to the date & time this sketch was compiled
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    if(! rtc.isrunning()) {
      Serial.println("RTC is NOT running!");
    }
    */

  
  // Initialize SD card
  SD.begin(SD_CS);  
  if(!SD.begin(SD_CS)) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();
  if(cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }
  Serial.println("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    Serial.println("ERROR - SD card initialization failed!");
    return;    // init failed
  }
  File file = SD.open("/genset_data_log.txt");
  if(!file) {
    Serial.println("File doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/genset_data_log.txt", "Date,Time,Temperature ( °C ),Humidity ( % ),Battery Voltage ( V ),Battery Current ( A ),Lubricant Pressure ( Bar ),Fuel Level ( L ),Engine Speed ( Rpm ),Cooling Water Temperature ( °C ),Generator Voltage 1 ( V ),Generator Voltage 2 ( V ),Generator Voltage 3 ( V ),Generator Current 1 ( A ),Generator Current 2 ( A ),Generator Current 3 ( A ),Apparent Power( kVA ),Real Power ( kW ),Power Factor,Frequency( Hz ) \r\n");
  }
  else {
    Serial.println("File already exists");  
  }
  file.close();

  /*
  //Prepare System
  delay(5000);

  
*/
  
  
}

void loop() {
  
  
  //Slave 1
  i2c_request_s1:
  Wire.requestFrom(1, 32);    
  Serial.println("Request");

  do   
  {
    char c = Wire.read();
    string = string + c; 
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
    fuel_lv=string3.toFloat()/10;
    vb=string4.toFloat()/100;
    ib=string5.toFloat()/100;
    cw_temp=string6.toFloat()/10;
    lub_pr=string7.toFloat()/100;
    rpm=string8.toFloat();
    
}

  while(Wire.available());{              

  Serial.println("Recieving float as String...");
  Serial.print("Full String: ");
  Serial.println(string);
  string = "";
 
  Serial.print("Panel Temperature : ");
  Serial.println(temp);
  Serial.print("Cooling Water Temperature : ");
  Serial.println(cw_temp);
  Serial.print("Panel Humidity : ");
  Serial.println(humi);
  Serial.print("Fuel Level : " );
  Serial.println(fuel_lv);
  Serial.print("Battery Voltage : " );
  Serial.println(vb);
  Serial.print("Battery Current : " );
  Serial.println(ib);
  Serial.print("Engine Speed : ");
  Serial.println(rpm);
  Serial.print("Lubricant Pressure : ");
  Serial.println(lub_pr);
  

}
      if(rpm==0){
          Serial.println("----------------------------i2c_request_s1 again");
          goto i2c_request_s1;
          }
delay(2000);
  
  //Slave 2
  i2c_request_s2:
  Wire.requestFrom(2, 32);    
  Serial.println("Request");

  do   
  {
    char c = Wire.read();
    string = string + c; 
    string1 = string.substring(0, 4);
    string2 = string.substring(4,8); 
    string3 = string.substring(8,12); 
    string4 = string.substring(12,16); 
    string5 = string.substring(16,20);
    string6 = string.substring(20,24);
    string7 = string.substring(24,28);    
    string8 = string.substring(28,31);
    vg1=string1.toFloat()/10;
    vg2=string2.toFloat()/10;
    vg3=string3.toFloat()/10;
    ig1=string4.toFloat()/100;
    ig2=string5.toFloat()/100;
    ig3=string6.toFloat()/100;
    f=string7.toFloat()/100;
    pf=string8.toFloat()/100;
    s=vg1*ig1;
    p=s*pf;
    
    
}

  while(Wire.available());{              

  Serial.println("Recieving float as String...");
  Serial.print("Full String: ");
  Serial.println(string);
   string = "";
 
  Serial.print("Generator Voltage 1 : ");
  Serial.println(vg1);
  Serial.print("Generator Voltage 2 : ");
  Serial.println(vg2);
  Serial.print("Generator Voltage 3 : ");
  Serial.println(vg3);
  Serial.print("Generator Current 1 : " );
  Serial.println(ig1);
  Serial.print("Generator Current 2 : " );
  Serial.println(ig2);
  Serial.print("Generator Current 3 : " );
  Serial.println(ig3);
  Serial.print("Apparent Power : ");
  Serial.println(s);
  Serial.print("Real Power : ");
  Serial.println(p);
  Serial.print("Power Factor : ");
  Serial.println(pf);
  Serial.print("Frequency : ");
  Serial.println(f);

}
      if(pf==0){
          Serial.println("----------------------------i2c_request_s2 again");
          goto i2c_request_s2;
          }

delay(2000);


  //Firebase
  StaticJsonBuffer<400> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  //Slave 1
  root["temp"] = temp;
  root["humi"] = humi;
  root["fuel_lv"] = fuel_lv;
  root["vb"] = vb;
  root["ib"] = ib;
  root["cw_temp"] = cw_temp;
  root["rpm"] = rpm;
  root["lub_pr"] = lub_pr;

  //Slave 2
  root["vg1"] = vg1;
  root["vg2"] = vg2;
  root["vg3"] = vg3;
  root["ig1"] = ig1;
  root["ig2"] = ig2;
  root["ig3"] = ig3;
  root["s"] = s;
  root["p"] = p;
  root["f"] = f;
  root["pf"] = pf;

  //Time
  root["time"] = NowString();
  
  delay(1000);
  
  String name = Firebase.push("parameter", root);
  if (Firebase.failed()) {
      Serial.print("pushing /Slave 1 failed:");
      Serial.println(Firebase.error());  
      Serial.print("  >>>>>>>>>>>>>>>>  Restart ESP 32");
      ESP.restart();
      return;
  }
  Serial.print("pushed: Slave 1 ");
  Serial.println(name);

  delay(1000);
  /*
 //บัคตาราง
    //slave 1
  Firebase.setFloat("slave_1/Temperature",temp);
  Firebase.setFloat("slave_1/Humidity",humi);
  Firebase.setFloat("slave_1/Fuel level",fuel_lv);
  Firebase.setFloat("slave_1/Battery Voltage",vb);
  Firebase.setFloat("slave_1/Battery Current",ib);
  Firebase.setFloat("slave_1/Cooling Water Temperature", cw_temp);
  Firebase.setFloat("slave_1/Engine Speed",rpm);
  Firebase.setFloat("slave_1/Oil Pressure",lub_pr);

  delay(1000);
  
    //slave 2
  Firebase.setFloat("slave_2/Generator Voltage 1",vg1);
  Firebase.setFloat("slave_2/Generator Voltage 2",vg2);
  Firebase.setFloat("slave_2/Generator Voltage 3",vg3);
  Firebase.setFloat("slave_2/Generator Current 1",ig1);
  Firebase.setFloat("slave_2/Generator Current 2",ig2);
  Firebase.setFloat("slave_2/Generator Current 3",ig3);
  Firebase.setFloat("slave_2/Apparent Power",s);
  Firebase.setFloat("slave_2/Real Power",p);
  Firebase.setFloat("slave_2/Power Factor",pf);
  Firebase.setFloat("slave_2/Frequency",f);
*/
  delay(1000);

  //Line Notify
  if(temp>45){
    client.sticker.package_id = 0;
    client.sticker.id = 0;
    client.message = "Panel Temperature is in DANGER !!!";
    LineNotify.send(client);
    client.message = "Please Check in https://test-33c48.web.app/  Now !!!";
    client.sticker.package_id = 1;
    client.sticker.id = 123;
    LineNotify.send(client);
    delay(100);
    }
  if(humi>80){
    client.sticker.package_id = 0;
    client.sticker.id = 0;
    client.message = "Panel Humidity is in DANGER !!!";
    LineNotify.send(client);
    client.message = "Please Check in https://test-33c48.web.app/  Now !!!";
    client.sticker.package_id = 1;
    client.sticker.id = 17;
    LineNotify.send(client);
    delay(100);
    }
  if(fuel_lv<4){
    client.sticker.package_id = 0;
    client.sticker.id = 0;
    client.message = "Fuel level is in DANGER !!!";
    LineNotify.send(client);
    client.message = "Please Check in https://test-33c48.web.app/  Now !!!";
    client.sticker.package_id = 1;
    client.sticker.id = 3;
    LineNotify.send(client);
    delay(100);
    }
  if(vb>15  || vb<11.5 ){
    client.sticker.package_id = 0;
    client.sticker.id = 0;
    client.message = "Battery Voltage is in DANGER !!!";
    LineNotify.send(client);
    client.message = "Please Check in https://test-33c48.web.app/  Now !!!";
    client.sticker.package_id = 1;
    client.sticker.id = 121;
    LineNotify.send(client);
    }
   /*
  if(ib>45){
    client.sticker.package_id = 0;
    client.sticker.id = 0;
    client.message = "Panel Temperature is in DANGER !!!";
    LineNotify.send(client);
    client.message = "Please Check in https://test-33c48.web.app/  Now !!!";
    client.sticker.package_id = 1;
    client.sticker.id = 123;
    LineNotify.send(client);
    delay(100);
    }
    */
    if(cw_temp>95){
    client.sticker.package_id = 0;
    client.sticker.id = 0;
    client.message = "Cooling Water Temperature is in DANGER !!!";
    LineNotify.send(client);
    client.message = "Please Check in https://test-33c48.web.app/  Now !!!";
    client.sticker.package_id = 1;
    client.sticker.id = 127;
    LineNotify.send(client);
    delay(100);
    }
  if(rpm>1700 || rpm<1300  ){//@ RPM : 1500)
    client.sticker.package_id = 0;
    client.sticker.id = 0;
    client.message = "Engine Speed is in DANGER !!!";
    LineNotify.send(client);
    client.message = "Please Check in https://test-33c48.web.app/  Now !!!";
    client.sticker.package_id = 1;
    client.sticker.id = 135;
    LineNotify.send(client);
    delay(100);
    }
  if(lub_pr<1){ //In normal state : 4-6 Bar
    client.sticker.package_id = 0;
    client.sticker.id = 0;
    client.message = "Lubricant Pressure is in DANGER !!!";
    LineNotify.send(client);
    client.message = "Please Check in https://test-33c48.web.app/  Now !!!";
    client.sticker.package_id = 1;
    client.sticker.id = 403;
    LineNotify.send(client);
    delay(100);
    }
  if(vg1>240 || vg1<200){
    client.sticker.package_id = 0;
    client.sticker.id = 0;
    client.message = "Generator Voltage 1 is in DANGER !!!";
    LineNotify.send(client);
    client.message = "Please Check in https://test-33c48.web.app/  Now !!!";
    client.sticker.package_id = 1;
    client.sticker.id = 420;
    LineNotify.send(client);
    delay(100);
    }
  if(vg2>240 || vg2<200){
    client.sticker.package_id = 0;
    client.sticker.id = 0;
    client.message = "Generator Voltage 2 is in DANGER !!!";
    LineNotify.send(client);
    client.message = "Please Check in https://test-33c48.web.app/  Now !!!";
    client.sticker.package_id = 1;
    client.sticker.id = 421;
    LineNotify.send(client);
    delay(100);
    }
  if(vg3>240 || vg3<200){
    client.sticker.package_id = 0;
    client.sticker.id = 0;
    client.message = "Generator Voltage 3 is in DANGER !!!";
    LineNotify.send(client);
    client.message = "Please Check in https://test-33c48.web.app/  Now !!!";
    client.sticker.package_id = 1;
    client.sticker.id = 422;
    LineNotify.send(client);
    delay(100);
    }
  if(ig1>40 ){// Current Rate = 45
    client.sticker.package_id = 0;
    client.sticker.id = 0;
    client.message = "Generator Current 1 is in DANGER !!!";
    LineNotify.send(client);
    client.message = "Please Check in https://test-33c48.web.app/  Now !!!";
    client.sticker.package_id = 2;
    client.sticker.id = 24;
    LineNotify.send(client);
    delay(100);
    }
  if(ig2>40 ){// Current Rate = 45
    client.sticker.package_id = 0;
    client.sticker.id = 0;
    client.message = "Generator Current 2 is in DANGER !!!";
    LineNotify.send(client);
    client.message = "Please Check in https://test-33c48.web.app/  Now !!!";
    client.sticker.package_id = 2;
    client.sticker.id = 32;
    LineNotify.send(client);
    delay(100);
    }
  if(ig3>40 ){// Current Rate = 45
    client.sticker.package_id = 0;
    client.sticker.id = 0;
    client.message = "Generator Current 3 is in DANGER !!!";
    LineNotify.send(client);
    client.message = "Please Check in https://test-33c48.web.app/  Now !!!";
    client.sticker.package_id = 2;
    client.sticker.id = 33;
    LineNotify.send(client);
    delay(100);
    }
    /*
  if(s>45){
    client.sticker.package_id = 0;
    client.sticker.id = 0;
    client.message = "Panel Temperature is in DANGER !!!";
    LineNotify.send(client);
    client.message = "Please Check in https://test-33c48.web.app/  Now !!!";
    client.sticker.package_id = 1;
    client.sticker.id = 123;
    LineNotify.send(client);
    delay(100);
    }
  if(p>45){
    client.sticker.package_id = 0;
    client.sticker.id = 0;
    client.message = "Panel Temperature is in DANGER !!!";
    LineNotify.send(client);
    client.message = "Please Check in https://test-33c48.web.app/  Now !!!";
    client.sticker.package_id = 1;
    client.sticker.id = 123;
    LineNotify.send(client);
    delay(100);
    }
    */
    if(pf<0.8){
    client.sticker.package_id = 0;
    client.sticker.id = 0;
    client.message = "Power Factor is in DANGER !!!";
    LineNotify.send(client);
    client.message = "Please Check in https://test-33c48.web.app/  Now !!!";
    client.sticker.package_id = 2;
    client.sticker.id = 524;
    LineNotify.send(client);
    delay(100);
    }
  if(f>51.5 || f<48.5){
    client.sticker.package_id = 0;
    client.sticker.id = 0;
    client.message = "Frequency is in DANGER !!!";
    LineNotify.send(client);
    client.message = "Please Check in https://test-33c48.web.app/  Now !!!";
    client.sticker.package_id = 2;
    client.sticker.id = 526;
    LineNotify.send(client);
    delay(100);
    }

    delay(1000);
    logSDCard();
    


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


// Write the sensor readings on the SD card
void logSDCard() {
  DateTime now = rtc.now();
  String log_time=String(now.year(), DEC) + "/" + String(now.month(), DEC) + "/" + String(now.day(), DEC)+","+ String(now.hour(), DEC)+":"+ String(now.minute(), DEC)+":"+ String(now.second(), DEC);
  dataMessage =  log_time+"," +String(temp) +","+ String(humi)+"," + String(vb)+","+ String(ib) +","+ String(lub_pr) +","+ String(fuel_lv) +","+ String(rpm) +","+ String(cw_temp) +","+ String(vg1) +","+ String(vg2) +","+ String(vg3) +","+ String(ig1) +","+ String(ig2) +","+ String(ig3) +","+ String(s) +","+ String(p) +","+ String(pf) +","+ String(f) +","+"\n";
  Serial.print("Save data: ");
  Serial.println(dataMessage);
  appendFile(SD, "/genset_data_log", dataMessage.c_str());
}
// Write to the SD card (DON'T MODIFY THIS FUNCTION)
void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);
  File file = fs.open(path, FILE_WRITE);
  if(!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}
// Append data to the SD card (DON'T MODIFY THIS FUNCTION)
void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);
  File file = fs.open(path, FILE_APPEND);
  if(!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if(file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}
