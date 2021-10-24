bool wifiConnect(uint8_t attempts)
{
  //connect on local wifi
  if(WiFi.status() != WL_CONNECTED) WiFi.begin();
  else return true;   //its connected;
  
  int counter = 0;
  while(WiFi.status() != WL_CONNECTED)
  {
    serialPrint(ENABLE_SERIAL, INFO_MSG, (String)counter + "  - Connecting");
    delay(1000);
    counter++;
    //M5.Lcd.print(".");
    if(counter > attempts ) break;
  }
  if(WiFi.status () == WL_CONNECTED) return true;
  else return false;
}

// Replaces placeholder with button section in your web page
String processor(const String& var){
  //Serial.println(var);
  if(var == "BUTTONPLACEHOLDER"){
    String kelcieData = "let kelcieData = [";
    /*kelcieData += "['My IP', '"+ WiFi.localIP().toString() +"'],";
    //kelcieData += "['Time server:', '"+ (String)ntpServer +"'],"; 
    //kelcieData += "['Time', '"+ printLocalTime() +"'],"; 
    kelcieData += "['Free heap:', '"+ (String)ESP.getFreeHeap() +"'],"; 
    kelcieData += "['Reset reason on CPU(0):', '"+ print_reset_reason(rtc_get_reset_reason(0)) +"'],"; 
    kelcieData += "['Reset reason on CPU(1):', '"+ print_reset_reason(rtc_get_reset_reason(1)) +"'],";
    //if( updatedNeeded)kelcieData += "['Available Update', 'Yes'],";
    //else  kelcieData += "['Available Update', 'No'],";
    kelcieData += "['Serial Message Debug:', '"+ serialMessageDebug +"'],";
    kelcieData += "['Serial Message Info:', '"+ serialMessageInfo +"'],";
    kelcieData += "['Serial Message Seconds:', '"+ serialMessageSeconds +"'],";
    //if(internetConnectionAvailable) kelcieData += "['Internet connection', 'Yes'],";
    //else kelcieData += "['Internet connection', 'No'],";
    //if(sensorAttached) kelcieData += "['Sensor attached', 'Yes'],";
    //else kelcieData += "['Sensor attached', 'No'],";
    /*kelcieData += "['Token', '"+ blynkToken +"'],";
    kelcieData += "['Current temperature', '"+ (String)currentTemperature +"'],";  
    kelcieData += "['Set Point', '"+ (String)setPoint +"&#8451;'],";
    kelcieData += "['Heater active set point', '"+ (String) maxHeaterActive +" minutes'],";  
    kelcieData += "['Heater active', '"+ (String) elapseMinutes +" minutes'],";  */
    kelcieData += "['January', '"+ (String)((monthsConsumption[0]*HEATER_KW/60)*KWH_COST) +"&#x20AC;'],";
    kelcieData += "['February', '"+ (String)((monthsConsumption[0]*HEATER_KW/60)*KWH_COST) +"&#x20AC;'],";
    kelcieData += "['March', '"+ (String)((monthsConsumption[0]*HEATER_KW/60)*KWH_COST) +"&#x20AC;'],";  
    kelcieData += "['April', '"+ (String)((monthsConsumption[0]*HEATER_KW/60)*KWH_COST) +"&#x20AC;'],";  
    kelcieData += "['May', '"+ (String)((monthsConsumption[0]*HEATER_KW/60)*KWH_COST) +"&#x20AC;'],";  
    kelcieData += "['June', '"+ (String)((monthsConsumption[0]*HEATER_KW/60)*KWH_COST) +"&#x20AC;'],";  
    kelcieData += "['July', '"+ (String)((monthsConsumption[0]*HEATER_KW/60)*KWH_COST) +"&#x20AC;'],";  
    kelcieData += "['August', '"+ (String)((monthsConsumption[0]*HEATER_KW/60)*KWH_COST) +"&#x20AC;'],";  
    kelcieData += "['September', '"+ (String)((monthsConsumption[0]*HEATER_KW/60)*KWH_COST) +"&#x20AC;'],";  
    kelcieData += "['October', '"+ (String)((monthsConsumption[0]*HEATER_KW/60)*KWH_COST) +"&#x20AC;'],";  
    kelcieData += "['November', '"+ (String)((monthsConsumption[0]*HEATER_KW/60)*KWH_COST) +"&#x20AC;'],";  
    kelcieData += "['December', '"+ (String)((monthsConsumption[0]*HEATER_KW/60)*KWH_COST) +"&#x20AC;']";  
    kelcieData += "['January', '"+ (String)((monthsConsumption[0]*HEATER_KW/60)*KWH_COST) +"&#x20AC;'],";  
    
          
    kelcieData += "];";
    return kelcieData;
  }
   if(var == "TOKEN_VARIABLE")
  {
    String kelcieData = "";
    String blynkToken="";
    if(!firstTimeSetupFlag) 
    {
      preferences.begin(PR_NAMESPACE, false);     //false --> start preferenece in Read and write mode, if true --> start preferences in read only mode
      blynkToken = preferences.getString(PR_BLYNK_TOKEN, "");
      preferences.end();
    }    
    kelcieData += "<form action=\"/get/\" method=\"get\" name=\"tokenSubmitForm\">";
    kelcieData += "<div class=\"form-group\">";
    kelcieData += "<label for=\"blynkToken\">Blynk Token</label>";
    kelcieData += "<input type=\"text\" value = \"" +blynkToken+ "\" name=\"message\" class=\"form-control\" id=\"blynkToken\" aria-describedby=\"tokenHelp\" placeholder=\"write your token\" maxlength=\"32\">";
    kelcieData += "<small id=\"tokenHelp\" class=\"form-text text-muted\">This text will help your Kelcie to communicate with your smart phone</small>";
    kelcieData += "</div>";
    kelcieData += "<button type=\"button\" onclick=\"document.forms['tokenSubmitForm'].submit();\" class=\"btn btn-primary\">Submit</button>";
    kelcieData += "</form>";
    
    return kelcieData;
  }
  return String();
}

void notFound(AsyncWebServerRequest *request) 
{
    request->send(404, "text/plain", "Not found");
}
void setupAsynchServer()
{
  /*server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Hello, world");
    });*/
    //setup asynch server only one time and when esp is connected
    asyncFirstTimeSetup = false;

    //check if wifi is connected (in case that the function is called outside main loo
    
    //setup mDNS
    if(!MDNS.begin(NETWORK_NAME)) 
    {
      serialPrint(ENABLE_SERIAL, DEBUG_MSG, "Error starting mDNS");
       return;
    }
     server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

    // Send a GET request to <IP>/get?message=<message>
    server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String message;
        if (request->hasParam(PARAM_MESSAGE)) {
            message = request->getParam(PARAM_MESSAGE)->value();
            blynkTemporaryToken = message;
            tokenSubmittedFlag = true;                    //this flag is used when user is trying to enter the token on token setup
        } else {
            message = "No message sent";
        }
        serialPrint(ENABLE_SERIAL, INFO_MSG, "Get message: " + message + "Flag: " + (String)tokenSubmittedFlag);
              
        request->send_P(200, "text/html", token_setup_html, processor);
        //TODO: receive the message from the server and update TOKEN
        
        
    });

    // Send a POST request to <IP>/post with a form field message set to <message>
    server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request){
        String message;
        if (request->hasParam(PARAM_MESSAGE, true)) {
            message = request->getParam(PARAM_MESSAGE, true)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, POST: " + message);
    });

    server.onNotFound(notFound);

    server.begin();
}
String print_reset_reason(RESET_REASON reason)
{
  switch ( reason)
  {
    case 1 : return ("POWERON_RESET: Vbat power on reset");break;          /**<1, Vbat power on reset*/
    case 3 : return ("SW_RESET: Software reset digital core");break;               /**<3, Software reset digital core*/
    case 4 : return("OWDT_RESET: Legacy watch dog reset digital core");break;             /**<4, Legacy watch dog reset digital core*/
    case 5 : return ("DEEPSLEEP_RESET: Deep Sleep reset digital core");break;        /**<5, Deep Sleep reset digital core*/
    case 6 : return ("SDIO_RESET: Reset by SLC module, reset digital core");break;             /**<6, Reset by SLC module, reset digital core*/
    case 7 : return ("TG0WDT_SYS_RESET: Timer Group0 Watch dog reset digital core");break;       /**<7, Timer Group0 Watch dog reset digital core*/
    case 8 : return ("TG1WDT_SYS_RESET: Timer Group1 Watch dog reset digital core");break;       /**<8, Timer Group1 Watch dog reset digital core*/
    case 9 : return ("RTCWDT_SYS_RESET: RTC Watch dog Reset digital core");break;       /**<9, RTC Watch dog Reset digital core*/
    case 10 : return ("INTRUSION_RESET:  Instrusion tested to reset CPU");break;       /**<10, Instrusion tested to reset CPU*/
    case 11 : return ("TGWDT_CPU_RESET: Time Group reset CPU");break;       /**<11, Time Group reset CPU*/
    case 12 : return ("SW_CPU_RESET: Software reset CPU");break;          /**<12, Software reset CPU*/
    case 13 : return ("RTCWDT_CPU_RESET: RTC Watch dog Reset CPU");break;      /**<13, RTC Watch dog Reset CPU*/
    case 14 : return ("EXT_CPU_RESET: for APP CPU, reseted by PRO CPU");break;         /**<14, for APP CPU, reseted by PRO CPU*/
    case 15 : return ("RTCWDT_BROWN_OUT_RESET: Reset when the vdd voltage is not stable");break;/**<15, Reset when the vdd voltage is not stable*/
    case 16 : return ("RTCWDT_RTC_RESET: RTC Watch dog reset digital core and rtc module");break;      /**<16, RTC Watch dog reset digital core and rtc module*/
    default : return ("NO_MEAN");
  }
}
int isBlynkTokenValid(String token)
{
  //TODO
  //RETURNS:
  /// HTTP client errors
  //  #define HTTPC_ERROR_CONNECTION_REFUSED  (-1)
  //  #define HTTPC_ERROR_SEND_HEADER_FAILED  (-2)
  //  #define HTTPC_ERROR_SEND_PAYLOAD_FAILED (-3)
  //  #define HTTPC_ERROR_NOT_CONNECTED       (-4)
  //  #define HTTPC_ERROR_CONNECTION_LOST     (-5)
  //  #define HTTPC_ERROR_NO_STREAM           (-6)
  //  #define HTTPC_ERROR_NO_HTTP_SERVER      (-7)
  //  #define HTTPC_ERROR_TOO_LESS_RAM        (-8)
  //  #define HTTPC_ERROR_ENCODING            (-9)
  //  #define HTTPC_ERROR_STREAM_WRITE        (-10)
  //  #define HTTPC_ERROR_READ_TIMEOUT        (-11)
  //(-100) --> No Wifi
  //(-99) --> token checked but is not valid
  //(1) --> OK
  //the function validates a blynk token and returns TRUE if token is valid and FALSE if token is not valid
  //http://blynk-cloud.com/TOKEN/project <-- this will return "Invalid token" if the token is not valid (if its valid it will return a json file containing all project details
  //IDEA: searc
  /*M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setFreeFont(SUBTITLE_FNT);
  M5.Lcd.setCursor(0,50);
  */
  //if(WiFi.status() != WL_CONNECTED) WiFi.begin();
  //uint_least8_t timeOutCounter = 0;
  serialPrint(ENABLE_SERIAL, INFO_MSG, "Checking token validity (http://blynk-cloud.com/" + token + "/project");
  serialPrint(ENABLE_SERIAL, INFO_MSG, "Connect to wifi....");
  /*while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    serialPrint(ENABLE_SERIAL, INFO_MSG, (String)timeOutCounter + "/10");
    timeOutCounter++;
    if(timeOutCounter > 10) break;
  }*/
  
  if(wifiConnect(10))  
  {
    //http.begin("http://blynk-cloud.com/eycylCuDXXMeJJao7T-piOd6hRWZ2WUr/project");
    
    http.begin("http://blynk-cloud.com/" + token + "/project");
    
    int httpCode = http.GET();
    if (httpCode > 0 )
    {
      String payload = http.getString();
      serialPrint(ENABLE_SERIAL, INFO_MSG, "Payload:");
      serialPrint(ENABLE_SERIAL, INFO_MSG, payload);
      if(payload.indexOf("name") >= 0)
      {
        serialPrint(ENABLE_SERIAL, INFO_MSG, "Token: (" + token + ") is valid");
        http.end();
        return 1;
      }
      else
      {
        serialPrint(ENABLE_SERIAL, INFO_MSG, "Token: (" + token + ") is not valid");
        http.end();
        return -99;
      }
    }
    else
    {
      serialPrint(ENABLE_SERIAL, INFO_MSG, "Error on HTTP request");
      http.end();
      return httpCode;
    }
  }
  else 
  {
    serialPrint(ENABLE_SERIAL, INFO_MSG, "No Wifi connection");
    return -100;
  }
}
void firstTimeSetUp(bool firstTime)
{
  if(firstTime)
  {
    //this is the first time set up
    //1. Welcome user (Hi I am KELCIE....)
    M5.Lcd.fillScreen(BACKGROUND_COLOR);
    M5.Lcd.setCursor(5,20);
    M5.Lcd.setFreeFont(SUBTITLE_FNT);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.println("Hello, my name is Kelcie!");
    M5.Lcd.println("");
    M5.Lcd.println("Lets start?");
    navigationButtons("", "", "GO", FTS_MENU_COLOR, FTS_MENU_TEXT_COLOR);
    while(1)if(M5.BtnC.read()) break;
    delay(DEBOUNCE_SCROLL_MENU*2);
    
    //2. Check for temperature sensor
    M5.Lcd.fillScreen(BACKGROUND_COLOR);
    M5.Lcd.setCursor(0,20);
    M5.Lcd.setFreeFont(SUBTITLE_FNT);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.println("Searching for temperature sensor...");
    M5.Lcd.println("");
    bool breakLoop = false;
    while(1)
    {
      searchTemperatureSensor(SEARCH_ATTEMPTS);
      //TODO: maybe store address?
      if(sensorAttached)
      {
        M5.Lcd.println("> Sensor found...");
        navigationButtons("", "", ">>>", FTS_MENU_COLOR, FTS_MENU_TEXT_COLOR);
        while(1)
        {
          if(M5.BtnC.read())
          { 
            breakLoop = true;
            break; 
          }
        }
      }
      else
      {
        M5.Lcd.println("> Sensor not found...");
        M5.Lcd.println("");
        M5.Lcd.println("Check again?");
        navigationButtons("Yes", "", "No", FTS_MENU_COLOR, FTS_MENU_TEXT_COLOR);
        while(1)
        {
          if(M5.BtnA.read()) break;
          if(M5.BtnC.read()) 
          {
            breakLoop = true;
            break;
          }
        }
      }
      if(breakLoop) break;
    }
    
     
    //3. Connect on wifi
    M5.Lcd.fillScreen(BACKGROUND_COLOR);
    M5.Lcd.setCursor(0,20);
    M5.Lcd.setFreeFont(SUBTITLE_FNT);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.println("Its time to connect with your wifi...");
    M5.Lcd.println("");
    M5.Lcd.println("Please select the configuration method");
    M5.Lcd.println("A. Smart config");
    M5.Lcd.println("B. Set wifi manually");
    M5.Lcd.println("C. Skip");
    navigationButtons("A", "B", "C", FTS_MENU_COLOR, FTS_MENU_TEXT_COLOR);
    unsigned int selection = 0;
    delay(DEBOUNCE_SCROLL_MENU*2);
    while(1)
    {
      if(M5.BtnA.read())
      {
        selection = 1;
        break;
      }
      if(M5.BtnB.read())
      {
        selection = 2;
        break;
      }
      if(M5.BtnC.read())
      {
        selection = 3;
        break;
      }
    }
    switch(selection)
    {
      case 1:
        smartConfig();
      break;
      case 2:
        setWifiManually();
      break;
      case 3:
      break;
      default:
      break;
    }
    //4. Setup Blynk
    M5.Lcd.fillScreen(BACKGROUND_COLOR);
    M5.Lcd.setCursor(0,20);
    M5.Lcd.setFreeFont(SUBTITLE_FNT);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.println("Let me speek with your phone...");
    M5.Lcd.println("");
    M5.Lcd.println("You need to download Blynk");
    M5.Lcd.println("application");
    M5.Lcd.println("");
    M5.Lcd.println("What smart phone do you have?");
    
    
    navigationButtons("iOs", "Android", "Skip", FTS_MENU_COLOR, FTS_MENU_TEXT_COLOR);
    delay(DEBOUNCE_SCROLL_MENU*2);
    selection = 0;
    while(1)
    {
      if(M5.BtnA.read())
      {
        selection = 1;
        break;
      }
      if(M5.BtnB.read())
      {
        selection = 2;
        break;
      }
      if(M5.BtnC.read())
      {
        selection = 3;
        break;
      }
    }
    M5.Lcd.fillScreen(BACKGROUND_COLOR);
    M5.Lcd.setCursor(0,20);
    M5.Lcd.setFreeFont(SUBTITLE_FNT);
    M5.Lcd.setTextColor(WHITE);
    delay(DEBOUNCE_SCROLL_MENU*2);
    
    switch(selection)
    {
      case 1:
        //QR code for iOs
        M5.Lcd.println("Scan the following QR code");
        M5.Lcd.println("and download the blynk app for iOS");
        M5.Lcd.println("Press any button to continue");
        M5.Lcd.qrcode("https://apps.apple.com/us/app/blynk-iot-for-arduino-esp32/id808760481",85,70,150,6);
      break;
      case 2:
        //QR code for Android
        M5.Lcd.println("Scan the following QR code");
        M5.Lcd.println("and download the blynk app for Android");
        M5.Lcd.println("Press any button to continue");
        M5.Lcd.qrcode("https://play.google.com/store/apps/details?id=cc.blynk&hl=en",85,70,150,6);
      break;
      case 3:
      break;
      default:
      break;
    }
    while(1)
    {
      if(M5.BtnA.read() or M5.BtnB.read() or M5.BtnC.read() || selection == 3) break;
    }
    //4a. Set blynk token
    M5.Lcd.fillScreen(BACKGROUND_COLOR);
    M5.Lcd.setCursor(0,20);
    M5.Lcd.setFreeFont(SUBTITLE_FNT);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.println("Give me the auth token");
    M5.Lcd.println("");
    M5.Lcd.println("In the following step, you should write the auth token from your blynk application");
    M5.Lcd.println("The token is 32 character word");

    M5.Lcd.println("Proceed?");

    navigationButtons("Yes", "", "Skip", FTS_MENU_COLOR, FTS_MENU_TEXT_COLOR);
    while(1)
    {
      if(M5.BtnA.read())
      {
        setAuthToken();
        break;
      }
      if(M5.BtnC.read()) break;
    }
    
    //5. Set up parameters
    M5.Lcd.fillScreen(BACKGROUND_COLOR);
    M5.Lcd.setCursor(0,20);
    M5.Lcd.setFreeFont(SUBTITLE_FNT);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.println("Final setup");
    M5.Lcd.println("Proceed?");
    delay(DEBOUNCE_SCROLL_MENU*2);

    navigationButtons("Yes", "", "Skip", FTS_MENU_COLOR, FTS_MENU_TEXT_COLOR);
    while(1)
    {
      if(M5.BtnA.read())
      {
        showSettings();
        break;
      }
      if(M5.BtnC.read()) break;
    }
    
    /*if((bool)EEPROM.read(EEPROM_FIRST_TIME_SETUP))
    {
      EEPROM.write(EEPROM_FIRST_TIME_SETUP, false);
      EEPROM.commit();
    }*/
    //update preferences
    preferences.begin(PR_NAMESPACE, false);             //false --> start preferenece in Read and write mode, if true --> start preferences in read only mode
    preferences.putBool(PR_FIRST_TIME_SETUP, false); 
    preferences.end();
    printMsg("Congratulations", "I am ready....", SUCCESS, 5000);
    ESP.restart();
    
  }
}

