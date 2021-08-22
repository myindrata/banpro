String debounce(int x){
  int reading = digitalRead(buttonPin[x]);  
  if (reading != lastButtonState[x]) {
    lastDebounceTime[x] = millis();
  } 
  if ((millis() - lastDebounceTime[x]) > debounceDelay) {
      if (reading != buttonState[x]) {
      buttonState[x] = reading;
      if (buttonState[x] == LOW) {
        ledState = !ledState;
         if (x==0){count[x]++;count[1]=0;count[2]=0;count[3]=0;}
         if (x==1)count[x]++; 
         if (x==2)count[1]--; 
         but_max();
         menu=String(count[0])+String(count[1]);     
         /*
         Serial.print(menu);
         Serial.print(" - ");
         Serial.print(count[0]);
         Serial.print(" - ");
         Serial.println(count[1]);
         */
         //OK
         if(x==0)main_menu(count[0]);
         if(x==1 || x == 2)sub_menu(menu.toInt());
         if(x==3)menu_ok(menu.toInt());    
        }
    }
  }

  digitalWrite(ledPin, ledState);
  lastButtonState[x] = reading;
  return menu;
}

void but_max(){
   if (count[0]>3)count[0]=1;
   if (count[0]==1 && count[1]>2 ) count[1]=1; //BT Menu ON/OFF
   if (count[0]==1 && count[1]<0 ) count[1]=2; //BT Menu ON/OFF
   
   if (count[0]==2 && count[1]>3) count[1]=1; // WF Menu ON/OF/Clr 
   if (count[0]==2 && count[1]<0) count[1]=3; // WF Menu ON/OF/Clr 

   if (count[0]==3 && wthres>100) wthres=0; // Threshold menu
   if (count[0]==3 && wthres<0) wthres=100;
}

void menu_ok(int var){
  switch (var){
    case 11:
      Serial.println("** Starting BT");
      SerialBT.begin(bluetooth_name);
      break;
    case 12:
      Serial.println("** Stopping BT");
      SerialBT.end();
      break;
    case 21:
      Serial.println("** Starting STA");
      new_con();           
      break;
    case 22:
      WiFi.mode(WIFI_OFF);
      Serial.println("** Stopping WiFi");
      break;
    case 23:
      preferences.remove("pref_ssid");
      preferences.remove("pref_pass");
      Serial.println("CLR WF OK");
      WiFi.mode(WIFI_OFF);
      new_con();
      break;
    case 30:
      Serial.print("Threshold OK ");
      Serial.print(wthres);
      preferences.putString("wthres", String(wthres));
      valthres=wthres;
      break;
  }
}

void main_menu(int var){
  switch (var){
    case 1:
      Serial.println("1. Set BT");
      break;
    case 2:
      Serial.println("2. Set WIFI");
      break;
    case 3:
      Serial.println("3. Set Threshold");
      set_threshold();
      break;
  }
}

void sub_menu(int var){
  switch (var){
    case 11:
      Serial.println("BT ON");
      break;
    case 12:
      Serial.println("BT OFF");
      break;
    case 21:
      Serial.println("WF ON");
      break;
    case 22:
      Serial.println("WF OFF");
      break;
    case 23:
      Serial.println("CLR WF");
      break;
  }
}

int set_threshold(){
  while(count[0]==3){
  int reading1 = digitalRead(buttonPin[1]);  
  int reading2 = digitalRead(buttonPin[2]);  
  if (reading1==0)wthres++;
  if (reading2==0)wthres--;
  but_max();
  delay(100);
   Serial.print(menu);
   Serial.print(" - ");
   Serial.print(count[0]);
   Serial.print(" - ");
   Serial.print(count[1]);
   Serial.print(" - ");
   Serial.println(wthres);
  debounce(0);
  debounce(3);
  }
}

void new_con(){
   if (!init_wifi()) { //Connect to Wi-Fi fails
     SerialBT.register_callback(callback);
     Serial.println("Connect via BT");
     
   } else {
     Serial.println(WiFi.localIP());
     SerialBT.register_callback(callback_show_ip);
   }   
   wifi_connect(); 
}

// Serial.print(but[0]);
// Serial.print(", ");
// Serial.print(but[1]);
// Serial.print(", ");
// Serial.print(but[2]);
// Serial.print(", ");
// Serial.println(but[3]);
