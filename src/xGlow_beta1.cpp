#include <Arduino.h>

#ifdef ESP8266
 #include <ESP8266WiFi.h>
 #include "FS.h" 
#else
 #include <WiFi.h>
 #include <SPIFFS.h>
#endif

#include <esp_now.h>
//#include <FastLED.h>

#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
FASTLED_USING_NAMESPACE

#include <Adafruit_GFX.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include <pgmspace.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <ESPAsyncWebServer.h>

#define print_EEPROM

#ifdef print_EEPROM
  #define EEPROM_PRINT(x) Serial.print(x)
  #define EEPROM_PRINTLN(x) Serial.println(x)
  #define EEPROM_PRINTF(x...) Serial.printf(x)
#else
  #define EEPROM_PRINT(x)
  #define EEPROM_PRINTLN(x)
  #define EEPROM_PRINTF(x...)
#endif

#define DEBUG_OUTPUT // comment out for debugging mode (mainly for checking memory issues and JSON communication)

#ifdef DEBUG_OUTPUT
  #define DEBUG_PRINT(x) Serial.print(x)
  #define DEBUG_PRINTLN(x) Serial.println(x)
  #define DEBUG_PRINTF(x...) Serial.printf(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
  #define DEBUG_PRINTF(x...)
#endif

// LED properties
#define NUM_SET 600 // THIS DEFINES THE MAXIMUM LED_NUMBER 

CRGB leds[NUM_SET];
int NUM_LEDS = 100; //EEPROM.readInt(93); THIS ONE WILL BE RE-INITIALIZED DURING SETUP. HOWEVER SOME VARIABLES ARE CALCULATED BASED ON THIS NUMBER (NOT FULLY TESTED/OPTIMIZED YET).

#ifdef ESP8266
  //const int DATA_PIN = 2; // GPIO2 - jumper set to the left
  const int DATA_PIN = 3; // This is GPIO3 jumper set to the right
#else
  const int DATA_PIN = 16; // GPIO2 - jumper set to the left
  //const int DATA_PIN = 3; // This is GPIO3 jumper set to the right

#endif
unsigned int FPS = 20; // Refresh time is 20 ms '20 FPS'. '20 FPS' is 50 FRAMES PER SECOND - sorry about the semantics.

// OLED SD1306 properties
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// IR properties
#ifdef ESP8266
  #define IR_PIN  12 
#else
  #define IR_PIN  19 
#endif  
  
IRrecv* irrecv;
decode_results results;

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

//uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0x7A, 0xAE, 0x7C};
 
// // Define a data structure
// typedef struct struct_message {
//   char a[32];
//   int b;
//   float c;
//   bool d;
// } struct_message;
 
// // Create a structured object
// struct_message myData;
 
// Peer info
//esp_now_peer_info_t peerInfo;


//uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
//uint8_t broadcastAddress[] = {0x24, 0x62, 0xAB, 0xDC, 0xA6, 0x8C}; //84:CC:A8:5F:58:A8 || 24:62:AB:DC:A6:F0

// Define variables to store BME280 readings to be sent
float temperature;
float humidity;
float pressure;

// Define variables to store incoming readings
float incomingTemp;
float incomingHum;
float incomingPres;

// Variable to store if sending data was successful
//String success;

//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
    float temp;
    float hum;
    float pres;
} struct_message;

// Create a struct_message called BME280Readings to hold sensor readings
struct_message BME280Readings;

// Create a struct_message to hold incoming sensor readings
struct_message incomingReadings;

char dataEspNow[250];

esp_now_peer_info_t peerInfo;

//boolean espNowMessage = false;

// // Callback when data is sent
// void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
//   DEBUG_PRINT("\r\nLast Packet Send Status:\t");
//   DEBUG_PRINTLN(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
//   if (status == ESP_NOW_SEND_SUCCESS){
//       espNowMessage = false;
//   }
//   else {

//   }
  
//   // if (status ==0){
//   //   success = "Delivery Success :)";
//   // }
//   // else{
//   //   success = "Delivery Fail :(";
//   // }
// }

// // Callback when data is received
// void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {

