// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3

#include "EmonLib.h"             // Include Emon Library
EnergyMonitor emon1;             // Create an instance

void setup()
{  
  Serial.begin(9600);
  
  emon1.voltage(A1, 397.22,1.7);  // Voltage: input pin, calibration, phase_shift
  emon1.current(A3, 66.67);       // Current: input pin, calibration.
}

void loop()
{
  float sensorValue = analogRead(A3);  

  emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  //emon1.serialprint();       // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)

  float realPower       = emon1.realPower;        //extract Real Power into variable
  float apparentPower   = emon1.apparentPower;    //extract Apparent Power into variable
  float powerFActor     = emon1.powerFactor;      //extract Power Factor into Variable
  float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
  float Irms            = emon1.Irms;             //extract Irms into Variable
   Serial.print("Irms");
   Serial.println(Irms);
   Serial.print("supplyVoltage "); 
   Serial.println(supplyVoltage); 
   Serial.print("powerFActor ");
    Serial.println(powerFActor);
   Serial.print("realPower :");
   Serial.println(realPower );
   Serial.print("apparentPower: "); 
   Serial.println(apparentPower); 
    
}