void checkForUpdates()
{
  //printMsg("Checking for updates", INFORMATION, 1000);
  M5.Lcd.fillScreen(BACKGROUND_INFORMATION_COLOR);
  M5.Lcd.setCursor(0,20);
  M5.Lcd.setFreeFont(SUBTITLE_FNT);
  M5.Lcd.setTextColor(WHITE);
  
  M5.Lcd.print("> Checking wifi connection...");
  //WiFi.begin();
  //int counter = 0;
  
  /*while (WiFi.status() != WL_CONNECTED) 
  {
    counter++;
    if(counter % 500 == 0) M5.Lcd.print(".");
    if(counter > (30*500)) break;
    delay(1);
  }*/
  if(wifiConnect(20))
  {
    M5.Lcd.println("");
    M5.Lcd.println("> Wifi connected!");
    M5.Lcd.println("> Checking for updates...");
    updatedNeeded = esp32FOTA.execHTTPcheck();
    if (updatedNeeded)
    {
      M5.Lcd.println("> Update found!");
      M5.Lcd.println("Proceed with the update?");
      navigationButtons("YES", "", "No", BLACK, WHITE);
      bool selection = false; //false --> no, true --> yes
      while(1)
      {
        if(M5.BtnC.read()) break;
        if(M5.BtnA.read())
        {
          selection = true;
          break;
        }
      }
      if(selection)
      {
        //printMsg("Updating...", "Things migh be quite for a while...", INFORMATION, 500);
        M5.Lcd.fillScreen(BACKGROUND_INFORMATION_COLOR);
        M5.Lcd.setCursor(0,20);
        M5.Lcd.setFreeFont(SUBTITLE_FNT);
        M5.Lcd.setTextColor(WHITE);
        esp32FOTA.execOTA();
      }
      else printMsg("Cancelling...", "", INFORMATION, 2000);
      
      
    }
    else
    {
        printMsg("No update", "Current version: "+(String)CURRENT_VERSION,  NO_SUCCESS, 5000);
        serialPrint(ENABLE_SERIAL, INFO_MSG, "No update available. Current version: "+(String)CURRENT_VERSION);
    }
  }    
  else printMsg("No wifi", "Connect to wifi and try again", NO_SUCCESS, 5000);
  
}

void menuActionSelected(int firstLevelMenu, int secondLevelMenu)
{
  serialPrint(ENABLE_SERIAL, INFO_MSG, "FIrst level: "+(String)firstLevelMenu);
  serialPrint(ENABLE_SERIAL, INFO_MSG, "Second Level Menu: " + (String)secondLevelMenu);

  delay(1000);
  /*First level
   * 0 --> Blynk
   * 1 --> WiFi
   * 2 --> Settings
   * 3 --> Other
   * 4 --> Exit
   * 
   * Second level:
   * 0.0 -->Read token from SD
   * 0.1 --> Set token 
   * 0.2 --> Check token validity
   * 0.3 --> Back
   * 1.0 --> Remove wifi credentials
   * 1.1 --> Smart configuration
   * 1.2 --> Set wifi manually
   * 1.3 --> Read credentials from file
   * 1.4 --> Back
   * 2.0 --> Modify variables
   * 2.1 --> Read variables from file
   * 2.2 --> Back
   * 3.0 --> Check for updates
   * 3.1 --> Reset Montlhy consumptions
   * 3.2 --> Reset to factory settings
   * 3.3 --> First time setup
   * 3.4 --> Reset overcurrent
   * 3.5 --> Back
   * 
   */
    int tokenCheckResult = 0;
    //String token = "eycylCuDXXMeJJao7T-piOd6hRWZ2WUr";
    switch(firstLevelMenu)
    {
      case 0:
        serialPrint(ENABLE_SERIAL, INFO_MSG, "Blynk menu selected");
        switch(secondLevelMenu)
        {
          case 0:
            //read token from SD
            serialPrint(ENABLE_SERIAL, INFO_MSG, "Read token from SD");
            printMsg("No function", "Coming in the following update", INFORMATION, 5000);
            
            //temporary test
            //localServer();
          break;
          case 1:
            //set token manually
            serialPrint(ENABLE_SERIAL, INFO_MSG, "Set token manually");
            setAuthToken();
          break;
          case 2:
            //check token validity
            serialPrint(ENABLE_SERIAL, INFO_MSG, "Check token validity");
            //int test = isBlynkTokenValid("tesT");
            M5.Lcd.fillScreen(BLACK);
            M5.Lcd.setFreeFont(SUBTITLE_FNT);
            M5.Lcd.setCursor(0,50);
            M5.Lcd.println("Validating token....");
            tokenCheckResult = 0;
            //token = EEPROM.readString(EEPROM_BLYNK_AUTH_START);
            //preferences.begin(PR_NAMESPACE, false);
            //tokenCheckResult = isBlynkTokenValid(EEPROM.readString(EEPROM_BLYNK_AUTH_START));
            tokenCheckResult = isBlynkTokenValid(blynkToken);
            //preferences.end();
            //tokenCheckResult = isBlynkTokenValid((String)auth);
            if(tokenCheckResult == 1) printMsg("Congratulations", "Token is valid", SUCCESS, 5000);
            else  printMsg("Token is NOT valid (" + (String)tokenCheckResult +")", blynkToken, NO_SUCCESS, 5000);
          case 3:
            //back
            serialPrint(ENABLE_SERIAL, INFO_MSG, "Go back");
          break;
          default:
          break;
            
        }
      break;

      case 1:
        serialPrint(ENABLE_SERIAL, INFO_MSG, "WiFi menu selected");
        switch(secondLevelMenu)
        {
          case 0:
            //Remove wifi credentials
            serialPrint(ENABLE_SERIAL, INFO_MSG, "Reseting wifi credentials");
            removeWifiCredentials();
          break;
          case 1:
            //Smart configuration
            serialPrint(ENABLE_SERIAL, INFO_MSG, "Smart config");
            smartConfig();
          break;
          case 2:
            //Set wifi manually
            serialPrint(ENABLE_SERIAL, INFO_MSG, "Set wifi manualy");
            setWifiManually();
          break;
          case 3:
            //Read credentials from file
            serialPrint(ENABLE_SERIAL, INFO_MSG, "Read credentials from SD");
            printMsg("No function", "Coming in the following update", INFORMATION, 5000);
          break;
          case 4:
            //back
            serialPrint(ENABLE_SERIAL, INFO_MSG, "Go Back");
          break;
          default:
          break;
            
        }
      break;

      case 2:
        serialPrint(ENABLE_SERIAL, INFO_MSG, "Settings menu selected");
        switch(secondLevelMenu)
        {
          case 0:
            //Modify variables
            serialPrint(ENABLE_SERIAL, INFO_MSG, "Modify variables");
            showSettings();
          break;
          case 1:
            //Read variables from file
            serialPrint(ENABLE_SERIAL, INFO_MSG, "Read variables from file");
            printMsg("No function", "Coming in the following update", INFORMATION, 5000);
          break;
          case 2:
            //back
            serialPrint(ENABLE_SERIAL, INFO_MSG, "Go back");
          break;
          default:
          break;
            
        }
      break;

      case 3:
        serialPrint(ENABLE_SERIAL, INFO_MSG, "Other");
        switch(secondLevelMenu)
        {
          case 0:
            //Check for updates
            serialPrint(ENABLE_SERIAL, INFO_MSG, "Check for updates");
            checkForUpdates();
          break;
          case 1:
            //Reset consumptions
            serialPrint(ENABLE_SERIAL, INFO_MSG, "Reset monthly consumptions");
            deleteMonthsInFlash();
            
          break;
          case 2:
            //Reset to factory settings
            resetToFactorySettings();
            serialPrint(ENABLE_SERIAL, INFO_MSG, "Reset to factory settings");
            printMsg("No function", "Coming in the following update", INFORMATION, 5000);
          break;
          case 3:
            firstTimeSetUp(true);
          break;
          /*case 4:
            //reset overcurrent detection (current sensor)
            serialPrint(ENABLE_SERIAL, INFO_MSG, "Reset overcurrent detection function");
            rstOverCurrentDetection();
          break;*/
          case 4:
            //Back
            serialPrint(ENABLE_SERIAL, INFO_MSG, "Go back");
          break;
          default:
          break;
            
        }
      break;

      default:
      break;
    }
   
}
/*void rstOverCurrentDetection()
{
  //reset
   digitalWrite(OCD_RESET, HIGH);
   delay(100);
   digitalWrite(OCD_RESET, LOW);
}*/
int printArray(String *myArray, String menuName, int arrayLength)
{
  //take as input an array and returns user's selection 
  M5.Lcd.fillScreen(BLACK);
  printHeader(menuName);
  int selected = 0;
  M5.Lcd.setFreeFont(SUBTITLE_FNT);
  M5.Lcd.setCursor(0,50);

 for(int i = 0;i < arrayLength;i++)
  {
    if(selected == i)
        {
          M5.Lcd.setTextColor(SELECTED_TXT);
          M5.Lcd.println((String)(i+1)+". " + myArray[i]);
        }
        else
        {
          M5.Lcd.setTextColor(NON_SELECTED_TXT);
          M5.Lcd.println((String)(i+1)+". " + myArray[i]);
        }
  }

  navigationButtons("<<<", "select", ">>>", BLACK, WHITE);

  //to prevent accidental selection
  delay(500);
  
  while(1)
  {    
    if(M5.BtnA.read() == 1 or M5.BtnB.read() == 1 or M5.BtnC.read() == 1)
    {
      if(M5.BtnC.read() == 1)
      {
        if(selected < (arrayLength-1))
          selected++;        
      }
      if(M5.BtnA.read() == 1)
      {
        if(selected > 0)
          selected--;
      }
      if(M5.BtnB.read() == 1)
      {
        //action
        //if(selected == arrayLength - 1) break;  //if the selection is the last element of array (usually "exit") then break while loop
        return selected;
       
      }
      serialPrint(ENABLE_SERIAL, INFO_MSG, "Selected: "+(String)selected);
      //draw the selection
      //drawSelectionConfigurationMenu(selected);
      //draw a black rectangle (to erase menu) and set cursor
      M5.Lcd.fillRect(0, 40, 320, 240, BLACK);
      M5.Lcd.setCursor(0,50);
      for(int i = 0;i < arrayLength;i++)
      {
        
        if(selected == i)
        {
          M5.Lcd.setTextColor(SELECTED_TXT);
          M5.Lcd.println((String)(i+1)+". " + myArray[i]);
          M5.Lcd.setTextColor(NON_SELECTED_TXT);
        }
        else
        {
          M5.Lcd.setTextColor(NON_SELECTED_TXT);
          M5.Lcd.println((String)(i+1)+". " + myArray[i]);
        }
      }
      //draw navigation buttons
      navigationButtons("<<<", "select", ">>>", BLACK, WHITE);
        
    }
    delay(DEBOUNCE_SCROLL_MENU);
  }
  
}


