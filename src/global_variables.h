/*
 * All the variables that are used. Most are defined globally. Some variables can be likely be grouped. I might cleans it up more one day.
 */

typedef void (*effect_f) (void);  // This is type definition for the pointertype...

effect_f effect_function = NULL; // This is the pointer variable used to remember pointer to function()

const char string_0[] PROGMEM = "static_glow"; 
const char string_1[] PROGMEM = "var_glow"; 
const char string_2[] PROGMEM = "warm_glow";
const char string_3[] PROGMEM = "reflection"; 
const char string_4[] PROGMEM = "deflection";
const char string_5[] PROGMEM = "coloursplash";
const char string_6[] PROGMEM = "palette";
//const char string_7[] PROGMEM = "colourwash"; 
const char string_7[] PROGMEM = "rainbow_1";
const char string_8[] PROGMEM = "rainbow_2";
const char string_9[] PROGMEM = "rainbow_3";
const char string_10[] PROGMEM = "rainbow_4";
const char string_11[] PROGMEM = "rainbow_5";
const char string_12[] PROGMEM = "rainbow_6";
const char string_13[] PROGMEM = "rainbow_7"; 
const char string_14[] PROGMEM = "gradient";
const char string_15[] PROGMEM = "7strings";
const char string_16[] PROGMEM = "7s_v2";
const char string_17[] PROGMEM = "7s_mirror";
const char string_18[] PROGMEM = "halcyon";
const char string_19[] PROGMEM = "snow";
const char string_20[] PROGMEM = "snow_v2"; 
const char string_21[] PROGMEM = "snow_pile";
const char string_22[] PROGMEM = "snow_storm";
const char string_23[] PROGMEM = "snow_rainbow"; 
const char string_24[] PROGMEM = "snow_mirror";
const char string_25[] PROGMEM = "sparkle";
const char string_26[] PROGMEM = "sparkle_storm";
const char string_27[] PROGMEM = "sparkle_rainbow"; 
const char string_28[] PROGMEM = "twinkle";
const char string_29[] PROGMEM = "casino";
//const char string_28[] PROGMEM = "casino";
const char string_30[] PROGMEM = "fine_canvas";
const char string_31[] PROGMEM = "rough_canvas"; 
const char string_32[] PROGMEM = "xmas_1"; 
const char string_33[] PROGMEM = "xmas_2"; 
//const char string_33[] PROGMEM = "xmas_3";
const char string_34[] PROGMEM = "splash";
const char string_35[] PROGMEM = "strobe";
const char string_36[] PROGMEM = "meteor"; 
const char string_37[] PROGMEM = "RGBmode";

const char *const string_table[] PROGMEM = {string_0, string_1, string_2, string_3, string_4, string_5, string_6, string_7, string_8, string_9, string_10, 
                                            string_11, string_12, string_13, string_14, string_15, string_16, string_17, string_18, string_19, string_20, 
                                            string_21, string_22, string_23, string_24, string_25, string_26, string_27, string_28, string_29, string_30, 
                                            string_31, string_32, string_33, string_34, string_35, string_36, string_37};

char buffer[30];  // make sure this is large enough for the largest string it must hold                                        
const int modeCount = (sizeof(string_table)/sizeof(string_table[0])); //  
boolean cmode[modeCount]={0};

struct storeInEEPROM {
  int check;
  char ssidStorage[32];
  char passStorage[32]; 
  uint8_t emptybyte; // secures ymin;
  uint8_t ymin;
  uint8_t ymax;
  uint8_t ymin1;
  uint8_t ymax1;
  uint8_t yminrood;
  uint8_t ymaxrood;
  uint8_t ymingroen;
  uint8_t ymaxgroen;
  uint8_t yminblauw;
  uint8_t ymaxblauw;
  boolean cmode[modeCount];
  boolean glitterON[modeCount];
  boolean glitterON2[modeCount];
  boolean glitterON3[modeCount];
  const byte rgbcolor;
  boolean cycle;
  boolean fadeFirst;
  boolean randomCycle;
  boolean excludeModes;
  //boolean personalizedModes;
  byte selectedPreset[modeCount];
  uint32_t cycleTime[modeCount];
  byte programMode;
  boolean tower;
  byte z5;
  byte Red;
  byte Green;
  byte Blue;
  byte yval;
  byte yval2;
  byte yval3;
  byte yvalm2;
  byte yvalm22;
  byte yvalm23;
  byte yvalm3;
  byte yvalm32;
  byte yvalm33;
  byte colorlengthm[3];
  byte colorlengthm2[3];
  byte colorlengthm3[3];
  byte varONglobal; 
  byte BRIGH[26];
  byte offBr[26];
  byte glowON[26];
  byte BrF[26];
  byte offS[26];
  byte S[26]; 
  byte SF[26];
  byte satON[26];
  byte numsat[26];
  byte numbrigh[26];
  byte BPMB[26];
  byte BPMS[26];
  uint32_t waveTimeBr[26];
  uint32_t waveTimeS[26];
  float timefactor3[modeCount];
  byte numsparks[modeCount];
  byte numsparks2[modeCount];
  byte numsparks3[modeCount];
  boolean Bees; 
  boolean varNumbrigh;
  boolean varBPMB;
  boolean varNumsat;
  boolean varBPMS;
  uint8_t ymin2;
  uint8_t ymax2;
  uint8_t ymin3;
  uint8_t ymax3;
  uint8_t ymin4;
  uint8_t ymax4;  
  uint8_t range;
  byte gCurrentPaletteNumber; 
  byte gCurrentPaletteNumber2; 
  byte gCurrentPaletteNumber3; 
  byte offdisC;
  byte numcolor1;
  byte numcolor12;
  byte numcolor13;
  byte numcolor2;
  byte numcolor22;
  byte numcolor23; 
  uint8_t BriSPreset[modeCount];
  uint8_t BriSPreset2[modeCount];
  uint8_t BriSPreset3[modeCount];
  unsigned long changeSpeed[modeCount];
  unsigned long changeSpeed2[modeCount];
  unsigned long changeSpeed3[modeCount];
  int setDifference[modeCount];
  int setDifference2[modeCount];
  int setDifference3[modeCount];
  int colorMode[modeCount];
  int colorMode2[modeCount];
  int colorMode3[modeCount];
  byte arrayn[modeCount];
  byte arrayn2[modeCount];
  byte arrayn3[modeCount];
  byte varON[modeCount];
  byte varON2[modeCount];
  byte varON3[modeCount];
  int NUM_LEDS;
  uint8_t num_esp;
  uint8_t Mac[60];  
  // uint8_t mac2[6]; 
  // uint8_t mac3[6]; 
  // uint8_t mac4[6]; 
  // uint8_t mac5[6]; 
  // uint8_t mac6[6]; 
  // uint8_t mac7[6]; 
  // uint8_t mac8[6]; 
  // uint8_t mac9[6]; 
  // uint8_t mac10[6]; 
};

byte RGBCOLOR = 0;

