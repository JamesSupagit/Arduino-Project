int buzzer = 8;
int buzzer1 = 5;
int i1=50,i2=80;
void setup ()
{
pinMode (buzzer, OUTPUT);
pinMode (buzzer1, OUTPUT);
}

void loop ()
{
unsigned char i, j ;
while (1)
{
for (i = 0; i <i1; i++) 
{

digitalWrite (buzzer1,HIGH);
delay (1) ;


digitalWrite (buzzer1,LOW);
delay (1) ;
}
for (i = 0; i <i2; i++) 
{

digitalWrite (buzzer1,HIGH);
delay (2) ;

digitalWrite (buzzer1,LOW);
delay (1) ;
}
for (i = 0; i <i1; i++) 
{
digitalWrite (buzzer, HIGH);
delay (1) ;

digitalWrite (buzzer, LOW); 
delay (1) ;
}
for (i = 0; i <i2; i++) 
{
digitalWrite (buzzer, HIGH);
delay (2) ;
digitalWrite (buzzer, LOW);
delay (1) ;
}
}
}
