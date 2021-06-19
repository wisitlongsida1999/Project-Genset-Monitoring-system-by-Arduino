

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif


#include <ESP_Line_Notify.h>



/* Set your WiFI AP credential */
#define WIFI_SSID "ART"
#define WIFI_PASSWORD "123456789"

/* Define the LineNotifyClient object */
LineNotiFyClient client;
int line_stk_pack;
int line_stk_id;

void setup()
{

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(200);
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  client.token = "d46VT4ggkGDsUkVQ2PwLggGBwJEAHNbYBgjmJwzOF5f";
  client.reconnect_wifi = true;

  Serial.println("Sending Line Notify message...");

  
  client.message = "Hello world";

 
  /** To send sticker
   * See https://devdocs.line.me/files/sticker_list.pdf for STKPKGID (Sticker Package ID).
   * See https://devdocs.line.me/files/sticker_list.pdf for STKID (Sticker ID).
  */
    client.sticker.package_id = 2;
    client.sticker.id = 157;

  

   
    //client.image.url = "https://cdn.pixabay.com/photo/2017/05/17/18/35/sewing-2321532_640.jpg";

  

 

  LineNotifySendingResult result = LineNotify.send(client);


}

void loop()
{
  
  client.message = "Hello world22";
    line_stk_pack = random(1,4);
  line_stk_id = random(1,500);
  client.sticker.package_id = line_stk_pack;
  client.sticker.id = line_stk_id;
LineNotify.send(client);
   delay(2000);
     client.message = "Hello world33";
       line_stk_pack = random(1,4);
  line_stk_id = random(1,500);
  client.sticker.package_id = line_stk_pack;
  client.sticker.id = line_stk_id;
 LineNotify.send(client);
   delay(2000);

  
}
