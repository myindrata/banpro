#include <Arduino.h>
#include <Ewma.h>
Ewma adcFilter1(0.01);   // Bigger Less smoothing - faster to detect changes, but more prone to noise
Ewma adcFilter2(0.01);  // Smaller More smoothing - less prone to noise, but slower to detect changes

void peak_det(){
 int mx1=0,mx2=0;
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
   vin=((mx1 * Vsupply) / 4095);
   vout=((mx2 * Vsupply) / 4095);
   float filtered1 = adcFilter1.filter(vin);
   float filtered2 = adcFilter2.filter(vout);
   //calculate z
   zSoil=((filtered1/filtered2)-1)*zref; //kOhm
   //display_out()
   mx1 = 0; 
   mx2 = 0;
}

//void display_out(){
//   Serial.print(vin);
//   Serial.print(",");
//   Serial.print(vout);
//   Serial.print(",");
//   Serial.print(filtered1);
//   Serial.print(",");
//   Serial.println(filtered2);
//}
