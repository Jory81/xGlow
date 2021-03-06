/*
 * initializes the LED presets
 */
void handleModeSwitch(){ // HANDLE SWITCHING MODUS
  if ((millis() - previousMillis45 >= cycleTime && (cycle) && (outOfModus)) || (modeUp) || (modeDown)) {
     executeScript=false;
      if (!randomCycle){
        if (modeUp){programMode++;}
        else if (modeDown){programMode--;}
        else if (cycle) {programMode++;} 
          if (programMode >= modeCount){programMode = 0;}
          else if (programMode < 0){programMode = modeCount-1;}  
        if ((cmode[programMode]) || (!excludeModes)){
        changeState();
        }
        else if (!cmode[programMode]){      
          while (!cmode[programMode]){  
              if (modeUp){programMode++;}
              else if (modeDown){programMode--;}
              else if (cycle){programMode++;} 
                    if (programMode >= modeCount){programMode = 0;}
                    else if (programMode < 0){programMode = modeCount-1;}             
          }
        changeState();
        }
      }
      else if (randomCycle){
        uint8_t newProgramMode = random(0,modeCount+1);   
        if (((cmode[newProgramMode]) && (newProgramMode != programMode)) || (!excludeModes)){
          programMode = newProgramMode;
          changeState();} 
        else if ((!cmode[newProgramMode]) || (newProgramMode == programMode)){
          while ((!cmode[newProgramMode]) || (newProgramMode == programMode)){ newProgramMode = random(0,modeCount+1); }
       programMode = newProgramMode;
       changeState();}
      }
  cycleT=0;
  previousMillis44 = millis();           
  previousMillis45 = millis();
  }
}

void changeState(){
          if (fadeFirst){
          modeUp = false;
          modeDown = false;
          executeScript = false;
          dimming = true;
          changeModus = false;
          }
          
          else if (!fadeFirst){
          modeUp = false;
          modeDown = false;     
          changeModus = true;
          fadeCounter=0;
          }
          return;
}

