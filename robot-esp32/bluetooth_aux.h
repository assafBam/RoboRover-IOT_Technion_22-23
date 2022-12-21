#ifndef BLUETOOTH_AUX__H__
#define BLUETOOTH_AUX__H__

#define BT_NAME "RoboRover"

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

extern String ssid;
extern String password;

namespace bluetooth{
  BluetoothSerial SerialBT;
  void init(){
    SerialBT.begin(BT_NAME);
    Serial.println("bluetooth started");
    while(!SerialBT.connected());
    Serial.println("bluetooth connected");
  }

  String read(){
    String res="";
    while(SerialBT.available()){
      res+=(char) SerialBT.read();     
    }
    return res; 
  }

  void write(String str){
    SerialBT.write((const unsigned char*)str.c_str(), str.length());
  }
   
  bool get_ssid_password(){
    write("ssid");
    while(!SerialBT.available());
    ssid = read();
    Serial.printf("ssid: %s\t", ssid);
    write("password");
    while(!SerialBT.available());
    password = read(); 
    Serial.printf("ssid: %s\t", ssid);
    Serial.printf("password: %s\n", password);   
    return true;
  }  

  bool sendIP(String ip){
    write(ip);  
    Serial.printf("sent the ip address via bluetooth\n");  
  }
}

#endif