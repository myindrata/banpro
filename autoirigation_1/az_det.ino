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
   if (filtered2!=0){
    zSoil=((filtered1/filtered2)-1)*zref*0.95; //kOhm
    if (zSoil>500)zSoil=500;
    //zSoil=(-0.0008*(zSoil-11)+0.9)*zSoil;
   }
   if (isnan(zSoil)|| zSoil<0)zSoil=0;
   
   //display_out()
//    display.clearDisplay();
//    display.setCursor(10,20);             
//    display.println(analogRead(pin1));  
//    display.setCursor(10,30);             
//    display.println(analogRead(pin2)); 
//    display.setCursor(10,40);             
//    display.println(zSoil);  
//    display.display();
   mx1 = 0; 
   mx2 = 0;
   valve_con();

}

void valve_con(){
   //just for testing
   //zSoil = random(0,4000)/100.0;
   //valve control
   if (zSoil>valthres+2){
    valvestate=1;
    digitalWrite(valvepin, valvestate);
   }
   else if(zSoil<valthres-2){
    valvestate=0;
    digitalWrite(valvepin, valvestate);
   }
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
