#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <dht.h>
#define DHT11 A0
dht DHT;
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS A1
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup()
{
  lcd.begin();
  sensors.begin();
}

void loop() 
{
  int chk = DHT.read11(DHT11);
  sensors.requestTemperatures();  
  lcd.setCursor(0,0); 
  lcd.print("Temp DH11: ");
  lcd.print(DHT.temperature);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Temp DS18: ");
  lcd.print(sensors.getTempCByIndex(0));
  lcd.print((char)223);
  lcd.print("C");
  delay(100);

}
