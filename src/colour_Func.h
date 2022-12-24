/*
 * Functions that modify variables of some effects, functions that changes colours or initialize the arrays
 */

// addition for the fastled library
// LIB8STATIC uint8_t beattriwave8(accum88 beats_per_minute, uint8_t lowest = 0, uint8_t highest = 255, uint32_t timebase = 0, uint8_t phase_offset = 0)
// {
//  uint8_t beat = beat8(beats_per_minute, timebase);
//  uint8_t beatcos = triwave8(beat + phase_offset);
//  uint8_t rangewidth = highest - lowest;
//  uint8_t scaledbeat = scale8(beatcos, rangewidth);
//  uint8_t result = lowest + scaledbeat;
//  return result;
//}

//


void handleAdditionalVariables(){ // HANDLE ADDITIONAL DEVIATION OF THE LED COLOUR. IN HINDSIGHT A SIMPLE SINUS FUNCTION DOES THE SAME - another future code improvement.
//if (effect_function != *rainbow_4 && effect_function != *xmas_solid){  
  if (millis() - previousMillis > 50) {
    previousMillis = millis();

    //if (effect_function == static_glow_2){
    if (millis() - previousMillis43 > 100) {
        previousMillis43 = millis();
        diff1+=dir2;
          if (diff1 >= setDifference){
            dir2 = -1;
          }
          else if (diff1 <= -setDifference){
            dir2 = 1;
          }
        }
    
    if (millis() - previousMillis46 > 200) {
        previousMillis46 = millis();
        diff2+=dir3;
          if (diff2 > setDifference2){
            dir3 = -1;
          }
          else if (diff2 < -setDifference2){
            dir3 = 1;
          }
        }   

    //    -setDifference2, setDifference2+1 
    //}
    // else {
    // diff1 = map(beattriwave8(diffbeat, 0, 255), 0, 255, -setDifference, setDifference+1); // triwave code below. Added to FastLed lib8tion.h -- library.
    // }

    // if (setDifference == 1){
    //   for (int i = 0; i < 10; i++){
    //     diff[i]=0;
    //   }      
    // }
    // else {
      if (effect_function == *rainbow_4 || effect_function == *xmas_solid){
        diff[0]=diff2;
        diff[1]=-diff1;
        diff[2]=diff1;
        diff[3]=-diff2;
        diff[4]=diff1;
        diff[5]=-diff1;
        diff[6]=diff2;
        diff[7]=diff1;
        diff[8]=-diff1;
        diff[9]=-diff2;
      }
      else {
        if (dir == 1){
          for (int i = 0; i < 10; i++){
            diff[i]=diff1;
          }
        }
        else {
          diff[0]=diff1;
          diff[1]=diff1;
          diff[2]=diff1;
          diff[3]=-diff1;
          diff[4]=diff1;
          diff[5]=-diff1;
          diff[6]=-diff1;
          diff[7]=diff1;
          diff[8]=diff1;
          diff[9]=-diff1;
      }
    }
  //}
}
}

    
    // else {
    //     if (dir == 1){
    //       for (int i = 0; i < 10; i++){
    //         diff[i]=diff1;
    //       }
    //     }
    //     else {
    //     diff[0]=diff1;
    //     diff[1]=diff1;
    //     diff[2]=diff1;
    //     diff[3]=-diff1;
    //     diff[4]=diff1;
    //     diff[5]=-diff1;
    //     diff[6]=-diff1;
    //     diff[7]=diff1;
    //     diff[8]=diff1;
    //     diff[9]=-diff1;  
    //   } 
    // }
// }
// }
  
// else if (effect_function == *rainbow_4 || effect_function == *xmas_solid){  
//   if (millis() - previousMillis >= FPS) {
//     previousMillis = millis();
//     diff1=map(beattriwave8(diffbeat, 0, 255), 0, 255, -setDifference, setDifference+1); // triwave code below. Added to FastLed lib8tion.h -- library.
//     diff2=map(beattriwave8(diffbeat2, 0, 255), 0, 255, -setDifference2, setDifference2+1);

//     if (setDifference == 1){
//       for (int i = 0; i < 10; i++){
//         diff[i]=0;
//       }      
//     }
//     else {
//         diff[0]=diff2;
//         diff[1]=-diff1;
//         diff[2]=diff1;
//         diff[3]=-diff2;
//         diff[4]=diff1;
//         diff[5]=-diff1;
//         diff[6]=+diff2;
//         diff[7]=diff1;
//         diff[8]=-diff1;
//         diff[9]=-diff2;  
//     }
//   }    
// }
//}