//         memcpy(&dataEspNow, incomingData, sizeof(dataEspNow));
//         dataEspNow[len] = 0;
//         for (int i = 0; i < len; i++){
//           Serial.print(dataEspNow[i]);
//         }
//         Serial.print("Bytes received: ");
//         Serial.println(len);

//         // DEBUG_PRINTLN(F("received JSON espnow message: "));
//         // for (int i = 0; i < len; i++){
//         // //strval[i]=(char)data[i];    
//         // DEBUG_PRINT((char)incomingData[i]);
//         // }
//         // DEBUG_PRINTLN(" ");

//         StaticJsonDocument<255> json;
//         //DeserializationError err = deserializeJson(json, incomingData);
//         DeserializationError err = deserializeJson(json, dataEspNow);
//         if (err) {
//             DEBUG_PRINT(F("deserializeJson() failed with code "));
//             DEBUG_PRINTLN(err.c_str());
//             return;
//         }

//       if (json.containsKey("SBSM")){BriSPreset = json["SBSM"]; readBriSData(BriSPreset);}// sendProgramInfo(1);}
//       else if (json.containsKey("SRED")){Red = json["SRED"]; loadHSV = true;}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Red), Red);  EEPROM.commit();};} 
//       else if (json.containsKey("SGRE")){Green = json["SGRE"]; loadHSV = true;}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Green), Green);  EEPROM.commit();};}   
//       else if (json.containsKey("SBLU")){Blue = json["SBLU"]; loadHSV = true;}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Blue), Blue);  EEPROM.commit();};}
      
//       else if (json.containsKey("SPST")){selectedPreset[programMode] = json["SPST"]; selectedPresetVariable = selectedPreset[programMode];}// cycleT=0;  previousMillis44 = millis();  previousMillis45 = millis();  if (saveToEEPROM){int offsetPosition = offsetof(storeInEEPROM, selectedPreset[0]); EEPROM.put((offsetPosition + programMode), selectedPresetVariable);  EEPROM.commit();} changeState();}
//       else if (json.containsKey("TCON")){cycle = json["TCON"];} //if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, cycle), cycle);  EEPROM.commit();};} // EEPROM
//       else if (json.containsKey("SGRA")){selectColor = json["SGRA"];   dir1=1;    ymax4 = pgm_read_byte(&selectColor_data[selectColor].ymax4);  ymin4 = pgm_read_byte(&selectColor_data[selectColor].ymin4);   setDifference = pgm_read_byte(&selectColor_data[selectColor].setDifference);    yval1=ymin4;   dir0=1;   if (effect_function == *rainbow_3){setDifference = 4;  }}
//       else if (json.containsKey("SPAL")){gCurrentPaletteNumber = json["SPAL"]; gTargetPalette =( gGradientPalettes[gCurrentPaletteNumber] );}
//       else if (json.containsKey("SCAR")){arrayn = json["SCAR"];     selectcolorArray();    newColors++;}  // THIS ONE
      
//       else if (json.containsKey("SDIF")){setDifference = json["SDIF"]; fillxmasArray(); diffbeat=60000/(setDifference*4*100); diffbeat2=diffbeat/2;  setDifference2 = setDifference+5;} // diff[0]=0;     x = 1;  num = 0;        diff[1]=0;     xn = 1;    num7 = 0; }
//       else if (json.containsKey("SLSP")){changeSpeed = json["SLSP"];}
//       else if (json.containsKey("SVAR")){varON = json["SVAR"]; for (int p=0; p<10; p++){if (varON == 0){yvar[p]= 0; yvarg[p]= 0;} else {yvar[p]=yvarC[p]; yvarg[p]=yvargC[p];};};}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, varON), varON);  EEPROM.commit();};}
//       else if (json.containsKey("SCOM")){colorMode = json["SCOM"]; colorMode = colorMode-1; procesColourMode();} // memoryByte = 'c'; processChange();} // THIS ONE
//       else if (json.containsKey("SHUE")){yval = json["SHUE"]; forcedColourChange = true;}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, yval), yval);  EEPROM.commit();};}
//       else if (json.containsKey("SPGM")){programMode = json["SPGM"]; cycleT=0;  previousMillis44 = millis();  previousMillis45 = millis(); changeState();} // if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, programMode), programMode);  EEPROM.commit();};          

