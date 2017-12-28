#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup()
{ 
lcd.begin();
for(int i=1;i<=5;i++) // Blink Display 3 times
{
  lcd.backlight();
  delay(350);
  lcd.noBacklight();
  delay(350);
}lcd.backlight(); 

lcd.setCursor(4, 0); 
lcd.print("Welcome");
lcd.setCursor(2, 1); 
lcd.print("James Supagit");
}

void loop()
{
}
