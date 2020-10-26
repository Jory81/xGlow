/*
 * All the variables that are used. Most are defined globally. Some variables can be likely be grouped. I might cleans it up more one day.
 */

typedef void (*effect_f) (void);  // This is type definition for the pointertype...

effect_f effect_function = NULL; // This is the pointer variable used to remember pointer to function()

const char string_0[] PROGMEM = "static_glow"; 
const char string_1[] PROGMEM = "varying_glow"; 
const char string_2[] PROGMEM = "warm_glow";
const char string_3[] PROGMEM = "reflection"; 
const char string_4[] PROGMEM = "deflection";
const char string_5[] PROGMEM = "coloursplash";
const char string_6[] PROGMEM = "palette"; 
const char string_7[] PROGMEM = "colourwash"; 
const char string_8[] PROGMEM = "rainbow_1";
const char string_9[] PROGMEM = "rainbow_2";
const char string_10[] PROGMEM = "rainbow_3";
const char string_11[] PROGMEM = "rainbow_4";
const char string_12[] PROGMEM = "rainbow_5";
const char string_13[] PROGMEM = "rainbow_6";
const char string_14[] PROGMEM = "rainbow_7"; 
const char string_15[] PROGMEM = "gradient";
const char string_16[] PROGMEM = "lucky7";
const char string_17[] PROGMEM = "goldstrike";
const char string_18[] PROGMEM = "halcyon"; 
const char string_19[] PROGMEM = "snow_melt";
const char string_20[] PROGMEM = "snow_pile";
const char string_21[] PROGMEM = "snow_storm";
const char string_22[] PROGMEM = "snow_rainbow"; 
const char string_23[] PROGMEM = "sparkle";
const char string_24[] PROGMEM = "sparkle_storm";
const char string_25[] PROGMEM = "sparkle_rainbow"; 
const char string_26[] PROGMEM = "twinkle";
const char string_27[] PROGMEM = "gambler";
const char string_28[] PROGMEM = "casino";
const char string_29[] PROGMEM = "fine_canvas";
const char string_30[] PROGMEM = "rough_canvas"; 
const char string_31[] PROGMEM = "xmas_1"; 
const char string_32[] PROGMEM = "xmas_2"; 
const char string_33[] PROGMEM = "xmas_3";
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
  const byte rgbcolor;
  boolean cycle;
  boolean fadeFirst;
  boolean randomCycle;
  boolean excludeModes;
  boolean personalizedModes;
  uint32_t cycleTime;
  byte programMode;
  boolean tower;
  byte z5;
  byte Red;
  byte Green;
  byte Blue;
  byte yval;
  byte yvalm2;
  byte yvalm3;
  byte colorlengthm[3];
  byte varONglobal; 
  byte BRIGH[6];
  byte offBr[6];
  byte glowON[6];
  byte BrF[6];
  byte offS[6];
  byte S[6]; 
  byte SF[6];
  byte satON[6];
  byte numsat[6];
  byte numbrigh[6];
  byte BPMB[6];
  byte BPMS[6];
  uint32_t waveTimeBr[6];
  uint32_t waveTimeS[6];
  float timefactor3;
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
  byte offdisC;
  byte numcolor1;
  byte numcolor2; 
  uint8_t BriSPreset[modeCount];
  unsigned long changeSpeed[modeCount];
  int setDifference[modeCount];
  int colorMode[modeCount];
  byte arrayn[modeCount];
  byte varON[modeCount];
  int NUM_LEDS;   
};

byte RGBCOLOR = 0;

