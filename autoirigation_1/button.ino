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
         ///*For Serial Monitor
         if(x==0)main_menu(count[0]);
         if(x==1 || x == 2)sub_menu(menu.toInt());
         if(x==3)menu_ok(menu.toInt());   
         //*/ 
        }
    }
  }
  /*For Oled
  if(x==0)main_menu(count[0]);
  if(x==1 || x == 2)sub_menu(menu.toInt());
  if(x==3)menu_ok(menu.toInt()); 
  */

  digitalWrite(ledPin, ledState);
  lastButtonState[x] = reading;
  return menu;

}

void but_max(){
   if (count[0]>3)count[0]=0;
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
      oled_show_center("** Starting BT");
      break;
    case 12:
      Serial.println("** Stopping BT");
      SerialBT.end();
      oled_show_center("** Stopping BT");
      break;
    case 21:
      Serial.println("** Starting STA");
      iot=1;
      preferences.putInt("iot", iot);
      new_con(); 
      oled_show_center("** Starting STA");          
      break;
    case 22:
      WiFi.mode(WIFI_OFF);
      Serial.println("** Stopping WiFi");
      iot=0;
      preferences.putInt("iot", iot);
      oled_show_center("** Stopping WiFi");  
      break;
    case 23:
      preferences.remove("pref_ssid");
      preferences.remove("pref_pass");
      Serial.println("CLR WF OK");
      WiFi.mode(WIFI_OFF);
      oled_show_center("** CLR WF OK");  
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
    case 0:
      Serial.println("0. Status");
      oled_case0();
      break;
    case 1:
      Serial.println("1. Set BT");
      oled_BT();
      break;
    case 2:
      Serial.println("2. Set WIFI");
      oled_Wifi();
      break;
    case 3:
      Serial.println("3. Set Threshold");
      oled_setth();
      set_threshold();
      break;
  }
}

void sub_menu(int var){
  switch (var){
    case 11:
      Serial.println("BT ON");
      oled_show_center("BT ON");
      break;
    case 12:
      Serial.println("BT OFF");
      oled_show_center("BT OFF");
      break;
    case 21:
      Serial.println("WF ON");
      oled_show_center("WIFI ON");
      break;
    case 22:
      Serial.println("WF OFF");
      oled_show_center("WIFI OFF");
      break;
    case 23:
      Serial.println("CLR WF");
      oled_show_center("CLR WF");
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
   while (!init_wifi()) { //Connect to Wi-Fi fails
     Serial.println("Connect via BT");
     oled_show_center("Connect Wifi via BT");
     SerialBT.register_callback(callback);  
     wifi_connect();    
   } 
   if (init_wifi()) {
     Serial.println(WiFi.localIP());
     oled_show_center(String(WiFi.localIP()));
     SerialBT.register_callback(callback_show_ip);
   }   
   
}

// Serial.print(but[0]);
// Serial.print(", ");
// Serial.print(but[1]);
// Serial.print(", ");
// Serial.print(but[2]);
// Serial.print(", ");
// Serial.println(but[3]);
