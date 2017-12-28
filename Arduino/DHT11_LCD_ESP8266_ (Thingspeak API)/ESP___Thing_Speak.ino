#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <time.h>
#include "DHT.h"
#define DHTPIN D3 
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Config Port
#define DEBUG_WIFICONNECT 14
#define DEBUG_PUTHDATA 5

// Include API form thingspeaks
String apiKey = "VM4GUMP74JT6YMGZ";
const char* server = "api.thingspeak.com";

// Define WiFi SSID and Password
#define WIFI_SSID "Pitsanu01"               
#define WIFI_PASSWORD "0930436150"

// Config Timezone
int timezone = 7;
char ntp_server1[20] = "ntp.ku.ac.th";
char ntp_server2[20] = "fw.eng.ku.ac.th";
char ntp_server3[20] = "time.uni.net.th";
int dst = 0;
WiFiClient client;

void setup()
{
  pinMode(DEBUG_WIFICONNECT,OUTPUT);
  pinMode(DEBUG_PUTHDATA,   OUTPUT);
  lcd.begin();
  dht.begin();
     
  for(int i=0;i<2;i++) //Blink Display two times.
  {
    lcd.backlight();
    delay(350);
    lcd.noBacklight();
    delay(350);
  }
  lcd.backlight(); // Finish for-loop with backlight on
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  lcd.setCursor(0,0);
  lcd.print("Connecting");  
  while (WiFi.status() != WL_CONNECTED) {
    lcd.print(".");
    digitalWrite(DEBUG_WIFICONNECT, !digitalRead(DEBUG_WIFICONNECT));
    delay(500);
  }
   digitalWrite(DEBUG_WIFICONNECT, HIGH);
   lcd.clear();
   lcd.setCursor(3,0);
   lcd.print("\"Connected\"");
   lcd.setCursor(2,1);
   lcd.print(WiFi.localIP());
   delay(2000);  
  
  // Blink display 4 times
  for(int i = 0; i< 4; i++) 
  {
    lcd.backlight();
    delay(100);
    lcd.noBacklight();
    delay(100);
  }
  lcd.backlight(); 

 
}
void loop() 
{
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

// Thingspeak Instruction    
if (client.connect(server,80)) // Connect to api.thingspeak.com
{ 
String postStr = apiKey;
postStr +="&field1=";
postStr += String(t);
postStr +="&field2=";
postStr += String(h);
postStr += "\r\n\r\n";
client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postStr.length());
client.print("\n\n");
client.print(postStr);
 
 // Show on LCD Display 
  lcd.clear();
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
client.stop();
Serial.println("Waiting…");
delay(16500); // Minimum Delay of thingspeak 
}


