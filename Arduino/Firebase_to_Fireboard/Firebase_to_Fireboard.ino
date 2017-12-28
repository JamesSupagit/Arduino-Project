#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include "DHT.h"
#define DHTPIN D1 
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
#include <time.h>

#define DEBUG_WIFICONNECT 14
#define DEBUG_PUTHDATA 5
// Config Firebase
#define FIREBASE_HOST "dht11sensor-18aff.firebaseio.com"
#define FIREBASE_AUTH "WBJYaWzFTvJ7rNpnykfNgZ4v9fB9CHCNzYZNzzEG"

#define WIFI_SSID "Pitsanu01"               
#define WIFI_PASSWORD "0930436150"

int timezone = 7;

char ntp_server1[20] = "ntp.ku.ac.th";
char ntp_server2[20] = "fw.eng.ku.ac.th";
char ntp_server3[20] = "time.uni.net.th";

int dst = 0;

  
void setup() 
{
  pinMode(DEBUG_WIFICONNECT,OUTPUT);
  pinMode(DEBUG_PUTHDATA,OUTPUT);

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(DEBUG_WIFICONNECT, !digitalRead(DEBUG_WIFICONNECT));
    delay(500);
  }
  digitalWrite(DEBUG_WIFICONNECT, HIGH);
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  configTime(timezone * 3600, dst, ntp_server1, ntp_server2, ntp_server3);
  Serial.println("Waiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Now: " + NowString());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  dht.begin();
  
}

void loop() {

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

 //Web Show
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["temperature"] = t;
  root["humidity"] = h;
  root["time"] = NowString();

  digitalWrite(DEBUG_PUTHDATA, HIGH);
  // append a new value to /logDHT
  String name = Firebase.push("logDHT", root);
  
    // check firebase ERROR
    if (Firebase.failed()) {
       Serial.print("Cannot connect to firebase");
       Serial.println(Firebase.error());  
       return;
 }
  Serial.println(t);
  Serial.println(h);  
  Serial.print("pushed: /logDHT/");
  Serial.println(name);
  delay(2000);
  digitalWrite(DEBUG_PUTHDATA, LOW);
  delay(600000);  
}
  String NowString() 
  {
  time_t now = time(nullptr);
  struct tm* newtime = localtime(&now);
  String tmpNow = "";
  tmpNow += String(newtime->tm_hour);
  tmpNow += ":";
  tmpNow += String(newtime->tm_min);
  tmpNow += ":";
  tmpNow += String(newtime->tm_sec);
  return tmpNow;
  }
