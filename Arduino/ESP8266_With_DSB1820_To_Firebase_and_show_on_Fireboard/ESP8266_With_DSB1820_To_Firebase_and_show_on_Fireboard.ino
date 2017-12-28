#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D1
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Config Firebase
#define FIREBASE_HOST "dht11-3fbeb.firebaseio.com"
#define FIREBASE_AUTH "uwWUBXumf4iavahj511GyufTE8kmvwHd22KJ9DIp"

const char* ssid = "Pitsanu01";               
const char* password = "0930436150";   


  
void setup() {
  
  //check connect wifi
  Serial.begin(115200);
   sensors.begin();  //DSB1820 Declare
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

  

  
    // check firebase ERROR
    if (Firebase.failed()) {
       Serial.print("Cannot connect to firebase");
       Serial.println(Firebase.error());  
       return;
    }
    
    
}
