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
const int ledPin = 13;      // the number of the LED pin

// Variables will change:
int ledState = LOW;         // the current state of the output pin
int buttonState[4]={HIGH,HIGH,HIGH,HIGH};             // the current reading from the input pin
int lastButtonState[4] = {HIGH,HIGH,HIGH,HIGH};   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime[4];  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
int count[4]={0,10,20,30};
void setup() {
  Serial.begin(115200);
  for(int x;x<4;x++)pinMode(buttonPin[x], INPUT_PULLUP);
  
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
}

void loop() {
for(int x=0;x<4;x++)count[x]=debounce(x);

}

int debounce(int x){
  int reading = digitalRead(buttonPin[x]);
  if (reading != lastButtonState[x]) {
    lastDebounceTime[x] = millis();
    
  }

  if ((millis() - lastDebounceTime[x]) > debounceDelay) {
    if (reading != buttonState[x]) {
      buttonState[x] = reading;
      if (buttonState[x] == LOW) {
        ledState = !ledState;
        count[x]++;
        but_max();
        Serial.println(count[x]);
        }
    }
  }

  digitalWrite(ledPin, ledState);
  lastButtonState[x] = reading;
  return count[x];
}

void but_max(){
  if (count[0]>4)count[0]=1;
  if (count[0]==1 && count[1]>12)count[1]=11;
  if (count[0]==2 && (count[1]>24 || count[1]<=20))count[1]=21;
  if (count[0]==3 && (count[1]>1000 || count[1]<=0) )count[1]=31;
}