void fillxmasArray(){
        numfirstcycle=0;
        yxmas=0;

        if (ymaxrood < yminrood){        
          for (int i = 0; i < 256; i++){
          longxArray[i]=yxmas;
          yxmasold=yxmas; 
          if ((yxmas < ymaxrood) || (yxmas > ymingroen && yxmas < ymaxgroen) || (yxmas > yminblauw && yxmas < ymaxblauw) || (yxmas > yminrood)){ 
            if (effect_function == xmas_singles){
              yxmas=yxmas+setDifference+offdis; 
            }
            else {
              yxmas+=offdis;
            }
          }
          else {
            if (effect_function == xmas_singles){
              yxmas+=offdis;
            }
            else {
              yxmas=yxmas+setDifference+offdis;
            }
          }
          if (yxmasold > yxmas && numfirstcycle == 0){
            numAmax=i;
            numfirstcycle++;
          }
          }
        }         
        else if (yminrood <= ymaxrood){        
          for (int i = 0; i < 256; i++){
          longxArray[i]=yxmas;
          yxmasold=yxmas; 
          if ((yxmas > yminrood && yxmas < ymaxrood) || (yxmas > ymingroen && yxmas < ymaxgroen) || (yxmas > yminblauw && yxmas < ymaxblauw)){  
            if (effect_function == xmas_singles){
              yxmas=yxmas+setDifference+offdis; 
            }
            else {
              yxmas+=offdis;
            }
          }
          else {
            if (effect_function == xmas_singles){
              yxmas+=offdis;
            }
            else {
              yxmas=yxmas+setDifference+offdis;
            }
          }
          if (yxmasold > yxmas && numfirstcycle == 0){
            numAmax=i;
            numfirstcycle++;
          }
          }
        }
}

void changePColors(){
newColors++;  
int pp = colour[0];
whitepos--;
if (whitepos == 0 || whitepos >= numcolor){
  whitepos = numcolor-1;
}

for (int t=0; t<numcolor; t++){
    colour[t]=colour[t+1];
    if (t == numcolor-1){
    colour[t] = pp;
    }
}
}


void selectcolorArray(){
  numcolor = pgm_read_byte(&selectColor_array[arrayn].numcolor);
  if ((effect_function == *pers_color && varON == 2) || (effect_function == *rainbow_1 && varON == 2) || (effect_function == *pers_block && varON == 2)){ //&& colorMode != 4
    numcolor=15;  
    for (int i = 0; i < 15; i++){
      newColour[i] = pgm_read_byte(&selectColor_array[arrayn].colour[i]); 
      // if (colorMode == 4){
      //   newColour[i] = pgm_read_byte(&selectColor_array[arrayn].colour[i]); 
      // }
      // else {
      //   newColour[i] = changeColourFcn(colorMode, newColour[i], 0, 255);
      // }
    }
  }
  else {     // else if (dir == 2)
    for (int i = 0; i < 15; i++){
      colour[i] = pgm_read_byte(&selectColor_array[arrayn].colour[i]); 
//      Serial.println(colour[i]);
    }
  }  
//if (syncEsp){espNowMessage = true;   EspNowMessageType = 7;  };                                                
}

void fillLongxArray(uint8_t colour, uint16_t num_leds){
      for (int i = 0; i < num_leds; i++){
        longxArray[i]=colour;
      }
      return;
}

void fillColourArray (uint8_t colour[], uint8_t mainColour, int var[], int diff[]){
        for (int i = 0; i<10; i++){
          colour[i]=mainColour+var[i]+diff[i];
        }
        return;
}

void fillArrayRainbow(uint8_t fillcase){  
  y0r++;
  hue=y0r;
  for (int i = 0; i < NUM_LEDS; i++){

      if (i % (int)cfactor2 == 0){
          hue++;
      }
    
      switch(fillcase){
        case 1: {
          longxArray[i]=hue; 
        } break;
        case 2: {
          blockArray[i]=hue; 
          longxArray[i]=hue; 
        } break;
      }
  }
  return;
}

    
void fillArrayGradient(uint8_t fillcase, uint8_t y0r, int setDifference){
    dir0=1;
  
    for(int i = 0; i < NUM_LEDS; i++ ){
      switch (fillcase){
        case 1:{
          longxArray[i] = y0r;
        } break;
        case 2: {
          longxArray[i] = y0r;
          blockArray[i] = y0r;
        } break;
        case 3: {
          blockArray[i] = y0r;
        } break;
      }            
      
      if (NUM_LEDS > 250){
        if (i % setDifference == 0){
          y0r+=(1*dir0);
        }
      }
      else {
      y0r+=setDifference*dir0;
      }

    if (((y0r > ymax4 && y0r <= ymax4+setDifference) || (y0r <= setDifference && ymax4 >= 255-setDifference)) && dir0 == 1){
      dir0 = -1;
      y0r=ymax4-(y0r-ymax4);
    }

    else if (((y0r < ymin4 && y0r >= ymin4-setDifference) || (y0r >= 255-setDifference && ymin4 <= setDifference)) && dir0 == -1){ 
      dir0 = 1;
      y0r=ymin4+(ymin4-y0r);
    }
    }
}