storeInEEPROM customVar = {
      // LARGE CHRISTMAS TREE
      // 22225, // code to check
      // 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, // ssid storage
      // 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, // pass storage
      // 1, // empty byte so ymin loads correctly
      // 42, // ymin
      // 85, // ymax
      // 87, // ymin1
      // 206, // ymax1
      // 245, // yminrood
      // 10, // ymaxrood
      // 55, // ymingroen
      // 115,// ymaxgroen
      // 145, // yminblauw
      // 180, // ymaxblauw
      // 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // cmodes (1 = active)
      // 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      // 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
      // 1, 1, 1, 1, 1, 1, 0, 0,
      // 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // glitterON (1 = active)
      // 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      // 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      // 0, 1, 1, 1, 0, 0, 0, 0,
      // 0, // rgb
      // 1, // cycle
      // 1, // fade 
      // 1, // random
      // 1, // excludemodes
      // 1, // personalizedModes
      // 600000, 240000, 600000, 150000, 300000,   240000, 600000, 150000, 60000, 60000, // cycleTime
      // 60000, 60000, 60000, 120000, 180000,      240000, 120000, 300000, 240000, 180000,
      // 300000, 120000, 540000, 60000, 60000,     60000, 20000, 30000, 20000, 180000, 
      // 240000, 120000, 120000, 120000, 60000,    10000, 60000, 30000,
      // 0, // programMode      
      // 0, // tower
      // 92, // z5
      // 62, // red
      // 25, // green
      // 6, // blue
      // 5, // yval
      // 18, // yvalm2
      // 217, // yvalm3
      // 20, 16, 10, // colorLength rainbow_6, random_string, pers_block
      // 1, // varON 
      // 205, 155, 205, 194, 205,         205, 205, 202, 202, 150,          202, 205, 136, 106, 205,         205, 205, 205, 205, 205,            205, 205, 194, 175, 255, 75,// BRIGH          position 0 is global variable
      // 30, 34, 35, 43, 40,              19, 40, 59, 60, 50,               1, 1, 93, 18, 35,                175, 90, 175, 74, 79,                45, 35, 43, 24, 0, 0, // offBr               position 0 is global variable
      // 2, 2, 2, 5, 5,                   2, 6, 3, 3, 3,                    3, 3, 4, 2, 8,                   6, 6, 6, 3, 3,                      8, 8, 5, 2, 0, 0,  // glowON                  position 0 is global variable
      // 50, 50, 50, 70, 55,              50, 0, 50, 0, 0,                  50, 50, 110, 110, 0,             0, 0, 0, 50, 50,                    50, 50, 50, 0, 0, 0, // BrF                position 0 is global variable
      // 35, 35, 35, 20, 54,              45, 160, 30, 112, 35,             30, 35, 45, 35, 56,              28, 142, 85, 45, 45,                35, 35, 20, 121, 35, 35,  // offS               position 0 is global variable
      // 250, 255, 255, 162, 200,         200, 200, 202, 248, 250,          255, 255, 200, 145, 200,         200, 200, 200, 200, 200,            200, 255, 161, 216, 255, 255,  // S            position 0 is global variable
      // 0, 0, 0, 50, 0,                  50, 0, 0, 0, 0,                   0, 0, 0, 50, 40,                 0, 40, 0, 0, 50,                    0, 0, 0, 0, 0, 0,  // Sf                     position 0 is global variable
      // 0, 0, 0, 5, 5,                   5, 3, 0, 4, 0,                    0, 0, 5, 0, 6,                   6, 4, 6, 5, 2,                      5, 0, 5, 4, 0, 0,  // satOn was 3             position 0 is global variable
      // 31, 31, 31, 32, 9,               31, 31, 31, 250, 31,              31, 31, 31, 31, 28,              30, 250, 28, 31, 31,                31, 31, 32, 250, 31, 31, // numsat             position 0 is global variable
      // 16, 13, 31, 13, 12,              13, 12, 29, 250, 10,              10, 255, 13, 13, 32,             28, 13, 31, 250, 250,               11, 29, 13, 13, 10, 10, // numbrigh           position 0 is global variable
      // 30, 30, 51, 30, 30,              20, 30, 12, 12, 20,               12, 10, 30, 30, 20,              60, 30, 60, 54, 48,                 45, 51, 30, 20, 0, 0,  // BPMB              position 0 is global variable
      // 30, 30, 30, 39, 60,              30, 45, 20, 15, 30,               20, 30, 60, 30, 60,              60, 60, 60, 60, 20,                 60, 30, 39, 52, 30, 30,  // BPMS               position 0 is global variable
      // 2000, 2000, 6000, 2000, 2000,    2000, 20000, 5000, 5000, 3000,    5000, 6000, 2000, 2000, 3000,    30000, 2000, 30000, 12000, 11000,    1333, 6000, 2000, 3000, 2000, 2000, // waveTimeBr           position 0 is global variable
      // 2000, 2000, 2000, 1538, 1000,    2000, 1333, 5000, 15000, 2000,     5000, 2000, 1000, 2000, 1000,    1000, 1000, 30000, 1000, 3000,      1000, 2000, 1538, 25000, 2000, 2000, // waveTimeS            position 0 is global variable
      // 1.00, 1.00, 1.00, 1.00, 1.00,     1.00, 1.00, 1.00, 1.00, 1.00, // timefactor3
      // 1.00, 1.00, 1.00, 1.00, 1.00,     1.00, 1.00, 1.00, 1.00, 1.00,
      // 1.00, 0.25, 1.00, 1.00, 1.00,     1.00, 1.00, 1.00, 1.00, 1.00, 
      // 1.00, 1.00, 1.00, 1.00, 1.00,     1.00, 1.00, 1.00,
      // 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, // numsparks
      // 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
      // 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
      // 10, 10, 10, 10, 10, 10, 10, 10,
      // 0, // Bees
      // 0, // varNumbrigh 
      // 0, //varBPMB  
      // 0, // varNumsat
      // 0, // varBPMS  
      // 122, // ymin2
      // 241, // ymax2
      // 110, // ymin3
      // 25, // ymax3
      // 248, // ymin4
      // 47, // ymax4
      // 60, // range
      // 7, // FastLDPalet;
      // 14, // offdisC
      // 3, //numcolor1 pers_color
      // 15, //numcolor2 pers_block
      // 22, 23, 23, 0, 0, 3, 11, 0, 10, 2, // uint8_t BriSpreset
      // 4, 0, 0, 0, 0, 6, 0, 0, 0, 0, 
      // 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 
      // 0, 0, 0, 0, 0, 0, 0, 0,
      // 100, 100, 100, 100, 100, 35, 50, 50, 20, 30, // unsigned long changeSpeed
      // 100, 200, 30, 1500, 100, 200, 110, 110, 110, 125, 
      // 125, 130, 125, 130, 135, 130, 30, 30, 2000, 2000, 
      // 1000, 200, 100, 40, 30, 20, 50, 50,
      // 7, 7, 7, 80, 80, 7, 1, 45, 1, 4, // int setDifference
      // 4, 7, 5, 25, 1, 1, 10, 15, 95, 7, 
      // 7, 7, 7, 7, 7, 7, 255, 40, 1, 1, 
      // 1, 7, 7, 7, 40, 40, 10, 1,
      // 0, 0, 0, 0, 1, 2, 1, 1, 0, 0, // int colorMode
      // 0, 0, 0, 0, 0, 0, 4, 4, 4, 4,
      // 1, 1, 0, 2, 1, 0, 4, 5, 1, 4, 
      // 1, 1, 1, 1, 5, 1, 2, 0,
      // 1, 1, 1, 1, 1, 1, 1, 1, 7, 7, // byte arrayn
      // 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
      // 1, 1, 1, 1, 1, 1, 1, 1, 1, 25, 
      // 4, 1, 1, 1, 1, 0, 0, 0,
      // 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // varON byte
      // 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      // 1, 1, 2, 1, 1, 1, 2, 1, 1, 0, 
      // 2, 1, 1, 1, 1, 1, 1, 1,
      // 50 // NUM_LEDS   

    // SMALL CHRISTMAS TREE
      11442, // code to check
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, // ssid storage
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, // pass storage
      1, // empty byte so ymin loads correctly
      42, // ymin
      85, // ymax
      87, // ymin1
      206, // ymax1
      245, // yminrood
      10, // ymaxrood
      55, // ymingroen
      115,// ymaxgroen
      145, // yminblauw
      180, // ymaxblauw
      // cmodes (1 = active)
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // cmodes (1 = active)
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
      1, 1, 1, 1, 1, 1, 1, 1,
      
      // glitterON (1 = active)
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // glitterON (1 = active)
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 1, 1, 1, 0, 0, 0, 0,
      
      // glitterON2 (1 = active)
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // glitterON2 (1 = active)
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 1, 1, 1, 0, 0, 0, 0,
      
      // glitterON3 (1 = active)
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // glitterON3 (1 = active)
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 1, 1, 1, 0, 0, 0, 0,
      0, // rgb
      1, // cycle
      1, // fade 
      1, // random
      1, // excludemodes
      //0, // personalizedModes
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, // selectedPreset
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
      4, 4, 4, 4, 4, 4, 4, 4, 
      300000, 240000, 300000, 150000, 300000,   240000, 600000, 150000, 180000, 180000, // cycleTime
      120000, 60000, 120000, 120000, 180000,    240000, 120000, 300000, 240000, 180000,
      300000, 300000, 300000, 300000, 300000,   300000, 200000, 60000, 120000, 180000, 
      240000, 120000, 120000, 120000, 120000,   150000, 450000, 60000,
      0, // programMode      
      0, // tower
      92, // z5
      0, // red
      0, // green
      7, // blue

      245, // yval
      8, // yval2
      5, // yval3

      18, // yvalm2
      18, // yvalm22
      18, // yvalm23

      198, // yvalm3
      198, // yvalm32
      198, // yvalm33

      20, 50, 10, // colorLength rainbow_6, random_string, pers_block
      25, 50, 10, // colorLength rainbow_6, random_string, pers_block
      20, 50, 10, // colorLength rainbow_6, random_string, pers_block

      1, // varON 
      205, 155, 205, 194, 205,         205, 205, 202, 202, 150,          255, 205, 136, 106, 205,         205, 205, 205, 205, 205,            205, 205, 194, 175, 255, 75,// BRIGH          position 0 is global variable
      36, 34, 35, 43, 40,              19, 40, 59, 60, 50,               1, 1, 93, 18, 35,                175, 90, 175, 74, 79,                45, 35, 43, 24, 0, 0, // offBr               position 0 is global variable
      2, 2, 2, 5, 5,                   2, 6, 3, 3, 6,                    3, 3, 4, 2, 8,                   6, 6, 6, 3, 3,                      8, 8, 5, 2, 0, 0,  // glowON                  position 0 is global variable
      50, 50, 50, 70, 55,              50, 0, 50, 0, 0,                  50, 50, 110, 140, 0,             0, 0, 0, 50, 50,                    50, 50, 50, 0, 0, 0, // BrF                position 0 is global variable
      35, 35, 35, 20, 80,              45, 160, 30, 112, 35,             30, 35, 45, 35, 56,              28, 142, 85, 45, 45,                35, 35, 20, 1, 115, 35,  // offS               position 0 is global variable
      250, 255, 255, 185, 225,         200, 200, 202, 248, 250,          255, 248, 200, 145, 200,         200, 200, 200, 200, 200,            200, 255, 161, 216, 248, 255,  // S            position 0 is global variable
      0, 0, 0, 50, 0,                  50, 0, 0, 0, 0,                   0, 0, 0, 110, 40,                 0, 40, 0, 0, 50,                    0, 0, 0, 0, 0, 0,  // Sf                     position 0 is global variable
      0, 0, 0, 5, 5,                   5, 3, 0, 4, 0,                    0, 0, 5, 0, 6,                   6, 4, 6, 5, 2,                      5, 0, 5, 4, 4, 0,  // satOn was 3             position 0 is global variable
      31, 31, 31, 32, 9,               31, 31, 31, 250, 31,              31, 31, 31, 31, 28,              30, 250, 28, 31, 31,                31, 31, 32, 250, 100, 31, // numsat             position 0 is global variable
      16, 13, 31, 13, 12,              13, 12, 29, 250, 100,             100, 255, 13, 13, 32,             28, 13, 31, 250, 250,               11, 29, 13, 13, 10, 10, // numbrigh           position 0 is global variable
      30, 30, 51, 30, 30,              20, 30, 12, 12, 20,               12, 10, 30, 30, 20,              60, 30, 60, 54, 48,                 45, 51, 30, 20, 0, 0,  // BPMB              position 0 is global variable
      30, 30, 30, 39, 60,              30, 45, 20, 15, 30,               20, 30, 60, 30, 60,              60, 60, 60, 60, 20,                 60, 30, 39, 52, 60, 30,  // BPMS               position 0 is global variable
      2000, 2000, 6000, 2000, 2000,    2000, 20000, 5000, 5000, 3000,    5000, 6000, 2000, 2000, 3000,    30000, 2000, 30000, 12000, 11000,    1333, 6000, 2000, 3000, 2000, 2000, // waveTimeBr           position 0 is global variable
      2000, 2000, 2000, 1538, 1000,    2000, 1333, 5000, 15000, 2000,     5000, 2000, 1000, 2000, 1000,    1000, 1000, 30000, 1000, 3000,      1000, 2000, 1538, 25000, 28000, 2000, // waveTimeS            position 0 is global variable
      1.00, 0.25, 1.00, 1.00, 1.00,     1.00, 1.00, 1.00, 1.00, 1.00, // timefactor3
      1.00, 1.00, 1.00, 1.00, 1.00,     1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 0.25, 1.00, 0.50, 0.50,     0.25, 1.00, 1.00, 1.00, 0.25, 
      0.25, 1.00, 1.00, 1.00, 1.00,     1.00, 1.00, 1.00,
      
      // numsparks
      10, 10, 10, 10, 10, 10, 10, 10, 10, 10, // numsparks
      10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
      10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
      10, 10, 10, 10, 10, 10, 10, 10,
      
      // numsparks2
      10, 10, 10, 10, 10, 10, 10, 10, 10, 10, // numsparks2
      10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
      10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
      10, 10, 10, 10, 10, 10, 10, 10,
      
      // numsparks3
      10, 10, 10, 10, 10, 10, 10, 10, 10, 10, // numsparks3
      10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
      10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
      10, 10, 10, 10, 10, 10, 10, 10,
      0, // Bees
      0, // varNumbrigh 
      0, //varBPMB  
      0, // varNumsat
      0, // varBPMS  
      122, // ymin2
      241, // ymax2
      110, // ymin3
      25, // ymax3
      248, // ymin4
      47, // ymax4
      60, // range

      7, // FastLDPalet;
      7, // FastLDPalet2;
      7, // FastLDPalet3;

      14, // offdisC

      3, //numcolor1 pers_color
      3, //numcolor1 pers_color2
      3, //numcolor1 pers_color3
      
      15, //numcolor2 pers_block
      15, //numcolor2 pers_block2
      15, //numcolor2 pers_block3
      
      // uint8_t BriSpreset
      22, 7, 9, 14, 21,    24, 11,  10, 21,     14, 10, 0, 11, 24,    0, 2, 0, 2, 14, 3, 3,     23, 13, 0, 3, 0, 0,    0, 0, 21,  8,     0, 24, 0,  0,    0, 0, 0,  
      
      // uint8_t BriSpreset2
      7, 3, 1, 16, 8,    1, 11,  2, 7,     8, 6, 10, 8, 7,     0, 0, 0, 0, 10, 2, 2,    12, 12, 14, 2, 0, 0,     0, 0, 10,  8,     0, 24, 0,  0,    0, 0, 0,  
      
      // uint8_t BriSpreset3
      3, 10, 3, 22, 7,     3, 11,  18, 20,     10, 14, 24, 14, 8,    0, 0, 0, 0, 18, 2, 2,     6, 14, 10, 2, 0, 0,    0, 0, 15,  8,     0, 24, 0,  0,     19, 0, 0,  
      
      // unsigned long changeSpeed
      100, 100, 100, 100, 100,     35, 50,  20, 46,    100, 70, 108, 61, 100,      200, 20, 20, 20, 124, 125, 125,    125, 130, 125, 125, 130, 135,       130, 30, 30,   2000,       1000, 200, 100,  30,       35, 50, 50,  
      
      // unsigned long changeSpeed2
      100, 100, 100, 100, 100,       35, 50,  20, 46,       100, 70, 108, 189, 100,       200, 20, 110, 20, 110, 125, 125,       125, 130, 125, 125, 130, 135,       130, 70, 30,  2000,       1000, 200, 100,  30,      10, 50, 50,  
      
      // unsigned long changeSpeed3
      100, 100, 100, 100, 100,       35, 50,  20, 46,      100, 70, 108, 53, 100,       200, 40, 30, 40, 110, 125, 125,       125, 130, 125, 125, 130, 135,      130, 70, 30,  2000,       1000, 200, 100,  30,       15, 50, 50,  

      // int setDifference
      7, 7, 7, 78, 80,       7, 1,  1, 2,       4, 7, 2, 25, 1,      1, 10, 6, 10, 147, 7, 7,       7, 7, 1, 7, 7, 7,      7, 200, 40,  1,       1, 7, 7,  40,      5, 3, 1,
      
      // int setDifference2
      7, 7, 7, 78, 80,      7, 1,  1, 2,      4, 7, 2, 25, 1,       1, 1, 6, 1, 95, 7, 7,      7, 7, 1, 7, 7, 7,       7, 255, 40,  1,       1, 7, 7,  40,       15, 10, 1,
      
      // int setDifference3
      1, 7, 1, 78, 80,       7, 1,  1, 2,       4, 7, 2, 25, 1,       1, 10, 6, 10, 95, 7, 7,      7, 7, 1, 7, 7, 7,      7, 255, 40,  1,       1, 7, 7,  40,       20, 10, 1,  

      // int colorMode
      0, 2, 0, 0, 1,      2, 1,  0, 0,       0, 0, 0, 0, 0,      0, 1, 5, 1, 4, 5, 5,      1, 1, 0, 5, 2, 1,      0, 4, 1,  4,       1, 1, 1,  1,      5, 1, 0,

      // int colorMode2
      0, 2, 0, 0, 1,      2, 1,  0, 0,       0, 0, 0, 0, 0,       0, 4, 1, 4, 4, 1, 1,       1, 1, 0, 1, 2, 1,      0, 5, 5,  4,      1, 1, 1,  4,      5, 5, 0,

      // int colorMode3
      0, 2, 0, 0, 1,      1, 1,  0, 0,       0, 0, 0, 0, 0,      0, 4, 4, 4, 4, 4, 4,      1, 1, 0, 4, 2, 1,      0, 1, 1,  4,       1, 1, 1,  4,      2, 4, 0,  
      
      // byte arrayn
      1, 1, 1, 1, 1,      1, 1,  7, 7,       1, 1, 1, 1, 1,       1, 0, 0, 0, 0, 0, 0,      1, 1, 1, 0, 1, 1,       1, 1, 1,  25,      4, 1, 1,  1,       0, 0, 0,
      
      // byte arrayn2
      4, 1, 1, 1, 1,      1, 1,  7, 7,       1, 1, 1, 1, 1,      1, 27, 32, 27, 0, 0, 0,       1, 1, 1, 0, 1, 1,       1, 57, 1,  25,      4, 1, 1,  27,       0, 0, 0,
      
      // byte arrayn3
      1, 52, 1, 1, 1,       1, 1,  7, 7,       1, 1, 1, 1, 1,      1, 19, 17, 19, 0, 0, 0,     1, 1, 1, 0, 1, 1,      1, 29, 1,  25,       4, 1, 1,  27,      0, 38, 0,  
      
      // varON byte
      1, 1, 1, 1, 1,       1, 1,  1, 1,      1, 1, 1, 1, 1,      1, 1, 1, 1, 1, 1, 1,      1, 1, 2, 1, 1, 1,      1, 2, 1,  2,      2, 1, 1,  1,      1, 2, 1,
      
      // varON byte
      1, 1, 1, 1, 1,       1, 1,  1, 1,      1, 1, 1, 1, 1,      1, 1, 2, 1, 1, 1, 1,       1, 1, 0, 1, 1, 1,      1, 2, 1,  2,       2, 1, 1,  1,      1, 1, 1,  
      
      // varON3 byte
      1, 1, 1, 1, 1,      0, 1,  1, 1,       1, 1, 1, 1, 1,      1, 2, 2, 2, 1, 2, 2,      1, 1, 1, 2, 1, 1,      1, 2, 1,  2,      2, 1, 1,  2,      2, 1, 1,
      50, // NUM_LEDS   
      0, // num_esp
      0, 0, 0, 0, 0, 0, //mac1
      0, 0, 0, 0, 0, 0, //mac2
      0, 0, 0, 0, 0, 0, //mac3
      0, 0, 0, 0, 0, 0, //mac4
      0, 0, 0, 0, 0, 0, //mac5
      0, 0, 0, 0, 0, 0, //mac6
      0, 0, 0, 0, 0, 0, //mac7
      0, 0, 0, 0, 0, 0, //mac8
      0, 0, 0, 0, 0, 0, //mac9
      0, 0, 0, 0, 0, 0 //mac10        
    };


