/*
 * code involved in receiving and processing data. Utimately the change or how the code is affected, can be found in process_change.h
 * 
 * Thanks to AIRCOOOKIE for this part of the code. See WLED on github. https://github.com/Aircoookie/WLED
 */
 /*  IR_CODES
 *  CHANGE THE HEX CODE TO PERSONAL VALUES
 *  IR function name         IR hex code     byte that is passed onto the the processing function
*/    

//#define IR47_RELAY_CONTROL       0xFF08F7  //  This one is not enabled in this script

#define IR47_EXCLUDE             0xFF28D7  // byte 'z' Enables exclude boolean. When exclude is set to false, all presets are enable (this is requierd for switching on modes that may have been disabled.

// FREE AVAILABLE INPUTS (were useful before webinterface - not anymore)
#define IR47_YMINRED             0xFF10EF  // does nothing 
#define IR47_YMINGREEN           0xFF906F  // does nothing 
#define IR47_YMINBLUE            0xFFB04F  // does nothing 
#define IR47_YMIN                0xFF8877  // does nothing 
#define IR47_YMIN1               0xFF48B7  // does nothing 
#define IR47_YMAXRED             0xFF12ED  // does nothing 
#define IR47_YMAXGREEN           0xFFB847  // does nothing 
#define IR47_YMAXBLUE            0xFF9867  // does nothing 
#define IR47_YMAX                0xFFA857  // does nothing 
#define IR47_YMAX1               0xFF9A65  // does nothing 
#define IR47_STATIC_COLOUR_UP    0xFF926D  // does nothing 
#define IR47_STATIC_COLOUR_DOWN  0xFFF807  // does nothing 

// additional system values. Also saved in EEPROM.
#define IR47_NUM_LEDS_UP         0xFFD827  // Increases LED NUMBER by 50
#define IR47_NUM_LEDS_DOWN       0xFFE817  // Decreases LED number by 50
#define IR47_MODE_EEPROM         0xFFD22D  // Enables/ disables MODES

// cycle values
#define IR47_CYCLE_MODE          0xFF52AD  // 
#define IR47_RANDOM_MODE         0xFFEA15  // 
#define IR47_FADE_MODE           0xFF827D  // 
#define IR47_TIME_LONGER         0xFF629D  // 
#define IR47_TIMER_SHORTER       0xFF4AB5  // 
#define IR47_EDIT_MODE_STATUS    0xFF00FF  // 

// variables mid section
#define IR47_NUMBRIGH_UP         0xFFCA35  // 
#define IR47_NUMBRIGH_DOWN       0xFFC23D  // 
#define IR47_NUMSPARK_UP         0xFFAA55  // 
#define IR47_NUMSPARK_DOWN       0xFF807F  // 
#define IR47_SPARK_BRI_UP        0xFF6A95  // 
#define IR47_SPARK_BRI_DOWN      0xFF18E7  // 
#define IR47_DENSITY             0xFFFA05  // 

// variables lower section
#define IR47_BRI_UP              0xFF0AF5  // 'f'
#define IR47_BRI_DOWN            0xFFA25D  // 'g'
#define IR47_MODE_UP             0xFF609F  // 'a'
#define IR47_MODE_DOWN           0xFF22DD  // 'b'
#define IR47_COLORMODE_UP        0xFF02FD  // 'c'
#define IR47_COLORMODE_DOWN      0xFFE21D  // 'd'
#define IR47_COLOR_UP            0xFFA05F  // 'h'
#define IR47_COLOR_DOWN          0xFF7A85  // 'i'
#define IR47_GLITTER             0xFFE01F  // 'e'
#define IR47_GLOW_MODE           0xFFF00F  // 'j'
#define IR47_VARIATION_MODE      0xFF42BD  // 'n'
#define IR47_SATURATION_UP       0xFF50AF  // 'k'
#define IR47_SATURATION_DOWN     0xFF708F  // 'o'
#define IR47_SPEED_UP            0xFF7887  // 'l'
#define IR47_SPEED_DOWN          0xFF58A7  // 'p'
#define IR47_SET_addi_VAR_UP     0xFFC03F  // 'm'
#define IR47_SET_addi_VAR_DOWN   0xFF40BF  // 'q'
 

