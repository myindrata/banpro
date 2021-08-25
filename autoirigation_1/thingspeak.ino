void send_thingspeak(){
  int z, valve;
  if ((millis() - lastTime) > timerDelay) {  
    if (datasend==0){
      z = ThingSpeak.writeField(myChannelNumber, 1, zSoil, myWriteAPIKey);
      if(z == 200)Serial.println("Channel z update successful.");
      else Serial.println("Problem updating z channel. HTTP error code " + String(z));
    }
    if (datasend==1){
      valve = ThingSpeak.writeField(myChannelNumber, 2, valvestate, myWriteAPIKey);
      if(valve == 200)Serial.println("Channel Valve update successful.");
      else Serial.println("Problem updating valve channel. HTTP error code " + String(valve));   
    }
    lastTime = millis();
    datasend++;
    if(datasend>1) datasend=0;
  }
}