//         //if (json.containsKey("SPGM")){Serial.println("containsprogramMode");};//programMode = json["SPGM"]; cycleT=0;  previousMillis44 = millis();  previousMillis45 = millis(); changeState();} // if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, programMode), programMode);  EEPROM.commit();};  




//   // incomingTemp = incomingReadings.temp;
//   // incomingHum = incomingReadings.hum;
//   // incomingPres = incomingReadings.pres;
// }



 
// Callback function called when data is sent

// void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
//   Serial.println("hi I sent esp now data");
// }

// void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
//   Serial.print("\r\nLast Packet Send Status:\t");
//   Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
// }

// void receiveCallback(const uint8_t *macAddr, const uint8_t *data, int dataLen)
// // Called when data is received
// {
//   // Only allow a maximum of 250 characters in the message + a null terminating byte
//   char buffer[ESP_NOW_MAX_DATA_LEN + 1];
//   int msgLen = min(ESP_NOW_MAX_DATA_LEN, dataLen);
//   strncpy(buffer, (const char *)data, msgLen);
 
//   // Make sure we are null terminated
//   buffer[msgLen] = 0;
//   for (int i = 0; i < dataLen; i++){
//     Serial.print(buffer[i]);
//   }
// }
//void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {

// void OnDataRecv(const uint8_t * mac, const uint8_t *data, int len) {
//   Serial.println("hi i received esp now data");
// }

// void OnDataRecv(const uint8_t * mac, const uint8_t *data, int len) {
//         uint8_t byteArray[] = {};
//         memcpy(&byteArray, data, sizeof(data));
//         Serial.print("Data ESP-NOW received: ");
//         for (int i = 0; i < len; i++){
//           Serial.println(byteArray[i]);
//         }
//         // Serial.println(len);

//         DEBUG_PRINTLN(F("received JSON message from ESP-NOW: "));
//         for (int i = 0; i < len; i++){
//         //strval[i]=(char)data[i];    
//         DEBUG_PRINT((char)data[i]);
//         }
//         DEBUG_PRINTLN(" ");

//         //const uint8_t size = JSON_OBJECT_SIZE(1);
//         StaticJsonDocument<250> json;
//         DeserializationError err = deserializeJson(json, data);
//         if (err) {
//             DEBUG_PRINT(F("deserializeJson() failed with code "));
//             DEBUG_PRINTLN(err.c_str());
//             return;
//         }

//       // if (json.containsKey("SPGM")){programMode = json["SPGM"]; cycleT=0;  previousMillis44 = millis();  previousMillis45 = millis(); changeState();} // if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, programMode), programMode);  EEPROM.commit();};  
//       // if (json.containsKey("SBSM")){BriSPreset = json["SBSM"]; readBriSData(BriSPreset);}// sendProgramInfo(1);}
//       // else if (json.containsKey("SRED")){Red = json["SRED"]; loadHSV = true;}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Red), Red);  EEPROM.commit();};} 
//       // else if (json.containsKey("SGRE")){Green = json["SGRE"]; loadHSV = true;}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Green), Green);  EEPROM.commit();};}   
//       // else if (json.containsKey("SBLU")){Blue = json["SBLU"]; loadHSV = true;}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Blue), Blue);  EEPROM.commit();};}
      
