/*
 * initializes the LED presets
 */
void handleModeSwitch(){ // HANDLE SWITCHING MODUS
  if ((millis() - previousMillis45 >= cycleTime && (cycle)) || (modeUp) || (modeDown)) {
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
        programMode= random(0,modeCount+1);   
        if ((cmode[programMode]) || (!excludeModes)){
          changeState();} 
        else if (!cmode[programMode]){
          while (!cmode[programMode]){programMode= random(0,modeCount);}
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
    case 0: {        effect_function = static_glow;        changeSpeed=100;          colorMode=0;             setDifference=7;                yval1=30;                               forcedColourChange = true;   numsparks=0;} break;
    case 1: {        effect_function = rainbow_1;        changeSpeed=100;          colorMode=0;             setDifference=1;                arrayn=7; selectcolorArray();      numsparks=0; } break;
    case 2: {        effect_function = rainbow_2;        changeSpeed=100;          colorMode=0;             setDifference=4;                arrayn=7; selectcolorArray();      numsparks=0; } break;
    case 3: {        effect_function = rainbow_3;        changeSpeed=100;        colorMode=0;        setDifference=4;  yval1=ymin2;        colour[0]= yval1+0;        colour[1]= yval1+15;        colour[2]= yval1+30;        colour[3]= yval1+45;        colour[4]= yval1+60;        colour[5]= yval1+75;        colour[6]= yval1+90;        colour[7]= yval1+105;        colour[8]= yval1+120;        colour[9]= yval1+135;      numsparks=0;
                      for (int i=0; i<10; i++){dirArray[i]=1;} } break;                                                      
    case 4: {        effect_function = rainbow_4;        changeSpeed=200;        setDifference=7;           ysr=0;    numsparks=0;}  break;    
    case 5: {        effect_function = rainbow_5;       changeSpeed=30;        setDifference=1;    if (tower) {offdis=1;} else {offdis=3;}      numsparks=0;} break;    
    case 6: {        effect_function = rainbow_6;        changeSpeed=200;       setDifference=25;       y0rCounter=0;   colorlength=10;     numcolor=1;        yint=0;        colour[0] = 75;        colour[1] = 230;        colour[2] = 175;        colour[3] = 25;        colour[4] = 100;        colour[5] = 200;        colour[6] = 50;        colour[7] = 150;        colour[8] = 0;        colour[9] = 125;   numsparks=0;} break;     
    case 7: {        effect_function = s7_strings;        changeSpeed=110;          colorMode=4;             setDifference=15;               arrayn=0; selectcolorArray();        ir[0]=0;        ir[1]=0;    previousMillis9=millis();        previousMillis10=millis();        previousMillis12=millis();    numsparks=5*cfactor2;     rainbowON = true;        } break;
    case 8: {        effect_function = s7_strings;     changeSpeed=110;       colorMode=4;        setDifference=15;       arrayn=0;   selectcolorArray();        i[0]=NUM_LEDS;;        numsparks=1;        previousMillis9=millis();        previousMillis10=millis();        previousMillis12=millis();     rainbowON = true; } break;                    
    case 9: {        effect_function = snow_flakes;        changeSpeed=125;          colorMode=4;           setDifference=7;    offdis = offdisC;                arrayn=0;  selectcolorArray();        sF=1;           previousMillis8=millis();     numsparks=7*cfactor2;} break;         
    case 10: {       effect_function = snow_flakes_2;        changeSpeed=125;        setDifference=7;        colorMode=1;        sF=1;      offdis = offdisC;      partialArrayCounter=0;     forcedColourChange = true;     numsparks=7*cfactor2; } break;
    case 11: {       effect_function = sparkling;         changeSpeed=130;       sparkSpeed=78;         colorMode=2;        setDifference=7;         sparkSpeed=98;        yval1=random(125,225);        yy=0;        hh=NUM_LEDS;;    variant=0;        offmin=15*cfactor2;        offmax=15*cfactor2;        offdis=1;       readyToChange = true;      numsparks=10*cfactor2;} break;                  
    case 12: {       effect_function = sparkling_2;        changeSpeed=135;        setDifference=7;        colorMode=1;        yval1=random(125,225);       sparkSpeed=98;      yy=0;        hh=NUM_LEDS;;        variant=0;        offmin=13*cfactor2;        offmax=10*cfactor2;        offdis=1;        readyToChange = true;       INTERVAL7=5000;        numsparks=cfactor2*3;        numcolor=5;       colour[0]=217;        colour[1]=164;        colour[2]=0;        colour[3]=96;        colour[4]=55;            colour[5]=140;} break;                       
    case 13: {       effect_function = snow_storm;        changeSpeed=130;        colorMode=1;        setDifference=7;        yval1=random(125,225);        hh=NUM_LEDS;;        offmin=1;        offmax=1;     sparkSpeed=120;       rrhh=-1;        poshh=-1;        flakeCounter=0;    offdis=cfactor2;   numsparks=5*cfactor2;} break;                        
    case 14: {       effect_function = twinkle;       changeSpeed=30;        colorMode=1;        setDifference=1;        numsparks=0;      density =cfactor2;  } break;
    case 15: {       effect_function = random_led;        changeSpeed=30;        colorMode=5;        setDifference=40;           cfactor1=300/NUM_LEDS;   numsparks=0;} break;                   
    case 16: {       effect_function = random_string;       changeSpeed=2000;       colorlength=16;      colorMode=1;        numsparks=0;} break;   
    case 17: {       effect_function = flowercolors;        changeSpeed=100;        setDifference=1;         dir1 = 1;       offdis=5;        y0r=ymin3+10;        colorCount=0;       numsparks=0;   ledspercolor=NUM_LEDS/range;} break;    
    case 18: {       effect_function = gradient;        changeSpeed=200;       setDifference=1;         colorMode=0;           yval1=ymin4;          numsparks=0;} break; 
    case 19: {       effect_function = pers_color;        changeSpeed=2000;      arrayn=8;  selectcolorArray();        numcolor=5;        colorlength=1;     numsparks=0;}        break;      
    case 20: {       effect_function = pers_block;        changeSpeed=1000;      setDifference=1;        newColors=1;    yint = 0;           arrayn=9;          selectcolorArray();        colorlength=10;    numsparks=0;  numcolor=10;} break;
    case 21: {       effect_function = xmas_string;        changeSpeed=200;       setDifference=1;        offdis=2;       fillxmasArray();    y0r=0;    numsparks=0;} break; 
    case 22: {       effect_function = xmas_singles;        changeSpeed=100;       setDifference=1;        offdis=2;       fillxmasArray();    colour[0]=0;       colour[1]=0+(numAmax/10*1);        colour[2]=0+(numAmax/10*2);        colour[3]=0+(numAmax/10*3);        colour[4]=0+(numAmax/10*4);        colour[5]=0+(numAmax/10*5);        colour[6]=0+(numAmax/10*6);        colour[7]=0+(numAmax/10*7);        colour[8]=0+(numAmax/10*8);        colour[9]=0+(numAmax/10*9);  numsparks=0; } break;
    case 23: {       effect_function = xmas_solid;        changeSpeed=200;        setDifference=7;       offdis=5;        ysr=0; numsparks=0;} break; 
    case 24: {       effect_function = static_glow_2;        changeSpeed=100;        setDifference=7;        colorMode=2;    numsparks=0;} break;    
    case 25: {       effect_function = static_glow;         changeSpeed=100;        setDifference=25;        colorMode=2;        forcedColourChange = false;       yval1=5;     numsparks=0;} break; 
    case 26: {       effect_function = static_glow;         changeSpeed=100;        setDifference=80;        colorMode=0;        forcedColourChange = true;    numsparks=0;} break;                                                              
    case 27: {       effect_function = static_glow_2;        changeSpeed=100;        setDifference=80;        colorMode=1;    numsparks=0;} break; 
    case 28: {       effect_function = colourSplash;        changeSpeed=35;        setDifference=7;         colorMode=2;    numsparks=0;} break;   
    case 29: {       effect_function = meteor;        if (tower){changeSpeed=60;} else{changeSpeed=50;}        setDifference=11;   flakeCounter=0;        colorMode=2;        offmin=13;        offmax=13;     offdis = offdisC;           numsparks=cfactor2*5;
                      for (int s=0;s<30; s++){y[s]=offdisC;}    poshh=-1;   if (tower){slingerSpeed=45/cfactor2;} else {slingerSpeed = changeSpeed;};} break;
    case 30: {       effect_function = palettes;        changeSpeed=50;         setDifference=1;         y0r=0;     gCurrentPaletteNumber=7;     gCurrentPalette =( gGradientPalettes[gCurrentPaletteNumber] );   numsparks=0;} break;                          
    case 31: {       effect_function = splash;        rn14=random(100, 300)*NUM_LEDS/100;        changeSpeed=30;        colorMode=5;        setDifference=40;           cfactor1=300/NUM_LEDS;   numsparks=0;} break;
    case 32: {       effect_function = palettes;        changeSpeed=50;         setDifference=45;         y0r=0;    gCurrentPaletteNumber=11;     gCurrentPalette =( gGradientPalettes[gCurrentPaletteNumber] );   numsparks=0;} break;    
    case 33: {       effect_function = strobe;        changeSpeed=20;        colorMode=1;        setDifference=40;           cfactor1=300/NUM_LEDS;   numsparks=0;} break;
    case 34: {       effect_function = gradient;    changeSpeed=200;       setDifference=1;         BRIGH=205;       S=200;       glowON=4;       satON=4;      colorMode=0; if((random(10)>5)){selectColor = 2;} else {selectColor = 8;} memoryByte = 'h';   processChange();        numsparks=0;} break;
    case 35: {       effect_function = snow_flakesR;        changeSpeed=125;         setDifference=7;      offdis = offdisC;           sF=1;         previousMillis8=millis();     numsparks=7*cfactor2; } break;      
    case 36: {       effect_function = sparklingR;         changeSpeed=130;       sparkSpeed=78;        setDifference=7;         sparkSpeed=98;        yval1=random(125,225);        yy=0;        hh=NUM_LEDS;;    variant=0;        offmin=15*cfactor2;        offmax=15*cfactor2;        offdis=1;       readyToChange = true;      numsparks=10*cfactor2;} break;  
    case 37: {       effect_function = RGBmode;   changeSpeed=50;          } break;     
   }
   for (int k=0; k<21; k++){
     i[k]=NUM_LEDS; 
     a[k]=NUM_LEDS; 
     pos1[k]=NUM_LEDS;        
     pos2[k]=NUM_LEDS;        
     pos3[k]=NUM_LEDS;        
     pos4[k]=NUM_LEDS;
     }
   for (int s=0; s<30; s++){
    rr[s]=-1;       
    pos[s]=NUM_LEDS;
    }
   fill_solid(leds, NUM_SET, CRGB::Black);
   FastLED.show();
   if (effect_function != *xmas_string && effect_function != *xmas_singles){
     fillArrayRainbow(2);
   }
   selectColor=-1;
   slowFactor=0;
   INTERVAL7=5000;
   dir1 = 1;
   if ((effect_function == *static_glow && programMode == 26)  || effect_function == colourSplash){
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
