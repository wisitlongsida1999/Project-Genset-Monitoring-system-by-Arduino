// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3

#include "EmonLib.h"                   // Include Emon Library
EnergyMonitor emon0; // L1 Instance
EnergyMonitor emon1; // L2 Instance
EnergyMonitor emon2; // L3 Instance

void setup()
{  
  Serial.begin(9600);
  
  emon0.current(A1, 5);             // Current: input pin, calibration.
  emon1.current(A3, 5);             // Current: input pin, calibration.
  emon2.current(A5, 5);             // Current: input pin, calibration.
}

void loop()
{
  double Irms1 = emon0.calcIrms(1480);  // Calculate Irms only
  

  Serial.print("Current 1 : ");
  Serial.print(Irms1);           // Irms
    Serial.println(" mA");
/*
    double Irms2 = emon1.calcIrms(1480);  // Calculate Irms only
  

  Serial.print("Current 2 : ");
  Serial.print(Irms2);           // Irms
    Serial.println(" mA");

    double Irms3 = emon2.calcIrms(1480);  // Calculate Irms only
  

  Serial.print("Current 3 : ");
  Serial.print(Irms3);           // Irms
    Serial.println(" mA");

    */
}