void initIR()
{
  if (irEnabled > 0){
    irrecv = new IRrecv(IR_PIN);
    irrecv->enableIRIn();
    }
} 

void handleIR(){
  if (irEnabled > 0 && millis() - irCheckedTime > 120){
    irCheckedTime = millis();
    if (irEnabled > 0){
      if (irrecv == NULL){ 
        initIR(); return;
      }
      if (irrecv->decode(&results))      {
        if (results.value != 0){ // only print results if anything is received ( != 0 )
        }
        decodeIR(results.value);
        irrecv->resume();
      }
    } 
    else if (irrecv != NULL){
      irrecv->disableIRIn();
      delete irrecv; irrecv = NULL;
    }
  }
}

void decodeIR(uint32_t code){
//Serial.println(code);  
decodeIR47(code); // this program decodes the IR code in 2 steps, this is because of easier implementation (code converted from arduino MEGA).
processChange();
return;
} 

void decodeIR47(uint32_t code){
//  Serial.println("decode_IR47");
  switch (code) {
    case IR47_EXCLUDE            : memoryByte='z';                      break;
    
    case IR47_YMINRED            :                                     break; // does nothing 
    case IR47_YMAXRED            :                                     break; // does nothing 
    case IR47_YMINGREEN          :                                     break; // does nothing 
    case IR47_YMAXGREEN          :                                     break; // does nothing     
    case IR47_YMINBLUE           :                                     break; // does nothing 
    case IR47_YMAXBLUE           :                                     break; // does nothing 
    case IR47_YMIN               :                                     break; // does nothing 
    case IR47_YMAX               :                                     break; // does nothing 
    case IR47_YMIN1              :                                     break; // does nothing 
    case IR47_YMAX1              :                                     break; // does nothing 
    case IR47_STATIC_COLOUR_UP   :                                     break; // does nothing 
    case IR47_STATIC_COLOUR_DOWN :                                     break; 
    case IR47_NUM_LEDS_UP        : memoryByte='1';                     break;
    case IR47_NUM_LEDS_DOWN      : memoryByte='2';                     break;
    case IR47_MODE_EEPROM        : memoryByte='3';                     break;
    case IR47_CYCLE_MODE         : memoryByte='A';                     break;
    case IR47_RANDOM_MODE        : memoryByte='B';                     break;
    case IR47_FADE_MODE          : memoryByte='C';                     break;
    case IR47_TIME_LONGER        : memoryByte='D';                     break;
    case IR47_TIMER_SHORTER      : memoryByte='E';                     break;
    case IR47_EDIT_MODE_STATUS   : memoryByte='x';                     break;
    case IR47_NUMBRIGH_UP        : memoryByte='v';                     break;
    case IR47_NUMBRIGH_DOWN      : memoryByte='w';                     break;
    case IR47_NUMSPARK_UP        : memoryByte='r';                     break;
    case IR47_NUMSPARK_DOWN      : memoryByte='s';                     break;
    case IR47_SPARK_BRI_UP       : memoryByte='t';                     break;
    case IR47_SPARK_BRI_DOWN     : memoryByte='u';                     break;
    case IR47_DENSITY            : memoryByte='y';                     break;
    case IR47_BRI_UP             : memoryByte='f';                     break;
    case IR47_BRI_DOWN           : memoryByte='g';                     break;
    case IR47_MODE_UP            : memoryByte='a';                     break;
    case IR47_MODE_DOWN          : memoryByte='b';                     break;
    case IR47_COLORMODE_UP       : memoryByte='c';                     break;
    case IR47_COLORMODE_DOWN     : memoryByte='d';                     break;
    case IR47_COLOR_UP           : memoryByte='h';                     break;
    case IR47_COLOR_DOWN         : memoryByte='i';                     break;
    case IR47_GLITTER            : memoryByte='e';                     break;
    case IR47_GLOW_MODE          : memoryByte='j';                     break;
    case IR47_VARIATION_MODE     : memoryByte='n';                     break;
    case IR47_SATURATION_UP      : memoryByte='k';                     break;
    case IR47_SATURATION_DOWN    : memoryByte='o';                     break;
    case IR47_SPEED_UP           : memoryByte='l';                     break;
    case IR47_SPEED_DOWN         : memoryByte='p';                     break;
    case IR47_SET_addi_VAR_UP    : memoryByte='m';                     break;
    case IR47_SET_addi_VAR_DOWN  : memoryByte='q';                     break;
    default: memoryByte=0; return;
  } 
}

