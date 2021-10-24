/* FIRMWARE FOTA UPDATE */
#define MINUTES_TO_CHECK_FOR_UPDATES 3600   //once per day
#define CURRENT_VERSION 1       //need to increase this everytime you need to be updated
#define FIRMWARE        "esp32-fota-http"
//#define UPDATE_SERVER   "http://192.168.0.23/fota/fota.json"
#define UPDATE_SERVER   "http://www.kelcie.eu/fota/fota.json"
//#define JSON_FILE       "update.json"
/*JSON FILE*/
//{
//    "type": "esp32-fota-http",
//    "version": 2,
//    "host": "kelcie.eu",
//    "port": 80,
//    "bin": "/fota/esp32-fota-http-2.bin"
//}
//IMPORTANT: "host": "kelcie.eu" NOT "host": "http://www.kelcie.eu"  
/****************   SERIAL    ****************/  


#define BAUD                  115200
//message types used by function serialPrint()
#define INFO_MSG              0
#define DEBUG_MSG             1
#define SECONDS_MSG           2
#define ENABLE_SERIAL         true
#define INFO_MSG_STR          "INFO"
#define DEBUG_MSG_STR         "DEBUG"
#define SECONDS_MSG_STR       "SECONDS"

/****************   CURRENT SENSOR    ****************/  
//MCA1101-20-5 
//ANALOG INPUT  G35 vout (Analog Output Signal linearly proportional to Primary Path Current)
//              G16 Vref (Zero Current Analog Reference Output )
//              G23 vocrst 
//              G19 flt (!faultb) --> Active Low (when Input G19 is 0 it means there is an overcurrent)
#define CURRENT_INPUT     35
#define CURRENT_SNR_VREF  16
#define OCD_RESET         23        //OUTPUT: keep low, set high when over current detection flag needs to be reset
#define OVC_FAULT         19        //INPUT: 1 --> OK, 0 --> over current detected


/****************************************************/

/****************   WEB SERVER    ****************/ 
#define NETWORK_NAME "KELCIE"
/****************************************************/
/****************   TEMPERATURE SENSOR    ****************/  

#define UPDATE_TEMPERATURE          5          //every 5 seconds updates temperature   
#define SEARCH_ATTEMPTS             10   
#define READ_TEMP_ATTEMPTS          5 
#define CONSECUTIVE_VALID_READINGS  3

#define ERROR_NO_SENSOR             -99
#define ERROR_BAD_TEMP_READING      -98

/****************   PINS    ****************/  
#define RLY                   17
#define EXTERNAL_TEMP         5

/************************* SPRITE  *********************************************/

#define SPRITE_WIDTH    320//320
#define SPRITE_HEIGHT   240//240
#define COLOR_DEPTH     4
/************************* HEATER  *********************************************/
#define HEATER_KW                       3         //average size of heater in KW
#define KWH_COST                        0.1311    
#define MIN_AMPERES_FOR_BROKEN_HEATER   2         //if amps is less than MIN_AMPERES_FOR_BROKEN_HEATER it means that heater or (something else) is not working
#define CONSECUTIVE_LOW_AMPS_READINGS   2
/************************* MISC  *********************************************/
#define DEFAULT_FONT_SIZE     6
#define HEADER_FONT_SIZE      1
#define MAIN_TEMP_FNT         FSB24
#define TITLE_FNT             FSSB12
#define SUBTITLE_FNT          FSS9
#define HEADER_PADDING        5
#define NO_SIGNAL_TXT         "---"
#define WIFI_CIRCLE_RADIUS    4
#define WIFI_CIRCLE_PADDING   4
#define WAIT_CIRCLES_RADIUS   3
#define WAIT_CIRCLES_R        90
#define BUTTON_PRESSED_FOR    1000      //ms
#define SECONDS               1000      //ms
#define CHECK_WIFI            10        //s
#define EVERY_MINUTE          60        //s

#define DEBOUNCE_SCROLL_MENU  200
#define MAX_SSID_LOAD         8
#define BLYNK_AUTH_TOKEN_LEN  32
#define BLYNK_PROJECT         "blynk://token/clone/bFLT9ZhttyCOIPhUcvn5MZ2kI95kaGHU?server=blynk-cloud.com"
#define SUCCESS               0
#define NO_SUCCESS            1
#define INFORMATION           2
#define HEATER_ACTIVE_AMPS    3000             //if amperes (current reading) is bigger than this it means that heater is activated. 