// void fillArrayRainbow(uint8_t blockArray[], uint16_t longxArray[]){
//         y0r++;
//         hue=y0r;
//         for (int i = 0; i < NUM_LEDS; i++){
//         hue++;
//         blockArray[i]=hue;
//         longxArray[i]=hue;    
//         }
// }

void fillNUM_LEDS1(uint8_t arrayType[], int NUM_LEDS){
       for(int i = 0; i < NUM_LEDS; i++ ){
       leds[i] = CHSV(arrayType[colourlu],satval[satlu],brigh[brighlu]);
        
        brighlu++;
        if (glowON != 11){
          if (brighlu >= numbrigh){brighlu = 0;}
        }

        satlu++;
        if (satON != 11){
          if (satlu >= numsat){satlu = 0;}
        }
       
       colourlu++;
       if (colourlu > 9){colourlu = 0;}

       } 

       handleGlitter();
       FastLED.show();

       satlu=0;
       brighlu=0;
       colourlu=0;
       return;
}

// void fillRainbow2(uint16_t arrayType[], uint8_t fillcase){

// switch (fillcase){
//   case 1: {
//         for(int i = 0; i < NUM_LEDS/2; i++ ){
//               arrayType[(NUM_LEDS/2)-i] = ysr;
//               arrayType[(NUM_LEDS/2)+i] = ysr;

//               if (NUM_LEDS > 300){
//                 if (i % setDifference == 0){
//                   ysr+=1;
//                 }
//               }
//               else {
//               ysr+=setDifference;
//               }
//         }
//   }
//   break;
//   case 2: {
//         for(int i = 0; i < NUM_LEDS; i++ ){
//               arrayType[i] = ysr;

//               if (NUM_LEDS > 300){
//                 if (i % setDifference == 0){
//                   ysr+=1;
//                 }
//               }
//               else {ysr+=setDifference;}
//             }

//   }
//   break;
//   return;
// }
// }


uint8_t changeColourFcn(int selectMode, uint8_t yvIn, uint8_t yvalmin, uint8_t yvalmax){
  switch (selectMode){
    case 0: { yvIn = yval; } break;  // Serial.println (yvIn); } break;   
    case 1: { yvIn = random(yvalmin, yvalmax); } break;   
    case 2: { yvIn = random(yvalmin, yvalmax);  while ((yvIn >= ymin && yvIn <= ymax) || (yvIn >= ymin1 && yvIn <= ymax1)){yvIn=random(yvalmin, yvalmax);}; } break;  
    case 3: { yvIn=random(yvalmin, yvalmax);   while (yvIn < ymin || (yvIn > ymax && yvIn < ymin1) || yvIn > ymax1){yvIn=random(yvalmin, yvalmax);}; } break;   
    case 4: { uint8_t rando = random(0,15); yvIn=colour[rando]; } break; 
    default: { yvIn = 0; } break;
  }
  return yvIn;
}

uint8_t changeColourFcn2(int selectMode, uint8_t yvIn, uint8_t yvMem, uint8_t yvalmin, uint8_t yvalmax){
  switch (selectMode){
    case 0: { yvIn = yval; } break; // Serial.println (yvIn); } break;   
    case 1: { yvIn = yvMem + random(yvalmin, yvalmax); } break;  // 
    case 2: { yvIn = yvMem + random(yvalmin, yvalmax);   while ((yvIn >= ymin && yvIn <= ymax) || (yvIn >= ymin1 && yvIn <= ymax1)){yvIn= yvMem + random(yvalmin, yvalmax);}; } break; 
    case 3: { yvIn = yvMem + random(yvalmin, yvalmax);   while (yvIn < ymin || (yvIn > ymax && yvIn < ymin1) || yvIn > ymax1){yvIn = yvMem + random(yvalmin, yvalmax);}; } break;   
    case 4: { yvIn = colour[random(0,15)]; while (yvIn == yvMem){yvIn = colour[random(0,15)];}; } break;
    case 5: { yvIn = yval; if (evenOddCounter % 2){yvIn = z5;}; } break; 
    default: { yvIn = 0; } break;
  }
  return yvIn;
}

