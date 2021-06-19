// Phase Angle By Solarduino 

// Note Summary
// Note :  Safety is very important when dealing with electricity. We take no responsibilities while you do it at your own risk.
// Note :  This Phase Angle Code needs 2 signal waves of the same frequency to work. You can use AC current module and AC Voltage Module. 
// Note :  This Code monitors phase difference between 2 waves and also its frequency value.
// Note :  The value shown in Serial Monitor is refreshed every second, can be used for 50Hz and 60Hz.
// Note :  The frequency is measured by counting time and average it for every 50 samples taken (for 50 hz)(1 sample is 1 cycle).
// Note :  The pre-calibration of voltageAnalogOffset & currentAnalogOffset are needed to do it manually.
// Note :  The unit provides reasonable accuracy and may not be comparable with other expensive branded and commercial product.
// Note :  All credit shall be given to Solarduino.

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/////////////*/

 
 
        /* 0- General */

        int decimalPrecision = 2;                   // decimal places for all values shown in LED Display & Serial Monitor


        /* 1 - Phase Angle, Frequency and Power Factor measurement */

        int expectedFrequency = 50;                 // Key in frequency for main grid (50 / 60 hz)
        int analogInputPin1PA = A2;                 // The input pin for analogRead1 sensor. Use voltage sensor as primary reference here.
        int analogInputPin2PA = A3;                 // The input pin for analogRead2 sensor. Use current or voltage as secondary reference.
        float voltageAnalogOffset =4;               // This is to offset analog value for analogInput1
        float currentAnalogOffset =-12;             // This is to offset analog value for analogInput2
        unsigned long startMicrosPA;                /* start counting time for Phase Angle and Period (in micro seconds)*/
        unsigned long vCurrentMicrosPA;             /* current time for analogInput1 (voltage) (in micro seconds). AnalogInput1 is used for reference for phase angle*/
        unsigned long iCurrentMicrosPA;             /* current time for analogInput2 (current/voltage) (in micro seconds).*/
        unsigned long periodMicrosPA;               /* current time for record period of wave */
        float vAnalogValue =0;                      /* is the analog value for voltage sensor / analogInput1 and center at 0 value */
        float iAnalogValue =0;                      /* is the analog value for current sensor / analogInput2 and center at 0 value */
        float previousValueV =0;                    /* use to record peak value for voltage sensor*/
        float previousValueI =0;                    /* use to record peak value for current sensro*/
        float previousphaseAngleSample=0;           /* previous sample reading to replace false value less than 100 micro seconds*/
        float phaseAngleSample =0;                  /* is the time difference between 2 sensor values (in micro seconds) */
        float phaseAngleAccumulate =0;              /* is the accumulate time difference for accumulate samples*/
        float periodSample=0;                       /* is the time difference for a period of wave for a sample (in micro seconds)*/
        float periodSampleAccumulate = 0;           /* is the accumulate time difference for accumulate samples */
        float phaseDifference =0;                   /* is the averaged set of time difference of 2 sensors*/
        float phaseAngle =0;                        /* is the phase angle in degree (out of 360)*/
        float frequency = 0;                        /* is the frequency of the voltage sensor wave*/
        float voltagePhaseAngle=0;                  /* is the time recorded from begining to reach peak value for analogInput1 in micro seconds*/
        float currentPhaseAngle=0;                  /* is the time recorded from begining to reach peak value for analogInput2 in micro seconds*/
        float averagePeriod =0;                     /* is the average set of time recorded for a period of wave */
        int sampleCount = 0;                        /* to count how many set of samples */
        int a = 3;                                  /* use for switching operation*/
        float powerFactor;                          /* to calculate power factor */
        

void setup() 
{
  
        /* 0- General */
        
        Serial.begin(9600);
  
}

