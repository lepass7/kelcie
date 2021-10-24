                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      #define BLYNK_PRINT Serial
#include "htmlFiles.h"
#include <rom/rtc.h>              //to catch reset reason

//For WEB server
#include <ESPmDNS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "constants.h"
//#include "pitches.h"
//#include <EEPROM.h>                           //read write data in eeprom memory
#include <Preferences.h>                      //read or write data in falsh memory
#include <M5Stack.h>
//#include <list>
//#include <math.h>
//#include <ACS712.h>                           //to be used to read current sensor
//#include "EmonLib.h"                          
#include <M5OnScreenKeyboard.h>               //used for virtual keyboard https://github.com/lovyan03/M5Stack_OnScreenKeyboard
#include <M5ButtonDrawer.h>                   //used for virtual keyboard
#include <WiFi.h>
#include <WiFiClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>                  //for temperature sensor
#include <BlynkSimpleEsp32.h>                   //BLYNK library
#include <Dns.h>
#include <ESP32Ping.h>                          //download https://github.com/marian-craciunescu/ESP32Ping and install C:\Users\<user name>\Documents\Arduino\libraries and rename to Esp32Ping 
#include "functions_declaration.h"
//#include "init_libraries.h"
#include <esp32fotaa.h>                          //(the original library is esp32fota.h I am using the modified library esp32fotaa.h . needs arduinojson to be downgrade or upgrade software https://arduinojson.org/v6/error/jsonbuffer-is-a-class-from-arduinojson-5/
#include <HTTPClient.h>                           //library to perform HTTP requests (used for blynk token validation)

#include "Free_Fonts.h"
//#include "fonts/OpenSans_Regular30pt7b.h"       //setup font https://rop.nl/truetype2gfx/
#include "fonts/OpenSans_Regular20pt7b.h"
#include "fonts/BebasNeue_Light40pt7b.h"
#include "fonts/BebasNeue_Light30pt7b.h"
/*#include "fonts/Neutraface_2_Display_Bold90pt7b.h"*/
#include "fonts/BebasNeue_Regular75pt7b.h"
#include "variables.h"
#include "init_libraries.h"


#include "functions.h"  

//TaskHandle_t Task1;

  

void setup() {
  // put your setup code here, to run once:
  //1. Start serial 
  initializeKelcie();  
  M5.Lcd.clear(BLACK);
  serialPrint(ENABLE_SERIAL, DEBUG_MSG, "SSID: "+(String)WiFi.SSID());
  serialPrint(ENABLE_SERIAL, DEBUG_MSG, "Pass: "+(String)WiFi.psk());
  serialPrint(ENABLE_SERIAL, DEBUG_MSG, "Setup function finished");      
  attachInterrupt(digitalPinToInterrupt(37), buttonCPressed, RISING);
  attachInterrupt(digitalPinToInterrupt(38), buttonBPressed, RISING);
  attachInterrupt(digitalPinToInterrupt(39), buttonAPressed, RISING);
  attachInterrupt(digitalPinToInterrupt(OVC_FAULT), overCurrentDetected, FALLING);

  //setup timer
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  //timerAlarmWrite(timer, 1000000, true);    //1 second
  timerAlarmWrite(timer, 1000, true);    //1 milisecond
  timerAlarmEnable(timer);    
}

void loop() {
  // put your main code here, to run repeatedly:
  loopInTime();
  //handleButtons();
  M5.update();      //updates buttons states
  handleBlynk();

  if(buttonBPressedFlag)
  {
    serialPrint(ENABLE_SERIAL, INFO_MSG, "Button B pressed");    
    heaterOnRequest = !heaterOnRequest;
    if(Blynk.connected()) Blynk.virtualWrite(V0, heaterOnRequest);
    if(heaterOnRequest) digitalWrite(RLY, true);
    else deactivateHeater();
    drawDefaultScreen(currentScreen);
    buttonBPressedFlag = false;
  }

  if(asyncFirstTimeSetup && WiFi.status() == WL_CONNECTED) setupAsynchServer();    
}