void showMainMenu()
{
  M5.Lcd.fillScreen(BLACK);
  printHeader("Main menu");
  String parentMenu[5] ={"Blynk","WiFi","Settings","Other","Exit"} ;
  String blynkMenu[4] = {"Read token from SD (N)","Set token", "Check Token validity", "Back"} ;
  String WiFiMenu[5] = {"Remove wifi credentials","Smart configuration","Set wifi Manualy", "Read credentials from file (N)", "Back"} ;
  String settingsMenu[3] = {"Modify variables","Read variables from file (N)","Back"} ;
  //String otherMenu[6] = {"Check for updates","Reset monthly Consumptions", "Reset to factory settings","First time setup", "Reset overcurrent", "Back"} ;
  String otherMenu[5] = {"Check for updates","Reset monthly Consumptions", "Reset to factory settings","First time setup", "Back"} ;
  M5.Lcd.setFreeFont(SUBTITLE_FNT);
  M5.Lcd.setCursor(0,50);

  int selected = 0;
  bool showChildMenu = false;

  int firstLevelMenu = 0;
  int secondLevelMenu = 0;
  
  for(int i = 0;i < (sizeof(parentMenu)/sizeof(parentMenu[0]));i++)
  {
    if(selected == i)
        {
          M5.Lcd.setTextColor(SELECTED_TXT);
          M5.Lcd.println((String)(i+1)+". " + parentMenu[i]);
        }
        else
        {
          M5.Lcd.setTextColor(NON_SELECTED_TXT);
          M5.Lcd.println((String)(i+1)+". " + parentMenu[i]);
        }
  }

  
  navigationButtons("<<<", "select", ">>>", BLACK, WHITE);

  //to prevent accidental selection
  delay(500);
  
  while(1)
  {
    firstLevelMenu = selected;
    
    if(showChildMenu)
    {
      switch(selected)
      {
        case 0:
          //showBlynkMenu();
          menuActionSelected(firstLevelMenu, printArray(blynkMenu, "Blynk", sizeof(blynkMenu)/sizeof(blynkMenu[0])));
        break;
        case 1:
          //showWifiMenu();
          menuActionSelected(firstLevelMenu, printArray(WiFiMenu, "WiFi", sizeof(WiFiMenu)/sizeof(WiFiMenu[0])));
        break;
        case 2:
          //showSettingsMenu();
          menuActionSelected(firstLevelMenu, printArray(settingsMenu, "Settings", sizeof(settingsMenu)/sizeof(settingsMenu[0])));
        break;
        case 3:
          menuActionSelected(firstLevelMenu, printArray(otherMenu, "Other", sizeof(otherMenu)/sizeof(otherMenu[0])));
          //showOtherMenu();
        break;
      }
       M5.Lcd.fillScreen(BLACK);
      printHeader("Main menu");
      M5.Lcd.setFreeFont(SUBTITLE_FNT);
      M5.Lcd.setCursor(0,50);
      for(int i = 0;i < (sizeof(parentMenu)/sizeof(parentMenu[0]));i++)
  {
    if(selected == i)
        {
          M5.Lcd.setTextColor(SELECTED_TXT);
          M5.Lcd.println((String)(i+1)+". " + parentMenu[i]);
        }
        else
        {
          M5.Lcd.setTextColor(NON_SELECTED_TXT);
          M5.Lcd.println((String)(i+1)+". " + parentMenu[i]);
        }
  }
      delay(DEBOUNCE_SCROLL_MENU);
      showChildMenu = false;
    }
    if(M5.BtnA.read() == 1 or M5.BtnB.read() == 1 or M5.BtnC.read() == 1)
    {
      if(M5.BtnC.read() == 1)
      {
        if(selected < ((sizeof(parentMenu)/sizeof(parentMenu[0]))-1))
          selected++;
        
      }
      if(M5.BtnA.read() == 1)
      {
        if(selected > 0)
          selected--;
      }
      if(M5.BtnB.read() == 1)
      {
        //action
        showChildMenu = true;
        if(selected == (sizeof(parentMenu)/sizeof(parentMenu[0]) - 1)) break;  //if the selection is the last element of array (usually "exit") then break while loop
       
      }
      serialPrint(ENABLE_SERIAL, INFO_MSG, "Selected: "+(String)selected);
      //draw the selection
      //drawSelectionConfigurationMenu(selected);
      //draw a black rectangle (to erase menu) and set cursor
      M5.Lcd.fillRect(0, 40, 320, 240, BLACK);
      M5.Lcd.setCursor(0,50);
      for(int i = 0;i < (sizeof(parentMenu)/sizeof(parentMenu[0]));i++)
      {
        
        if(selected == i)
        {
          M5.Lcd.setTextColor(SELECTED_TXT);
          M5.Lcd.println((String)(i+1)+". " + parentMenu[i]);
          M5.Lcd.setTextColor(NON_SELECTED_TXT);
        }
        else
        {
          M5.Lcd.setTextColor(NON_SELECTED_TXT);
          M5.Lcd.println((String)(i+1)+". " + parentMenu[i]);
        }
      }
      //draw navigation buttons
      navigationButtons("<<<", "select", ">>>", BLACK, WHITE);
        
    }
    delay(DEBOUNCE_SCROLL_MENU);
  }
}

void printMsg(String msg, String subMsg, int type, int delayms)
{
  switch(type)
  {
    case SUCCESS:
      M5.Lcd.fillScreen(BACKGROUND_SUCCESS_COLOR);
    break;
    case NO_SUCCESS:
      M5.Lcd.fillScreen(BACKGROUND_NO_SUCCESS_COLOR);
    break;
    case INFORMATION:
      M5.Lcd.fillScreen(BACKGROUND_INFORMATION_COLOR);
    break;
    default:
      M5.Lcd.fillScreen(BLACK);
    break;
  }
  M5.Lcd.setFreeFont(&OpenSans_Regular20pt7b);
  M5.Lcd.setTextColor(SUCCESS_TXT);
  M5.Lcd.setTextDatum(MC_DATUM);
  M5.Lcd.drawString(msg, 160, 100, 1);
  M5.Lcd.setFreeFont(SUBTITLE_FNT);
  M5.Lcd.drawString(subMsg, 160, 160, 1);
  delay(delayms);
}
  
String rssiToPercent(String rssi)
{
  //best -30dB --> 100%
  //worst -90db --> 0%
  return (String)(150+10*rssi.toInt()/6);
}

void printHeader(String str)
{
  //M5.Lcd.setTextDatum(TC_DATUM);
  //M5.Lcd.setTextSize(HEADER_FONT_SIZE); 
  M5.Lcd.setFreeFont(TITLE_FNT);
  //M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.fillRect(0, 0, 340,40,BLACK);
  M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
  //Serial.println("width: "+(String)M5.Lcd.width());
  M5.Lcd.setCursor((M5.Lcd.width()/2)-(int)((str.length()*12)/2), M5.Lcd.fontHeight());//20);//(M5.Lcd.width()/2)-(int)(str.length()/2));70
  M5.Lcd.println(str);
}

void navigationButtons(String btnA, String btnB, String btnC, uint16_t backgroundColor, uint16_t textColor)
{
   M5.Lcd.fillRect(0, 200, 340,40,backgroundColor);
   M5.Lcd.setTextColor(textColor);
   M5.Lcd.setCursor(45,230);
   M5.Lcd.print(btnA);
   M5.Lcd.setCursor(M5.Lcd.width()/2 - 20, 230);
   M5.Lcd.println(btnB);
   M5.Lcd.setCursor(M5.Lcd.width()-65, 230);
   M5.Lcd.println(btnC);
}
void showSettings()
{
  
  //All settings menu
  M5.Lcd.fillScreen(BLACK);
  printHeader("Settings");
  M5.Lcd.setFreeFont(SUBTITLE_FNT);

  //Actual Seetings
  const int arrayRows = 3;
  const unsigned int lineHeight = 30;
  String settingsMenu[arrayRows][2] = {{"Set point", (String)setPoint}, {"Timer", (String)maxHeaterActive}, {"Back", ""}};
  
  int counter=0;
  bool selected = false;
  int selection = 0;
  
  //1. Draw menu
  for(int i=0; i < arrayRows; i++)
  {
    if(i == counter)  M5.Lcd.setTextColor(SELECTED_TXT);
    else              M5.Lcd.setTextColor(NON_SELECTED_TXT);
    M5.Lcd.setCursor(10, 60+lineHeight*i);
    M5.Lcd.print(settingsMenu[i][0]);
    M5.Lcd.setCursor(200, 60+lineHeight*i);
    M5.Lcd.print(settingsMenu[i][1]);
  }
  
  navigationButtons("<<<", "select", ">>>", BLACK, WHITE);
  delay(DEBOUNCE_SCROLL_MENU*2); //to prevent accidental selection
  //2. endless loop for the menu
  while(1)
  {
    if(M5.BtnA.read() or M5.BtnB.read() or M5.BtnC.read())
    {      
        if(M5.BtnA.read() == true && counter > -1)
        {
          if(!selected) 
          {
            if(counter > 0) counter--;
          }
          else settingsMenu[counter][1] = (String)(settingsMenu[counter][1].toInt()-1);
        }
        if(M5.BtnC.read() == true && counter < arrayRows)
        {
          if(!selected) 
          {
            if(counter < arrayRows) counter++;
          }
          else settingsMenu[counter][1] = (String)(settingsMenu[counter][1].toInt()+1);
        }
          
      
      if(M5.BtnB.read() == true)
      {
        if(counter >= 2) //exit selected
          break;
        if(selected)
        {        
          //EEPROM.begin(EEPROM_SIZE);  
          //EEPROM.write(EEPROM_SETTINGS + counter * sizeof(int), settingsMenu[counter][1].toInt());
          //EEPROM.commit();

          preferences.begin(PR_NAMESPACE, false);
          switch(counter)
          {
            case 0:
              preferences.putUInt(PR_SETPOINT, settingsMenu[counter][1].toInt());
              
            break;
            case 1:
              preferences.putUInt(PR_MAX_TIMER, settingsMenu[counter][1].toInt());
            break;
            default:
            break;
          }
          preferences.end();
          serialPrint(ENABLE_SERIAL, INFO_MSG, "Value " + settingsMenu[counter][0] + "updated. New value: " + settingsMenu[counter][1]); 
          //Serial.println("Value: [" + settingsMenu[counter][1] + "] stored at address [" + (String)(EEPROM_SETTINGS + counter * sizeof(int))+"]");
        }
        //Serial.println("Button B pressed");
        selected = !selected;
        selection = counter;
      }

      for(int i = 0;i < arrayRows; i++)
      {
        if(i == counter)  M5.Lcd.setTextColor(SELECTED_TXT);
        else              M5.Lcd.setTextColor(NON_SELECTED_TXT);
        M5.Lcd.setCursor(10, 60+lineHeight*i);
        M5.Lcd.print(settingsMenu[i][0]);
        //needs to print first a black rectangle
        M5.Lcd.fillRect(200, 45+lineHeight*i, 40,20,BLACK);
        delay(5);
        M5.Lcd.setCursor(200, 60+lineHeight*i);
        M5.Lcd.print(settingsMenu[i][1]);
        if(selected && i == selection) M5.Lcd.drawFastHLine(200, 70+lineHeight*i, 20, WHITE);
        else M5.Lcd.drawFastHLine(200, 70+lineHeight*i, 20, BLACK);
      }
            
      if(!selected) navigationButtons("<<<", "select", ">>>", BLACK, WHITE);
      else         navigationButtons("-", "ok", "+", BLACK, WHITE);
                
    }
    delay(DEBOUNCE_SCROLL_MENU);
  }
}

void removeWifiCredentials()
{
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0,20);
  M5.Lcd.setFreeFont(TITLE_FNT);
  M5.Lcd.println("Disconnect Wifi");
  M5.Lcd.setFreeFont(SUBTITLE_FNT);
  M5.Lcd.println("Would you like to reset wifi credentials?");

  M5.Lcd.setCursor(50,230);
  M5.Lcd.print("Yes");
  M5.Lcd.setCursor(M5.Lcd.width()-70, 230);
  M5.Lcd.println("No");

  //to prevent accidental activation
  delay(1000);
  while(1)
  {
    if(M5.BtnA.read() == 1 or M5.BtnC.read() == 1)
    {
      if(M5.BtnA.read())
      {
        //remove wifi
        WiFi.mode(WIFI_STA);
        WiFi.disconnect(true,true);
        serialPrint(ENABLE_SERIAL, INFO_MSG, "Reseting wifi credentials");
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(80,120);
        M5.Lcd.setFreeFont(SUBTITLE_FNT);
        printMsg("Wifi disconnected", "", INFORMATION, 5000);
        break;
      }
      if(M5.BtnC.read())
      {
        break;
      }
    }
  }
}