void loop() 
{


        /* 1 - Phase Angle, Frequency and Power Factor measurement */
        
        vAnalogValue = analogRead(analogInputPin1PA)-512 + voltageAnalogOffset;       /* read analogInput1 with center adjusted*/
        iAnalogValue = analogRead(analogInputPin2PA)-512 + currentAnalogOffset;       /* read analogInput2 with center adjusted*/

        if((vAnalogValue>0) && a == 3)                                          /* initial begining stage of measurement when analogInput1 wave larger than 0 */
        {
          a=0;                                                                  /* allow to change to the next stage */
        }
        
        if((vAnalogValue<=0) && a ==0)                                          /* when analog value of analogInput1 smaller or equal than 0*/
        {
          startMicrosPA = micros();                                             /* start counting time for all*/
          a=1;                                                                  /* allow to change to the next stage */
        }
        
        if((vAnalogValue>0) && a ==1)                                           /* when analog value of analogInput1 larger than 0*/
        {
          a = 2;                                                                /* allow to change to the next stage */
          previousValueV = 0;                                                   /* reset value. This value to be compared to measure peak value for analogInput1 */
          previousValueI = 0;                                                   /* reset value. This value to be compared to measure peak value for analogInput2 */
        }  
     
        if((vAnalogValue > previousValueV ) && a==2)                            /* if current measured value larger than previous peak value of analogInput1 */
        {
          previousValueV = vAnalogValue ;                                       /* record current measure value replace previous peak value */
          vCurrentMicrosPA = micros();                                          /* record current time for analogInput1 */
        }
        
        if((iAnalogValue > previousValueI) && a==2)                             /* if current measured value larger than previous peak value of analogInput2 */
        {
          previousValueI = iAnalogValue ;                                       /* record current measure value replace previous peak value */
          iCurrentMicrosPA = micros();                                          /* record current time for analogInput2 */
        }
  
        if((vAnalogValue <=0) && a==2)                                          /* when analog value of analogInput1 smaller or equal than 0*/
        {
          periodMicrosPA = micros();                                            /* record current time for 1 period */
          periodSample = periodMicrosPA - startMicrosPA;                        /* period wave is the current time minus the starting time (for 1 sample)*/
          periodSampleAccumulate = periodSampleAccumulate + periodSample;       /* accumulate or add up time for all sample readings of period wave */
          voltagePhaseAngle = vCurrentMicrosPA - startMicrosPA;                 /* time taken for analogInput1 from 0 (down wave) to peak value (up wave)*/
          currentPhaseAngle = iCurrentMicrosPA - startMicrosPA;                 /* time taken for analogInput2 from 0 (down wave) to peak value (up wave)*/
          phaseAngleSample = currentPhaseAngle - voltagePhaseAngle;             /* time difference between analogInput1 peak value and analogInput2 peak value*/
          if(phaseAngleSample>=100)                                             /* if time difference more than 100 micro seconds*/
          {
          previousphaseAngleSample = phaseAngleSample;                          /* replace previous value using new current value */ 
          }
          if(phaseAngleSample<100)                                              /* if time difference less than 100 micro seconds (might be noise or fake values)*/
          {
          phaseAngleSample = previousphaseAngleSample;                          /* take previous value instead using low value*/
          }
          phaseAngleAccumulate = phaseAngleAccumulate + phaseAngleSample;       /* accumulate or add up time for all sample readings of time difference */
          sampleCount = sampleCount + 1;                                        /* count sample number */
          startMicrosPA = periodMicrosPA;                                       /* reset begining time */
          a=1;                                                                  /* reset stage mode */
          previousValueV = 0;                                                   /* reset peak value for analogInput1 for next set */
          previousValueI = 0;                                                   /* reset peak value for analogInput2 for next set */
        }

        if(sampleCount == expectedFrequency)                                          /* if number of total sample recorded equal 50 by default */
        {
          averagePeriod = periodSampleAccumulate/sampleCount;                         /* average time for a period of wave from all the sample readings*/
          frequency = 1000000 / averagePeriod;                                        /* the calculated frequency value */
          phaseDifference = phaseAngleAccumulate / sampleCount;                       /* average time difference between 2 sensor peak values from all the sample readings */
          phaseAngle = ((phaseDifference*360) / averagePeriod);                       /* the calculated phase angle in degree (out of 360)*/
          powerFactor = cos(phaseAngle*0.017453292);                                  /* power factor. Cos is in radian, the formula on the left has converted the degree to rad. */
          Serial.print("Phase Angle :");
          Serial.print(phaseAngle,decimalPrecision);
          Serial.print("Â°  ");
          Serial.print("Frequency :");
          Serial.print(frequency,decimalPrecision);
          Serial.print("Hz  ");
          Serial.print("Power Factor :");
          Serial.println(powerFactor,decimalPrecision);
          sampleCount = 0;                                                            /* reset the sample counting quantity */
          periodSampleAccumulate = 0;                                                 /* reset the accumulated time for period wave from all samples */
          phaseAngleAccumulate =0;                                                    /* reset the accumulated time for time difference from all samples*/
        
        }
    }
  
       
