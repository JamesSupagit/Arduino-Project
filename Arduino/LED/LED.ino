int led;

void setup() {
  for(led=8;led<=11;led++)
  {
    pinMode(led,OUTPUT);
  }

}

void loop() {
  for(led=8;led<=11;led++)
  {
     digitalWrite(led,HIGH);
     delay(50);
     digitalWrite(led,LOW);
     delay(50);
  }
  for(led=11;led>=8;led--)
  {
     digitalWrite(led,HIGH);
     delay(50);
     digitalWrite(led,LOW);
     delay(50);
  }
 
 
 

}
