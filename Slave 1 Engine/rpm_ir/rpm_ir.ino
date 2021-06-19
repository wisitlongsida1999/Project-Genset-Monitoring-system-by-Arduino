float REV = 0;
int RPM_VALUE;
int PREVIOUS = 0;
int TIME;

void INTERRUPT()
{
  REV++;
}

void setup()
{
  Serial.begin(9600);
  attachInterrupt(0, INTERRUPT, RISING);
}

void loop()
{
  delay(1000);
  detachInterrupt(0);                   
  TIME = millis() - PREVIOUS;          
  RPM_VALUE = (REV/TIME) * 60000;       
  PREVIOUS = millis();                  
  REV = 0;
  Serial.println(RPM_VALUE);
  attachInterrupt(0, INTERRUPT, RISING);
}