void configureM5Keyboard()
{
  m5osk.useFACES = false;       // FACES unit support.
  m5osk.useCardKB = false;      // CardKB unit support.
  m5osk.useJoyStick = false;    // JoyStick unit support.
  m5osk.usePLUSEncoder = false; // PLUS Encoder unit support.
  m5osk.useFACESEncoder = false;// FACES Encoder unit support.
   // style change example.
    m5osk.fontColor[0] = 0x0000;        //font color of keyboard
    m5osk.fontColor[1] = 0xFFFF;        //font color of text
    m5osk.backColor[0] = BACKGROUND_COLOR;//0xF79E;    
    m5osk.backColor[1] = 0x8410;
    m5osk.frameColor[0]  = 0x4208;
    m5osk.frameColor[1]  = 0xFFFF;
    m5osk.textboxFontColor = 0xFFFF;
    m5osk.textboxBackColor = 0x8410;
  m5osk.keyHeight = 20;
  m5osk.setTextFont(2);

  
}


bool checkInternetConnectivity()
{
  return Ping.ping("www.google.com", 3);
}


void buttonBPressed()
{
  if(currentScreen != MAIN_SCREEN)  currentScreen = MAIN_SCREEN;
  else
  {
    if(idle_timer <= MAX_IDLE_TIME) buttonBPressedFlag = true;
    else  idle_timer = 0;
  }
}
void buttonAPressed()
{
  idle_timer = 0;
  //button A is always pressed on startup (BUG???)
  //currentScreen = DETAILS_SCREEN;
  
}
void buttonCPressed()
{
  idle_timer = 0;
  currentScreen = DETAILS_SCREEN;
}
void overCurrentDetected()
{
  //detected over current on heater
  overCurrentFault = true;
}

void deleteMonthsInFlash()
{
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0,20);
  M5.Lcd.println("Erase month consumption?");
  M5.Lcd.setCursor(50,230);
  M5.Lcd.print("YES");
  M5.Lcd.setCursor(M5.Lcd.width()-70, 230);
  M5.Lcd.println("NO");
  delay(2000);
  bool erase = false;
  
  while(1)
  {
    if(M5.BtnA.read())
    {
      erase = true;
      break;
    }
    if(M5.BtnC.read())
    {
      erase = false;
      break;
    }
  }
  if(erase)
  {
    /*int months = 0;
    while(months < 12)
    {
      EEPROM.write((EEPROM_MONTH_ADDR + (months)*sizeof(int)), 0);
      months++;
    }
    EEPROM.commit();*/
    preferences.begin(PR_NAMESPACE, false);     //false --> start preferenece in Read and write mode, if true --> start preferences in read only mode
    monthsConsumption[0] = preferences.getUInt(PR_JAN, 0);
    preferences.putUInt(PR_FEB, 0);
    preferences.putUInt(PR_MAR, 0);
    preferences.putUInt(PR_APR, 0);
    preferences.putUInt(PR_MAY, 0);
    preferences.putUInt(PR_JUN, 0);
    preferences.putUInt(PR_JUL, 0);
    preferences.putUInt(PR_AUG, 0);
    preferences.putUInt(PR_SEP, 0);
    preferences.putUInt(PR_OCT, 0);
    preferences.putUInt(PR_NOV, 0);
    preferences.putUInt(PR_DEC, 0);
  }
}

String userInputString(String menuName)
{
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0,50);
  M5.Lcd.println(menuName);
  //character array
  char UC_char[] = "AB";
  char LC_char[] = "ab";
  char specialCharacters[] = "-+=";
  
  while(1){}
}

void setWifiManually()
{
  M5.Lcd.fillScreen(BLACK);
  printHeader("Select your wifi's name");
  M5.Lcd.setFreeFont(SUBTITLE_FNT);
  M5.Lcd.println("");
  
  serialPrint(ENABLE_SERIAL, INFO_MSG, "Scanning all available SSIDs");
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  serialPrint(ENABLE_SERIAL, INFO_MSG, "Scan is done, found " +(String)n + "] available SSIDs");
  //TODO: inform user that you are scanning all wifis
  if(n > 0)
  {
    for (int i = 0; i < n; ++i) 
    {
            // Print SSID and RSSI for each network found
            if(i==0) M5.Lcd.setTextColor(SELECTED_TXT);
            else M5.Lcd.setTextColor(NON_SELECTED_TXT);    
            M5.Lcd.print(i + 1);
            M5.Lcd.print(": ");
            M5.Lcd.print(WiFi.SSID(i));
            M5.Lcd.print(" (");
            M5.Lcd.print(rssiToPercent((String)WiFi.RSSI(i))+"%");
            M5.Lcd.print(")");
            M5.Lcd.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
            if(n > MAX_SSID_LOAD) break;    //TODO: check this logic
        }
  }
  navigationButtons("<<<", "select", ">>>", BLACK, WHITE);
  //TODO: inform user if no ssids found
  

  int selected = 0;
  String ssid = "";
  while(1)
  {
    if(M5.BtnA.read() == 1 or M5.BtnB.read() == 1 or M5.BtnC.read() == 1)
    {
       if(M5.BtnC.read() == 1)
      {
        if(selected < (n-1))
          selected++;        
      }
      if(M5.BtnA.read() == 1)
      {
        if(selected > 0)
          selected--;
      }
      if(M5.BtnB.read() == 1) break;
    
      //draw a black rectangle (to erase menu) and set cursor
      M5.Lcd.fillRect(0, 30, 320, 240, BLACK);
      navigationButtons("<<<", "select", ">>>", BLACK, WHITE);
      M5.Lcd.setCursor(0,80);
      
      for(int i = 0;i < n;i++)
      {
        if(selected == i) M5.Lcd.setTextColor(SELECTED_TXT);
        else M5.Lcd.setTextColor(NON_SELECTED_TXT);
        M5.Lcd.println((String)(i+1) + ": "+(String)WiFi.SSID(i) + " (" + rssiToPercent((String)WiFi.RSSI(i))+"%" + ")");        
        //M5.Lcd.println(i+1 + ":" + WiFi.SSID(i) + " (" + rssiToPercent((String)WiFi.RSSI(i))+"%" + ")" + (WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
        if(n > MAX_SSID_LOAD) break;
      }      
      delay(DEBOUNCE_SCROLL_MENU);
  }
  }
  M5.Lcd.fillScreen(BLACK);
  //delay(1000);
  //write the password manually using virtual keaboard

  m5osk.setup();
  
  M5.Lcd.setCursor(0,20);
  M5.Lcd.println("SSID: "+WiFi.SSID(selected));
  while(1)
  {
    while (m5osk.loop()) 
    {
      // users writes the wifi password
      delay(1);
    }
  
    // Get input string.
    String text = m5osk.getString();
    m5osk.close();

    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(1,10);
    M5.Lcd.println("SSID: "+WiFi.SSID(selected));
    M5.Lcd.println("");
    M5.Lcd.println("Password: "+text);

    M5.Lcd.setCursor(1,120);
    M5.Lcd.println("Proceed?");
  
    /*M5.Lcd.drawString("Yes", 60, M5.Lcd.height()-M5.Lcd.fontHeight()-10);
    M5.Lcd.drawString("No", 250, M5.Lcd.height()-M5.Lcd.fontHeight()-10);*/
    navigationButtons("YES", "", "No", BLACK, WHITE);
    bool selection = false; //false --> no, true --> yes
    while(1)
    {
      if(M5.BtnC.read()) break;
      if(M5.BtnA.read())
      {
        selection = true;
        break;
      }
    }
    //ask user to verify password, if its correct proceed else restart function
    m5osk.setup(text);
    
    if(selection) 
    {
      WiFi.begin(WiFi.SSID(selected).c_str(), text.c_str());
      //int attempts, counter = 0;
      printMsg("Connecting...", "Wait a minute or two...", INFORMATION, 0);
      /*while (WiFi.status() != WL_CONNECTED) 
      {
        counter++;
        if(counter % 500 == 0)
        {
          serialPrint(ENABLE_SERIAL, INFO_MSG, "Connecting to WiFi...");
          attempts++;
        }
        if(attempts > 30) break;
        delay(1);
      }
      M5.Lcd.fillScreen(BLACK);
      */
      if(wifiConnect(15)) printMsg("Connected", WiFi.localIP().toString().c_str(), SUCCESS, 5000);
      else printMsg("Can't connect","Check credentials", NO_SUCCESS, 5000);
      break;
    }
    else
    {
      //modify password input
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0,20);
      M5.Lcd.println("SSID: "+WiFi.SSID(selected));
    }
  } 
  //TODO: write wifi
}

/*void drawConsumption()
{
  
}
*/
/*void clearUnusedMemory()
{
  //delete[] menu;
 //delete[] auth;
}*/
void initVariables()
{
  //1. Initiallize monthly consumption (read from eeprom)
  /*int months = 0;
  while(months < 12)
  {
    monthsConsumption[months] = (int)EEPROM.read((EEPROM_MONTH_ADDR + (months)*sizeof(int)));
    months++;
  }*/

  //2. Current sensor
  //reset on restart
  digitalWrite(OCD_RESET, HIGH);
  delay(100);
  digitalWrite(OCD_RESET, LOW);
  
}
void deactivateHeater()
{  
  digitalWrite(RLY,0);
  amperes = 0.0;
  
  currentIndex = 0;
  currentSamplingPeriod = 0;
  
  calculateConsumption(elapseMinutes);
  elapseMinutes = 0;
  heaterOnRequest = 0;
  Blynk.virtualWrite(V0, heaterOnRequest);
  drawDefaultScreen(currentScreen);
  heaterOnSeconds = 0;
  validReadingsAboveSP = 0;
  consecutiveAmperesReadingsBelowSP = 0;
}

void configureIO()
{
  pinMode(RLY, OUTPUT);                   //relay for heater
  pinMode(OCD_RESET, OUTPUT);             //over current reset
  pinMode(CURRENT_INPUT, INPUT);          //current measurement
  pinMode(OVC_FAULT, INPUT);              //set to LOW when overcurrent detected. 
}

void calculateConsumption( int minutes)
{
  //1. If year is changed then erase all previous months 
//  if(currentYear != year)
//  {
//    currentYear = year;
//    int months = 1;
//    while(months < 13)
//    {
//      EEPROM.write((EEPROM_MONTH_ADDR + (months - 1)*sizeof(int)), 0);
//      months++;
//    }
//    monthsConsumption[month] = 0;
//  }
  //2. add consumption of this month 
  monthsConsumption[month] = monthsConsumption[month] + minutes;
  preferences.begin(PR_NAMESPACE, false);     //false --> start preferenece in Read and write mode, if true --> start preferences in read only mode
  switch(month)
  {
    case 0:
      preferences.putUInt(PR_JAN, monthsConsumption[month]);
    break;
    case 1:
      preferences.putUInt(PR_FEB, monthsConsumption[month]);
    break;
    case 2:
      preferences.putUInt(PR_MAR, monthsConsumption[month]);
    break;
    case 3:
      preferences.putUInt(PR_APR, monthsConsumption[month]);
    break;
    case 4:
      preferences.putUInt(PR_MAY, monthsConsumption[month]);
    break;
    case 5:
      preferences.putUInt(PR_JUN, monthsConsumption[month]);
    break;
    case 6:
      preferences.putUInt(PR_JUL, monthsConsumption[month]);
    break;
    case 7:
      preferences.putUInt(PR_AUG, monthsConsumption[month]);
    break;
    case 8:
      preferences.putUInt(PR_SEP, monthsConsumption[month]);
    break;
    case 9:
      preferences.putUInt(PR_OCT, monthsConsumption[month]);
    break;
    case 10:
      preferences.putUInt(PR_NOV, monthsConsumption[month]);
    break;
    case 11:
      preferences.putUInt(PR_DEC, monthsConsumption[month]);
    break;
    default:
    break;
  }
  preferences.end();
  /*EEPROM.write((EEPROM_MONTH_ADDR + (monthsConsumption[month])*sizeof(int)), monthsConsumption[month]);
  EEPROM.commit();
  */
}

