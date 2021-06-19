int vb_1;
float vb_2;
float calb_vb;
void setup()
{
Serial.begin(9600);
}
void loop()
{

vb_1=analogRead(A1);
Serial.println(vb_1);
calb_vb=vb_1/4.092;
vb_1=(int)calb_vb;//
vb_2=((vb_1%100)/10.0);

Serial.println(vb_2);
delay(1000);
}