struct presetBrighSat_pgm
{
  byte BRIGH;
  byte BrF;
  byte glowON;
  byte offBr;
  byte numbrigh; // numBrigh
  byte BPMB;
  uint32_t waveTimeBr;
  byte S; 
  byte SF;
  byte satON;
  byte offS;
  byte numsat; // numSat
  byte BPMS;
  uint32_t waveTimeS;
};

static const presetBrighSat_pgm selectPresetB_data[] PROGMEM = 
{
  //BRIGH,    BrF,  glowON, offBr, numbrigh, BPMB, waveTimeBr,   S,      SF,    satON,    offS,   numsat,     BPMS,    waveTimeS  
  {205,       50,   2,      30,    16,       30,   2000,         250,    0,     0,         35,    31,         30,      2000}, // 0 GLOBAL STORAGE
  {155,       50,   2,      34,    13,       30,   2000,         255,    0,     0,         35,    31,         30,      2000}, // 1 basic glow nice glow 19
  {205,       50,   2,      35,    31,       51,   6000,         255,    0,     0,         35,    31,         30,      2000}, // 2 subtle glow
  {194,       70,   5,      43,    13,       30,   2000,         161,    50,    5,         20,    32,         39,      1538}, // 3 NEW small wave less saturated
  {205,       55,   5,      40,    12,       30,   2000,         200,    0,     5,         54,     9,         60,      1000}, // 4 small wave ok
  {205,       50,   2,      19,    13,       20,   2000,         200,    50,    5,         45,    31,         20,      2000}, // 5 gradient
  {205,       0,    6,      40,    12,       30,   2000,         200,    0,     3,        160,    31,         45,      1333}, // 6 diamond perfect  
  {202,       50,   3,      59,    29,       12,   5000,         202,    0,     0,         30,    31,         20,      5000}, // 7 NEW slow twinkle with baseine no saturation variation
  {202,       0,    3,      145,   250,      12,   5000,         250,    0,     4,         112,   250,        15,      15000}, // 8 slow_Twinkle_2
  {150,       0,    3,      50,    10,       20,   3000,         250,    0,     0,         35,    31,         30,      2000}, // 9 slow_Twinkle_r1
  {202,       50,   3,      1,     10,       12,   5000,         255,    0,     0,         30,    31,         20,      5000}, // 10 NEW rainbow 1 MODE num_color 10 for special effect
  {205,       50,   3,      1,     250,      10,   6000,         255,    0,     0,         35,    31,         30,      2000}, // 11 slow_Twinkle (black))
  {136,       110,  4,      93,    13,       30,   2000,         200,    0,     5,         45,    31,         60,      1000}, // 12 sparkle_2 16
  {106,       110,  2,      18,    13,       30,   2000,         145,    50,    0,         35,    31,         30,      2000}, // 13 sparkle_3 17 sat 255 to 145
  {205,       0,    8,      35,    32,       20,   3000,         200,    40,    6,         56,    28,         60,      1000}, // 14 long wave
  {205,       0,    6,      175,   28,       60,   30000,        200,    0,     6,         28,    30,         60,      1000}, // 15 diamond  better than 5 not nice?  
  {205,       0,    6,      90,    13,       30,   2000,         200,    40,    4,        142,    250,        60,      1000}, // 16 diamond tower NEW
  {205,       0,    6,      175,   31,       60,   30000,        200,    0,     6,         85,    28,         60,     30000}, // 17 diamond  fast twinkle (EEPROM?)
  {205,       50,   3,      74,    250,      54,   12000,        200,    0,     5,         45,    31,         60,      1000}, // 18 fast_Twinkle (baseline)
  {205,       50,   3,      79,    250,      48,   11000,        200,    50,    2,         45,    31,         20,      3000}, // 19 fast_Twinkle too fast, optimize not better than 8? 
  {205,       50,   8,      45,    11,       45,   1333,         200,    0,     5,         35,    31,         60,      1000}, // 20 wave fast twinkle 18 ROOM FOR NEW PRESET
  {205,       50,   8,      35,    29,       51,   6000,         255,    0,     0,         35,    31,         30,      2000}, // 21 fast_Twinkle fullcolor
  {194,       50,   5,      43,    13,       30,   2000,         161,    0,     5,         20,    32,         39,      1538}, // 22 neon twinkle
  {175,       82,   2,      24,    13,       20,   3000,         216,    0,     4,        121,    250,        52,     25000}, // 23 fire
  {255,       0,    0,      0,     10,       0,    0,            255,    0,     0,         35,    31,         30,      2000}, // 24 no glow
  {75,        0,    0,      0,     10,       0,    0,            255,    0,     0,         35,    31,         30,      2000} // 25 no glow low
};