void handleBlynk()
{
  
  if(WiFi.status() == WL_CONNECTED)
  {
    if(!configurationDone)
    {  
      //configTime(7200, 3600, "pool.ntp.org"); 
      configTime(GMTOFFSET_SEC, DAYLIGHTOFFSET_SEC, NTP_SERVER); 

      if(isBlynkTokenValid((String)blynkToken) == 1)  blynkAuthTokenIsValid = true;   
      configurationDone = true;
    }
    if(internetConnectionAvailable)
    {
      millisBeforeBlynkRun = (int)millis();
      //if(blynkAuthTokenIsValid) Blynk.run();
      //TODO: if token is not valid bypass blynk.run()
      Blynk.run();      
      blynkRunTotalTime = (int)millis() - millisBeforeBlynkRun;
      
      if(blynkRunTotalTime > MAX_BLYNK_EXECUTION_TIME_MS)
      {
        //CHECK FOR INTERNET CONNECTIVITY
        internetConnectionAvailable = checkInternetConnectivity();
      }
    }
  }
  
}
void loopInTime()
{
  if(millis() - loopTimeMiliSecond > 1) loopTimeMiliSecond = millis();
  
  if(millis() - loopTimeMainClock > SECONDS)
  {
    //tick every second
    if(amperes > HEATER_ACTIVE_AMPS && !heaterOnRequest) heaterActivatedManually = true;
     else heaterActivatedManually = false;
    
    if(feedbackCounter < 10) feedbackCounter++;
    else  feedbackCounter = 0;
    
    if(idle_timer < MAX_IDLE_TIME+1)  idle_timer++;
    
    if(buttonDebounce > 0) buttonDebounce--;

    //TODO: check valid readings after temperature update
    if(digitalRead(RLY) == 1)
    {
      //deactivate heater after CONSECUTIVE_VALID_READINGS which temperature is still above SP
      if(validReadingsAboveSP < (CONSECUTIVE_VALID_READINGS))
      {
        if(currentTemperature > (int)setPoint)
          validReadingsAboveSP++;
        else
          validReadingsAboveSP = 0;
      }
      serialPrint(ENABLE_SERIAL, DEBUG_MSG, "Amperes: "+(String)amperes + " | Consecutive readings: " + (String)consecutiveAmperesReadingsBelowSP);
      if(abs(amperes) < MIN_AMPERES_FOR_BROKEN_HEATER)
      {
        if(consecutiveAmperesReadingsBelowSP < (CONSECUTIVE_LOW_AMPS_READINGS+1) ) consecutiveAmperesReadingsBelowSP++;
        if(consecutiveAmperesReadingsBelowSP > CONSECUTIVE_LOW_AMPS_READINGS)
          drawDefaultScreen(MAIN_SCREEN);   //if heater is broken the display will blinking every second to indicate the problem.
      }
      else consecutiveAmperesReadingsBelowSP = 0;
       
      /**********************************************/
      serialPrint(ENABLE_SERIAL, SECONDS_MSG, "Valid readings: "+(String)validReadingsAboveSP + "Current temperature[" + (String)currentTemperature + "], Set point[" + (String)setPoint + "]");
      //heater is active
      heaterOnSeconds++;
      if(heaterOnSeconds >= (maxHeaterActive*60) or validReadingsAboveSP >= CONSECUTIVE_VALID_READINGS) deactivateHeater();
      else{ if(digitalRead(RLY) == 0) digitalWrite(RLY, 1);}
    }
    /*******************************************/
    /*******************************************/

    /********* UPDATE_TEMPERATURE sencods ******/
    //update temperature
    updateTemperatureInTheLoop();
    
    /*******************************************/
    /*******************************************/


    /***************** CHECK_WIFI_CONNECTION seconds *******************/
    checkWifiInTheLoop();
    

    /***************** CHECK_WIFI_CONNECTION seconds *******************/
    loopTimeMinute++;
    if(loopTimeMinute >= EVERY_MINUTE)
    {
      //tick every EVERY_MINUTE x 1 seconds

      //UPDATE BLYNK set points every minute
      Blynk.virtualWrite(V2, setPoint);
      Blynk.virtualWrite(V3, maxHeaterActive);
      
      if(digitalRead(RLY) == 1)
        elapseMinutes++;
      loopTimeMinute = 0;

      if(!sensorAttached)
        searchTemperatureSensor(2);

      //TODO: check for updates every day not every minute
      if(minutesToCheckForUpdates > MINUTES_TO_CHECK_FOR_UPDATES )
      {
        updatedNeeded = esp32FOTA.execHTTPcheck();
        minutesToCheckForUpdates == 0;
      }
      else minutesToCheckForUpdates++;
    }
    
    loopTimeMainClock = millis();
    
  }
}
void updateTemperatureInTheLoop()
{
  loopTime++;
    if(loopTime >= UPDATE_TEMPERATURE)
    {
      //tick every UPDATE_1TEMPERATURE x 1 second
      serialPrint(ENABLE_SERIAL, SECONDS_MSG, "Every 5 seconds, Idle timer:" + (String)idle_timer);
      /*float currentTemp = analogRead(CURRENT_INPUT);
      serialPrint(ENABLE_SERIAL, SECONDS_MSG, "Current sensor voltage: [" + (String)(currentTemp*3.3/4095) +" V] - Raw reading:" + currentTemp);*/
      serialPrint(ENABLE_SERIAL, SECONDS_MSG, "Current:" + (String)amperes);
      currentTemperature = externalTemperature();
      Blynk.virtualWrite(V1, currentTemperature);
      
      
      
      //Blynk.virtualWrite(V1, (int)((temprature_sens_read() - 32) / 1.8));

      //if system detected heater error (low ampere) do not update the screen because its been updated every second (blinking)
      if(consecutiveAmperesReadingsBelowSP < (CONSECUTIVE_LOW_AMPS_READINGS+1))
        drawDefaultScreen(currentScreen);
     
      loopTime = 0;
    }
}

void checkWifiInTheLoop()
{
  loopTimeWiFi++;
    if(loopTimeWiFi >= CHECK_WIFI)
    {
      
      
      //tick every CHECK_WIFI_CONNECTION x 1 seconds
      serialPrint(ENABLE_SERIAL, INFO_MSG, "Check for wifi connection");
      if(!Blynk.connected())
      {
        if(WiFi.status() != WL_CONNECTED)
        {
          serialPrint(ENABLE_SERIAL, INFO_MSG, "******** WIFI not connected  **************");
          WiFi.begin();
        }
        else
        {
          serialPrint(ENABLE_SERIAL, INFO_MSG, "Blynk Reconnecting ... ");
          //Blynk.connect();
          internetConnectionAvailable = checkInternetConnectivity();
        }
           
      }
      else
      {
        serialPrint(ENABLE_SERIAL, INFO_MSG, "Obtained IP Address: "+(String)WiFi.localIP().toString());
      }
      loopTimeWiFi = 0;
    }
}

void handleButtons()
{
  //check button B
  if((M5.BtnB.pressedFor(BUTTON_PRESSED_FOR) && buttonDebounce == 0))
  {
    buttonDebounce = 5;
    serialPrint(ENABLE_SERIAL, INFO_MSG, "Button B pressed");    
    heaterOnRequest = !heaterOnRequest;
    if(Blynk.connected()) Blynk.virtualWrite(V0, heaterOnRequest);
    if(heaterOnRequest)
      digitalWrite(RLY, true);
    else
      deactivateHeater();
    drawDefaultScreen(currentScreen);
  }
  if(M5.BtnA.pressedFor(BUTTON_PRESSED_FOR) && M5.BtnC.pressedFor(BUTTON_PRESSED_FOR))
  {
    serialPrint(ENABLE_SERIAL, INFO_MSG, "Starting Menu");
  }
  /*if(M5.BtnC.read() == true)
  {
    serialPrint(ENABLE_SERIAL, INFO_MSG, "Disconnect wifi");  
    WiFi.disconnect();
    ESP.restart();
  }*/
  
}
void drawTime()
{
  String currentTime = "";
  imgSprite.setTextSize(HEADER_FONT_SIZE);
  imgSprite.setFreeFont(&FreeSerif9pt7b); 
  if(configurationDone)
  {
    currentTime = printLocalTime();
//    if(!monthsUpdatedFromEEPROM)
//    {
//      //this will run when "Time" is read (because kelcie needs to knwo which month is)
//      monthsConsumption[month] = (int)EEPROM.read(EEPROM_MONTH_ADDR+(month-1)*sizeof(int));
//      serialPrint(ENABLE_SERIAL, INFO_MSG, "Address to store:"+(String)(EEPROM_MONTH_ADDR+(month-1)*sizeof(int))+" - Consumption: "+(String)monthsConsumption[month]+ "Month:"+(String)month);
//      monthsUpdatedFromEEPROM = true;
//    }
  

  currentTime += " - " + (String)((monthsConsumption[month]*HEATER_KW/60)*KWH_COST)+" euro";
  currentTime += " T:" + (String)blynkRunTotalTime;
  if(updatedNeeded) currentTime += " U:1";
  else              currentTime += " U:0";
  currentTime += " I:"+(String)(amperes);
  if(overCurrentFault) currentTime += " OCD:1";
  else                 currentTime += " OCD:0";
  
  
  //currentTime += "(CPU:"+(String)((temprature_sens_read() - 32) / 1.8)+")";
  imgSprite.setTextSize(HEADER_FONT_SIZE); 
  //imgSprite.setTextDatum(TL_DATUM);
  imgSprite.drawString(currentTime, 0, 15,2);
  }
}

String printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    serialPrint(ENABLE_SERIAL, INFO_MSG, "Failed to obtain time");
    return NO_TIME;
  }

//  int tm_sec;         /* seconds,  range 0 to 59          */
//   int tm_min;         /* minutes, range 0 to 59           */
//   int tm_hour;        /* hours, range 0 to 23             */
//   int tm_mday;        /* day of the month, range 1 to 31  */
//   int tm_mon;         /* month, range 0 to 11             */
//   int tm_year;        /* The number of years since 1900   */
//   int tm_wday;        /* day of the week, range 0 to 6    */
//   int tm_yday;        /* day in the year, range 0 to 365  */
//   int tm_isdst;       /* daylight saving time             */

  year = timeinfo.tm_year;
  month = timeinfo.tm_mon;
  
  int hours = timeinfo.tm_hour;
  int minutes = timeinfo.tm_min;
  int seconds = timeinfo.tm_sec;

  String localTime = "";
  if(hours < 10 )
    localTime = "0"+(String)hours;
  else
    localTime = (String)hours;
  localTime += ":";
  if(minutes < 10)
    localTime += "0"+(String)minutes;
  else
    localTime += (String)minutes;
  localTime += ":";
  if(seconds < 10)
    localTime += "0"+(String)seconds;
  else
    localTime += (String)seconds;

  return localTime;
    
  //return ((String)timeinfo.tm_hour+":"+(String)timeinfo.tm_min+":"+(String)timeinfo.tm_sec);
}
 
String readFile(fs::FS &fs, const char * path) 
{
    //Reading file
    File file = fs.open(path);
    if(!file)        
        return ""; //Failed to open file for reading
    String str;
    //Read from file
    while(file.available())
    {
        int ch = file.read();
        str += String((char)ch);
    }
    return str;
}

int writeFile(fs::FS &fs, const char * path, String message)//const char * message)
{
    //Writing file
    File file = fs.open(path, FILE_WRITE);
    if(!file)      
        return -1;//Failed to open file for writing
    if(file.print(message))      
      return 1; //file written
    else
      return -1; //write failed
}


