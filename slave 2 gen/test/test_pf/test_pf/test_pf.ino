// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3

#include "EmonLib.h"             // Include Emon Library
EnergyMonitor emon1;             // Create an instance

void setup()
{  
  Serial.begin(9600);
  
 emon1.voltage(A0, 257.5, 1.7);  // Voltage: input pin, calibration, phase_shift257.5
  emon1.current(A6, 60.6);       // Current: input pin, calibration.
}

void loop()
{
 

  //emon1.calcF(50);     // 50 zero crossings
  emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  emon1.serialprint();       // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)

  float realPower       = emon1.realPower;        //extract Real Power into variable
  float apparentPower   = emon1.apparentPower;    //extract Apparent Power into variable
  float powerFActor     = emon1.powerFactor;      //extract Power Factor into Variable
  float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable*/
  float Irms            = emon1.Irms;             //extract Irms into Variable
  //float freq            = emon1.frequency;
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
 /* Serial.print("Frequency: ");
  Serial.println(freq);*/
  delay(1000);
}