storeInEEPROM customVar = {
      33335, // code to check
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, // ssid storage
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, // pass storage
      1, // empty byte so ymin load correctly
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
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // cmodes (1 = active)
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
      1, 1, 1, 1, 1, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // glitterON (1 = active)
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 1, 1, 1, 0, 0, 0, 0,
      0, // rgb
      1, // cycle
      1, // fade 
      1, // random
      1, // excludemodes
      0, // personalizedModes
      600000, // CycleTime
      0, // programMode      
      0, // tower
      92, // z5
      62, // red
      25, // green
      6, // blue
      10, // yval
      5, // yvalm2
      217, // yvalm3
      20, 16, 10, // colorLength rainbow_6, random_string, pers_block
      1, // varON 
      205,        200, 175, 150, 125, 100,// BRIGH          position 0 is global variable
      80,         50, 50, 50, 50, 50,// offBr               position 0 is global variable
      5,          0, 0, 0, 0, 0, // glowON                  position 0 is global variable
      70,         50, 50, 50, 50, 50, // BrF                position 0 is global variable
      25,         30, 30, 30, 30, 30, // offS               position 0 is global variable
      205,        250, 250, 250, 250, 250,  // S            position 0 is global variable
      0,          0, 0, 0, 0, 0,  // Sf                     position 0 is global variable
      0,          0, 0, 0, 0, 0, // satOn was 3             position 0 is global variable
      31,         31, 31, 31, 31, 31, // numsat             position 0 is global variable
      13,         13, 13, 13, 13, 13, // numbrigh           position 0 is global variable
      30,         20, 20, 20, 20, 20,  // BPMB              position 0 is global variable
      60,         20, 20, 20, 20, 20, // BPMS               position 0 is global variable
      2000,       3000, 3000, 3000, 3000, 3000, // waveTimeBr           position 0 is global variable
      1000,       3000, 3000, 3000, 3000, 3000, // waveTimeS            position 0 is global variable

      1.00, // timefactor3 
      0, // Bees
      0, // varNumbrigh 
      0, //varBPMB  
      0, // varNumsat
      0, // varBPMS  
      122, // ymin2
      241, // ymax2
      110, // ymin3
      25, // ymax3
      212, // ymin4
      40, // ymax4
      60, // range
      7, // FastLDPalet;
      14, // offdisC
      3, //numcolor1 pers_color
      15, //numcolor2 pers_block
      3, 0, 0, 0, 0, 3, 9, 0, 8, 2, // uint8_t BriSpreset
      4, 0, 0, 0, 0, 6, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 
      0, 0, 0, 0, 0, 0, 0, 0,
      100, 100, 100, 100, 100, 35, 50, 50, 20, 30, // unsigned long changeSpeed
      100, 200, 30, 1500, 100, 200, 110, 110, 110, 125, 
      125, 130, 125, 130, 135, 130, 30, 30, 2000, 2000, 
      1000, 200, 100, 40, 30, 20, 50, 50,
      7, 7, 25, 80, 80, 7, 1, 45, 1, 4, // int setDifference
      4, 7, 5, 25, 1, 1, 10, 15, 95, 7, 
      7, 7, 7, 7, 7, 7, 1, 40, 1, 1, 
      1, 7, 7, 7, 40, 40, 10, 1,
      0, 0, 0, 0, 1, 2, 1, 1, 0, 0, // int colorMode
      0, 0, 0, 0, 0, 0, 4, 4, 4, 4,
      1, 1, 0, 2, 1, 0, 4, 5, 1, 4, 
      1, 1, 1, 1, 5, 1, 2, 0,
      1, 1, 1, 1, 1, 1, 1, 1, 7, 7, // byte arrayn
      1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 27, 
      4, 1, 1, 1, 1, 0, 0, 0,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // varON byte
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 
      2, 1, 1, 1, 1, 1, 1, 1,
      300 // NUM_LEDS      
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
  {205,       50,   2,      45,    16,       30,   2000,         250,    0,     0,         35,    31,         30,      2000}, // 0 EEPROM values
  {155,       50,   2,      34,    13,       30,   2000,         255,    0,     0,         35,    31,         30,      2000}, // 1 basic glow nice glow 19
  {205,       50,   2,      35,    31,       51,   6000,         255,    0,     0,         35,    31,         30,      2000}, // 2 subtle glow
  {194,       70,   5,      43,    13,       30,   2000,         161,    50,    5,         20,    32,         39,      1538}, // 3 NEW small wave less saturated
  //{205,       50,   5,      45,    13,       30,   2000,         200,    0,     5,         45,    31,         60,      1000}, // 3 small wave ok
  {205,       55,   5,      40,    12,       30,   2000,         200,    0,     5,         54,     9,         60,      1000}, // 4 small wave ok
  {205,       50,   5,      65,    13,       20,   2000,         200,    50,    5,         45,    31,         60,      1000}, // 5 gradient
  {205,       0,    6,      40,    12,       30,   2000,         200,    0,     3,        160,    31,         45,      1333}, // 6 diamond perfect  
  {202,       50,   3,      59,    29,       12,   5000,         202,    0,     0,         30,    31,         20,      5000}, // 7 NEW slow twinkle with baseine no saturation variation
  //{205,       50,   3,      55,    13,       10,   6000,         200,    0,     5,         45,    31,         60,      1000}, // 7 slow_Twinkle (baseline)
  {202,       50,   3,      1,     10,       12,   5000,         255,    0,     0,         30,    31,         20,      5000}, // 8 NEW rainbow 1 MODE num_color 10 for special effect
  {205,       50,   3,      15,    31,       10,   6000,         255,    0,     0,         35,    31,         30,      2000}, // 9 slow_Twinkle (black))
  //{80,        110,  6,      28,    13,       30,   2000,         200,    0,     5,         45,    31,         60,      1000}, // 9 sparkle_1 doubt
  {136,       110,  4,      93,    13,       30,   2000,         200,    0,     5,         45,    31,         60,      1000}, // 10 sparkle_2 16
  {106,       110,  2,      18,    13,       30,   2000,         145,    50,    0,         35,    31,         30,      2000}, // 11 sparkle_3 17 sat 255 to 145
  {205,       0,    8,      35,    32,       20,   3000,         200,    40,    6,         56,    28,         60,      1000}, // 12 long wave
  {205,       0,    6,      175,   28,       60,   30000,        200,    0,     6,         28,    30,         60,      1000}, // 13 diamond  better than 5 not nice?  
  {205,       0,    6,      90,    13,       30,   2000,         200,    40,    4,        142,    31,         60,      1000}, // 14 diamond tower NEW
  {205,       0,    6,      175,   31,       60,   30000,        200,    0,     6,         85,    28,         60,     30000}, // 15 diamond  fast twinkle (EEPROM?)
  {205,       50,   3,      74,    31,       42,   3000,         200,    0,     5,         45,    31,         60,      1000}, // 16 fast_Twinkle (baseline)
  {205,       50,   3,      79,    31,       48,   11000,        200,    50,    2,         45,    31,         20,      3000}, // 17 fast_Twinkle too fast, optimize not better than 8? 
  {205,       50,   8,      45,    11,       45,   1333,         200,    0,     5,         35,    31,         60,      1000}, // 18 wave fast twinkle 18 ROOM FOR NEW PRESET
  {205,       50,   8,      35,    29,       51,   6000,         255,    0,     0,         35,    31,         30,      2000}, // 19 fast_Twinkle fullcolor
  {255,       0,    0,      0,     10,        0,    0,            255,    0,    0,         35,    31,         30,      2000} // 20 no glow
};



