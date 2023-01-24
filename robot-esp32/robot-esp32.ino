#include <ESP32Servo.h>
// #include <analogWrite.h>
// #include <tone.h>
// #include <ESP32Tone.h>
// #include <ESP32PWM.h>


#include "esp_camera.h"
#include <WiFi.h>

//
// WARNING!!! Make sure that you have either selected ESP32 Wrover Module,
//            or another board which has PSRAM enabled
//
// Adafruit ESP32 Feather

// Select camera model
//#define CAMERA_MODEL_WROVER_KIT
//#define CAMERA_MODEL_M5STACK_PSRAM
#define CAMERA_MODEL_AI_THINKER

#include "credentials.h"
#include "bluetooth_aux.h"
#include "camera_aux.h"
#include "wifi_aux.h"

String ssid;   //Enter SSID WIFI Name
String password;   //Enter WIFI Password


// GPIO Setting
extern int gpLb =  2; // Left 1
extern int gpLf = 14; // Left 2
extern int gpRb = 15; // Right 1
extern int gpRf = 13; // Right 2
extern int gpLed =  33; // Light
int gpClaw = 12;
extern String WiFiAddr ="";
Servo claw_servo;
namespace Claw{
const int open = 30;
const int closed = 83;
}

extern void startCameraServer();

void init();
void claw();


void setup() {
  init();
  camera::init();  
  bluetooth::init();
  bluetooth::get_ssid_password();
  wifi::init(ssid.c_str(), password.c_str());
  

  startCameraServer();

  Serial.print("\nCamera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  WiFiAddr = WiFi.localIP().toString();
  Serial.println("' to connect");  
  bluetooth::write(WiFiAddr);
  Serial.printf("sent the ip address via bluetooth\n"); 
  bluetooth::SerialBT.end();  
}

void loop() {
  // put your main code here, to run repeatedly:

}

void init(){
  Serial.begin(9600);
  Serial.setDebugOutput(false);
  Serial.println();
  delay(10); 
  Serial.println("starting"); 


  pinMode(gpLb, OUTPUT); //Left Backward
  pinMode(gpLf, OUTPUT); //Left Forward
  pinMode(gpRb, OUTPUT); //Right Forward
  pinMode(gpRf, OUTPUT); //Right Backward
  pinMode(gpLed, OUTPUT); //Light
  claw_servo.attach(gpClaw);  // Claw 

  //initialize
  digitalWrite(gpLb, LOW);
  digitalWrite(gpLf, LOW);
  digitalWrite(gpRb, LOW);
  digitalWrite(gpRf, LOW);
  digitalWrite(gpLed, LOW);
  claw_servo.write(Claw::closed);
}


void claw(){
  static bool pos=true;
  claw_servo.write(pos? Claw::closed : Claw::open); //TODO: check the pose of the claw when closed and change here
  pos = !pos;    
}