//const byte rgbcolor = 1;
struct selectColorArray_pgm
{
  byte numcolor;         // numcolor
  byte colour[15];        // colour[15]
};
         
static const selectColorArray_pgm selectColor_array[] PROGMEM = 
{
            {15, 226, 243,  16,  81, 244, 244, 117, 139, 175, 193, 188, 217, 226,   9, 168,}, // 0, 1
            {15, 226, 243,  71,  81, 226, 205,  71,  91, 175, 193, 188, 217, 226,  91, 226,}, // 2
            {15,  10, 255,  16,  25, 255,  22,  15,  25,   4,   0,  10,  15, 245,   9,  35,}, // 3
            {15, 226, 243, 235, 226, 235, 217, 205, 144, 226, 193, 205, 217, 226, 193, 243,}, // 4
            {15, 135, 155, 210, 230, 190, 128, 200, 190, 230, 135, 210, 217, 230, 190, 155,}, // 5           
            {15, 226, 243,  16,  10, 244, 168,  10, 139, 210, 193, 188,  15, 244,   9, 164,}, // 6  
            {15,   0,   5,  10,  20,  40,  60,  80,  86,  95, 100, 110, 120, 130, 140, 150,}, // 7
            {10,   0,  25,  50,  75, 100, 125, 150, 175, 200, 225, 188, 217, 193, 246,   9,}, // 8             
            {5,   22,  55, 201, 239,   4, 134,  84,  50, 120,  190, 210, 236, 134, 120, 15,}, // 9
            {10,  22,  55, 201, 239,   4, 134,  84,  50, 120,  190, 210, 236, 134, 120, 15,}, // 10      
            {15,  14, 125, 180,  28, 129, 180,  14, 117, 180, 193, 188, 217, 226,   9, 168,}, // 11             
            {15,   0,  22,  37,  35,   4,  12,  41,  49,  44,  24,  33,  14,   0,  19,   6,}, // 12            
            {15,  36,   8,   4,  16,  32,   6, 238, 233, 228, 251, 229, 207, 240, 133, 108,}, // 13 108 = 122 
            {15,  55,  65,  75,  85,  95, 105, 115, 125, 135, 145, 155, 165, 175, 185, 195,},        
            {15,  32,   7,  84, 133,  19, 138, 159, 193, 193, 132,  88, 191, 188,  45,  99,}, // 15            
            {4,   92,   0, 164,  55,  92,   0, 164,  55,  92,   0, 164,  55,  92,   0, 164,}, // 
            {4,   15,  55, 134, 230,  15,  55, 134, 230,  15,  55, 134, 230,  15,  55, 134,}, // 
            {4,    9,  22,  55,  84,   9,  22,  55,  84,   9,  22,  55,  84,   9,  22,  55,}, // 
            {3,   92,   0, 164,  92,   0, 164,  92,   0, 164,  92,   0, 164,  92,   0, 164,}, // 
            {3,   15, 210, 175,  15, 210, 175,  15, 210, 175,  15, 210, 175,  15, 210, 175,}, // 20          
            {3,    4,  22,  50,   4,  22,  50,   4,  22,  50,   4,  22,  50,   4,  22,  50,}, //                       
            {3,   84, 210,  14,  84, 210,  14,  84, 210,  14,  84, 210,  14,  84, 210,  14,}, //                      
            {3,   35, 210,  14,  35, 210,  14,  35, 210,  14,  35, 210,  14,  35, 210,  14,}, //                      
            {3,   22,  55,  84,  22,  55,  84,  22,  55,  84,  22,  55,  84,  22,  55,  84,}, //         
            {3,  190,  10, 128, 190,  10, 128, 190,  10, 128, 190,  10, 128, 190,  10, 128,}, // 25   
            {3,   22,   4, 230,  22,   4, 230,  22,   4, 230,  22,   4, 230,  22,   4, 230,}, //         
            {3,   22,   4, 245,  22,   4, 245,  22,   4, 245,  22,   4, 245,  22,   4, 245,},         
            {3,  120,   3,  18, 120,   3,  18, 120,   3,  18, 120,   3,  18, 120,   3,  18,},                                       
            {3,  130, 180, 210, 130, 180, 210, 130, 180, 210, 130, 180, 210, 130, 180, 210,},              
            {3,   14, 125, 180,  14, 125, 180,  14, 125, 180,  14, 125, 180,  14, 125, 180,}, // 30                        
            {2,   92,   0,  92,   0,  92,   0,  92,   0,  92,   0,  92,   0,  92,   0,  92,}, // 
            {2,   81,   4,  81,   4,  81,   4,  81,   4,  81,   4,  81,   4,  81,   4,  81,},
            {2,   84, 134,  84, 134,  84, 134,  84, 134,  84, 134,  84, 134,  84, 134,  84,},
            {2,   84, 230,  84, 230,  84, 230,  84, 230,  84, 230,  84, 230,  84, 230,  84,},
            {2,  195,  92, 195,  92, 195,  92, 195,  92, 195,  92, 195,  92, 195,  92, 195,}, // 35
            {2,   84,  55,  84,  55,  84,  55,  84,  55,  84,  55,  84,  55,  84,  55,  84,}, // 
            {2,  135,  40, 135,  40, 135,  40, 135,  40, 135,  40, 135,  40, 135,  40, 135,},
            {2,   20, 128,  20, 128,  20, 128,  20, 128,  20, 128,  20, 128,  20, 128,  20,},
            {2,   22, 230,  22, 230,  22, 230,  22, 230,  22, 230,  22, 230,  22, 230,  22,},
            {2,   22, 245,  22, 245,  22, 245,  22, 245,  22, 245,  22, 245,  22, 245,  22,}, // 40
            {2,   45,   6,  45,   6,  45,   6,  45,   6,  45,   6,  45,   6,  45,   6,  45,}, // 
            {2,  239,   4, 239,   4, 239,   4, 239,   4, 239,   4, 239,   4, 239,   4, 239,},
            {2,   50, 236,  50, 236,  50, 236,  50, 236,  50, 236,  50, 236,  50, 236,  50,},
            {2,  134, 120, 134, 120, 134, 120, 134, 120, 134, 120, 134, 120, 134, 120, 134,},
            {2,  134, 210, 134, 210, 134, 210, 134, 210, 134, 210, 134, 210, 134, 210, 134,},  // 45
            {2,  123, 201, 123, 201, 123, 201, 123, 201, 123, 201, 123, 201, 123, 201, 123,},  // 
            {2,  210,  35, 210,  35, 210,  35, 210,  35, 210,  35, 210,  35, 210,  35, 210,},
            {2,   10, 180,  10, 180,  10, 180,  10, 180,  10, 180,  10, 180,  10, 180,  10,},
            {2,  245, 134, 245, 134, 245, 134, 245, 134, 245, 134, 245, 134, 245, 134, 245,},
            {2,  230, 134, 230, 134, 230, 134, 230, 134, 230, 134, 230, 134, 230, 134, 230,},  // 50
            {15,  16,  47,  24,  44,  10,   9,   7,   3,  23,  16,  10,  12,  35,  19,  45,},  //      
            {15,  11,  38,  31,  10,   7,  31, 245, 247, 207, 228, 215, 213, 226, 165, 138,},             
            {15,  41,  32,  25,  14,  26,  15, 227, 248, 213, 225, 228, 223, 230, 118, 161,},             
            {15,  31,   3,  16,   9,  31,  15, 237, 245, 232, 241, 221, 233, 215, 108, 140,},             
            {15,  41,   6,  14,  17,  39,  11, 251, 237, 252, 241, 254, 221, 215,  93, 177,},  // 55          
            {15,  11,   1,   4,  34,  26,   5, 225, 252, 209, 245, 235, 222, 252, 128,  55,},  //            
            {15, 251,  35,  98,  95, 103, 192,  63, 100, 100,  73, 134, 192, 147,  61, 127,},             
            {15, 226,   6, 106,  70, 178,  99,  75, 109, 116, 131, 111, 128, 116, 176,  50,},             
            {15,   4, 227, 193, 173, 104, 170,  61,  93, 150,  93,  74,  43,  28,  56, 194,}   // 59          
            };

