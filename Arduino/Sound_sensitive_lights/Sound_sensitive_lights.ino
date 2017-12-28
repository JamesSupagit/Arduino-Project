int DO = 7; //Pin for Digital Output - DO
int DA = A0; // Pin for Analog Output - AO
int threshold = 75; //Set minimum threshold for LED lit
int sensorvalue = 0;
 
void setup() {
  Serial.begin(9600);
  pinMode(DA,INPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  
}
 
void loop() {
  sensorvalue = analogRead(DA);  //Read the analog value
  Serial.print("Analog: ");
  Serial.println(sensorvalue);  //Print the analog value
  //Serial.print("  ");
  //Serial.print("Digital: ");
  //Serial.println(digitalRead(DO));  //Print the digital value
 
  if (sensorvalue >= threshold) { //Compare analog value with threshold
    
    
    digitalWrite(8,  HIGH);
    digitalWrite(9,  HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    
 
  }
  else {
    digitalWrite(8,  LOW);
    digitalWrite(9,  LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
  }
}
