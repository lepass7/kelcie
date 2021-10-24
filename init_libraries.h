  // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(EXTERNAL_TEMP);
DallasTemperature sensors(&oneWire);
DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address




/************************* SPRITE  *********************************************/
/*
 * To update partially without flickering the display
 */
 TFT_eSprite imgSprite = TFT_eSprite(&M5.Lcd);
/************************* BLynk  *********************************************/

//BlynkTimer BlynkTime;
Preferences preferences;


DNSClient dnsClient;



M5OnScreenKeyboard m5osk;



//ACS712  ACS(CURRENT_INPUT, 5, 4095, 1250);
//ACS712  ACS(CURRENT_INPUT, 2.175, 4095, 90);
//EnergyMonitor emon1;
esp32FOTA esp32FOTA(FIRMWARE, CURRENT_VERSION);

HTTPClient http;

//WiFiServer webServer(80);

AsyncWebServer server(80);
const char* PARAM_MESSAGE = "message";