void handleModeInitialization(){ // HANDLE MODUS SETTINGS
if (changeModus){
  switch (programMode){ 
    case 0: {        effect_function = static_glow;       if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=22;          changeSpeed=100;        setDifference=7;      colorMode=0;      yval=10;        }; forcedColourChange = true  ;} break;
    case 1: {        effect_function = static_glow_2;     if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=23;          changeSpeed=100;        setDifference=7;      colorMode=2;                      };  }  break; 
    case 2: {        effect_function = static_glow;       if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=23;          changeSpeed=100;        setDifference=7;      colorMode=0;      yval=18;        }; forcedColourChange = true ;} break;
    case 3: {        effect_function = static_glow;       if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=100;        setDifference=80;     colorMode=0;      yval=217;       }; forcedColourChange = true  ;} break;                                                             
    case 4: {        effect_function = static_glow_2;     if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=100;        setDifference=80;     colorMode=1;                      };  } break;
    case 5: {        effect_function = colourSplash;      if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=3;           changeSpeed=35;         setDifference=7;      colorMode=2;                      };  } break;
    case 6: {        effect_function = palettes;          if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=11;          changeSpeed=50;         setDifference=1;      gCurrentPaletteNumber=7;          };    gTargetPalette = gGradientPalettes[gCurrentPaletteNumber];  y0r=0;   } break;
    case 7: {        effect_function = palettes_2;        if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=50;         setDifference=45;                                       }; y0r=0;     gCurrentPaletteNumber=11;     gTargetPalette = gGradientPalettes[gCurrentPaletteNumber] ;} break;
    case 8: {        effect_function = rainbow_1;         if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=10;          changeSpeed=20;         setDifference=1;      colorMode=0;    arrayn=7;         selectcolorArray();     };} break;
    case 9: {        effect_function = rainbow_2;         if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=2;           changeSpeed=30;         setDifference=4;      colorMode=0;    arrayn=7;         selectcolorArray();     };} break;
    case 10: {       effect_function = rainbow_3;         if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=4;           changeSpeed=100;        setDifference=4;      colorMode=0;                      }; colour[0]= yval1+0;        colour[1]= yval1+15;        colour[2]= yval1+30;        colour[3]= yval1+45;        colour[4]= yval1+60;        colour[5]= yval1+75;        colour[6]= yval1+90;        colour[7]= yval1+105;        colour[8]= yval1+120;        colour[9]= yval1+135; };   yval1=ymin2;       for (int i=0; i<10; i++){dirArray[i]=1;} break;                                                     
    case 11: {       effect_function = rainbow_4;         if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=200;        setDifference=7;                                        }; ysr=0;  } break;    
    case 12: {       effect_function = rainbow_5;         if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=30;         setDifference=5;                                        }; if (tower) {offdis=1;} else {offdis=3;}    } break;   
    case 13: {       effect_function = rainbow_6;         if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=1500;       setDifference=25;                                       colorlength=10*cfactor2; };  y0rCounter=0;         numcolor=1;        yint=0;        colour[0] = 75;        colour[1] = 230;        colour[2] = 175;        colour[3] = 25;        colour[4] = 100;        colour[5] = 200;        colour[6] = 50;        colour[7] = 150;        colour[8] = 0;        colour[9] = 125;} break;    
    case 14: {       effect_function = rainbow_7;         if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=100;        setDifference=1;                                        }; dir1 = 1;    offdis=5;        y0r=ymin3+10;        colorCount=0;        ledspercolor=NUM_LEDS/range ;} break;   
    case 15: {       effect_function = gradient;          if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=6;           changeSpeed=200;        setDifference=1;      colorMode=0;                      }; yval1=ymin4;        } break;
    case 16: {       effect_function = s7_strings;        if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=110;        setDifference=10;     colorMode=4;    arrayn=0;         selectcolorArray();   numsparks=5*cfactor2;  };     ir[0]=0;        ir[1]=0;    previousMillis9=millis();        previousMillis10=millis();        previousMillis12=millis();          } break;
    case 17: {       effect_function = s7_strings;        if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=110;        setDifference=15;     colorMode=4;    arrayn=0;         selectcolorArray();  numsparks=1;   };     i[0]=NUM_LEDS;               previousMillis9=millis();        previousMillis10=millis();        previousMillis12=millis();    } break;                   
    case 18: {       effect_function = s7_strings;        if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=110;        setDifference=95;     colorMode=4;    arrayn=0;         selectcolorArray();   numsparks=5*cfactor2; };     ir[0]=0;        ir[1]=0;    previousMillis9=millis();        previousMillis10=millis();        previousMillis12=millis();           } break;
    case 19: {       effect_function = snow_flakes;       if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=125;        setDifference=7;      colorMode=4;    arrayn=0;         selectcolorArray();   numsparks=7*cfactor2;  };   offdis = offdisC;       sF=1;           previousMillis8=millis();     } break;        
    case 20: {       effect_function = snow_flakes_2;     if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=125;        setDifference=7;      colorMode=1;                      numsparks=7*cfactor2; }; sF=1;      offdis = offdisC;      partialArrayCounter=0;     forcedColourChange = true;      } break;
    case 21: {       effect_function = snow_storm;        if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=130;        setDifference=7;      colorMode=1;                      numsparks=5*cfactor2;}; yval1=random(125,225);        hh=NUM_LEDS;        offmin=1;        offmax=1;     sparkSpeed=120;       rrhh=-1;        poshh=-1;        flakeCounter=0;    offdis=cfactor2;   } break;       
    case 22: {       effect_function = snow_flakesR;      if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=125;        setDifference=7;                                        numsparks=7*cfactor2; }; offdis = offdisC;           sF=1;         previousMillis8=millis();     } break;
    case 23: {       effect_function = sparkling;         if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=130;        setDifference=7;      colorMode=2;                      numsparks=10*cfactor2;}; sparkSpeed=78;                        sparkSpeed=98;        yval1=random(125,225);        yy=0;        hh=NUM_LEDS;    variant=0;        offmin=15*cfactor2;        offmax=15*cfactor2;        offdis=1;       readyToChange = true;      } break;                 
    case 24: {       effect_function = sparkling_2;       if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=135;        setDifference=7;      colorMode=1;                      numsparks=cfactor2*3;  }; yval1=random(125,225);       sparkSpeed=98;      yy=0;        hh=NUM_LEDS;        variant=0;        offmin=13*cfactor2;        offmax=10*cfactor2;        offdis=1;        readyToChange = true;         numcolor=5; } break;                       
    case 25: {       effect_function = sparklingR;        if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=130;        setDifference=7;                                        numsparks=10*cfactor2;}; sparkSpeed=78;                 sparkSpeed=98;        yval1=random(125,225);        yy=0;        hh=NUM_LEDS;    variant=0; offmin=15*cfactor2;        offmax=15*cfactor2;        offdis=1;       readyToChange = true;     } break;
    case 26: {       effect_function = twinkle;           if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=30;         setDifference=1;      colorMode=1;                      }; density =cfactor2;} break;
    case 27: {       effect_function = random_led;        if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=30;         setDifference=40;     colorMode=5;                      };} break;                   
    case 28: {       effect_function = random_string;     if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=2000;                             colorMode=1;                      colorlength=16;};} break;   
    case 29: {       effect_function = pers_color;        if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=8;           changeSpeed=2000;                             colorMode=4;    arrayn=25;        colorlength=10*cfactor2;       selectcolorArray();   numcolor=5;};   } break;      
    case 30: {       effect_function = pers_block;        if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=1000;       setDifference=1;                      arrayn=4;         selectcolorArray();   numcolor=10;  };     newColors=1;   yint = 0;              } break;
    case 31: {       effect_function = xmas_string;       if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=200;        setDifference=7;                                        }; offdis=1;       fillxmasArray();    y0r=0;  } break; 
    case 32: {       effect_function = xmas_singles;      if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=100;        setDifference=7;                                        }; offdis=1;       fillxmasArray();    colour[0]=0;       colour[1]=0+(numAmax/10*1);        colour[2]=0+(numAmax/10*2);        colour[3]=0+(numAmax/10*3);        colour[4]=0+(numAmax/10*4);        colour[5]=0+(numAmax/10*5);        colour[6]=0+(numAmax/10*6);        colour[7]=0+(numAmax/10*7);        colour[8]=0+(numAmax/10*8);        colour[9]=0+(numAmax/10*9);  } break;
    case 33: {       effect_function = xmas_solid;        if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=40;         setDifference=7;                                        }; offdis=5;        ysr=0;} break;                            
    case 34: {       effect_function = splash;            if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=30;         setDifference=40;     colorMode=5;                      }; rn14=(random(100, 300)*cfactor2); }break;   
    case 35: {       effect_function = strobe;            if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=20;         setDifference=40;     colorMode=1;                      };} break;
    case 36: {       effect_function = meteor;            if (personalizedModes == true){ loadPersonalSettings(); } else { BriSPreset=0;           changeSpeed=50;         setDifference=10;     colorMode=2;                      numsparks=cfactor2*5;}; flakeCounter=0;               offmin=13;        offmax=13;     offdis = offdisC;       hh=NUM_LEDS;          endFlag=false;    poshh=NUM_LEDS;   if (tower){slingerSpeed=45/cfactor2;} else {slingerSpeed = changeSpeed;} ;} break; // for (int s=0;s<30; s++){y[s]=offdisC;}   
    case 37: {       effect_function = RGBmode;           changeSpeed=50;          } break;     
   }
  for (int k=0; k<21; k++){
    i[k]=NUM_LEDS; 
    a[k]=NUM_LEDS; 
    pos1[k]=NUM_LEDS;        
    pos2[k]=NUM_LEDS;        
    pos3[k]=NUM_LEDS;        
    pos4[k]=NUM_LEDS;
    num17[k]=NUM_LEDS;
    }
  for (int s=0; s<30; s++){
    rr[s]=-1;       
    pos[s]=NUM_LEDS;
    }
  fill_solid(leds, NUM_SET, CRGB::Black);
  FastLED.show();

  if (!personalizedModes){
    if (effect_function == xmas_string || effect_function == xmas_singles || effect_function == xmas_solid){
      glitterON = true;
    }
    else {
      glitterON = false;
    }
    initializeGlitter();
    String mergedString = "GTGLI"+String(glitterON);
    ws.textAll(mergedString);
  }

  if (effect_function != *xmas_string && effect_function != *xmas_singles){
    fillArrayRainbow(2);
  }
  readBriSData(BriSPreset);
  selectColor=-1;
  slowFactor=0;
  INTERVAL7=5000;
  outOfModus = true;
  dir1 = 1;
  if ((effect_function == *static_glow && programMode == 3)  || effect_function == colourSplash){
  dir = 1; xdir = 0;
  }
  else {
  dir = 2; xdir = 1;
  }
  diffbeat=60000/(setDifference*4*100);
  diffbeat2=diffbeat/2;            
  setDifference2 = setDifference+5;
  changeModus=false;
  executeScript=true;
  mergedString = "HSPE "; ws.textAll(mergedString);
  mergedString = "HY1N "; ws.textAll(mergedString);
  mergedString = "HY1O "; ws.textAll(mergedString);   
  displayOled();                            
}
}