//       // else if (json.containsKey("SPST")){selectedPreset[programMode] = json["SPST"]; selectedPresetVariable = selectedPreset[programMode];}// cycleT=0;  previousMillis44 = millis();  previousMillis45 = millis();  if (saveToEEPROM){int offsetPosition = offsetof(storeInEEPROM, selectedPreset[0]); EEPROM.put((offsetPosition + programMode), selectedPresetVariable);  EEPROM.commit();} changeState();}
//       // else if (json.containsKey("TCON")){cycle = json["TCON"];} //if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, cycle), cycle);  EEPROM.commit();};} // EEPROM
//       // else if (json.containsKey("SGRA")){selectColor = json["SGRA"];   dir1=1;    ymax4 = pgm_read_byte(&selectColor_data[selectColor].ymax4);  ymin4 = pgm_read_byte(&selectColor_data[selectColor].ymin4);   setDifference = pgm_read_byte(&selectColor_data[selectColor].setDifference);    yval1=ymin4;   dir0=1;   if (effect_function == *rainbow_3){setDifference = 4;  }}
//       // else if (json.containsKey("SPAL")){gCurrentPaletteNumber = json["SPAL"]; gTargetPalette =( gGradientPalettes[gCurrentPaletteNumber] );}
//       // else if (json.containsKey("SCAR")){arrayn = json["SCAR"];     selectcolorArray();    newColors++;}  // THIS ONE
      
//       // else if (json.containsKey("SDIF")){setDifference = json["SDIF"]; fillxmasArray(); diffbeat=60000/(setDifference*4*100); diffbeat2=diffbeat/2;  setDifference2 = setDifference+5;} // diff[0]=0;     x = 1;  num = 0;        diff[1]=0;     xn = 1;    num7 = 0; }
//       // else if (json.containsKey("SLSP")){changeSpeed = json["SLSP"];}
//       // else if (json.containsKey("SVAR")){varON = json["SVAR"]; for (int p=0; p<10; p++){if (varON == 0){yvar[p]= 0; yvarg[p]= 0;} else {yvar[p]=yvarC[p]; yvarg[p]=yvargC[p];};};}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, varON), varON);  EEPROM.commit();};}
//       // else if (json.containsKey("SCOM")){colorMode = json["SCOM"]; colorMode = colorMode-1; procesColourMode();} // memoryByte = 'c'; processChange();} // THIS ONE
//       // else if (json.containsKey("SHUE")){yval = json["SHUE"]; forcedColourChange = true;}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, yval), yval);  EEPROM.commit();};}
//       // else if (json.containsKey("SPGM")){programMode = json["SPGM"]; cycleT=0;  previousMillis44 = millis();  previousMillis45 = millis(); changeState();} // if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, programMode), programMode);  EEPROM.commit();};  
//       return;
//   //memcpy(&myData, incomingData, sizeof(myData));
//   // Serial.print("Data received: ");
//   // Serial.println(len);
//   // Serial.print("Character Value: ");
//   // Serial.println(myData.a);
//   // Serial.print("Integer Value: ");
//   // Serial.println(myData.b);
//   // Serial.print("Float Value: ");
//   // Serial.println(myData.c);
//   // Serial.print("Boolean Value: ");
//   // Serial.println(myData.d);
//   // Serial.println();
// }

// Timing properties
#define interval1 50 // pixel swap
#define interval2 60000 // sparkling
#define interval3 30000 // omgerdraaid
#define interval4 45000 // omgedraaid regenboog
#define interval5 15 // reverse pfixelswap
#define interval6 10 // reverse pixelswap
#define interval7 35000 // pause en slinger verandering at snow 65000
#define interval9 35000 // sparke modus 6 sparkling used to b 35000
#define interval8 600000 // sF factor 

#include "global_variables.h"
#include "palettes.h"

// Setup functions. Setup_func.h
void SerialMonitor();

void serialMonitor();
void oledDisplay();
void spiffs();
void eeprom();
void initializeEEPROM();
void printEEPROM();
void wifi();
void espNow();
void LED_properties();
void initialize_preset();
void seedRandomNumbers();
void endSetup();

// SHORT DESCRIPTION AND INITIALIZATION OF THE FUNCTIONS. Project has not been been copied to VSC, but should work with this layout.
// initialize EEPROM variables Global variables at the bottom.
void initializeEEPROMvariables();

// functions: IR data and further processing IR_func.h
void initIR(); // enables IR pin and incoming messages
void handleIR(); // decodes IR signal to HEX
void handleEspNowMessage();
void decodeIR(uint32_t code); // processes HEX, via decode IR47 (HEX to a byte) and calls processchange
void decodeIR47(uint32_t code);
void processChange (); // has it's own header file. Processes byte values from decodeIR47. This is done this way because of older versions with arduino MEGA.

