/****************   MISC    ****************/  
bool buttonBPressedFlag = false;
bool firstTimeSetupFlag = true;
int millisBeforeBlynkRun = 0;
int blynkRunTotalTime = 0;                                    //total time for the Blynk.run() to be executed
bool internetConnectionAvailable = true;                     //if internet connection is available (for the first time is true)
//char server[]= "www.google.com";
//IPAddress dnsResult;
bool updatedNeeded = false;
/*unsigned int*/uint8_t idle_timer = 0;
/*unsigned int*/uint8_t feedbackCounter = 0;
float amperes = 0;
/*int*/uint8_t maxAmperes = 0;
bool heaterActivatedManually = false;                      
unsigned int minutesToCheckForUpdates = 0;                             //it would be used to count 3600 minutes every day
/*unsigned int*/uint8_t currentScreen = MAIN_SCREEN;                             //which display to show
String serialMessageInfo = "";
String serialMessageDebug = "";
String serialMessageSeconds = "";
/****************   Temperature    ****************/ 
bool sensorAttached = false;                                  //external sensor is attached
int currentTemperature = 0;                                   //last read temperature 
int lastGoodTemperatureReading = ERROR_BAD_TEMP_READING;     //the last good reading
uint8_t validReadingsAboveSP = 0;
uint8_t consecutiveAmperesReadingsBelowSP = 0;
bool blinking = false;
bool asyncFirstTimeSetup = true;
bool tokenSubmittedFlag = false;                //is going to be used during web setup of Blynk token (m5 will wait the user to enter the token)

//************* INTERRUPT ******************//
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

//******************************************//

/*************** BLYNK ***********************/
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
//char auth[] = "eycylCuDXXMeJJao7T-piOd6hRWZ2WUr";
String blynkToken = "";
String blynkTemporaryToken = "";
bool heaterOnRequest = false;
bool blynkAuthTokenIsValid = false;


/*************** Heater ***********************/
/*unsigned int*/ uint8_t maxHeaterActive = MAX_HEATER_ACTIVE_DEFAULT;     //minutes /TODO: remove after migrate to preferences library. 
/*unsigned int*/ uint8_t setPoint = SET_POINT_DEFAULT;    //TODO: remove after migrate to preferences library. 

int heaterLoopTime = 0;
int buttonDebounce = 0;
int heaterOnSeconds = 0;    //how many seconds heater is active
int elapseMinutes = 0;      //how many minutes has passed since heater was activated
//float monthlyConsumption[12];        //array to store KWh consumption for every month of a year

/************* Current Sensor **********************/
bool overCurrentFault = false;
/*int*/ uint8_t currentSampling[20];
/*int*/ uint8_t currentIndex = 0;
/*int*/ uint8_t currentSamplingPeriod = 0;

/*************** Loop Timer ***********************/
/*int*/ uint8_t loopTime = 5;
int loopTimeMiliSecond = 0;
/*int*/ uint8_t loopTimeWiFi = CHECK_WIFI; //because we need to start checking wifi from the first loop
/*int*/ uint8_t loopTimeMinute = 0;      //every minute
unsigned long loopTimeMainClock = 0;

/************* configuration  ****************************/
//String menu[7] ={"Set auth token","Remove wifi cred","Smart Config","Set Wifi Cred","Erase KWh consumption","Settings", "Exit"} ;

/****************** NTP (TIME)  *************************/
/*const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 7200;             //UTC offset for your timezone in milliseconds
const int   daylightOffset_sec = 3600;        //Daylight offset in milliseconds*/
bool configurationDone = false;
/*int*/ uint8_t year = 0;                                 //stores the current year
/*int*/ uint8_t currentYear = 0;                         
/*int*/ uint8_t month = 0;                                //start from 1 - january

/****************** consumption  *************************/
/*unsigned int*/ uint8_t monthsConsumption[11];
bool monthsUpdatedFromEEPROM = false;         //To update the value just once.