const int arrayCount = (sizeof(selectColor_array)/sizeof(selectColor_array[0]));          

struct selectColorMod19_Mod26_pgm
{
  byte  ymax4;       // ymax
  byte  ymin4;        // ymin4 
  int   setDifference;  // setdifference
};

static const selectColorMod19_Mod26_pgm selectColor_data[14] PROGMEM = 
{
  {40,    0,  1,},
  {240, 200,  1,},
  {200, 130,  1,},
  {90,    0,  3,},
  {40,  246,  1,},
  {150, 110,  1,},
  {150,  80,  1,},
  {150,   0,  3,},
  {40,  140,  3,},
  {40,  230,  3,},
  {40,  190,  3,},
  {215, 115,  1,},
  {250, 150,  1,}, 
  {60,  130,  1,}      
};

uint8_t   brigh[255]={0};
uint8_t   colour[15]={};

//colour[4] = 0;   colour[0] = 55;     colour[1] = 158;     colour[2] = 88;     colour[3] = 217;

uint8_t   colourS[6]={55, 164, 96, 217, 0, 140}; //  colourS[0]=217;        colourS[1]=164;        colourS[2]=0;        colourS[3]=96;        colourS[4]=55;            colour[5]=140;
uint8_t   newColour[15]={};
uint8_t   colourR[10]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int       dirArray[10]={1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
uint8_t   blockArray[750]={0};
uint16_t  longxArray[NUM_SET]={0};
byte      seedNumber=10;
uint16_t  seedArray[100]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 40};

