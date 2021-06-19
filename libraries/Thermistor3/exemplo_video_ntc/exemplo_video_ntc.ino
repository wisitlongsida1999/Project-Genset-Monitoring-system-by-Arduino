#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <Thermistor3.h>
//begin object Thermistor in pin 0
Thermistor temp(0);
//value of resistor in ohms
double resistor = 10060;


//variable to store the average of read
double average =0;

//number of samples
int sample = 5000;


/*Declaracao de Constates e Objetos*/
// seta o Endereco do Display LCD  0x27 
// Seta os pinos do I2C usado (padrao da biblioteca)
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address



void setup() {
  Serial.begin(9600);
  
 // inicializa o lcd de 20 caracters e 4 linhas
lcd.begin(20,4);  
}

void loop() {
  //Read the data and plus to variable average
  for(int index =0; index < sample; index++){
    double temperature = temp.getTemp(resistor);
    average += temperature; 
    // a small delay for read again
    delayMicroseconds(1);
 }
 // get the average
  average = average / sample;
  Serial.print("A Temperatura e : ");
  Serial.print( average );
  Serial.println(" Celsius");
  
  lcd.clear();
   //Reposiciona o cursor na linha 0 e coluna 0
   lcd.setCursor(0,0);
   lcd.print("A Temperatura e : ");
   
   lcd.setCursor(0,2);
   lcd.print(average);
   lcd.print(" Celsius");
  
  delay(10);
}
