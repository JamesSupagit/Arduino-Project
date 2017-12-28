int WaterSensor;
void setup()
{
  Serial.begin(9600);
  
}

void loop()
{
  WaterSensor=analogRead(A0);
  WaterSensor=map(WaterSensor,720,0,100,0);
  Serial.print(WaterSensor);
  Serial.println("%");
  delay(100);
}