const uint8_t brivalbpm[16] = {12, 23, 7, 63, 37, 14, 24, 26, 58, 32, 11, 62, 43, 13, 53, 31};
const uint8_t brivalmin[16] = {135, 75, 75, 175, 75, 95, 105, 125, 135, 175, 75, 175, 75, 95, 135, 175};
const uint8_t brivalmax[16] = {255, 205, 255, 255, 255, 205, 255, 205, 255, 205, 255, 255, 255, 205, 255, 205};
const uint8_t satvalbpm[16] = {7, 11, 4, 5, 3, 12, 9, 8, 2, 6, 5, 3, 7, 8, 9, 2};
const uint8_t satvalmin[16] = {135, 75, 75, 175, 75, 95, 105, 125, 135, 175, 75, 95, 135, 175};

float timeSpeed[30]={1.05, 1.23, 1.43, 1.67, 1.86, 2.13, 2.46, 1.05, 1.23, 1.43, 1.67, 0.77, 3.04, 2.87, 1, 1.1, 1.35, 1.9, 2.2, 2.7, 1.5, 1.67, 1.86, 2.13, 2.46, 1.05, 1.23, 1.43, 1.67, 0.77,}; // string speeds
float sFtab[30]={2, 2, 2, 2, 2, 2 ,2, 2, 1.4, 1.4, 1.6, 1.6, 1.8, 1.8, 1.2, 1.3, 1.4, 1.6, 1.7, 2, 1.2, 2 ,2, 1.4, 1.4, 1.6, 1.7, 1.8, 1.9, 1.2};
float interRun[30]={1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
float timeArray[5]={0.5, 0.75, 1.0, 1.5, 2.0};
float timeArray2[6]={0.5, 1.0, 1.5, 2.0, 3.0, 4.0};  // pause
float timeArray3[6]={0.7, 0.8, 0.9, 1.1, 1.3, 1.5}; // interval loopsnelheid
float timeArraySpark[5]={2, 6, 12, 18, 30};
float timeArrayReverse[5]={1, 2, 4, 6, 10};
float timeArrayRainbow[5]={2, 4, 8, 12, 15};

byte cycleGlow3[255]={0};
uint32_t rtGlow3[255] = {0};
int     numGlow3[255]={0};
unsigned long timeFactorGlow3[255]={0};
unsigned long previousMillisGlow3[255]={0};

byte cycleSat3[255]={0};
uint32_t rtSat3[255] = {0};
int     numSat3[255]={0};
unsigned long timeFactorSat3[255]={0};
unsigned long previousMillisSat3[255]={0};

unsigned long previousMillisLN[30]={0};
unsigned long previousMillisAM[30]={0};
unsigned long changeSpeedMA[20] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
uint16_t rtAM[30] = {0};
float INTERVALf[30]={100, 120, 140, 160, 180, 200, 220, 240, 260, 280, 300, 320, 340, 360, 150, 170, 210, 290, 330, 350, 130, 140, 160, 180, 100, 220, 240, 360, 280, 300};
//uint16_t rn[19]={70, 60, 50, 40, 30, 0, 0, 180, 170, 160, 150, 140, 500, 0, 0, 0, 200, 210, 220};
uint16_t rn[30]={70, 60, 50, 40, 40, 50, 60, 180, 170, 160, 150, 140, 50, 60, 70, 80, 200, 210, 220, 230, 210, 50, 60, 70, 80, 200, 210, 220, 230, 210};

int yvarC[10]={0, 9, 4, -11, -3, -6, 7, 10, 0, -6};
int yvargC[10]={-3, -9, 4, 16, 0, 11, 7, 19, 0, -3};
int yvar[10]={0, 9, 4, -11, -3, -6, 7, 10, 0, -6};
int yvarb[16]={0, 3, 1, 0, -1, 0, -4, 0, 0, 3, -2, 0, 2, 0, -3, 0};
int yvarg[10]={-3, -9, 4, 16, 0, 11, 7, 19, 0, -3};
byte varlu = 0;
byte difflu = 0;


int pos[30] ={-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int pos1[30] ={-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int pos2[30] ={-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int pos3[30] ={-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int pos4[30] ={-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int rr[30]  ={-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

int pos7[30] ={-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int pos8[30] ={-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int pos9[30] ={-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int pos10[30] ={-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int pos11[30] ={-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int rr2[30]  ={-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
//boolean setLedBack[30] = {0};

//uint16_t randomNumberMinimum[30]={25, 10, 25, 10, 25, 60,  100, 125, 115, 125, 145, 145, 145, 155, 200, 60, 125, 150, 175, 25, 120, 145, 155, 200, 60, 125, 150, 175, 25, 120};
//uint16_t randomNumberMaximum[30]={50, 50, 50, 50, 50, 140, 140, 140, 180, 180, 240, 240, 240, 240, 250, 140, 250, 200, 250, 175, 200, 240, 240, 250, 140, 250, 200, 250, 175, 200};

//uint16_t randomNumberMinimum[30]={4, 10, 4, 10, 4, 2,  2, 2, 7, 3, 2, 2, 5, 8, 2, 10, 125, 150, 175, 25, 120, 145, 155, 200, 60, 125, 150, 175, 10, 20};
//uint16_t randomNumberMaximum[30]={2, 2, 2, 2, 2, 1, 140, 140, 180, 180, 240, 240, 240, 240, 250, 140, 250, 200, 250, 175, 200, 240, 240, 250, 140, 250, 200, 250, 175, 200};

boolean  rainbowPossibility[30]={0};
boolean  revPossibility[30]={1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
boolean  endFlag = false;

uint8_t  flakeListMode7[30]={0, 4, 8, 12, 12, 0, 8, 12, 16, 16, 8, 6, 16, 20, 24, 28, 30, 35, 35, 35, 40, 46, 50, 54, 58, 60, 65, 65, 68, 70};
uint8_t  flakeListMode16[30]={0, 2, 6, 12, 8, 12, 12, 12, 12, 16, 16, 16, 16, 24, 0, 4, 8, 12, 16, 24, 12, 26, 24, 30, 34, 38, 42, 46, 54, 62};
int      num17[30]={NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1 ,NUM_LEDS-1, NUM_LEDS-1};
int      num26[30]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int      num23[30]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int     i[30] = {NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1 ,NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1 ,NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1 ,NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1 ,NUM_LEDS-1, NUM_LEDS-1};
byte    y[30] = {0};
int     ir[2] = {0,0};
int     a[30] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

uint8_t satval[255]={255};
byte    satlu=0;
uint8_t z[30] = {88};
uint8_t zmem = 99;
uint8_t zr[4]={140, 10, 228, 88};
uint8_t yMA[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

// int sparkarray[30]={0};
// int arraypos=0;
// int arrayPos=0;

String dataString;
String wifiID;
String wifiPASS;
uint8_t num_esp = 0;
uint8_t Mac[60] = {0};
// uint8_t mac2[6] = {0};
// uint8_t mac3[6] = {0};
// uint8_t mac4[6] = {0};
// uint8_t mac5[6] = {0};
// uint8_t mac6[6] = {0};
// uint8_t mac7[6] = {0};
// uint8_t mac8[6] = {0};
// uint8_t mac9[6] = {0};
// uint8_t mac10[6] = {0};

//const char *WIFI_SSID = "Su***s**l";
//const char *WIFI_PASS = "se*******at13";

const char *WIFI_SSID_AP = "ESP32-AP";
const char *WIFI_PASS_AP =  "";

uint16_t EEPROMposition = 0;
uint16_t stringLength;

int check;
uint8_t sensorType = 1;
uint8_t sensorAmount = 1;
char ssidStorage[32];
char passStorage[32];
char stringStorage[32];

const int dns_port = 53;
const int http_port = 80;
const int ws_port = 1337;

char strval[5]={0};
char getsval[3]={0};
//char wifiIDs[30]={0};
//char wifiPASSs[30]={0};
//uint8_t passSize =0;
//uint8_t idSize =0;
String str;
String strget;
String mergedString;
char msg_buf[11];

boolean     inSync = false; // if the decives receives messages from another esp, it turns 'inSync'
uint8_t     inSyncCounter = 0; // this is a counter to get the esp out of sync, if the messages fail to send
boolean     espNowMessage = false; // tells the Esp_now void function there's a message waiting to be sent.
//boolean     incomingMessage = false;
boolean     syncEsp = false; // syncs the Esps
boolean     alertColor = false; // alertsColor change in runmode (needed to sync color in 3 modes)
boolean     colourSync = false; // sometimes timing determines colour, with this varianle timing and colour can be synced too
boolean     randomCycle = false; // EEPROM.readByte(96);
boolean     changeModus = false;
boolean     fadeFirst = true;
boolean     cycle = false;
boolean     saveForAllModes = false;
boolean     changeColor = false;
boolean     readyToChange = true;
boolean     executeScript=true;
boolean     dimming = false;
boolean     modeUp=false;
boolean     modeDown=false;
boolean     outOfModus = true;
boolean     excludeModes=true;
boolean     forcedColourChange = false;
boolean     sparkON = true;
boolean     rainbowON = true;
boolean     reverseON = true;
boolean     glitterON = false;
boolean     whiteON = false;
//boolean     glitter = false;
boolean     irEnabled = true;
boolean     fadeIsActive = false;
boolean     saveToEEPROM = false;
boolean     tower = true;
boolean     loadHSV = false;
boolean     updateHSV = true;
boolean     maintainWaveForm = true;
boolean     Bees = false;
boolean     varNumbrigh = false;
boolean     varBPMB = false;
boolean     varNumsat = false;
boolean     varBPMS = false;
boolean     colourTimerActive = true;
byte        selectedPreset[modeCount] = {0};
byte        selectedPresetVariable = 0;
boolean     sendDelayWSMessage=false;
byte        message = 0;

uint16_t    dataVar=0;

uint8_t EspNowMessageType = 0;
uint8_t BriSPreset=0;
byte glowON = 2; // glow is ON
byte satON = 0;
byte varON = 1; // standard variance is ON
//int MODUS=0;
int colorMode=0;
byte programMode = 0;
byte arrayn = 0; // 0
byte oldArrayn = 0;
int dir = 2; // direction 2 is 2 kanten op 1 is kant
int dir1 = 1; // richting regenboog
int xdir = 1; // intermediate - not effecient, remove later on
int dir0 = 1; // modus 19 among others
int8_t dir2 = 1;

uint8_t lr26 = 0;
uint8_t lg26 = 0;
uint8_t lb26 = 0;
uint8_t ymin;
uint8_t ymax;
uint8_t ymin1;
uint8_t ymax1;
uint8_t yminrood;
uint8_t ymaxrood;
uint8_t ymingroen;
uint8_t ymaxgroen;
uint8_t yminblauw;
uint8_t ymaxblauw;
uint8_t ymax3 = 190; // 215
uint8_t ymin3 = 130;
uint8_t ymax4 = 40;
uint8_t ymin4 = 0;
uint8_t ymax2 = 42;        
uint8_t ymin2 = 130;  
uint8_t yxmas = 0;
uint8_t yxmasold = 0;
uint8_t yx= 210;
uint8_t yval1=28;
uint8_t reverseColour=0; // reverseON
uint8_t rainbowColour=0; // rainbowON
uint8_t sparkColour=95; // sparkON
uint8_t yval8=96;  //
byte yval = 217;
uint8_t ysr=0;
uint8_t yold = 0;
uint8_t yold1 = 0;
uint8_t y0r = 0;
uint8_t y01m = 0;
uint16_t yint = 0;
uint16_t yintm = 0;
uint16_t whitepos=0;

uint8_t lastBRIGH = 0;
uint8_t lastS = 0;
//int offbr=30;
byte offS=50;
byte colorNumber = 0;
int slowFactor=0;
byte numsparks=3;
//byte BPS = 8;
byte BPMB = 30;
byte BPMS = 30;
byte offBr = 30;
byte m20delay = 1;
byte m20offset = 1;
byte m21delay = 1;
byte numbrigh=11; // or 1-16
byte numsat=13;
byte BRIGH = 205; //205;
uint32_t waveTimeBr = 2000;
uint32_t convBrigh=waveTimeBr/numbrigh;
uint32_t waveTimeS = 2000;
uint32_t convSat=waveTimeS/numsat;
uint8_t yStart = 0;
uint8_t yTrans= 10;
uint16_t brighlu = 0;
uint16_t colourlu = 0;
uint8_t range = 100;
float ledspercolor = 1;  
int colorCount=0;
int selectColor=-1;
int y0rCounter=0;
byte newColors=0;
float numAmax=0;
byte BrF=0;
byte SF=0;
int offdis = 1;
byte offdisC = 1;
byte numcolor = 5;
byte colorlength = 10;
float timefactor3 = 1.00f;

int sparkSpeed = 98; // 78
int slingerSpeed=55;

byte numfirstcycle = 0;
byte S = 255;
uint8_t Stwinkle = 255;
byte z5 = 0;
byte z7 = 0;
int cn = 20;
int diff1=0;
int diff2=0;
int diff[10]={0};
uint8_t diffbeat=15;
uint8_t diffbeat2=15;
int setDifference = 1;
int setDifferenceMem = 1;
int setDifference2 = setDifference+5;
int num1=0;
int r = 0;
int variant=0;
int offmin = 1;
int offmax = 1;
int df = 4;

//int density =0;
int ydiff = 10;
byte hue=0;
byte Red=0;
byte Green=0;
byte Blue=0;
int colourChangeDelay=0;
int cyclesToFade=0;
boolean sparking = false;
//int num50=0; // variable that determines additional setDifference
int partialArrayCounter=-1;
int partialArraySize=0;
byte memoryByte = 0;

int fadeInSpeed = 16; // 32
int fadeOutSpeed = 35; // 52
//uint8_t DENSITY = 255;
enum { GETTING_DARKER = 0, GETTING_BRIGHTER = 1 };

int num30 =0;
int yy = 0;
int hh = NUM_LEDS;
int xx = 0;
int xp=2;
int xp2=2;
int w = NUM_LEDS-1;
int p = NUM_LEDS-1;
int poshh=NUM_LEDS;
int rrhh=NUM_LEDS;
int p1=0;
int p2=0;
int p3=0;
int ig=0;
int ig3= NUM_LEDS-1;
int lp = 90;
int xnum=3;
int num2=0;

int num4=0;

uint8_t rainbow2m = 1;

int num6=0;
int num15=75;
int flakeCounter=0;
int evenOddCounter=0;
uint8_t fadeCounter=0;
uint16_t rn6 =0;
uint16_t rn13 =500;
uint16_t rn14=5000;
uint16_t rn15=0;
uint16_t rn16=0;

int     T = 0;
long    cycleT = 0;
unsigned long irCheckedTime = 0;
unsigned long previousMillis = 0;
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis5 = 0;  
unsigned long previousMillis6 = 0;
unsigned long previousMillis7 = 0;
unsigned long previousMillis8 = 0;
unsigned long previousMillis9 = 0;
unsigned long previousMillis10 = 0;
unsigned long previousMillis11 = 0;
unsigned long previousMillis12 = 0;
unsigned long previousMillis13 = 0;
unsigned long previousMillis14 = 0;
unsigned long previousMillis20 = 0;
unsigned long previousMillis35 = 0;
unsigned long previousMillis36 = 0;
unsigned long previousMillis37 = 0;
unsigned long previousMillis38 = 0;
unsigned long previousMillis43 = 0;
unsigned long previousMillis44 = 0;
unsigned long previousMillis45 = 0;
unsigned long previousMillis52 = 0;
unsigned long previousMillis54 = 0;

unsigned long changeSpeed = 100; //100;
unsigned long modeDelay = 100; //100;

//unsigned long sparkSpeed = 100;
uint32_t changeSpeedOld = 100;
uint32_t cycleTime=600000;

float INTERVAL=100;
float INTERVAL2=interval2;
float INTERVAL3=interval3;
float INTERVAL4=interval4;
float INTERVAL7=interval7;
float INTERVAL9=interval7;

float sF=1.000;
float cfactor1=1;
float cfactor2;
float cfactor3;
byte speedFact = 1;

// gradient properties
extern const TProgmemRGBGradientPalettePtr gGradientPalettes[];
extern const uint8_t gGradientPaletteCount;
uint8_t gCurrentPaletteNumber = 0;
CRGBPalette16 gCurrentPalette( gGradientPalettes[1] );
CRGBPalette16 gTargetPalette( gGradientPalettes[1] );



void initializeEEPROMvariables(){  
#ifdef ESP8266  
EEPROM.get(offsetof(storeInEEPROM, NUM_LEDS), NUM_LEDS);
//EEPROM.get(offsetof(storeInEEPROM, BPMB), BPMB);
//EEPROM.get(offsetof(storeInEEPROM, BPMS), BPMS);
EEPROM.get(offsetof(storeInEEPROM, waveTimeBr), waveTimeBr);
EEPROM.get(offsetof(storeInEEPROM, waveTimeS), waveTimeS);
EEPROM.get(offsetof(storeInEEPROM, timefactor3), timefactor3);
EEPROM.get(offsetof(storeInEEPROM, cycleTime), cycleTime);
//Serial.print("NUM_LEDS: "); Serial.println(NUM_LEDS);
#else
NUM_LEDS = EEPROM.readInt(offsetof(storeInEEPROM, NUM_LEDS));
waveTimeBr = EEPROM.readLong(offsetof(storeInEEPROM, waveTimeBr[0]));
waveTimeS = EEPROM.readLong(offsetof(storeInEEPROM, waveTimeS[0]));
timefactor3 = EEPROM.readFloat(offsetof(storeInEEPROM, timefactor3));
cycleTime = EEPROM.readLong(offsetof(storeInEEPROM, cycleTime));
#endif
BPMB = EEPROM.read(offsetof(storeInEEPROM, BPMB[0]));
BPMS = EEPROM.read(offsetof(storeInEEPROM, BPMS[0]));
ymin  = EEPROM.read(offsetof(storeInEEPROM, ymin));
ymax = EEPROM.read(offsetof(storeInEEPROM, ymax));
ymin1 = EEPROM.read(offsetof(storeInEEPROM, ymin1));
ymax1 = EEPROM.read(offsetof(storeInEEPROM, ymax1));
ymin2 = EEPROM.read(offsetof(storeInEEPROM, ymin2));
ymax2 = EEPROM.read(offsetof(storeInEEPROM, ymax2));
ymin3 = EEPROM.read(offsetof(storeInEEPROM, ymin3));
ymax3 = EEPROM.read(offsetof(storeInEEPROM, ymax3));
ymin4 = EEPROM.read(offsetof(storeInEEPROM, ymin4));
ymax4 = EEPROM.read(offsetof(storeInEEPROM, ymax4));
yminrood = EEPROM.read(offsetof(storeInEEPROM, yminrood));
ymaxrood = EEPROM.read(offsetof(storeInEEPROM, ymaxrood));
ymingroen = EEPROM.read(offsetof(storeInEEPROM, ymingroen));
ymaxgroen = EEPROM.read(offsetof(storeInEEPROM, ymaxgroen));
yminblauw = EEPROM.read(offsetof(storeInEEPROM, yminblauw));
ymaxblauw = EEPROM.read(offsetof(storeInEEPROM, ymaxblauw));
cycle = EEPROM.read(offsetof(storeInEEPROM, cycle));
fadeFirst = EEPROM.read(offsetof(storeInEEPROM, fadeFirst));
randomCycle = EEPROM.read(offsetof(storeInEEPROM, randomCycle));
excludeModes = EEPROM.read(offsetof(storeInEEPROM, excludeModes));
programMode = EEPROM.read(offsetof(storeInEEPROM, programMode));
tower = EEPROM.read(offsetof(storeInEEPROM, tower));
BRIGH = EEPROM.read(offsetof(storeInEEPROM, BRIGH[0]));
offBr = EEPROM.read(offsetof(storeInEEPROM, offBr[0]));
glowON = EEPROM.read(offsetof(storeInEEPROM, glowON[0]));
BrF = EEPROM.read(offsetof(storeInEEPROM, BrF[0]));
z5 = EEPROM.read(offsetof(storeInEEPROM, z5));
offS = EEPROM.read(offsetof(storeInEEPROM, offS[0]));
S = EEPROM.read(offsetof(storeInEEPROM, S[0]));
SF = EEPROM.read(offsetof(storeInEEPROM, SF[0]));
satON = EEPROM.read(offsetof(storeInEEPROM, satON[0]));
Red = EEPROM.read(offsetof(storeInEEPROM, Red));
Green = EEPROM.read(offsetof(storeInEEPROM, Green));
Blue = EEPROM.read(offsetof(storeInEEPROM, Blue));
yval = EEPROM.read(offsetof(storeInEEPROM, yval));
varON = EEPROM.read(offsetof(storeInEEPROM, varONglobal));
numsat = EEPROM.read(offsetof(storeInEEPROM, numsat[0]));
numbrigh = EEPROM.read(offsetof(storeInEEPROM, numbrigh[0]));
Bees = EEPROM.read(offsetof(storeInEEPROM, Bees));
range = EEPROM.read(offsetof(storeInEEPROM, range));
offdisC = EEPROM.read(offsetof(storeInEEPROM, offdisC));
num_esp = EEPROM.read(offsetof(storeInEEPROM, num_esp));
//personalizedModes = EEPROM.read(offsetof(storeInEEPROM, personalizedModes));

#ifdef ESP8266 
      for (int m = 0; m < modeCount; m++){
      int offsetPosition = offsetof(storeInEEPROM, cmode[0]);
      EEPROM.get(offsetPosition+m, cmode[m]); 
      //Serial.print(offsetPosition+m); Serial.print(" "); Serial.println(cmode[m]);
      //Serial.println("heeree in setupp 222");
      }

      for (int m = 0; m < 60; m++){
      int offsetPosition = offsetof(storeInEEPROM, Mac[0]);
      EEPROM.get(offsetPosition+m, Mac[m]); 
      //Serial.print(offsetPosition+m); Serial.print(" "); Serial.println(cmode[m]);
      //Serial.println("heeree in setupp 222");
      }      

      for (int m = 0; m < modeCount; m++){
      int offsetPosition = offsetof(storeInEEPROM, selectedPreset[0]);
      EEPROM.get(offsetPosition+m, selectedPreset[m]); 
      //Serial.print(offsetPosition+m); Serial.print(" "); Serial.println(cmode[m]);
      //Serial.println("heeree in setupp 222");
      }

      Serial.println(F(" "));
      Serial.println(F("wifi settings"));
      for (int m = 0; m < 32; m++){
      int offsetPosition = offsetof(storeInEEPROM, ssidStorage[0]);
      EEPROM.get(offsetPosition+m, ssidStorage[m]); 
      }
      wifiID = String(ssidStorage);
      Serial.print("wifiID "); Serial.println(wifiID);
      
      for (int m = 0; m < 32; m++){
      //Serial.print(m); Serial.print("m ");   
      int offsetPosition = offsetof(storeInEEPROM, passStorage[0]);
      EEPROM.get(offsetPosition+m, passStorage[m]); 
      }
      wifiPASS = String(passStorage);
      Serial.print("wifiPASS "); Serial.println(wifiPASS);

#else
      for (int m = 0; m < modeCount; m++){
      int offsetPosition = offsetof(storeInEEPROM, cmode[0]);
      cmode[m]  = EEPROM.read(offsetPosition+m);
      }

      for (int m = 0; m < 60; m++){
      int offsetPosition = offsetof(storeInEEPROM, Mac[0]);
      Mac[m]  = EEPROM.read(offsetPosition+m);
      //Serial.print("MAC initialization "); Serial.println(Mac[m]);
      }      

      for (int m = 0; m < modeCount; m++){
      int offsetPosition = offsetof(storeInEEPROM, selectedPreset[0]);
      selectedPreset[m]  = EEPROM.read(offsetPosition+m);
      }
      
      for (int m = 0; m < 32; m++){
      int offsetPosition = offsetof(storeInEEPROM, ssidStorage[0]);
      ssidStorage[m]  = EEPROM.read(offsetPosition+m);
      }
      wifiID = String(ssidStorage);
      Serial.print("wifiID "); Serial.println(wifiID);
      
      for (int m = 0; m < 32; m++){
      //Serial.print(m); Serial.print("m ");   
      int offsetPosition = offsetof(storeInEEPROM, passStorage[0]);
      passStorage[m]  = EEPROM.read(offsetPosition+m);
      }
      wifiPASS = String(passStorage);
      Serial.print("wifiPASS "); Serial.println(wifiPASS);
#endif
} 
