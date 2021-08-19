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
int ledState = LOW;  
long interval = 1000;   
const int ledPin = 2;
unsigned long previousMillis = 0; 
////
////
#define pin1 4
#define pin2 15
float tArr=5;
int sensorValue1, sensorValue2;
float volt1, volt2;
const float zref= 20.0;
const float Vsupply = 3.3; 

unsigned long int cur_time = 0 ;
unsigned long int time_elapsed = 0;
int time_period = 1;  




//////


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200); 
  //wifi setup
  Serial.println("Booting...");
  pinMode(ledPin, OUTPUT);
  preferences.begin("wifi_access", false);

//  if (!init_wifi()) { // Connect to Wi-Fi fails
//    SerialBT.register_callback(callback);
//  } else {
//    SerialBT.register_callback(callback_show_ip);
//  }

  SerialBT.begin(bluetooth_name);
  //button setup
  for(int x=0;x<4;x++)pinMode(buttonPin[x],INPUT_PULLUP);
}