//  {205,        55,  4,      120,    12,      30,   2000,         200,    0,     4,        145,    31,         60,      1000}, // 15 small wave ok


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

uint8_t   brigh[32]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t   colour[15]={};

uint8_t   colourS[6]={217, 164, 0, 96, 55, 140}; //  colourS[0]=217;        colourS[1]=164;        colourS[2]=0;        colourS[3]=96;        colourS[4]=55;            colour[5]=140;
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

float timeSpeed[21]={1.05, 1.23, 1.43, 1.67, 1.86, 2.13, 2.46, 1.05, 1.23, 1.43, 1.67, 0.77, 3.04, 2.87, 1, 1.1, 1.35, 1.9, 2.2, 2.7, 1.5}; // string speeds
float sFtab[21]={2, 2, 2, 2, 2, 2 ,2, 2, 1.4, 1.4, 1.6, 1.6, 1.8, 1.8, 1.2, 1.3, 1.4, 1.6, 1.7, 2, 1.2};
float interRun[21]={1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
float timeArray[5]={0.5, 0.75, 1.0, 1.5, 2.0};
float timeArray2[6]={0.5, 1.0, 1.5, 2.0, 3.0, 4.0};  // pause
float timeArray3[6]={0.7, 0.8, 0.9, 1.1, 1.3, 1.5}; // interval loopsnelheid
float timeArraySpark[5]={2, 6, 12, 18, 30};
float timeArrayReverse[5]={1, 2, 4, 6, 10};
float timeArrayRainbow[5]={2, 4, 8, 12, 15};

byte cycleGlow3[32]={0};
uint16_t rtGlow3[32] = {0};
int     numGlow3[32]={0};
unsigned long timeFactorGlow3[32]={0};
unsigned long previousMillisGlow3[32]={0};

byte cycleSat3[32]={0};
uint16_t rtSat3[32] = {0};
int     numSat3[32]={0};
unsigned long timeFactorSat3[32]={0};
unsigned long previousMillisSat3[32]={0};

unsigned long previousMillisLN[21]={0};
unsigned long previousMillisAM[21]={0};
unsigned long changeSpeedMA[20] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
uint16_t rtAM[21] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float INTERVALf[21]={100, 120, 140, 160, 180, 200, 220, 240, 260, 280, 300, 320, 340, 360, 150, 170, 210, 290, 330, 350, 130};
//uint16_t rn[19]={70, 60, 50, 40, 30, 0, 0, 180, 170, 160, 150, 140, 500, 0, 0, 0, 200, 210, 220};
uint16_t rn[21]={70, 60, 50, 40, 40, 50, 60, 180, 170, 160, 150, 140, 50, 60, 70, 80, 200, 210, 220, 230, 210};

int yvarC[10]={0, 9, 4, -11, -3, -6, 7, 10, 0, -6};
int yvargC[10]={-3, -9, 4, 16, 0, 11, 7, 19, 0, -3};
int yvar[10]={0, 9, 4, -11, -3, -6, 7, 10, 0, -6};
int yvarb[16]={0, 3, 1, 0, -1, 0, -4, 0, 0, 3, -2, 0, 2, 0, -3, 0};
int yvarg[10]={-3, -9, 4, 16, 0, 11, 7, 19, 0, -3};
byte varlu = 0;
byte difflu = 0;


int pos[30] ={-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int pos1[21] ={-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int pos2[21] ={-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int pos3[21] ={-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int pos4[21] ={-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int rr[30]  ={-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
//boolean setLedBack[30] = {0};

uint16_t randomNumberMinimum[21]={25, 10, 25, 10, 25, 60,  100, 125, 115, 125, 145, 145, 145, 155, 200, 60, 125, 150, 175, 25, 120};
uint16_t randomNumberMaximum[21]={50, 50, 50, 50, 50, 140, 140, 140, 180, 180, 240, 240, 240, 240, 250, 140, 250, 200, 250, 175, 200};
boolean  rainbowPossibility[30]={0};
boolean  revPossibility[30]={1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
boolean  endFlag = false;

uint8_t  flakeListMode7[21]={0, 4, 8, 12, 12, 0, 8, 12, 16, 16, 8, 6, 16, 20, 24, 28, 30, 35, 35, 35, 40};
uint8_t  flakeListMode16[21]={0, 2, 6, 12, 8, 12, 12, 12, 12, 16, 16, 16, 16, 24, 0, 4, 8, 12, 16, 24, 12};
int      num17[21]={NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS, NUM_LEDS};
int      num26[21]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int      num23[21]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int     i[21] = {NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1 ,NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1 ,NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1 ,NUM_LEDS-1, NUM_LEDS-1, NUM_LEDS-1};
byte    y[30] = {0};
int     ir[2] = {0,0};
int     a[21] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

uint8_t satval[32]={255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
byte    satlu=0;
uint8_t z[21] = {88};
uint8_t zmem = 99;
uint8_t zr[4]={140, 10, 228, 88};
uint8_t yMA[21]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int sparkarray[30]={0};
int arraypos=0;
int arrayPos=0;

String dataString;
String wifiID;
String wifiPASS;

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

boolean     randomCycle = false; // EEPROM.readByte(96);
boolean     changeModus = false;
boolean     fadeFirst = true;
boolean     cycle = false;
boolean     changeColor = false;
boolean     readyToChange = true;
boolean     executeScript=true;
boolean     dimming = false;
boolean     modeUp=false;
boolean     modeDown=false;
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
boolean     personalizedModes = false;
boolean     sendDelayWSMessage=false;
byte        message = 0;

uint16_t    dataVar=0;

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

int density =0;
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
uint8_t DENSITY = 255;
enum { GETTING_DARKER = 0, GETTING_BRIGHTER = 1 };

int num30 =0;
int yy = 0;
int hh = NUM_LEDS;
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
personalizedModes = EEPROM.read(offsetof(storeInEEPROM, personalizedModes));

#ifdef ESP8266 
      for (int m = 0; m < modeCount; m++){
      int offsetPosition = offsetof(storeInEEPROM, cmode[0]);
      EEPROM.get(offsetPosition+m, cmode[m]); 
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
