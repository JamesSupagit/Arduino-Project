#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <time.h>
#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include "DHT.h"
#define DHTPIN D3 
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);

// Config Port 
#define DEBUG_WIFICONNECT 14
#define DEBUG_PUTHDATA 5

// Config Firebase
#define FIREBASE_HOST "dht11sensor-18aff.firebaseio.com"
#define FIREBASE_AUTH "WBJYaWzFTvJ7rNpnykfNgZ4v9fB9CHCNzYZNzzEG"

// Define WiFi SSID and password 
#define WIFI_SSID "Pitsanu02"               
#define WIFI_PASSWORD "0930436150"

// Define timezone 
int timezone = 7;
char ntp_server1[20] = "ntp.ku.ac.th";
char ntp_server2[20] = "fw.eng.ku.ac.th";
char ntp_server3[20] = "time.uni.net.th";
int dst = 0;


  
void setup() 
{
  lcd.begin();
  dht.begin();
  pinMode(DEBUG_WIFICONNECT,OUTPUT);
  pinMode(DEBUG_PUTHDATA,   OUTPUT);

 
  WiFi.mode(WIFI_STA);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
   lcd.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    lcd.print(".");
    digitalWrite(DEBUG_WIFICONNECT, !digitalRead(DEBUG_WIFICONNECT));
    delay(500);
  }
  digitalWrite(DEBUG_WIFICONNECT, HIGH);
  lcd.println();
  lcd.print("connected: ");
  lcd.print(WiFi.localIP());

  configTime(timezone * 3600, dst, ntp_server1, ntp_server2, ntp_server3);
  lcd.println("Waiting for time");
  while (!time(nullptr)) {
    lcd.print(".");
    delay(500);
  }
  lcd.println();
  lcd.println("Now: " + NowString());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  
}

void loop() {
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  
 StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["temperature"] = t;
  root["humidity"] = h;
  root["time"] = NowString(); 
  
  digitalWrite(DEBUG_PUTHDATA, HIGH);
  // append a new value to /logDHT
  String name = Firebase.push("logDHT", root);
  
if (Firebase.failed()) {
       
       lcd.print("Cannot connect to firebase");
       lcd.println(Firebase.error());  
       return;
 }
  lcd.setCursor(0,0); 
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");
  digitalWrite(DEBUG_PUTHDATA, LOW);
  delay(2000);
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

