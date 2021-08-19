#include <Arduino.h>
#include <Ewma.h>
Ewma adcFilter1(0.01);   // Less smoothing - faster to detect changes, but more prone to noise
Ewma adcFilter2(0.01);  // More smoothing - less prone to noise, but slower to detect changes

void peak_det(){
 int mx1=0,mx2=0;
 float peak1=0, peak2=0;
 int count;
  cur_time = millis();
  time_elapsed =0; 
  count=0;
  while(time_elapsed <=time_period)
  { 
     sensorValue1 = analogRead(pin1);
     sensorValue2 = analogRead(pin2);
     mx1 = max(sensorValue1, mx1);
     mx2 = max(sensorValue2, mx2);  
     time_elapsed = millis()-cur_time;
     count++;
  } 
   volt1=((mx1 * Vsupply) / 4095);
   volt2=((mx2 * Vsupply) / 4095);
   float filtered1 = adcFilter1.filter(volt1);
   float filtered2 = adcFilter2.filter(volt2);
   Serial.print(volt1);
   Serial.print(",");
   Serial.print(volt2);
   Serial.print(",");
   Serial.print(filtered1);
   Serial.print(",");
   Serial.println(filtered2);
   peak1 = peak1+volt1;
   mx1 = 0; 
   peak2 = peak2+volt2;
   mx2 = 0;
}
