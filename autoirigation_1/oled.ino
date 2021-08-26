void oled_init(){
 if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);             
  if (millis() - previousMillis1 >= 2000) {
    previousMillis1 = millis();
    display.setTextColor(WHITE);       
    drawCentreString("Auto", 64, 22);
    drawCentreString("Watering", 64, 32);
    display.display();
  }
}

void drawCentreString(String buf, int x, int y)
{
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(buf, x, y, &x1, &y1, &w, &h); //calc width of new string
    display.setCursor(x - w / 2, y);
    display.print(buf);
}

void oled_def(){
    if(!SerialBT.isReady())BTstate="BT-OFF";
    else if(SerialBT.isReady()) BTstate="BT-ON";
    else if(SerialBT.connect()) BTstate="BT-Connected";
    if(WiFi.status()==255)Wifistate="WIFI-OFF";
    else if (WiFi.status()==6)Wifistate="No-Connection";
    else if (WiFi.status()==3)Wifistate="WIFI-Connected";
    valthres=preferences.getString("wthres", "").toInt();
    if (valthres==0) valthres=20;
    dwthres="Thres "+ String(valthres);
    impd="Z = "+ String(zSoil);  
    display.clearDisplay();
    display.setTextSize(1); 
    display.setTextColor(WHITE);   
    display.setCursor(10,20);             
    display.println(BTstate);  
    display.setCursor(10,30);             
    display.println(Wifistate); 
    display.setCursor(10,40);             
    display.println(dwthres);    
    display.setCursor(10,50);             
    display.println(impd); 
    display.display();
}

void oled_case0(){
    String BTstate,Wifistate,dwthres,impd;
    if(!SerialBT.isReady())BTstate="BT-OFF";
    else if(SerialBT.isReady()) BTstate="BT-ON";
    else if(SerialBT.connect()) BTstate="BT-Connected";
    if(WiFi.status()==255)Wifistate="WIFI-OFF";
    else if (WiFi.status()==6)Wifistate="No-Connection";
    else if (WiFi.status()==3)Wifistate="WIFI-Connected";
    valthres=preferences.getString("wthres", "").toInt();
    dwthres="Thres "+ String(valthres);
    impd="Z = "+ String(zSoil);
    display.clearDisplay();
    display.setTextSize(1);         
    display.setTextColor(WHITE);   
    display.setCursor(10,20);             
    display.println(BTstate);  
    display.setCursor(10,30);             
    display.println(Wifistate); 
    display.setCursor(10,40);             
    display.println(dwthres);    
    display.setCursor(10,50);             
    display.println(impd); 
    display.display();
}

void oled_BT(){
    display.clearDisplay();
    display.setTextSize(1);         
    display.setTextColor(BLACK,WHITE);   
    display.setCursor(10,20);             
    display.println("1. Set BT");  
    display.setTextColor(WHITE); 
    display.setCursor(10,30);             
    display.println("2. Set WIFI"); 
    display.setCursor(10,40);             
    display.println("3. Set Threshold");
    display.display(); 
}

void oled_Wifi(){
    display.clearDisplay();
    display.setTextSize(1);         
    display.setTextColor(WHITE);   
    display.setCursor(10,20);             
    display.println("1. Set BT");  
    display.setTextColor(BLACK,WHITE);
    display.setCursor(10,30);             
    display.println("2. Set WIFI"); 
    display.setTextColor(WHITE);
    display.setCursor(10,40);             
    display.println("3. Set Threshold");
    display.display();
}

void oled_setth(){
    display.clearDisplay();
    display.setTextSize(1);         
    display.setTextColor(WHITE);   
    display.setCursor(10,20);             
    display.println("1. Set BT");  
    display.setCursor(10,30);             
    display.println("2. Set WIFI"); 
    display.setTextColor(BLACK,WHITE);
    display.setCursor(10,40);             
    display.println("3. Set Threshold");
    display.display();  
}

void oled_show_center(String buf) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    drawCentreString(buf, 64, 32); 
    display.display();
}
