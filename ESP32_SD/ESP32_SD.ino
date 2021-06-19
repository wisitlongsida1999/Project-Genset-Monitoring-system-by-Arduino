
#include "FS.h"
#include "SD.h"
#include <SPI.h>
#include <RTClib.h> // for the RTC
// RTC
RTC_DS1307 rtc;

#define SD_CS 5
String dataMessage;


float temp,humi,fuel_lv,vb,ib,cw_temp,rpm,lub_pr;
float vg1,vg2,vg3,ig1,ig2,ig3,f,pf,s,p;
void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT); // i use this to supply 3.3volts to the variable resistor
  digitalWrite(13, HIGH);

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
  File file = SD.open("/genset_data.txt");
  if(!file) {
    Serial.println("File doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/genset_data.txt", "Date,Time,Temperature ( °C ),Humidity ( % ),Battery Voltage ( V ),Battery Current ( A ),Lubricant Pressure ( Bar ),Fuel Level ( L ),Engine Speed ( Rpm ),Cooling Water Temperature ( °C ),Generator Voltage 1 ( V ),Generator Voltage 2 ( V ),Generator Voltage 3 ( V ),Generator Current 1 ( A ),Generator Current 2 ( A ),Generator Current 3 ( A ),Apparent Power( kVA ),Real Power ( kW ),Power Factor,Frequency( Hz ) \r\n");
  }
  else {
    Serial.println("File already exists");  
  }
  file.close();
}
void loop() {

    logSDCard();
    temp+=11.99;
 
    delay(5000); //Wait for 5 seconds before writing the next data 
}

// Write the sensor readings on the SD card
void logSDCard() {
  DateTime now = rtc.now();
  String log_time=String(now.year(), DEC) + "/" + String(now.month(), DEC) + "/" + String(now.day(), DEC)+","+ String(now.hour(), DEC)+":"+ String(now.minute(), DEC)+":"+ String(now.second(), DEC);
  dataMessage =  log_time+"," +String(temp) + String(humi)+"," + String(vb)+","+ String(ib) +","+ String(lub_pr) +","+ String(fuel_lv) +","+ String(rpm) +","+ String(cw_temp) +","+ String(vg1) +","+ String(vg2) +","+ String(vg3) +","+ String(ig1) +","+ String(ig2) +","+ String(ig3) +","+ String(s) +","+ String(p) +","+ String(pf) +","+ String(f) +","+"\n";
  Serial.print("Save data: ");
  Serial.println(dataMessage);
  appendFile(SD, "/data.txt", dataMessage.c_str());
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