void procesColourMode(){
      if ((effect_function == *pers_color || effect_function == *pers_block) && numcolor <= 14){
      numcolor++;
      newColors++;
      }
      else {
  //      if ((effect_function == *static_glow && colorMode <= 3) ||  (effect_function == *s7_strings && colorMode <= 3) || (effect_function == *snow_flakes && colorMode <= 4) || (effect_function == *sparkling && colorMode <= 4) || (effect_function == *snow_storm && colorMode <= 4) || (effect_function == *random_led && colorMode <= 4) || (effect_function == *random_string && colorMode <= 3) || (effect_function == *twinkle && colorMode <= 4) || (effect_function == *static_glow_2 && colorMode <= 3) || (effect_function == *sparkling_2 && colorMode <=4) || (effect_function == *meteor && colorMode <=4) || (effect_function == *snow_flakes_2 && colorMode <=4)){
        colorMode++;
        forcedColourChange = true;
        INTERVAL7=5000;  
      }
return;      
}

uint8_t fadeFnc(uint8_t value, uint8_t valueTo){
    if (value < valueTo){
      if (valueTo-value <=128){
        value++;
      }   
      else {value--;}
    }
    else if (value > valueTo){
      if (value-valueTo <=128){
        value--;  
      }
      else {value++;}
    }
  return value;
}


void initializeGlitter(){
  if (glitterON){
  FPS = 30;
  }
  else {
    FPS = 20;
    }
  return;  
}
/*
 * specifically handles the twinkles. Modified from Mark Kriegman's code. 
 * https://gist.github.com/kriegsman/5408ecd397744ba0393e
 */



void colortwinkles(){
fadeOutSpeed=35;
Stwinkle = random(150,256);

if (millis() - previousMillis36 > INTERVAL7 && varON == 2 && colorMode == 4) {
      arrayn = random(arrayCount);
      updateOled(24, 40, &arrayn);
      selectcolorArray();
      INTERVAL7=(interval9/5)*timeArray2[random(0,6)]*timefactor3;
      updateOledFloat(88, 0, &INTERVAL7, 0); 
      previousMillis36 = millis();
      T=0;        
}

if (colorMode == 0){
     yval1=yval;}
 else if (colorMode == 1){
     yval1=random(256);} 
 else if (colorMode == 2){
     yval1=random(256);
      while ((yval1 >= ymin && yval1 <= ymax) || (yval1 >= ymin1 && yval1 <= ymax1)){
      yval1=random(256);
      }}
 else if (colorMode == 3){
     yval1=random(256);
      while ((yval1 < ymin || yval1 > ymax) && (yval1 < ymin1 || yval1 > ymax1)){
      yval1=random(256);
      }}
 else if (colorMode == 4){
     yval1=colour[random(0, 15)];
 }
 else if (colorMode == 5){
  colourChangeDelay++;
  if (colourChangeDelay >= 200/changeSpeed){
  yval1++;
  colourChangeDelay=0;}
 }
      
    brightenOrDarkenEachPixel(fadeInSpeed, fadeOutSpeed);

  // if (density == 0){
  //   DENSITY=setDifference;}
  // else if (density == 1){
  //   DENSITY=85;}
  // else if (density == 2){
  //   DENSITY=170;}
  // else if (density == 3){
  //   DENSITY=255;}    
  for (int k = 0; k<numsparks; k++){
    if( random(255) < setDifference ) {
      int pos = random(NUM_LEDS);
      if(!leds[pos]) {
        leds[pos] = CHSV(yval1,Stwinkle,150);
        setPixelDirection(pos, GETTING_BRIGHTER);
      }
    }
  }
}

void brightenOrDarkenEachPixel( fract8 fadeUpAmount, fract8 fadeDownAmount)
{
 for( uint16_t i = 0; i < NUM_LEDS; i++) {
    if( getPixelDirection(i) == GETTING_DARKER) {
      leds[i] = makeDarker( leds[i], fadeDownAmount);
    } else {
      leds[i] = makeBrighter( leds[i], fadeUpAmount);
      if( leds[i].r >= 255 || leds[i].g >= 255 || leds[i].b >= 255) { // 255 vervangen met BRIGH
        setPixelDirection(i, GETTING_DARKER);
      }
    }
  }
}

CRGB makeBrighter( const CRGB& color, fract8 howMuchBrighter) 
{
  CRGB incrementalColor = color;
  incrementalColor.nscale8( howMuchBrighter);
  return color + incrementalColor;
}

CRGB makeDarker( const CRGB& color, fract8 howMuchDarker) 
{
  CRGB newcolor = color;
  newcolor.nscale8( 255 - howMuchDarker);
  return newcolor;
}

uint8_t directionFlags[NUM_SET];

bool getPixelDirection( uint16_t i) {
  return directionFlags[i];
}

void setPixelDirection( uint16_t i, bool dir) {
  directionFlags[i] = dir;
}

/*
 * specifically handles the twinkles. Modified from Mark Kriegman's code. 
 * https://gist.github.com/kriegsman/36a1e277f5b4084258d9af1eae29bac4
 */