void setAuthToken()
{
  delay(DEBOUNCE_SCROLL_MENU);
  String token = "";  
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0,20);
  M5.Lcd.setFreeFont(TITLE_FNT);
  M5.Lcd.println("Auth Token");
  M5.Lcd.setFreeFont(SUBTITLE_FNT);
  M5.Lcd.println("You will find this unique 32 characters");
  M5.Lcd.println("in Blynk App.");
  M5.Lcd.println("By entering this text you are connecting");
  M5.Lcd.println("your smart phone with Kelcie!");
  M5.Lcd.println("");
  M5.Lcd.println("Select input method:");
  
  navigationButtons("web", "", "kelcie", BLACK, WHITE);
  bool inputMethod = true;
  bool selection = false; //false --> no, true --> yes
  
  //inputMethod --> true (WEB)
  //inputMethod --> false (M5 keyboard)  
  while(1)
  {
    if(M5.BtnC.read()) 
    {
      inputMethod = false; //user selected M5 keyboard
      break;
    }
    if(M5.BtnA.read()) break;   //input method is by default true;    
  }
  M5.Lcd.fillScreen(BLACK);
  if(!firstTimeSetupFlag) 
  {
    preferences.begin(PR_NAMESPACE, false);     //false --> start preferenece in Read and write mode, if true --> start preferences in read only mode
    token = preferences.getString(PR_BLYNK_TOKEN, "");
    preferences.end();
  }
  delay(DEBOUNCE_SCROLL_MENU*2);
  while(1)
  {
    //if user selectes WEB input start server otherwise start M5 Keyboard
    if(inputMethod) 
    {
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(1,20);
      M5.Lcd.println("You selected the WEB input method");
      M5.Lcd.println("I will try now to connect to your");
      M5.Lcd.println("local network");
      
      /*int counter = 0;
      if(WiFi.status() != WL_CONNECTED) WiFi.begin();
      while(WiFi.status() != WL_CONNECTED)
      {  
        serialPrint(ENABLE_SERIAL, INFO_MSG, (String)counter + "  - Connecting");
        delay(1000);
        counter++;
        M5.Lcd.print(".");
        if(counter > 20 ) break;
      }*/
      serialPrint(ENABLE_SERIAL, INFO_MSG, "Connecting on local wifi...");
      if(!wifiConnect(20))
      {
        Serial.println("Cant connect");
        printMsg("No wifi connection", "You have to be connected on local network", NO_SUCCESS, 5000);
        ESP.restart();
      }
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(1,10);
      M5.Lcd.println("Please open a browser and write this url: http://"+ WiFi.localIP().toString() + "/");
      M5.Lcd.println("Enter the Blynk TOKEN and press 'Send to kelcie'");
      M5.Lcd.qrcode("http://" + WiFi.localIP().toString()+"/get",85,70,150,6);
      
      //Check should be done in website
      //token = localServer(token);
      setupAsynchServer();
      tokenSubmittedFlag = false;
      Serial.println("Before while");
      while(1) if(tokenSubmittedFlag or M5.BtnA.read()) break;
      Serial.println("After while");
      //ToDo: button to cancell
      token = blynkTemporaryToken;
      
    }
    else
    {
      m5osk.fontColor[0] = 0x0000; //to xromo to grammaton sto keyboard
      m5osk.fontColor[1] = 0x0000; //to xroma tou epilegmenou grammatos
      m5osk.backColor[0] = 0xE71B; //to background xroma ton grammaton 
      m5osk.backColor[1] = 0x42D8; //to bacgkroun xroma tou epilegmenou grammatos
      m5osk.frameColor[0]  = 0x0000; // i grammes pou xorizoun to keyboard
      m5osk.frameColor[1]  = 0x0000; //to xroma tou tetragonoy poy epilegei to gramma
      m5osk.textboxFontColor = 0xFFFF; //to font xroma auton pou grafeis
      m5osk.textboxBackColor = 0x0000;  //to background tou text box
      m5osk.keyHeight = 20;
      m5osk.setTextFont(2);
    
      m5osk.setTextFont(2);
      m5osk.keyHeight = 40;
      m5osk.setFreeFont(&FreeMono9pt7b);
      m5osk.setFreeFont(&FreeSans9pt7b);
      m5osk.setup(token);
    
      M5ButtonDrawer::fontColor[0] = 0xFFFF;
      M5ButtonDrawer::fontColor[1] = 0x0000;
      M5ButtonDrawer::backColor[0] = 0x0010;
      M5ButtonDrawer::backColor[1] = 0xF79E;
      M5ButtonDrawer::width = 100;
      M5ButtonDrawer::height = 20;
      M5ButtonDrawer::setTextFont(2);  
      while (m5osk.loop()) 
      {
        // users writes the auth token      
      }
    
      // Get input string.
      token = m5osk.getString();
      m5osk.close();
    }
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(1,10);
    M5.Lcd.println("The auth token you have entered is:");
    M5.Lcd.println("");
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.println(token);
    M5.Lcd.setTextColor(WHITE);
    Serial.println("Fucking token is:" + token);
    M5.Lcd.println("");
    M5.Lcd.println("Checking auth token.... Please wait");
    int tokenCheckResult = isBlynkTokenValid(token);
    if(tokenCheckResult != 1)
    {
      M5.Lcd.setTextColor(RED);
      M5.Lcd.println("The auth token is not valid (" + (String)tokenCheckResult + ")");
      M5.Lcd.println("please select either 'retry' or 'new'");
      M5.Lcd.println("");
      M5.Lcd.setTextColor(WHITE);
    }
    else 
    {
      M5.Lcd.println("Congratulations, the token you entered is valid");
      M5.Lcd.println("Proceed?");
    }
    
    navigationButtons("Yes", "Retry", "New", BLACK, WHITE);
    while(1)
    {
      if(M5.BtnA.read())
      {
        //YES
        if(token.length() == BLYNK_AUTH_TOKEN_LEN)
        {
          selection = true;
          break;
        }
      }
      //cancel
      if(M5.BtnB.read())
        break;
      if(M5.BtnC.read())
      {
        //NO
        token = "";
        break;
      }

    }
    //ask user to verify token, if its correct proceed else restart function
    m5osk.setup(token);
    if(selection) break;
    else
    {
      //modify password input
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0,20);
      M5.Lcd.println("Write your auth token (from Blynk application)");
    }
  }

  if(selection)
  {
     //save the token
      //TODO: save the token into EEPROM memory or SD
      /*if(writeFile(SD, FILE_TOKEN_PATH, token) > 0)
        serialPrint(ENABLE_SERIAL, INFO_MSG, "Token: ["+token+"] was written in file token.txt");
      else
        serialPrint(ENABLE_SERIAL, INFO_MSG, "Token: ["+token+"] was NOT written in file token.txt");
        */
      //TODO: ask user where to store the value (EEPROM, ssd, both)
     /* Serial.println("Writing into EEPROM: "+token+" starting from address:"+ (String)EEPROM_BLYNK_AUTH_START);
      EEPROM.writeString(EEPROM_BLYNK_AUTH_START, token);
      EEPROM.writeString(EEPROM_BLYNK_AUTH_START+token.length(), '\0');
      EEPROM.commit();
      Serial.println("TOKEN from eeprom: " + EEPROM.readString(EEPROM_BLYNK_AUTH_START));
      */
      preferences.begin(PR_NAMESPACE, false);     //false --> start preferenece in Read and write mode, if true --> start preferences in read only mode
      Serial.println("Writing into flash memory the auth token: "+token);
      preferences.putString(PR_BLYNK_TOKEN, token);  
      preferences.end();
      delay(2000);
  }
  ESP.restart();
}
//void showConfigurationMenu()
//{
//  //TODO: modify menu
//  /*1. Blynk
//    |
//    |-Read token from SD
//    |-Set token
//    |-Check token validity
//    |-Back
//  2. WiFi
//    |
//    |-Remove wifi credentials
//    |-Smart configuration
//    |-Set wifi Manualy
//    |-Read credentials from file
//    |-Back
//  3. Settings
//    |
//    |-Modify variables
//    |-Read variables from file
//    |-Back
//  4. Other
//    |
//    |-Check for Updates
//    |-Reset monthly consumption
//    |-Reset to factory settings
//    |-First time setup
//    |-Back
//  */
//  //user request requested configuration menu
//  //print header
//  M5.Lcd.fillScreen(TFT_BLACK);
//  printHeader("Configuration");
//    
//  M5.Lcd.setFreeFont(SUBTITLE_FNT);
//  M5.Lcd.setCursor(0,50);
//
//  int selected = 0;
//  for(int i = 0;i < (sizeof(menu)/sizeof(menu[0]));i++)
//  {
//    if(selected == i)
//        {
//          M5.Lcd.setTextColor(SELECTED_TXT);
//          M5.Lcd.println((String)(i+1)+". " + menu[i]);
//        }
//        else
//        {
//          M5.Lcd.setTextColor(NON_SELECTED_TXT);
//          M5.Lcd.println((String)(i+1)+". " + menu[i]);
//        }
//  }
//
//  
//  navigationButtons("<<<", "select", ">>>", BLACK, WHITE);
//
//  //to prevent accidental selection
//  delay(500);
//  
//  while(1)
//  {
//    if(M5.BtnA.read() == 1 or M5.BtnB.read() == 1 or M5.BtnC.read() == 1)
//    {
//      if(M5.BtnC.read() == 1)
//      {
//        if(selected < ((sizeof(menu)/sizeof(menu[0]))-1))
//          selected++;
//        
//      }
//      if(M5.BtnA.read() == 1)
//      {
//        if(selected > 0)
//          selected--;
//      }
//      if(M5.BtnB.read() == 1)
//      {
//        //action
//        switch(selected)
//        {
//          case 0:
//            setAuthToken();
//           break;
//          case 1:
//            removeWifiCredentials();
//            break;
//          case 2:
//            smartConfig();
//            break;
//          case 3:
//            //set wifi
//            setWifiManually();
//            break;
//          case 4:
//            deleteMonthsInFlash();
//            break;
//          case 5:
//            showSettings();
//            break;
//          case 6:
//            ESP.restart();
//            break;
//          default:
//            break;
//        }
//        break;  //break while loop
//       
//      }
//      Serial.println("Selected: "+(String)selected);
//      //draw the selection
//      //drawSelectionConfigurationMenu(selected);
//      //draw a black rectangle (to erase menu) and set cursor
//      M5.Lcd.fillRect(0, 40, 320, 240, BLACK);
//      M5.Lcd.setCursor(0,50);
//      for(int i = 0;i < (sizeof(menu)/sizeof(menu[0]));i++)
//      {
//        
//        if(selected == i)
//        {
//          M5.Lcd.setTextColor(SELECTED_TXT);
//          M5.Lcd.println((String)(i+1)+". " + menu[i]);
//          M5.Lcd.setTextColor(NON_SELECTED_TXT);
//        }
//        else
//        {
//          M5.Lcd.setTextColor(NON_SELECTED_TXT);
//          M5.Lcd.println((String)(i+1)+". " + menu[i]);
//        }
//      }
//      //draw navigation buttons
//      navigationButtons("<<<", "select", ">>>", BLACK, WHITE);
//        
//    }
//    delay(DEBOUNCE_SCROLL_MENU);
//  }
//  
//  
//}

bool configurationMenu()
{
  //ask user to press any button to enter the configuration menu
  imgSprite.setTextSize(HEADER_FONT_SIZE); 
  imgSprite.setTextDatum(TL_DATUM);
  imgSprite.drawString("Press any button to enter configuration menu", 0, 0, 1);
  imgSprite.pushSprite(0, 0);
  int counter = 0;
  int seconds = 0;
  bool flag = false;
  while(1)
  {
    //loop for X seconds or until user press a button
    if(counter == 1000)
    {
      seconds++;
      imgSprite.drawString("Press button A to enter configuration menu", 0, 0, 1);
      imgSprite.drawString("Seconds: "+(String)seconds+"/5", 0, 40, 1);
      imgSprite.pushSprite(0, 0);
      counter = 0;
    }
    
    counter++;
    delay(1);
    
    if(seconds >= 5)
    {
      flag = false;
      break;
    }
    if(M5.BtnA.read())
    {
      flag = true;
      break;
    }
  }
  return flag;
}

void drawButtonsNavigation()
{
    imgSprite.drawRect(137,233,50,5,TFT_WHITE);
    imgSprite.fillRect(137,233,50,5,TFT_WHITE);

    imgSprite.drawRect(240,233,50,5,TFT_WHITE);
    imgSprite.fillRect(240,233,50,5,TFT_WHITE);
    
    imgSprite.drawRect(25,233,50,5,TFT_WHITE);
    imgSprite.fillRect(25,233,50,5,TFT_WHITE);
  
    
}

void drawCirclePoints(int r, int minutesPassed)
{
  int circle = 360; //degrees
  float angle = 0;
  if(maxHeaterActive != 0) angle = circle / maxHeaterActive;
  //int angle = circle / points;
  int x = 0;
  int y = 0;
  int width = M5.Lcd.width()/2;
  int height = M5.Lcd.height()/2 + 10;

  /*serialPrint(ENABLE_SERIAL, INFO_MSG, "Angle: "+(String)angle);
  serialPrint(ENABLE_SERIAL, INFO_MSG, "Points: "+(String)maxHeaterActive);*/
  for(int i=0;i<maxHeaterActive;i++)
  {
    //x[i] = r*cos(angle*i);
    //y[i] = r*sin(angle*i);
    x = width + r*cos(angle*i*1000/57296);
    y = height + r*sin(angle*i*1000/57296);

    serialPrint(ENABLE_SERIAL, INFO_MSG, (String)(angle*i*1000/57296)+","+(String)(angle*i*1000/57296));
    //serialPrint(ENABLE_SERIAL, INFO_MSG, "POINT("+(String)i+"):["+(String)x + ","+(String)y+"]");

    imgSprite.drawCircle(x, y, WAIT_CIRCLES_RADIUS, TFT_WHITE);
    if(i<minutesPassed)
    {
      imgSprite.fillCircle(x, y, WAIT_CIRCLES_RADIUS, 0xF180);
    }
  }

  //imgSprite.pushSprite(0, 0);

}

void drawSignalCircles(long rssi)
{
  int circles;
  int circlesColor = TFT_WHITE;
  //wifiSignal = (int)rssi;
  //serialPrint(ENABLE_SERIAL, INFO_MSG, "Draw signal circles [RSSI:"+(String)rssi+"]");  
  if (rssi >= -30)
  {
    circles = 4;
  }
  else if (rssi > -69 && rssi < -30)
  {
    circles = 3;
  } else if (rssi > -83 && rssi < -69)
  {
    circles = 2;
  } else if (rssi > -96 && rssi < -83)
  {
    circles = 1;
  } else if (rssi < -96)
  {
    circles = 0;
  }
  if(!internetConnectionAvailable)
  {
    //if no internet is available then paint circles red
    circlesColor = TFT_RED;
  }
  for (int i = 0; i <= 3; i++)
  {
    //display.drawCircle(100 + i * 6, 2, 2, GxEPD_BLACK);
    imgSprite.drawCircle((M5.Lcd.width() - (7*WIFI_CIRCLE_RADIUS + 4 * WIFI_CIRCLE_PADDING) + i * 12), WIFI_CIRCLE_RADIUS+3, WIFI_CIRCLE_RADIUS, circlesColor);
    //serialPrint(ENABLE_SERIAL, INFO_MSG, "X:" + (String)(M5.Lcd.width() - (4*WIFI_CIRCLE_RADIUS + 3 * WIFI_CIRCLE_PADDING) + i * 6));  
    if (i < circles)
    {
      //display.fillCircle(100 + i * 6, 2, 1, GxEPD_BLACK);
      imgSprite.fillCircle((M5.Lcd.width() - (7*WIFI_CIRCLE_RADIUS + 4 * WIFI_CIRCLE_PADDING) + i * 12), WIFI_CIRCLE_RADIUS+3, WIFI_CIRCLE_RADIUS-1, circlesColor);
    }
  }
}

void drawWiFiSignal()
{
  if (WiFi.status() == WL_CONNECTED) 
  {
      drawSignalCircles(WiFi.RSSI());
  }
  else
  {
    //imgSprite.setTextDatum(BL_DATUM);
    imgSprite.setTextSize(HEADER_FONT_SIZE);
    imgSprite.setCursor(320-imgSprite.textWidth(NO_SIGNAL_TXT), imgSprite.fontHeight());
    //imgSprite.drawString(NO_SIGNAL_TXT, SPRITE_WIDTH, SPRITE_HEIGHT);
    imgSprite.print(NO_SIGNAL_TXT);
    
  }
}

