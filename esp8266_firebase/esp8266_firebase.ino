#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>


// Config Firebase
#define FIREBASE_HOST "test-app-android-studio.firebaseio.com"
#define FIREBASE_AUTH "UAsnKUjoH48RnvMqx8GQrhcp5GsuUK8bByvHFnzf"

// Config connect WiFi
#define WIFI_SSID "ART"
#define WIFI_PASSWORD "123456789"



void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
}

void loop() {
  // Read temp & Humidity for DHT22
  float h = 45.65;
  float t = 48.69;

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["temperature"] = t;
  root["humidity"] = h;
  
  // append a new value to /logDHT
  String name = Firebase.push("logDHT", root);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logDHT failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /logDHT/");
  Serial.println(name);
  
  delay(5000);
}
