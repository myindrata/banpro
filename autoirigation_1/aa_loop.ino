// the loop routine runs over and over again forever:
String testext;
void loop() {
  //az_det();
  send_thingspeak();
  for(int x=0;x<4;x++)menuStr=debounce(x);
 

}

void loop_con(){
  for(int x=0;x<4;x++)menuStr=debounce(x);
  if(WiFi.status() != WL_CONNECTED && WiFi.status() != 255){
    Serial.println("try to connect");
    wifi_connect();
  }
  if(WiFi.status() == WL_CONNECTION_LOST || WiFi.status() == WL_CONNECT_FAILED){
    Serial.println("try to connect");
    wifi_connect();
  }
  if(WiFi.status() == WL_CONNECTED)send_thingspeak();
}



//void manual_con(){
//  Serial.println(WiFi.status());
//  delay(3000);
//  Serial.println(WiFi.status());
//  delay(1000);
//  WiFi.begin("Fauzian 2857", "1756rustam");
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.println(WiFi.status());
//    Serial.println("Connecting to WiFi..");
//  }
//  Serial.println("Connected to the WiFi network");
//
//}