void drawDefaultScreen(int screenID)
{
  if(screenID == DETAILS_SCREEN)
  {
    serialPrint(ENABLE_SERIAL, INFO_MSG, "Screen selected: " + (String)DETAILS_SCREEN);
    M5.Lcd.fillScreen(DETAILS_SCREEN_COLOR);
    M5.Lcd.setTextSize(HEADER_FONT_SIZE); 
    M5.Lcd.setFreeFont(FS9);
    M5.Lcd.setTextColor(DETAILS_SCREEN_TXT);
    M5.Lcd.setCursor(0,15);
    /*M5.Lcd.println("Version________________: " + (String)CURRENT_VERSION);
    M5.Lcd.println("Nov: " + (String)((monthsConsumption[0]*HEATER_KW/60)*KWH_COST) + " - Feb: " + (String)((monthsConsumption[1]*HEATER_KW/60)*KWH_COST) + " - Mar: " + (String)((monthsConsumption[2]*HEATER_KW/60)*KWH_COST));
      M5.Lcd.println("Apr: " + (String)((monthsConsumption[3]*HEATER_KW/60)*KWH_COST) + " - May: " + (String)((monthsConsumption[4]*HEATER_KW/60)*KWH_COST) + " - Jun: " + (String)((monthsConsumption[5]*HEATER_KW/60)*KWH_COST));
      M5.Lcd.println("Jul: " + (String)((monthsConsumption[6]*HEATER_KW/60)*KWH_COST) + " - Aug: " + (String)((monthsConsumption[7]*HEATER_KW/60)*KWH_COST) + " - Sep: " + (String)((monthsConsumption[8]*HEATER_KW/60)*KWH_COST));
      M5.Lcd.println("Oct: " + (String)((monthsConsumption[9]*HEATER_KW/60)*KWH_COST) + " - Nov: " + (String)((monthsConsumption[10]*HEATER_KW/60)*KWH_COST) + " - Dec: " + (String)((monthsConsumption[11]*HEATER_KW/60)*KWH_COST));
      M5.Lcd.setTextColor(GREEN);
      M5.Lcd.println(">" + msg1);
      M5.Lcd.println(">" + msg2);
      M5.Lcd.println("> Ampers samples: ");
      for(int i=0;i< ((sizeof(currentSampling)/sizeof(currentSampling[0])));i++)
        M5.Lcd.print((String)currentSampling[i] + "-");
    */
    
    M5.Lcd.println(printLocalTime() + " | V" +(String)CURRENT_VERSION + ".0");
    M5.Lcd.print("SSID: " + WiFi.SSID() + "(" + WiFi.RSSI() + "dB) | ");
    if(WiFi.status() == WL_CONNECTED)
    {
      M5.Lcd.setTextColor(GREEN);
      M5.Lcd.println("Connected");
    }
    else
    {
      M5.Lcd.setTextColor(DETAILS_SCREEN_TXT);
      M5.Lcd.println("Disconnected");
    }
    
    if(digitalRead(RLY))
    {
      M5.Lcd.setTextColor(GREEN);
      M5.Lcd.print("Heater:ON");
    }
    else
    {
      M5.Lcd.setTextColor(DETAILS_SCREEN_TXT);
      M5.Lcd.print("Heater:off");
    }
    M5.Lcd.setTextColor(DETAILS_SCREEN_TXT);
    M5.Lcd.print(" | ");
    if(currentTemperature >= setPoint)
    {
      M5.Lcd.setTextColor(GREEN);
      M5.Lcd.print((String)currentTemperature);
      M5.Lcd.print("/"+(String)setPoint);
    }
    else
    {
      M5.Lcd.setTextColor(DETAILS_SCREEN_TXT);
      M5.Lcd.print((String)currentTemperature);
      M5.Lcd.print("/"+(String)setPoint);
    }
    M5.Lcd.setTextColor(DETAILS_SCREEN_TXT);
    M5.Lcd.print(" | ");

    if(sensorAttached)
    {
      M5.Lcd.setTextColor(GREEN);
      M5.Lcd.println("Sensor:Yes");
    }
    else
    {
      M5.Lcd.setTextColor(DETAILS_SCREEN_TXT);
      M5.Lcd.println("Sensor:No");
    }

    if(blynkAuthTokenIsValid)
    {
      M5.Lcd.setTextColor(GREEN);
      M5.Lcd.println("Token:valid");
    }
    else
    {
      M5.Lcd.setTextColor(DETAILS_SCREEN_TXT);
      M5.Lcd.println("Token:Not valid");
    }
    
    M5.Lcd.setTextColor(DETAILS_SCREEN_TXT);

    M5.Lcd.println("Amps: " + (String)amperes + " | " + (String)((monthsConsumption[month] * HEATER_KW / 60)*KWH_COST) + " euro");
    M5.Lcd.println("Heater: " + (String)HEATER_KW + "KW" + " | " + "KWh cost: " + KWH_COST + " euro");
    M5.Lcd.println("Heater Monthly use: " + (String)(monthsConsumption[month]) + "min");
    int totalMinutes = 0;
    for(int i = 0; i < 12 ; i++)
      totalMinutes += monthsConsumption[i];
    M5.Lcd.println("Heater yearly use: " + (String)(totalMinutes / 60) + " hrs");
    M5.Lcd.println("Yearly cost: " + (String)((totalMinutes * HEATER_KW /60)*KWH_COST) + " euro");
    
    //M5.Lcd.println("Heater: Active: " + (String)digitalRead(RLY) + "  Temp: " + (String)currentTemperature + "Sensor attached: " + (String)sensorAttached);
    //M5.Lcd.println("Update: " + (String)updatedNeeded);
    
    navigationButtons("", "Home", "", DETAILS_SCREEN_COLOR, DETAILS_SCREEN_TXT);
  }
  if(screenID == MAIN_SCREEN)
  {
    serialPrint(ENABLE_SERIAL, INFO_MSG, "Screen selected: " + (String)MAIN_SCREEN);
    if(heaterOnRequest == 1 || heaterActivatedManually)
    {
      /*if(consecutiveAmperesReadingsBelowSP >= CONSECUTIVE_LOW_AMPS_READINGS-1 ) imgSprite.setTextColor(TFT_WHITE, HEATER_ON_DISPLAY_ERROR);
      else imgSprite.setTextColor(TFT_WHITE, HEATER_ON_DISPLAY_CLR);*/
      //TODO: change color on NO current
      if(consecutiveAmperesReadingsBelowSP >= CONSECUTIVE_LOW_AMPS_READINGS )
      {
        blinking = !blinking;
        serialPrint(ENABLE_SERIAL, INFO_MSG, "Warning... Heater is broken");
        if(blinking)
        {        
          imgSprite.setTextColor(TFT_WHITE, HEATER_ON_DISPLAY_ERROR);
          imgSprite.fillSprite(HEATER_ON_DISPLAY_ERROR);
        }
        else
        {
          imgSprite.setTextColor(TFT_WHITE, TFT_BLACK);
          imgSprite.fillSprite(TFT_BLACK);
        }
      }
      else
      {
        imgSprite.setTextColor(TFT_WHITE, HEATER_ON_DISPLAY_CLR);
        imgSprite.fillSprite(HEATER_ON_DISPLAY_CLR);
       
      }
      //imgSprite.setTextColor(TFT_WHITE, HEATER_ON_DISPLAY_CLR);
      //imgSprite.fillSprite(HEATER_ON_DISPLAY_CLR);
      
    }
    else
    {
      imgSprite.setTextColor(TFT_WHITE, TFT_BLACK);
      imgSprite.fillSprite(TFT_BLACK);      
    }    
    imgSprite.setTextDatum(CC_DATUM);
    imgSprite.setFreeFont(&BebasNeue_Regular75pt7b);
    
    if(idle_timer > MAX_IDLE_TIME)  M5.Lcd.setBrightness(IDLE_BRIGHTNESS);
    else M5.Lcd.setBrightness(NORMALL_BRIGHTNESS);     
    imgSprite.drawString((String)currentTemperature,(int)(M5.Lcd.width()/2), (int)(M5.Lcd.height()/2), 1);
    serialPrint(ENABLE_SERIAL, INFO_MSG, (String)currentTemperature);
    imgSprite.setFreeFont(&FreeSans9pt7b);
    drawTime();        
    drawWiFiSignal();
    drawButtonsNavigation(); 
    if(heaterOnRequest == 1)
      drawCirclePoints(WAIT_CIRCLES_R, elapseMinutes);
    imgSprite.pushSprite(0, 0);
  }
  
  
}

BLYNK_WRITE(V0)
{
// in Blynk app writes values to the Virtual Pin 1
  heaterOnRequest = param.asInt(); // assigning incoming value from pin V1 to a variable
  
  if(heaterOnRequest == 1)
  {
    serialPrint(ENABLE_SERIAL, INFO_MSG, "Remotelly: Activate heater");
    digitalWrite(RLY, true);
    //returnCirclePoints(80);
  }
  else
  {
    serialPrint(ENABLE_SERIAL, INFO_MSG, "Remotelly: Deactivate heater");
    deactivateHeater();
  }

  drawDefaultScreen(currentScreen);
}
BLYNK_WRITE(V4)
{
  // This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin 1
  long startTimeInSecs = param[0].asLong();
  Serial.println("Start time in seconds: " + (String)startTimeInSecs);
  //TimeInputParam t(param);
  //  Serial.println(Time);
//  TimeInputParam t(param);
//
//  // Process start time
//
//  if (t.hasStartTime())
//  {
//    Serial.println(String("Start: ") +
//                   t.getStartHour() + ":" +
//                   t.getStartMinute() + ":" +
//                   t.getStartSecond());
//  }
//  else if (t.isStartSunrise())
//  {
//    Serial.println("Start at sunrise");
//  }
//  else if (t.isStartSunset())
//  {
//    Serial.println("Start at sunset");
//  }
//  else
//  {
//    // Do nothing
//  }
//
//  // Process stop time
//
//  if (t.hasStopTime())
//  {
//    Serial.println(String("Stop: ") +
//                   t.getStopHour() + ":" +
//                   t.getStopMinute() + ":" +
//                   t.getStopSecond());
//  }
//  else if (t.isStopSunrise())
//  {
//    Serial.println("Stop at sunrise");
//  }
//  else if (t.isStopSunset())
//  {
//    Serial.println("Stop at sunset");
//  }
//  else
//  {
//    // Do nothing: no stop time was set
//  }
//
//  // Process timezone
//  // Timezone is already added to start/stop time
//
//  Serial.println(String("Time zone: ") + t.getTZ());
//
//  // Get timezone offset (in seconds)
//  Serial.println(String("Time zone offset: ") + t.getTZ_Offset());
//
//  // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)
//
//  for (int i = 1; i <= 7; i++) {
//    if (t.isWeekdaySelected(i)) {
//      Serial.println(String("Day ") + i + " is selected");
//    }
//  }
//
//  Serial.println();
}
BLYNK_WRITE(V2)
{
  //SET POINT from the device
  setPoint = param.asInt(); // assigning incoming value from pin V1 to a variable
  //store in flash memory
  preferences.begin(PR_NAMESPACE, false);
  preferences.putUInt(PR_SETPOINT, setPoint);
  preferences.end();
  Serial.println("Temperature set point from the slider:" + (String)setPoint);
}
BLYNK_WRITE(V3)
{
  //SET POINT from the device
  maxHeaterActive = (uint8_t)param.asInt(); // assigning incoming value from pin V1 to a variable
  //store in flash memory
  preferences.begin(PR_NAMESPACE, false);
  preferences.putUInt(PR_MAX_TIMER, maxHeaterActive);
  preferences.end();
  Serial.println("Timer set point from the slider:" + (String)maxHeaterActive);
}
void initializeBlynk()
{
  serialPrint(ENABLE_SERIAL, INFO_MSG, "Initialize Blynk");
  //Read token from file
  //TODO: check token
  /*char token[blynkToken.length() + 1];
  strcpy(token, blynkToken.c_str()); 
  Blynk.config(token);*/
  Blynk.config(blynkToken.c_str());

  //update set points
  /*Blynk.virtualWrite(V2, setPoint);
  Blynk.virtualWrite(V3, maxHeaterActive);*/
  
}

void defineSprites()
{
  serialPrint(ENABLE_SERIAL, INFO_MSG, "Initializing sprites");
  imgSprite.setColorDepth(COLOR_DEPTH ); // Optionally set depth to 8 to halve RAM use
  imgSprite.createSprite(SPRITE_WIDTH, SPRITE_HEIGHT);
  imgSprite.fillSprite(TFT_BLACK);

}

int externalTemperature()
{
  if(!sensorAttached)
  {
    serialPrint(ENABLE_SERIAL, INFO_MSG, "No sensor attached");
    return ERROR_NO_SENSOR;
  }
  else
  {
    int result = 0;
    for(int i = 0; i < READ_TEMP_ATTEMPTS;i++)
    {
      sensors.requestTemperatures(); 
      delay(100);
      result = (int)sensors.getTempCByIndex(0);
      if(result != -127)
      {
        lastGoodTemperatureReading = result;
        return result;
      }
    }
    serialPrint(ENABLE_SERIAL, INFO_MSG, "Consecutive wrong readings (actual reading: "+(String)result + "), returning the last good reading (last good reading: "+(String)lastGoodTemperatureReading+")");
    //return ERROR_BAD_TEMP_READING;
    return lastGoodTemperatureReading;

  }
}

void smartConfig()
{
  
  serialPrint(ENABLE_SERIAL, INFO_MSG, "Activate smart config");

  M5.Lcd.setTextDatum(TC_DATUM);
  M5.Lcd.setTextSize(HEADER_FONT_SIZE); 
  M5.Lcd.setFreeFont(FSB9);
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
 // M5.Lcd.setCursor(5,M5.Lcd.fontHeight()+5);  
 //M5.Lcd.println("Select your device");

 M5.Lcd.setTextDatum(MC_DATUM);

  M5.Lcd.drawString("Select your device", 160, 120, 1);

 M5.Lcd.drawString("iOS", 60, M5.Lcd.height()-M5.Lcd.fontHeight()-10);
 M5.Lcd.drawString("android", 250, M5.Lcd.height()-M5.Lcd.fontHeight()-10);
 bool selection = false; //false --> ios, true --> android
 while(1)
 {
  if(M5.BtnA.read())
    break;
  if(M5.BtnC.read())
  {
    selection = true;
    break;
  }
 }
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setCursor(5,M5.Lcd.fontHeight()+5);
  M5.Lcd.println("Download smart config app");
  delay(2000);
  
  if(selection)
    M5.Lcd.qrcode("https://play.google.com/store/apps/details?id=com.cmmakerclub.iot.esptouch&hl=en",70,50,150,6);
  else
    M5.Lcd.qrcode("https://apps.apple.com/us/app/esptouch/id1495177097", 70, 50, 150, 6);

  M5.Lcd.drawString("Press any button to continue", 0,M5.Lcd.height() - M5.Lcd.fontHeight(),1);
  while(1)
  {
    if(M5.BtnA.read() or M5.BtnB.read() or M5.BtnC.read())
    {
      break;
    }
    
    M5.update();
  }
  M5.Lcd.fillScreen(BLACK);
  /*M5.Lcd.setFreeFont(FSB12);
  M5.Lcd.drawString("Smart Configuration ", 5,M5.Lcd.fontHeight()+10,1);
  */
  WiFi.mode(WIFI_AP_STA);
  WiFi.beginSmartConfig();
   M5.Lcd.setFreeFont(FSB9);
  int i = 0;
  M5.Lcd.drawString("Wait....", 5,M5.Lcd.fontHeight()+5,1);
  M5.Lcd.drawString("I am speaking with your smartphone", 5,2*M5.Lcd.fontHeight()+10,1);
  while (!WiFi.smartConfigDone())
  {
    
    //TODO: infinite loop!!!
    delay(500);
    Serial.print(".");
    if ((i + 1) % 30 == 0) Serial.print(".");
    M5.Lcd.fillRect(40, (M5.Lcd.height()/2) - M5.Lcd.fontHeight(), M5.Lcd.width()-2*40, 2*M5.Lcd.fontHeight(), BLACK);
    
    if (i % 2 == 0)
    {
      M5.Lcd.setCursor((M5.Lcd.width()/2)-10,(M5.Lcd.height()/2)-5);
      M5.Lcd.println("*");
    }
    else
    {
      M5.Lcd.setCursor((M5.Lcd.width()/2)+10,(M5.Lcd.height()/2)-5);
      M5.Lcd.println("*");
    }
    
    i++;
    if (i >= 50)  i = 0;
  }
  printMsg("Connected", WiFi.localIP().toString().c_str(),  SUCCESS, 5000);
  
  serialPrint(ENABLE_SERIAL, INFO_MSG, "Smart config completed, IP:" + (String)WiFi.localIP());
}

