/////////wifi dec
#include <WiFi.h>
#include <Preferences.h>
#include "BluetoothSerial.h"

String ssids_array[50];
String network_string;
String connected_string;

const char* pref_ssid = "";
const char* pref_pass = "";
String client_wifi_ssid;
String client_wifi_password;

const char* bluetooth_name = "myindrata";

long start_wifi_millis;
long wifi_timeout = 10000;
bool bluetooth_disconnect = false;

enum wifi_setup_stages { NONE, SCAN_START, SCAN_COMPLETE, SSID_ENTERED, WAIT_PASS, PASS_ENTERED, WAIT_CONNECT, LOGIN_FAILED };
enum wifi_setup_stages wifi_stage = NONE;

BluetoothSerial SerialBT;
Preferences preferences;
long interval = 1000;   
unsigned long previousMillis = 0; 
unsigned long previousMillis1 = 0; 
////
                                                                                                                                                                        
////
#define pin1 33
#define pin2 32
#define valvepin 5
float tArr=5;
int sensorValue1, sensorValue2;
float vin, vout;
const float zref= 20.0;
const float Vsupply = 3.3; 
float zSoil;

unsigned long int cur_time = 0 ;
unsigned long int time_elapsed = 0;
int time_period = 4;  


///////////////////////////////////////////////////////////////
/* Menu
 * Button 1
 *  1. Bluetooth -> active/deactive 
 *  2. Wifi-> Button 2: active/deactive/clear ssid
 *  3. Valve Threshold ->  
 * Button 2: Prev
 * Button 3: Next
 * Button 4: OK
 */

const int buttonPin[] = {14,27,13,12};     // if 5 ground {12,13,27,14} if 1 ground {14,27,13,12}
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
String menu="status";
String menuStr;
int wthres=20;//default
int valthres=20;//default
int valvestate;
String BTstate,Wifistate,dwthres,impd;
//////////////////////////////////////////////
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
//////////////////////////////////////////////
#include "ThingSpeak.h"
unsigned long myChannelNumber = 1489052;
const char * myWriteAPIKey = "2758Z5RECAP7ZZSF";
unsigned long lastTime = 0;
unsigned long timerDelay = 20000;
WiFiClient  client;
int iot=0;
int datasend=0;

///
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200); 

  //wifi setup
  Serial.println("Booting...");
  pinMode(ledPin, OUTPUT);
  preferences.begin("wifi_access", false);
  oled_init();
  iot=preferences.getInt("iot", 0);
  Serial.print("IOT...");
  Serial.println(iot);
  if (!init_wifi()&& iot == 1) { // Connect to Wi-Fi fails
    SerialBT.register_callback(callback);
  } else {
    SerialBT.register_callback(callback_show_ip);
  }

  //SerialBT.begin(bluetooth_name);
  //button setup
  for(int x=0;x<4;x++)pinMode(buttonPin[x],INPUT_PULLUP);
  pinMode(valvepin, OUTPUT);
  digitalWrite(valvepin, LOW);
  digitalWrite(ledPin, ledState);
 ////
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  oled_case0();
  delay(1000);
}