// functions: update oled & WS. update_OLED_WS.h
void handleProgramTimer();
void handleCycleTimer();
void displayOled();
void updateOled(byte xAxis, byte yAxis, uint8_t* variable);
void updateOledFloat(byte xAxis, byte yAxis, float* variable, int decimal);

// functions: brightness or 'glow' modes. Bri_Sat_Settings.h
void handleBrightnessSettings();
void handleSaturationSettings();

// functions: handles all the preset cases. Preset_modes.h. Contains all kinds of sub-void functions, likely junk-code which can probably be removed, but it works..
void handleLEDSettings();
void handleGlitter();

// initializes modes when mode is changed. Change_preset.h
void handleModeSwitch();
void changeState();
void handleModeInitialization();
void handleWebsocketUpdate();
void enableMode();

// functions: inilizes arrays or modifies variables. colour_Func.h
void changePColors();
void fillxmasArray();
void initializeGlitter();
void loadPersonalSettings();
void saveCurrentPresetToEEPROM();
void saveCurrentBriSPresetToEEPROM();
void saveCycleParamToEEPROM();
void fillArrayRainbow(uint8_t fillcase);
//void fillRainbow2(uint16_t arrayType[], uint8_t fillcase);
void fillArrayGradient(uint8_t fillcase, uint8_t y0r, int setDifference);
void fillLongxArray(uint8_t colour, uint16_t num_leds);
void fillColourArray (uint8_t colour[], uint8_t mainColour, int var[], int diff[]);
void fillNUM_LEDS1(uint8_t arrayType[], int NUM_LEDS);
//void receivedSignal();
void selectcolorArray();
void handleAdditionalVariables();
uint8_t changeColourFcn(int colorMode, uint8_t* yvIn, uint8_t yvalmin, uint8_t yvalmax);
uint8_t changeColourFcn2(int colorMode, uint8_t* yvIn, uint8_t* yvMem, uint8_t yvalmin, uint8_t yvalmax);
uint8_t fadeFnc(uint8_t* value, uint8_t* valueTo);
void procesColourMode();
// used in twinkle MODE. 
CRGB makeBrighter( const CRGB& color, fract8 howMuchBrighter); 
CRGB makeDarker( const CRGB& color, fract8 howMuchDarker);
bool getPixelDirection( uint16_t i);
void setPixelDirection( uint16_t i, bool dir);
void brightenOrDarkenEachPixel( fract8 fadeUpAmount, fract8 fadeDownAmount);
void colortwinkles();

//all the effectFunctions
void static_glow(void); 
void rainbow_1(void); 
void rainbow_2(void); 
void s7_strings(void);

void s7_strings_2(void);

void snow_flakes(void); 

void snow_flakes2(void);

void rainbow_4(void); 
void sparkling(void); 
void snow_storm(void);
void rainbow_3(void); 
void random_led(void);
void pers_color(void);
void random_string(void); 
void rainbow_5(void); 
void twinkle(void); 
void static_glow_2(void); 
void colourSplash(void); 
void sparkling_2(void); 
void meteor(void); 
void snow_flakes_2(void); 
void rainbow_7(void);
void gradient(void); 
void rainbow_6(void); 
void pers_block(void); 
void xmas_string(void);
void xmas_singles(void); 
void xmas_solid(void); 
void demo100(void); 
void splash(void);
void strobe(void);
void palettes(void); 
void palettes_2(void); 
void sparklingR(void); 
void RGBmode(void); 
void snow_flakesR(void); 

// webserver files defined in "websocket.h"
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
void processWebSocketMessage(String str, int dataVar);
void processWebSocketMessageS(String str, int stringLength, String dataString);
void notifyClients();
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);
//void OnDataRecv(const uint8_t * mac, const uint8_t *data, int len);
//void receiveCallback(const uint8_t *macAddr, const uint8_t *data, int dataLen);

