#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include "DHT.h"
#define DHTPIN D3 
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);

// Declared Port
#define DEBUG_WIFICONNECT 14
#define DEBUG_PUTHDATA 5

// Define WiFi SSID and Password 
#define WIFI_SSID "Pitsanu02"               
#define WIFI_PASSWORD "0930436150"

void setup() 
{
  lcd.begin();
  dht.begin();
  pinMode(DEBUG_WIFICONNECT,OUTPUT);
  pinMode(DEBUG_PUTHDATA,   OUTPUT);

 
  WiFi.mode(WIFI_STA);
  //Connect to wifi.
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
}

void loop() 
{
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  // LCD show 
  lcd.setCursor(0,0); 
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");
  }

