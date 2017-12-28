#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS A0
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() 
{
  Serial.begin(115200);
}
  

void loop() 
{
  delay(10000);
  float temptemp;
  String temperature;
  do {
  sensors.requestTemperatures(); // Send the command to get temperatures
  temptemp = sensors.getTempCByIndex(0);
  temperature = String(temptemp);
  Serial.print("Temperature: ");
  Serial.println(temperature);
  } while (temptemp == 85.0 || temptemp == (-127.0));  
 }
  
  
