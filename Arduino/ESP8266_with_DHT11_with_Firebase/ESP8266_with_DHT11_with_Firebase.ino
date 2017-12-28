#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#define DHTTYPE DHT11
#include "DHT.h"
#define DHTPIN D1 
DHT dht(DHTPIN, DHTTYPE);

// Config Firebase
#define FIREBASE_HOST "dht11-3fbeb.firebaseio.com"
#define FIREBASE_AUTH "uwWUBXumf4iavahj511GyufTE8kmvwHd22KJ9DIp"

const char* ssid = "Pitsanu_1";               
const char* password = "054459096";   


  
void setup() {
  
  //check connect wifi
  Serial.begin(115200);
  dht.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //set firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 
}

void loop() {

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  
    // check firebase ERROR
    if (Firebase.failed()) {
       Serial.print("Cannot connect to firebase");
       Serial.println(Firebase.error());  
       return;
    }
    
    Firebase.setInt("Temparature",t);
    Serial.println(t); 
    Firebase.setInt("Humidity",h);
    Serial.println(h); 
    delay(1000);
    
}
