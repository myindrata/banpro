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
count[0]=debounce(0);
count[1]=debounce(1);
count[2]=debounce(2);
count[3]=debounce(3);
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
  if (count[0]>4)count[0]=0;
  if (count[1]>14)count[1]=10;
  if (count[2]>24)count[2]=20;
  if (count[3]>34)count[3]=30;
}