void notifyClientsSingleObject(String object, boolean value);
void notifyClientsSingleObjectByte(String object, byte value);
void notifyClientsSingleObjectInt(String object, uint32_t value);
void notifyClientsSingleObjectSignedInt(String object, int32_t value);
void notifyClientsSingleString(String object, String &message);
void sendProgramInfo(byte message);
void writeStringToEEPROM(int addrOffset, const String &strToWrite);
void writeMacTooEEPROM(uint8_t mac);

void sendMessageToClient(int dataVar);
void initWebSocket();
void onRootRequest(AsyncWebServerRequest *request);
void initWebServer();
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
void saveEverythingToEEPROM();
void ActiveModesToEEPROM();
void DeactiveModesToEEPROM();
void readBriSData(byte preset);

#include "Change_preset.h"
#include "Bri_Sat_Settings.h"
#include "colour_Func.h"
#include "Preset_modes.h"
#include "IR_func.h"
#include "Setup_func.h"
#include "Update_OLED_WS.h"
#include "websocket.h"

void setup() {
serialMonitor();
oledDisplay();
spiffs();
eeprom();
initializeEEPROM();
wifi();
espNow();
LED_properties();
initialize_preset();
seedRandomNumbers();
endSetup();
} 

void loop() {
ws.cleanupClients();
handleEspNowMessage();
handleIR();
handleProgramTimer(); // contains display.display function. Printing to the OLED display, even tiny bits of text, take about 29000 micro seconds (29ms). 
handleCycleTimer(); 
handleModeSwitch();
handleModeInitialization();
handleBrightnessSettings();
handleSaturationSettings();
handleAdditionalVariables();
handleLEDSettings();
handleIR(); 
handleWebsocketUpdate();
}

void handleEspNowMessage(){
  if (espNowMessage){

  DynamicJsonDocument doc(250);
  switch (EspNowMessageType){
    case 0:    {
                doc["SPGM"] = programMode;
                doc["SPST"] = selectedPresetVariable;
                doc["TCON"] = false;
    } break;
    case 1:    {doc["SBSM"] = BriSPreset;}break;
    case 2:    {doc["SHUE"] = yval;}  break;
    case 3:    {doc["SCOM"] = colorMode;}  break;
    case 4:    {doc["SVAR"] = varON;}  break;
    case 5:    {doc["SDIF"] = setDifference;}  break;
    case 6:    {doc["SLSP"] = changeSpeed;}  break;
    case 7:    {doc["SCAR"] = arrayn;}  break;
    case 8:    {doc["SPAL"] = gCurrentPaletteNumber;}  break;
    case 9:    {doc["SGRA"] = selectColor;}  break;
    case 10:   {
                doc["SRED"] = Red;
                doc["SGRE"] = Green;
                doc["SBLU"] = Blue;
    } break;
  }   
                                        
    char data[250]; // 250
    size_t len = serializeJson(doc, data);

        DEBUG_PRINT(F("sending JSON message: ")); DEBUG_PRINTLN(len);
        for (int i = 0; i < len;  i++){
        DEBUG_PRINT(data[i]);
        }
        DEBUG_PRINTLN(" ");

      //for (int i = 0; i < num_esp; i++){
        //uint8_t broadcastAddress[6] = {Mac[i*6], Mac[(i*6)+1], Mac[(i*6)+2], Mac[(i*6)+3], Mac[(i*6)+4], Mac[(i*6)+5]};
        //Serial.println(broadcastAddress[i]);
        esp_now_send(NULL, (uint8_t *) &data, len);
      //}
  }

  // BME280Readings.temp = random(255);
  // BME280Readings.hum = random(255);
  // BME280Readings.pres = random(255);
  
  // for (int i = 0; i < num_esp; i++){
  // uint8_t broadcastAddress[6] = {Mac[i*6], Mac[(i*6)+1], Mac[(i*6)+2], Mac[(i*6)+3], Mac[(i*6)+4], Mac[(i*6)+5]};
  // esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &BME280Readings, sizeof(BME280Readings));
   
  // if (result == ESP_OK) {
  //   Serial.println("Sent with success");
  // }
  // else {
  //   Serial.println("Error sending the data");
  // }
  // espNowMessage = false;
  // }

espNowMessage = false;

// }
}




