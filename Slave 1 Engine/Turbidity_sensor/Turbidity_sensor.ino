float lub_pr;

void setup() {
  Serial.begin(9600); //Baud rate: 9600
}
void loop() {
  int sensorValue_lub = analogRead(A7);// read the input on analog pin 0:
  float voltage_lub = sensorValue_lub * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  if (voltage_lub<=2.5)
    {
      
      lub_pr=3000;

      }
   else
    {
      lub_pr=-1120.4*voltage_lub *voltage_lub +5742.3*voltage_lub -4352.9;
      }
  

  
  Serial.println(lub_pr); // print out the value you read:
  delay(1000);
}
