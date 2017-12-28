//ESP8266**************************************
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
//DHTtype**************************************
#define DHTTYPE DHT11
#include "DHT.h"
#define DHTPIN D3 
DHT dht(DHTPIN, DHTTYPE);
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup()
{
  lcd.begin();
  dht.begin();
  
}

void loop() 
{
  float h = dht.readHumidity(); // Read temperature as Celsius (the default)
  float t = dht.readTemperature();// Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  lcd.setCursor(0,0); 
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");
  delay(2000);

}
