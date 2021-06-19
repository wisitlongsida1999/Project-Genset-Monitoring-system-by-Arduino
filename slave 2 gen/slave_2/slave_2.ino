// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3

#include "EmonLib.h"             // Include Emon Library
EnergyMonitor emon1;             // Create an instance
EnergyMonitor emon2;             // Create an instance
EnergyMonitor emon3;             // Create an instance


//i2c
#include<Wire.h> 
float vg1,vg2,vg3,ig1,ig2,ig3,f,pf,s,p;
char send_vg1[5];
char send_vg2[5];
char send_vg3[5];
char send_ig1[5];
char send_ig2[5];
char send_ig3[5];
char send_f[5];
char send_pf[5];


void setup()
{  
  Serial.begin(9600);

  //Emon
  emon1.voltage(0, 257.5, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon1.current(6, 60.6);       // Current: input pin, calibration.
  emon2.voltage(1, 257.5, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon2.current(3, 60.6);       // Current: input pin, calibration.
  emon3.voltage(2, 257.5, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon3.current(7, 60.6);       // Current: input pin, calibration.


  //I2c
  Wire.begin(2);
  Wire.onRequest(requestEvent); 

  
}

void loop()
{
 

  emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  emon1.serialprint();       // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)
  emon2.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  emon2.serialprint();       // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)
  emon3.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  emon3.serialprint();       // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)
  
  
  float realPower       = emon1.realPower;        //extract Real Power into variable
  float apparentPower   = emon1.apparentPower;    //extract Apparent Power into variable
  float powerFActor     = emon1.powerFactor;      //extract Power Factor into Variable
  float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
  float Irms            = emon1.Irms;             //extract Irms into Variable
  float realPower2       = emon2.realPower;        //extract Real Power into variable
  float apparentPower2   = emon2.apparentPower;    //extract Apparent Power into variable
  float powerFActor2     = emon2.powerFactor;      //extract Power Factor into Variable
  float supplyVoltage2   = emon2.Vrms;             //extract Vrms into Variable
  float Irms2            = emon2.Irms;             //extract Irms into Variable
  float realPower3       = emon3.realPower;        //extract Real Power into variable
  float apparentPower3   = emon3.apparentPower;    //extract Apparent Power into variable
  float powerFActor3     = emon3.powerFactor;      //extract Power Factor into Variable
  float supplyVoltage3   = emon3.Vrms;             //extract Vrms into Variable
  float Irms3            = emon3.Irms;             //extract Irms into Variable
//   emon1.calcF(50);     // 50 zero crossings
//  float frequency = emon1.frequency;
  if(powerFActor >1.00){
    powerFActor=1.00;
    
    };
     if(powerFActor <0.00){
    powerFActor=0.00;
    
    };
  Serial.print("realPower : ");
  Serial.println(realPower );
  Serial.print("apparentPower : ");
  Serial.println(apparentPower);
  Serial.print("powerFActor : ");
  Serial.println(powerFActor );
  Serial.print("supplyVoltage : ");
  Serial.println(supplyVoltage);
  Serial.print("Irms  : ");
  Serial.println(Irms  );
  //Serial.print("Frequency  : ");
  //Serial.println(frequency);
  delay(1000);


/*
// random ทศนิยม
float a = random(0,9);
float b =random(0,9);
float c =random(0,9);

//vg1
vg1  = random(100,300)+a/10;//emon1.Vrms;       
vg1=vg1*10;
dtostrf(vg1, 4, 0, send_vg1); 

//vg2
vg2   =random(100,300)+b/10; //emon2.Vrms;      
vg2=vg2*10; 
dtostrf(vg2, 4, 0, send_vg2); 

//vg3
vg3  =random(100,300)+c/10; //emon3.Vrms;     
vg3=vg3*10;  
dtostrf(vg3, 4, 0, send_vg3); 

//ig1
ig1  = random(10,70)+a/10+b/100;//emon1.Irms;    
ig1=ig1*100;   
dtostrf(ig1, 4, 0, send_ig1); 

//ig2
ig2   = random(10,70)+b/10+c/100;//emon2.Irms;       
ig2=ig2*100;  
dtostrf(ig2, 4, 0, send_ig2); 

//ig3
ig3   = random(10,70)+c/10+a/100;//emon3.Irms;     
ig3=ig3*100;    
dtostrf(ig3, 4, 0, send_ig3); 

//f
float f   = ( random(47,53)+a/10+c/100)*100;       
dtostrf(f, 4, 0, send_f); 


//pf
pf  = c/10 +b/100; //emon1.powerFactor;    
pf=pf*100;   
dtostrf(pf, 3, 0, send_pf); 

Serial.print("Generator Voltage 1 : ");
Serial.println(send_vg1);
Serial.print("Generator Voltage 2 : ");
Serial.println(send_vg2);
Serial.print("Generator Voltage 3 : ");
Serial.println(send_vg3);
Serial.print("Generator Current 1 : " );
Serial.println(send_ig1);
Serial.print("Generator Current 2 : " );
Serial.println(send_ig2);
Serial.print("Generator Current 3 : " );
Serial.println(send_ig3);
Serial.print("Apparent Power : ");
Serial.println(s);
Serial.print("Real Power : ");
Serial.println(p);
Serial.print("Power Factor : ");
Serial.println(send_pf);
Serial.print("Frequency : ");
Serial.println(send_f);

delay(3000);
*/
}






// Data Sending With I2C
void requestEvent(){

Wire.write(send_vg1);   
                                   
Wire.write(send_vg2);   

Wire.write(send_vg3);   

Wire.write(send_ig1);   

Wire.write(send_ig2);   

Wire.write(send_ig3);   

Wire.write(send_f);   

Wire.write(send_pf);   

      } 