/************************* NPT TIME  *********************************************/
#define NO_TIME               "NT"
#define GMTOFFSET_SEC         7200            //UTC offset for your timezone in milliseconds
#define DAYLIGHTOFFSET_SEC    3600            //Daylight offset in milliseconds*/
#define NTP_SERVER            "pool.ntp.org"
/*const char* ntpServer = "pool.ntp.org";
 * 

     
/************** EEPROM - FLASH **********************/
/*#define EEPROM_MONTH_ADDR       0           //starting address of eeprom to store months (second starting address should be EEPROM_MONTH_ADDR + 12*(sizeof(int)) sizeof(int) = 4 ==> next available address os 48
#define EEPROM_SETTINGS         52          //available space for integers (64-52)/4 = 3 integers max
#define EEPROM_BLYNK_AUTH_START 72          //where to start to put blynk auth token into eeprom 56+ 32*4 = 184 (the next address should be 184 + sizeof(int) = 186
#define EEPROM_FIRST_TIME_SETUP 190         //where to start to put the first time setup flag (next address should be 190+sizeof(boolean)
#define EEPROM_SIZE             512
*/
//DATA FOR preferences 
 
#define PR_FIRST_TIME_SETUP   "firstSetup"
#define PR_JAN                "JAN"
#define PR_FEB                "FEB"
#define PR_MAR                "MAR"
#define PR_APR                "APR"
#define PR_MAY                "MAY"
#define PR_JUN                "JUN"
#define PR_JUL                "JUL"
#define PR_AUG                "AUG"
#define PR_SEP                "SEP"
#define PR_OCT                "OCT"
#define PR_NOV                "NOV"
#define PR_DEC                "DEC"
#define PR_TOTAL_CONS         "consumption"
#define PR_NAMESPACE          "kelcie"
    
#define PR_MAX_TIMER          "timer"
#define PR_SETPOINT           "setpoint"
#define PR_BLYNK_TOKEN        "token"



/*
 * 
 * 0 --> Months
 * 1 --> Settings
 * 2 --> Auth TOKEN
 * 3 --> First time setup
 * 
 * 
 */
#define SET_POINT_DEFAULT             45      //celsius
#define MAX_HEATER_ACTIVE_DEFAULT     30      //minutes

/*********************** DISPLAY  *********************************************/
#define MAIN_SCREEN                   1         //shows the main screen (temperature)
#define DETAILS_SCREEN                0         //shows details of the device

#define DETAILS_SCREEN_COLOR          0x0000
#define DETAILS_SCREEN_TXT            0xFFFF      

#define BACKGROUND_COLOR              0x4A7E     //https://ee-programming-notepad.blogspot.com/2016/10/16-bit-color-generator-picker.html
#define FTS_MENU_COLOR                0xBDF7    //FTS --> firstTimeSetup function
#define FTS_MENU_TEXT_COLOR           0xFFFF     //FTS --> firstTimeSetup function
#define BACKGROUND_SUCCESS_COLOR      0x4D69
#define BACKGROUND_NO_SUCCESS_COLOR   0xEA06
#define BACKGROUND_INFORMATION_COLOR  0x24BD
#define SUCCESS_TXT                   0xE73C
#define SELECTED_TXT                  0xFFFF
#define NON_SELECTED_TXT              0x6B6D
#define SPLASH_SCREEN_TEXT            "KELCIE°"
#define DELAY_BW_INIT                 1000
#define DISPLAY_BRIGHTNESS            255
#define CONFIGURE_MENU_DLY            5000           //in miliseconds. Time for the operator to select configure menu during booting
#define HEATER_ON_DISPLAY_CLR         0xFAC2
#define HEATER_ON_DISPLAY_ERROR       0xF800
#define IDLE_BRIGHTNESS               40
#define NORMALL_BRIGHTNESS            255
#define MAX_IDLE_TIME                 120           //2 minutes
//#define UPDATE_SCREEN_ON_SERIAL       TRUE          //change this to "false" if you dont want to update display every time that change something from variable serialPrint

/*********************** BLYNK  *********************************************/
#define BLYNK_PRINT Serial
#define LENGTH_OF_TOKEN   32
#define FILE_TOKEN_PATH   "/token.txt"
#define MAX_BLYNK_EXECUTION_TIME_MS   800         //1000 milisecond
//#define TOKEN_ADDR_EEPROM 0
