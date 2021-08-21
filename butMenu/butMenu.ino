/* Menu
 * Button 1
 *  1. Bluetooth -> active/deactive 
 *  2. Wifi-> Button 2: active/deactive/clear ssid
 *  3. Valve Threshold ->  
 * Button 2: Prev
 * Button 3: Next
 * Button 4: OK
 */


// constants won't change. They're used here to set pin numbers:
const int buttonPin[4] = {4,5,6,7};    // the number of the pushbutton pin
const int ledPin = 2;      // the number of the LED pin

// Variables will change:
int ledState = LOW;         // the current state of the output pin
int buttonState[4]={HIGH,HIGH,HIGH,HIGH};             // the current reading from the input pin
int lastButtonState[4] = {HIGH,HIGH,HIGH,HIGH};   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime[4];  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
int count[4]={0,1,1,1};
String menu, menuStr;
int wthres;


void setup() {
  Serial.begin(115200);
  for(int x;x<4;x++)pinMode(buttonPin[x], INPUT_PULLUP);
  
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
}

void loop() {
for(int x=0;x<4;x++)menuStr=debounce(x);

}

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
      Serial.println("BT ON OK");
      break;
    case 12:
      Serial.println("BT OFF OK");
      break;
    case 21:
      Serial.println("WF ON OK");
      break;
    case 22:
      Serial.println("WF OFF OK");
      break;
    case 23:
      Serial.println("CLR WF OK");
      break;
    case 30:
      Serial.print("Threshold OK ");
      Serial.print(wthres);
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