/*
 * This function ultimately decodes the received IR values
 */

void processChange(){
// Serial.println("entered processchange event");
if (memoryByte == 'a')      {modeUp = true;}
else if (memoryByte == 'b') {modeDown = true;}
else if (memoryByte == 'c') {procesColourMode();}
else if (memoryByte == 'd'){ 
      if ((effect_function == *random_string && colorMode >= 2) || (effect_function != *pers_color && effect_function != *random_string && colorMode >= 1)){ 
        colorMode--;
        forcedColourChange = true;
        INTERVAL7=5000;  
        }
       else if ((effect_function == *pers_color || effect_function == *pers_block) && numcolor >= 2){
       numcolor--;
       newColors++;
       }
}
  
else if (memoryByte == 'e'){
  if (glowON != 3 && (!glitterON)){
    glitterON = true;
    FPS=30;
  }
  else if (glowON != 3 && (glitterON)){
    glitterON = false;
    FPS=20;
  }  
}

else if (memoryByte == 'f'){if (BRIGH <= 250){BRIGH+=5;}}
else if (memoryByte == 'g'){if (BRIGH >= 5) {BRIGH-=5;}}
 
else if (memoryByte == 'k'){if (S <= 250){S+=5;}} 
else if (memoryByte == 'o'){if (S >= 5) {S-=5;}}

else if (memoryByte == 'r'){
  if (effect_function == *sparkling){
  if (numsparks < 30){numsparks++;}
  }
  else if (effect_function == *snow_flakes || effect_function == *s7_strings || effect_function == *snow_storm || effect_function == *sparkling_2 || effect_function == *meteor || effect_function == *snow_flakes_2){
  if (numsparks < 20){numsparks++;}    
  }
}
else if (memoryByte == 's'){
  if (numsparks > 1) {numsparks--;}
}

else if (memoryByte == 't'){if (BrF <= 250){BrF+=5;}}   
else if (memoryByte == 'u'){if (BrF >= 5) {BrF-=5;}}
else if (memoryByte == 'v'){if (numbrigh < 16){numbrigh++; convBrigh=waveTimeBr/numbrigh;}}  
else if (memoryByte == 'w'){if (numbrigh > 1) {numbrigh--; convBrigh=waveTimeBr/numbrigh;}}

else if (memoryByte == 'l'){ 
       if (changeSpeed < 40){
       changeSpeed+=2;}
       else if (changeSpeed >= 40 && changeSpeed <= 300){
       changeSpeed+=10;}
       else if (changeSpeed > 300 && changeSpeed <= 1000){
       changeSpeed+=50;}
       else if (changeSpeed > 1000){
       changeSpeed+=500;}  
}

else if (memoryByte == 'p'){
        if (changeSpeed < 40){
        changeSpeed-=2;}
        else if (changeSpeed >= 40 && changeSpeed <= 300){
        changeSpeed-=10;}
        else if (changeSpeed > 300 && changeSpeed < 1500){
        changeSpeed-=50;}
        else if (changeSpeed >= 1500){
        changeSpeed-=500;} 
}
  
else if (memoryByte == 'h'){ 
    if (colorMode != 4 && effect_function != *rainbow_5 && effect_function != *pers_color && effect_function != *gradient && effect_function != *pers_block && effect_function != *rainbow_3 && effect_function != *rainbow_1){
        yval+=3;
        if (effect_function == *static_glow){
        forcedColourChange = true;
        }
        }

    else if ((effect_function == *rainbow_1 || effect_function == *pers_color || effect_function == *pers_block) || colorMode == 4){  
        arrayn++;
        if (arrayn >= arrayCount){
          arrayn=0;
        }
        selectcolorArray(); 
        newColors++;                  
        }
        
    else if ((effect_function == *gradient || effect_function == *rainbow_3) && selectColor <= 12){
        selectColor++;
        dir1=1;
        ymax4 = pgm_read_byte(&selectColor_data[selectColor].ymax4); 
        ymin4 = pgm_read_byte(&selectColor_data[selectColor].ymin4);
        setDifference = pgm_read_byte(&selectColor_data[selectColor].setDifference);  
        yval1=ymin4;      
        dir0=1;

        if (effect_function == *rainbow_3){
          setDifference = 4;
        }                 
    }
    
    else if (effect_function == *rainbow_5 && offdis < 15){
    offdis++;  
  }    
}

else if (memoryByte == 'i'){
    if (colorMode != 4 && effect_function != *rainbow_5 && effect_function != *pers_color && effect_function != *gradient && effect_function != *pers_block && effect_function != *rainbow_3 && effect_function != *rainbow_1 && effect_function != *palettes){
        yval-=3;
        if (effect_function == *static_glow){
        forcedColourChange = true;
        }
    }
    else if ((effect_function == *rainbow_1 || effect_function == *pers_color || effect_function == *pers_block) || colorMode == 4){  
        arrayn--;
        if (arrayn < 0 || arrayn > arrayCount){
          arrayn=arrayCount-1;
        }
        selectcolorArray();
        newColors++;      
        }
        
      else if ((effect_function == *gradient || effect_function == *rainbow_3) && selectColor >= 1){
        selectColor--;
        dir1=1;
        ymax4 = pgm_read_byte(&selectColor_data[selectColor].ymax4); 
        ymin4 = pgm_read_byte(&selectColor_data[selectColor].ymin4);
        setDifference = pgm_read_byte(&selectColor_data[selectColor].setDifference);
        yval1=ymin4;
        dir0=1;

        if (effect_function == *rainbow_3){
          setDifference = 4;
        }
      }

  else if (effect_function == *palettes){
      gCurrentPaletteNumber = addmod8( gCurrentPaletteNumber, 1, gGradientPaletteCount);
      gTargetPalette =( gGradientPalettes[gCurrentPaletteNumber] );
      }

  else if (effect_function == *rainbow_5 && offdis > 1){
    offdis--;  
  }                   
}
  
else if (memoryByte == 'j'){
  glowON++; 
  if (glowON > 8){
    glowON = 0;
    }
}
        

else if (memoryByte == 'z'){
  if (excludeModes){excludeModes = false;}
  else if (!excludeModes){excludeModes = true;}   
  }

else if (memoryByte == 'y'){ // currently only affects twinkle program
    // density++;
    // if (density == 0){
    //   DENSITY=setDifference;}
    // else if (density == 1){
    //   DENSITY=85;}
    // else if (density == 2){
    //   DENSITY=170;}
    // else if (density == 3){
    //   DENSITY=255;}
    // else if (density == 4){
    // density=-1;
    // }
}
  
else if (memoryByte == 'x'){ 
        if (effect_function != *pers_color){
          if (dir == 1){
          dir = 2;
          dir1= -1;}
          else if (dir == 2){
          dir = 1;
          dir1 = 1;}
          }
        else if (effect_function == *pers_color){
            if (!whiteON){
              whiteON = true;
            }
            else if (whiteON){
              whiteON = false;
           }
        }  
}
  
else if (memoryByte == 'n'){
    varON++;
    if (varON > 2){
      varON=0;
    }
    for (int p=0; p<10; p++){
      if (varON == 0){
          yvar[p]= 0;
          yvarg[p]= 0;
          }
      else{
        yvar[p]=yvarC[p];
        yvarg[p]=yvargC[p];  
        }
     } 
}         

else if (memoryByte == 'A'){
        if (!cycle){
        cycle = true;}
        else if (cycle){
        cycle = false;} 
}
  
else if (memoryByte == 'B'){
        if (!randomCycle){
        randomCycle = true;}
        else if (randomCycle){
        randomCycle = false;}
}

else if (memoryByte == 'q'){
    if (effect_function != *pers_block){
        if (setDifference >= 1) {
          if (setDifference < 25){
          setDifference-=1;
          }
          else if (setDifference >= 25){
          setDifference-=5;
          }
        diffbeat=60000/(setDifference*4*100);
        diffbeat2=diffbeat/2;   
        setDifference2 = setDifference+5;
        }
    }
  if ((effect_function == *pers_block || effect_function == *rainbow_6) && colorlength > 2){
    colorlength--; 
    newColors++;       
  }

  if (effect_function == *xmas_string || effect_function == *xmas_singles){
          fillxmasArray();        
      if (effect_function == *xmas_string){
            ysr=0;
      }
      else if (effect_function == *xmas_singles){
              for (int i = 0; i < 10; i++){
                colour[i]=(numAmax/10*i);
              }
      }
  }
  } 

else if (memoryByte == 'C'){
        if (!fadeFirst){
        fadeFirst = true;}
        else if (fadeFirst){
        fadeFirst = false;} 
  }

else if (memoryByte == 'D'){ 
      if (cycleTime < 900000){
        cycleTime+=60000;
        }
      else if (cycleTime >= 900000){
        cycleTime+=300000;
        }
      cycleT=0;
      previousMillis44 = millis();
      previousMillis45 = millis();    
}
else if (memoryByte == 'E'){ 
      if (cycleTime <= 900000){
        cycleTime-=60000;
        }
      else if (cycleTime > 900000){
        cycleTime-=300000;
        }
      cycleT=0;
      previousMillis44 = millis();
      previousMillis45 = millis(); 
}

 else if (memoryByte == 'm'){ 
    if (effect_function != *pers_block){
          if (setDifference < 25){
          setDifference+=1;
          }
          else if (setDifference >= 25){
          setDifference+=5;
          }
        diffbeat=60000/(setDifference*4*100);
        diffbeat2=diffbeat/2;   
      setDifference2 = setDifference+5;     
    }

    if ((effect_function == *pers_block || effect_function == *rainbow_6) && colorlength < 50){
    colorlength++; 
    newColors++;       
    }      
    
    if (effect_function == *xmas_string || effect_function == *xmas_singles){
          fillxmasArray();
                  
      if (effect_function == *xmas_string){
          ysr=0;

    }
    else if (effect_function == *xmas_singles){
          for (int i = 0; i < 10; i++){
            colour[i]=(numAmax/10*i);
          }
    }
    }        
 }

else if (memoryByte == '3'){enableMode();}// usual code, this function allows to enable or disable certain presets.
else if (memoryByte == '1'){if (NUM_LEDS <= 250){NUM_LEDS+=50;} EEPROM.put(offsetof(storeInEEPROM, NUM_LEDS) , NUM_LEDS);  EEPROM.commit();}
else if (memoryByte == '2'){if (NUM_LEDS >= 100){NUM_LEDS-=50;} EEPROM.put(offsetof(storeInEEPROM, NUM_LEDS), NUM_LEDS);  EEPROM.commit();}

//EEPROM.commit();

if ((memoryByte == 'a') || (memoryByte == 'b')){ 
memoryByte = 0;  
return;
}
else{
displayOled();
memoryByte = 0;
return;
}
}
