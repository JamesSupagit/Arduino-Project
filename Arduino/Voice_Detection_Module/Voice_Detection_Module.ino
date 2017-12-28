int sensor=A0;
int led=8;
int sensorvalue;

void setup() 
{
  pinMode(led,OUTPUT);
  pinMode(sensor,INPUT);
  Serial.begin(9600);
}

void loop() 
{
  sensorvalue=analogRead(sensor);
  if(sensorvalue>50)
  {
  digitalWrite(led,1);
  delay(sensorvalue);
  }
  else
  {
  digitalWrite(led,0);
  delay(sensorvalue);
  
  }
  Serial.println(sensorvalue);
  

}