void searchTemperatureSensor(int attempts)
{
  serialPrint(ENABLE_SERIAL, INFO_MSG, "Searching for external sensor...");
  // Start up the library
  sensors.begin();
  // Grab a count of devices on the wire
  int numberOfDevices = 0;
  for(int i=0;i < attempts;i++)
  {
    serialPrint(ENABLE_SERIAL, INFO_MSG, "Attempt["+(String)i+"]");
    numberOfDevices = sensors.getDeviceCount();
    if(numberOfDevices > 0)
    {
      sensorAttached = true;
      break;
    }
    delay(100);
  }
    
  
}
//void playShowerReadySound()
//{
//  //this function will play a "ready shower" tone
////  M5.Speaker.tone(200, 200);
////  delay(100);
////  M5.Speaker.tone(500, 200);
////  delay(100);
////  M5.Speaker.tone(1000, 200);
////  delay(100);
////  M5.Speaker.end();
//
//
//  // notes in the melody:
//  //int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
//  int melody[] = {NOTE_C4, NOTE_C4};
//  // note durations: 4 = quarter note, 8 = eighth note, etc.:
//  //int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};
//   int noteDurations[] = {8, 8};
//  for (int thisNote = 0; thisNote < 8; thisNote++) 
//  {
//    // to calculate the note duration, take one second divided by the note type.
//    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
//    int noteDuration = 1000 / noteDurations[thisNote];
//    M5.Speaker.tone(melody[thisNote], noteDuration);
//    // to distinguish the notes, set a minimum time between them.
//    // the note's duration + 30% seems to work well:
//    int pauseBetweenNotes = noteDuration * 2.3;
//    delay(pauseBetweenNotes);
//    // stop the tone playing:
//     M5.Speaker.end();
//  }  
//}
void initializeKelcie()
{
  Serial.begin(BAUD);
  serialPrint(ENABLE_SERIAL, INFO_MSG, "Initialize KELCIE...");
  //Start the splash screen
  M5.begin();
  //set default screen
  currentScreen = MAIN_SCREEN;
  M5.Lcd.setBrightness(DISPLAY_BRIGHTNESS);  
  M5.Lcd.setTextDatum(MC_DATUM);
  M5.Lcd.setTextColor(TFT_WHITE, BACKGROUND_COLOR);
  /*M5.Lcd.setFreeFont(FSSB9);
  M5.Lcd.drawString("V:"+CURRENT_VERSION, 50, 50, 1);*/
  m5.lcd.setTextDatum(CC_DATUM);
  m5.lcd.setFreeFont(&BebasNeue_Light40pt7b);
  M5.Lcd.fillScreen(BACKGROUND_COLOR);//0x51d
  M5.Lcd.drawString(SPLASH_SCREEN_TEXT, M5.Lcd.width()/2, (M5.Lcd.height()/2)-20, 1);
  m5.lcd.setFreeFont(&BebasNeue_Light30pt7b);
  M5.Lcd.drawString("knows", M5.Lcd.width()/2+10, (M5.Lcd.height()/2)+50, 1);
  M5.Lcd.drawCircle(165, 80, 5, WHITE);

  //Initiallize FOTA (HTTP update)
  serialPrint(ENABLE_SERIAL, INFO_MSG, "Initialize HTTP update");
  esp32FOTA.checkURL = UPDATE_SERVER;
  
  
  bool enterConfigurationMenu = false;
  int counter = 0;
  M5.Lcd.fillRoundRect(37, 235, 60, 20,8, WHITE);//0x31A6);
  M5.Lcd.fillRoundRect(225, 235, 60, 20,8, WHITE);//0x31A6);
  
  //M5.Lcd.fillRect(50,120,240,20,0);
  //M5.Lcd.progressBar(50,120,240,20, 20);

  //5. Initialize EEPROM
  //TODO: remove eeprom initialize
  /*if (!EEPROM.begin(EEPROM_SIZE)) serialPrint(ENABLE_SERIAL, INFO_MSG, "Failed to initialise EEPROM"); 
  else serialPrint(ENABLE_SERIAL, INFO_MSG, "Initialize EEPROM");
  serialPrint(ENABLE_SERIAL, INFO_MSG, "EEPROM length: " + (String)EEPROM_SIZE);
  */
  preferences.begin(PR_NAMESPACE, false);     //false --> start preferenece in Read and write mode, if true --> start preferences in read only mode
  serialPrint(ENABLE_SERIAL, INFO_MSG, "Start preferences (flash memory) under" + (String)PR_NAMESPACE + " namespace");
  
  //5a. Initialize variables
  /*setPoint = EEPROM.read(EEPROM_SETTINGS);
  maxHeaterActive = EEPROM.read(EEPROM_SETTINGS+sizeof(int));
  firstTimeSetupFlag = (bool)EEPROM.read(EEPROM_FIRST_TIME_SETUP);*/

  setPoint = preferences.getUInt(PR_SETPOINT, SET_POINT_DEFAULT);                     //if PR_SETPOINT key doesnt exist then it should be created and loaded with default value SET_POINT_DEFAULT
  maxHeaterActive = preferences.getUInt(PR_MAX_TIMER, MAX_HEATER_ACTIVE_DEFAULT);     //if PR_MAX_TIMER key doesnt exist then it should be created and loaded with default value MAX_HEATER_ACTIVE_DEFAULT
  firstTimeSetupFlag = preferences.getBool(PR_FIRST_TIME_SETUP, true);                 //if PR_FIRST_TIME_SETUP key doesnt exist then it should be created and loaded with default value TRUE
  blynkToken = preferences.getString(PR_BLYNK_TOKEN, "");                               //if PR_BLYNK_TOKEN key doesnt exist then it should be created and loaded with default value ""
  monthsConsumption[0] = preferences.getUInt(PR_JAN, 0);
  monthsConsumption[1] = preferences.getUInt(PR_FEB, 0);
  monthsConsumption[2] = preferences.getUInt(PR_MAR, 0);
  monthsConsumption[3] = preferences.getUInt(PR_APR, 0);
  monthsConsumption[4] = preferences.getUInt(PR_MAY, 0);
  monthsConsumption[5] = preferences.getUInt(PR_JUN, 0);
  monthsConsumption[6] = preferences.getUInt(PR_JUL, 0);
  monthsConsumption[7] = preferences.getUInt(PR_AUG, 0);
  monthsConsumption[8] = preferences.getUInt(PR_SEP, 0);
  monthsConsumption[9] = preferences.getUInt(PR_OCT, 0);
  monthsConsumption[10] = preferences.getUInt(PR_NOV, 0);
  monthsConsumption[11] = preferences.getUInt(PR_DEC, 0);
  
  //5b. End preferences
  preferences.end();
  
  //strcpy(auth, EEPROM.readString(EEPROM_BLYNK_AUTH_START).c_str());
  //strncpy(auth, EEPROM.readString(EEPROM_BLYNK_AUTH_START).c_str(), BLYNK_AUTH_TOKEN_LEN);
  serialPrint(ENABLE_SERIAL, INFO_MSG, "Settings read from preferences with namespace:" + (String)PR_NAMESPACE);
  serialPrint(ENABLE_SERIAL, INFO_MSG, "Set Point         ----------------------------->"+ (String)setPoint);
  serialPrint(ENABLE_SERIAL, INFO_MSG, "Max Heater On     ----------------------------->"+ (String)maxHeaterActive);
  serialPrint(ENABLE_SERIAL, INFO_MSG, "Blynk Auth Token  ----------------------------->"+ blynkToken);
  serialPrint(ENABLE_SERIAL, INFO_MSG, "First time setup  ----------------------------->"+ (String)firstTimeSetupFlag);
  
  //for(int i = 0;i<12;i++) serialPrint (ENABLE_SERIAL, INFO_MSG, (String)i); //serialPrint(ENABLE_SERIAL, INFO_MSG, "Month[" + (String)(i+1) + "] consumption: " + (String)monthsConsumption[i] + "minutes");
  for(int i = 0;i<11;i++) serialPrint (ENABLE_SERIAL, INFO_MSG,(String)monthsConsumption[i]);

  firstTimeSetUp(firstTimeSetupFlag);
  //playShowerReadySound();
  M5.Speaker.end();
  
  while(1)
  {
    if(M5.BtnA.read() && M5.BtnC.read())
    {
      enterConfigurationMenu = true;
      break;
    }
    if (counter > CONFIGURE_MENU_DLY) break;
    counter++;
    if(counter%100) M5.Lcd.drawFastHLine(87, 145, counter/22, TFT_WHITE);
    delay(1);
    
  }
  delay(500);   //to enjoy splash screen ;)
  
  configureM5Keyboard();
  configureIO();
  initVariables();
  
  //2. Search for temperature sensor
  searchTemperatureSensor(SEARCH_ATTEMPTS);

  defineSprites();
  
  if(WiFi.status() == WL_CONNECTED) serialPrint(ENABLE_SERIAL, INFO_MSG, "Obtained IP Address: "+(String)WiFi.localIP().toString());
 
  initializeBlynk();

  //configuration 
  if(enterConfigurationMenu) showMainMenu();//showConfigurationMenu();
 
}

void serialPrint(bool enableSerial, int msgType, String printMsg)
{
  if (!enableSerial) return;      
    switch (msgType)
    {
      Serial.print("["+(String)millis()+"]-C"+(String)xPortGetCoreID()+" KELCIE:");
      case INFO_MSG:
        //Serial.println("["+(String)millis()+"]-C"+(String)xPortGetCoreID()+" KELCIE:"+(String)INFO_MSG_STR + ": " + printMsg);
        Serial.println((String)INFO_MSG_STR + ": " + printMsg);
        serialMessageInfo = printMsg;
        break;
      case DEBUG_MSG:
        //Serial.println("["+(String)millis()+"]-C"+(String)xPortGetCoreID()+" KELCIE:"+(String)DEBUG_MSG_STR + ": " + printMsg);
        Serial.println((String)DEBUG_MSG_STR + ": " + printMsg);
        serialMessageDebug = printMsg;
        break;
      case SECONDS_MSG:
        //Serial.println("["+(String)millis()+"]-C"+(String)xPortGetCoreID()+" KELCIE:"+(String)SECONDS_MSG_STR + ": " + printMsg);
        Serial.println((String)SECONDS_MSG_STR + ": " + printMsg);
        serialMessageSeconds = printMsg;
        break;
    }
}
void resetToFactorySettings()
{
  //This function resets all settings that are stored in the EEPROM. 
  
  M5.Lcd.fillScreen(BACKGROUND_COLOR); 
  M5.Lcd.setCursor(0,20);
  M5.Lcd.setFreeFont(SUBTITLE_FNT);
  M5.Lcd.setTextColor(RED);
  M5.Lcd.println("Do you really want to reset all settings?");
  serialPrint(ENABLE_SERIAL, INFO_MSG, "Do you really want to reset all settings?");
  M5.Lcd.println("");
  navigationButtons("Yes", "", "No", FTS_MENU_COLOR, FTS_MENU_TEXT_COLOR);
  delay(DEBOUNCE_SCROLL_MENU*2);  //to prevent wrong input from the previous menu
  
  while(1)
  {
    if(M5.BtnC.read()) break;
    if(M5.BtnA.read())
    {
      serialPrint(ENABLE_SERIAL, INFO_MSG, "Reseting flash memory");
      /*for(int i=0;i<EEPROM_SIZE;i++)
        EEPROM.write(i,0);

      //Set default values
      EEPROM.write(EEPROM_SETTINGS, SET_POINT_DEFAULT);
      EEPROM.write(EEPROM_SETTINGS+sizeof(int), MAX_HEATER_ACTIVE_DEFAULT);
      
      //commit changes
      EEPROM.commit();*/
      //1. Start preferences
      preferences.begin(PR_NAMESPACE, false);     //false --> start preferenece in Read and write mode, if true --> start preferences in read only mode
      serialPrint(ENABLE_SERIAL, INFO_MSG, "Start preferences (flash memory) under" + (String)PR_NAMESPACE + " namespace");

      //2. Set preferences with default values
      preferences.putUInt(PR_SETPOINT, SET_POINT_DEFAULT);                     
      preferences.putUInt(PR_MAX_TIMER, MAX_HEATER_ACTIVE_DEFAULT);     
      preferences.putBool(PR_FIRST_TIME_SETUP, true);                 
      preferences.putString(PR_BLYNK_TOKEN, "");                               
      preferences.putUInt(PR_JAN, 0);
      preferences.putUInt(PR_FEB, 0);
      preferences.putUInt(PR_MAR, 0);
      preferences.putUInt(PR_APR, 0);
      preferences.putUInt(PR_MAY, 0);
      preferences.putUInt(PR_JUN, 0);
      preferences.putUInt(PR_JUL, 0);
      preferences.putUInt(PR_AUG, 0);
      preferences.putUInt(PR_SEP, 0);
      preferences.putUInt(PR_OCT, 0);
      preferences.putUInt(PR_NOV, 0);
      preferences.putUInt(PR_DEC, 0); 
      //3. End preferences
      preferences.end();
      
      serialPrint(ENABLE_SERIAL, INFO_MSG, "Deleting wifi credentials");
      WiFi.disconnect(false, true);       //bool disconnect(bool wifioff = false, bool eraseap = false) --> If wifioff is true, the network settings will be restored. If eraseap is true, the network parameters saved in flash will be cleared.
      serialPrint(ENABLE_SERIAL, INFO_MSG, "DONE");
      printMsg("Reset is done", "restarting in 5 seconds", SUCCESS, 5000);
      ESP.restart();
      break;
    }
  }
  
  
}
void IRAM_ATTR onTimer() 
{
  portENTER_CRITICAL_ISR(&timerMux);
  //execute very 
  //int currentSampling[20];
  //int currentIndex = 0;
  if(heaterOnRequest)
  {
    currentSamplingPeriod++;            //increase by one every "onTimer" (every millisecond)
    if(currentSamplingPeriod > 1000)    //take samples every second
    {
      int currentSamplingSize = sizeof(currentSampling) / sizeof(currentSampling[0]);
      if(currentIndex > (currentSamplingSize-1))
      {
        //calculate the size of the array
        
        unsigned int currentSamplingTotal = 0;
        //float analogReadRMS = 0.0;
        //calculate Irms and reinitialize
        for(int i = 0;i < currentSamplingSize;i++)
        {
          //calculate the sum of the readings on the power of 2 
          //subtracting 2699 which is the equilavent of 2.175 volts which is 0 Amperes (current sensor)
          currentSamplingTotal = currentSamplingTotal + pow((currentSampling[i]-2699),2);//(currentSampling[i]*currentSampling[i]);
          //currentSamplingTotal = currentSamplingTotal + pow((currentSampling[i]-analogRead(CURRENT_SNR_VREF)),2);
        }
        //analogReadRMS = (float)sqrt(currentSamplingTotal / currentSamplingSize);
        //amperes = (analogReadRMS - 2608)/111.8;
        amperes = (sqrt(currentSamplingTotal / (currentSamplingSize)) - 2608)/111.8;
        currentIndex = 0;
        currentSamplingPeriod = 0;
      }
      currentSampling[currentIndex] = analogRead(CURRENT_INPUT);
      currentIndex++;
    }
  }
  else
    amperes = 0.0;
  portEXIT_CRITICAL_ISR(&timerMux);
 
}
