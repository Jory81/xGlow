/*
 * This file contains all the LED program cases
 */

void handleLEDSettings(){ // HANDLE LED SETTINGS
if (effect_function != NULL && (executeScript)){
    effect_function();
    }
else if ((!executeScript) && (dimming)){
    if (millis() - previousMillis2 >= 35) { 
    previousMillis2 = millis(); 
    fadeCounter++;
    fadeToBlackBy(leds, NUM_SET,25);
    FastLED.show();
          if (fadeCounter >= 60){     
          changeModus = true;
          dimming=false;
          executeScript=true;
          fadeCounter=0;    
          }  
    }
}
return;
}  

void static_glow(void){
  if (forcedColourChange){
     yval1 = changeColourFcn(colorMode, yval1, 0, 255);
     forcedColourChange = false; 
     updateOled(102, 56, &yval1); 
     notifyClientsSingleObjectByte("SHUE", yval);
    //  mergedString = "GSHUE"+String(yval);
    //  ws.textAll(mergedString); 
  }

    if (millis() - previousMillis2 >= FPS) { 
    previousMillis2 = millis(); 
    fillColourArray(colour, yval1, yvar, diff);        
    fillNUM_LEDS1(colour, NUM_LEDS);     
    }
} 

void rainbow_1(void){
if (millis() - previousMillis1 >= changeSpeed) {
  previousMillis1 = millis();

  if (varON == 2 && changeColor == true){ 
  } 
  else{
   for(int i = 0; i < 10; i++ ){
   colour[i]=colour[i]+=setDifference*dir1;     
   }
  }
}

if (millis() - previousMillis36 > INTERVAL7 && varON == 2) { 
  if (millis() - previousMillis37 >= FPS) {
    previousMillis37 = millis(); 
    
    if ((syncEsp) && (alertColor)){
    espNowMessage = true;
    EspNowMessageType = 7;
    alertColor = false;
    };
  
    for (int i = 0;  i < 10; i++){
     if (colour[i] != newColour[i]) { 
       changeColor = true;
       break;}
     else{
      changeColor = false;}
    } 
         
    if (changeColor) {
        for (int i = 0; i < 10; i++){
          if (colour[i] != newColour[i]){
            colour[i] = fadeFnc(colour[i], newColour[i]); 
          }
        }      
      }
    else if ((!changeColor) && (!inSync)){
      byte oldArrayn = arrayn;
      arrayn = random(arrayCount);
      updateOled(24, 40, &oldArrayn);
      selectcolorArray();
      alertColor = true;
      INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
      updateOledFloat(88, 0, &INTERVAL7, 0); 
      previousMillis36 = millis();
      T=0;        
    }
  }
}

if (millis() - previousMillis2 >= FPS) { 
previousMillis2 = millis();  
    
   for(int i = 0; i < NUM_LEDS; i++ ){
   leds[i] = CHSV(colour[colourlu]+yvar[varlu],satval[satlu],brigh[brighlu]);
    
   brighlu++;
   if (brighlu >= numbrigh){brighlu = 0;}
   
   colourlu++;
   if (colourlu > 9){colourlu = 0;}
   
   varlu++;
   if (varlu >= 10){varlu = 0;}

   satlu++;
   if (satlu >= numsat){satlu = 0;}
   }
   
   handleGlitter();  
   FastLED.show();

   brighlu=0;
   satlu=0;
   colourlu=0;
   varlu=0;
}
}

// void rainbow_2(void){ 
// if (millis() - previousMillis1 >= changeSpeed) {
//   previousMillis1 = millis();

//    for(int i = 0; i < 10; i++ ){
//    colour[i]=colour[i]+=random(0,setDifference)*dir1;  
//    }
// }

// if (millis() - previousMillis2 >= FPS) { 
// previousMillis2 = millis();  
// fillNUM_LEDS1(colour, NUM_LEDS);
//    }
// }

void s7_strings(void){   
for (int k=0; k<numsparks; k++){
if (millis() - previousMillisLN[0] >= INTERVAL7 && ((numsparks == 1) || (numsparks > 1))){       
if (millis() - previousMillisAM[k] >= (INTERVALf[k]*timeSpeed[k])) {
    previousMillisAM[k] = millis();
    longxArray[i[k]]=yMA[k];//+random(-ydiff,ydiff);
    if (varON == 2 && i[k] > 0 && colorMode !=4){
      longxArray[i[k]-1]=z[k];
    }
    i[k]=i[k]-1;

    if (i[k]<0){
      i[k]=NUM_LEDS-1;
    
    if (colorMode == 5){
          yval1 = yval1 + (60/numsparks);
          yMA[k] = yval1;
     }
     else {
      yMA[k] = changeColourFcn(colorMode, yMA[k], 0, 255); 
     }

      if (varON == 2 && colorMode !=4 ){
        z[k] = yMA[k] + random(50, 200);
        //  if ((yMA[k] >=230 && yMA[k] <= 255) || (yMA[k] >= 0 && yMA[k] <= 79)){
        //     z[k]=zr[0];
        //  }
        //  else if (yMA[k] >=130 && yMA[k] < 168){
        //     z[k]=zr[1];
        //  }
        //  else if (yMA[k] >= 168 && yMA[k] < 205){
        //     z[k]=zr[1];
        //  }
        //  else if (yMA[k] >=80 && yMA[k] < 130){
        //     z[k]=zr[2];
        //  }
        //  else if (yMA[k] >=205 && yMA[k] < 230){
        //     z[k]=zr[3];
        //  }
      }
      if (millis() - previousMillis36 > INTERVAL9 && colorMode == 4 && varON == 2 && inSync == false) {
      arrayn = random(arrayCount);
      updateOled(24, 40, &arrayn);
      selectcolorArray();
      if (syncEsp){espNowMessage = true;   EspNowMessageType = 7;  };
      INTERVAL9=interval9*timeArray2[random(0,6)]*timefactor3;
      previousMillis36 = millis();
      T=0;        
      }
      if (k == 0){
      num2+=1;
          if (numsparks == 1){
            updateOled(102, 56, &yMA[0]);
            num2+=1;
            if (varON == 0 || varON == 2){
            if (yval1 == 11 || yval1 == 81 || yval1 == 16 || yval1 == 117 || yval1 == 139 || yval1 == 175 || yval1 == 193 || yval1 == 244){
            setDifference=5;}
            else if (yval1 == 9 || yval1 == 217 || yval1 == 243){
            setDifference=10;}
            else if (yval1 == 188 || yval1 == 226 || yval1 == 168){
            setDifference=20;}
            else {
            setDifference=10;}
            }
            // else if (varON == 1){
            // ydiff=setDifference;}   
          }
      }
    }
    if (num2 >= xp ){
    num2=0;
    xp=random(2,7);
    INTERVALf[0]=changeSpeed*timeArray[random(0,5)];
    if (numsparks == 1){
        INTERVAL7=interval7*timeArray2[random(0,6)]*timefactor3;
        T=0;
        previousMillisLN[0] = millis();
        updateOledFloat(72, 56, &INTERVALf[0], 0);
        updateOledFloat(88, 0, &INTERVAL7, 0);       
    }
    updateOledFloat(72, 56, &INTERVALf[0], 0);   
    }
    else if (k > 0){
    INTERVALf[k]=INTERVALf[0];
    // ydiff=setDifference;
}
}    
}
} 
    
if (millis() - previousMillisLN[1] >= INTERVAL3 && (reverseON)){
  if (millis() - previousMillisLN[2] >= interval5) {
    previousMillisLN[2] = millis();
    i[0]=NUM_LEDS-1;
    longxArray[ir[0]]=reverseColour+random(-5,5);
    ir[0]=ir[0]+1;
    if (ir[0]>NUM_LEDS-1){
    ir[0]=0;
    num4++;
    if (arrayn == 1){
      reverseColour = 25;
    }
    reverseColour=colour[random(0, 15)];
      if (num4 >= xp2){
      num4=0;
      xp2=random(1,6);         
      INTERVAL3=interval3*timeArrayReverse[random(0,5)];
      previousMillisLN[1] = millis();}
    }
    }
}    
    
if (millis() - previousMillisLN[3] >= INTERVAL4 && (rainbowON)){
  if (millis() - previousMillisLN[4] >= interval6) {
    previousMillisLN[4] = millis();
    i[0]=NUM_LEDS-1;
    longxArray[ir[1]]=rainbowColour;
    rainbowColour+=3;
    ir[1]=ir[1]+1;
    if (ir[1]>NUM_LEDS-1){  
    ir[1]=0;
    rainbowColour=random(256);     
    INTERVAL4=interval4*timeArrayRainbow[random(0,5)];
    previousMillisLN[3] = millis();}
    }
}

if (millis() - previousMillis2 >= FPS) { 
previousMillis2 = millis();  

   for(int i = 0; i < NUM_LEDS; i++ ){
   leds[i] = CHSV((longxArray[i]+yvar[varlu]+diff[difflu]),satval[satlu],brigh[brighlu]);
    
   brighlu++;
   if (brighlu >= numbrigh){brighlu = 0;}

   satlu++;
   if (satlu >= numsat){satlu = 0;}

   varlu++;
   if (varlu >= 10){varlu = 0;}

   difflu++;
   if (difflu >= 10){difflu = 0;}
   }
     
   handleGlitter(); 
   FastLED.show();
   brighlu=0;
   satlu=0;
   difflu=0;
   varlu=0;
   }
}  

void s7_strings_2(void){   
for (int k=0; k<numsparks; k++){
if (millis() - previousMillisLN[0] >= INTERVAL7 && ((numsparks == 1) || (numsparks > 1))){       
if (millis() - previousMillisAM[k] >= (INTERVALf[k]*timeSpeed[k])) {
    previousMillisAM[k] = millis();

    longxArray[NUM_LEDS/2-(i[k])]=yMA[k];//+random(-ydiff,ydiff);
    longxArray[NUM_LEDS/2+(i[k])]=yMA[k];//+random(-ydiff,ydiff);

    if (varON == 2 && i[k] > 0 && colorMode !=4){
      longxArray[NUM_LEDS/2-(i[k]-1)]=z[k];
      longxArray[NUM_LEDS/2+(i[k]+1)]=z[k];
    }
    i[k]=i[k]+=1;

    if (i[k]>(NUM_LEDS/2)){
      i[k]=0;
    
    if (colorMode == 5){
          yval1 = yval1 + (60/numsparks);
          yMA[k] = yval1;
     }
     else {
      yMA[k] = changeColourFcn(colorMode, yMA[k], 0, 255); 
     }

      if (varON == 2 && colorMode !=4 ){
        z[k] = yMA[k] + random(50, 200);
      }
      if (millis() - previousMillis36 > INTERVAL9 && colorMode == 4 && varON == 2 && inSync == false) {
      arrayn = random(arrayCount);
      updateOled(24, 40, &arrayn);
      selectcolorArray();
      if (syncEsp){espNowMessage = true;   EspNowMessageType = 7;  };   
      INTERVAL9=interval9*timeArray2[random(0,6)]*timefactor3;
      previousMillis36 = millis();
      T=0;        
      }
      if (k == 0){
      num2+=1;
          if (numsparks == 1){
            updateOled(102, 56, &yMA[0]);
            num2+=1;
            if (varON == 0 || varON == 2){
            if (yval1 == 11 || yval1 == 81 || yval1 == 16 || yval1 == 117 || yval1 == 139 || yval1 == 175 || yval1 == 193 || yval1 == 244){
            setDifference=5;}
            else if (yval1 == 9 || yval1 == 217 || yval1 == 243){
            setDifference=10;}
            else if (yval1 == 188 || yval1 == 226 || yval1 == 168){
            setDifference=20;}
            else {
            setDifference=10;}
            }
            // else if (varON == 1){
            // ydiff=setDifference;}   
          }
      }
    }
    if (num2 >= xp ){
    num2=0;
    xp=random(2,7);
    INTERVALf[0]=changeSpeed*timeArray[random(0,5)];
    if (numsparks == 1){
        INTERVAL7=interval7*timeArray2[random(0,6)]*timefactor3;
        T=0;
        previousMillisLN[0] = millis();
        updateOledFloat(72, 56, &INTERVALf[0], 0);
        updateOledFloat(88, 0, &INTERVAL7, 0);       
    }
    updateOledFloat(72, 56, &INTERVALf[0], 0);   
    }
    else if (k > 0){
    INTERVALf[k]=INTERVALf[0];
    // ydiff=setDifference;
}
}    
}
} 
    
if (millis() - previousMillisLN[1] >= INTERVAL3 && (reverseON)){
  if (millis() - previousMillisLN[2] >= interval5) {
    previousMillisLN[2] = millis();
    i[0]=NUM_LEDS-1;
    longxArray[ir[0]]=reverseColour+random(-5,5);
    ir[0]=ir[0]+1;
    if (ir[0]>NUM_LEDS-1){
    ir[0]=0;
    num4++;
    if (arrayn == 1){
      reverseColour = 25;
    }
    reverseColour=colour[random(0, 15)];
      if (num4 >= xp2){
      num4=0;
      xp2=random(1,6);         
      INTERVAL3=interval3*timeArrayReverse[random(0,5)];
      previousMillisLN[1] = millis();}
    }
    }
}    
    
if (millis() - previousMillisLN[3] >= INTERVAL4 && (rainbowON)){
  if (millis() - previousMillisLN[4] >= interval6) {
    previousMillisLN[4] = millis();
    i[0]=NUM_LEDS-1;
    longxArray[ir[1]]=rainbowColour;
    rainbowColour+=3;
    ir[1]=ir[1]+1;
    if (ir[1]>NUM_LEDS-1){  
    ir[1]=0;
    rainbowColour=random(256);     
    INTERVAL4=interval4*timeArrayRainbow[random(0,5)];
    previousMillisLN[3] = millis();}
    }
}

if (millis() - previousMillis2 >= FPS) { 
previousMillis2 = millis();  

   for(int i = 0; i < NUM_LEDS; i++ ){
   leds[i] = CHSV((longxArray[i]+yvar[varlu]+diff[difflu]),satval[satlu],brigh[brighlu]);
    
   brighlu++;
   if (brighlu >= numbrigh){brighlu = 0;}

   satlu++;
   if (satlu >= numsat){satlu = 0;}

   varlu++;
   if (varlu >= 10){varlu = 0;}

   difflu++;
   if (difflu >= 10){difflu = 0;}
   }
     
   handleGlitter(); 
   FastLED.show();
   brighlu=0;
   satlu=0;
   difflu=0;
   varlu=0;
   }
}

void snow_flakes(void){
if (millis() - previousMillis11 >= interval8) {
    previousMillis11 = millis();
    sF= sF+0.0675;
      if (sF >= 2.0){
        sF=1.00;
    }
}  

if (millis() - previousMillis6 >= INTERVAL7 && (!inSync)){
      
    if (colorMode == 0 && varON == 0){
      yval1=yval;
      for (int p=0; p<numsparks; p++){
      z[p]=yval;}
      }
    else if (colorMode == 0 && varON == 1){
      yval1 = yval1 + random(25,230);
      for (int p=0; p<numsparks; p++){
      z[p]=yval1;}
    }  
    else if (colorMode == 5 && varON != 2){ //varON != 2
      yval1=yval;
      for (int p=0; p<numsparks; p++){
        z[p]=z5;
        }
     }
    else {  
    yval1 = changeColourFcn2(colorMode, yval1, yval1, 50, 200);
    }
  
  if ((varON == 0) && (colorMode == 1 || colorMode == 2 || colorMode == 3 || colorMode == 4 )){ // colorMode == 2 || colorMode == 3 || colorMode == 4){
     if ((yval1 >=230 && yval1 <= 255) || (yval1 >= 0 && yval1 <= 79)){
        for (int p=0; p<numsparks; p++){
        z[p]=zr[0];}
        }
     else if (yval1 >=130 && yval1 < 168){
        for (int p=0; p<numsparks; p++){
        z[p]=zr[1];}
        }
     else if (yval1 >= 168 && yval1 < 205){
        for (int p=0; p<numsparks; p++){
        z[p]=zr[1];}
        }
     else if (yval1 >=80 && yval1 < 130){
        for (int p=0; p<numsparks; p++){
        z[p]=zr[2];}
        }
     else if (yval1 >=205 && yval1 < 230){
        for (int p=0; p<numsparks; p++){
        z[p]=zr[3];}
        }
  }
  else if ((varON == 1) && (colorMode == 1 || colorMode == 2 || colorMode == 3 || colorMode == 4 )){ // colorMode != 5
       z[0] = yval1 + random(35,225);
        for (int p=0; p<numsparks; p++){
        z[p] = z[0];}
  }
  else if ((varON == 2) && (colorMode != 5)){
        for (int p=0; p<numsparks; p++){
        z[p] = yval1 + random(35,225);
        //Serial.println(z[p]);}
        }
  }
  
     
   if (varON == 0){
    if (yval1 == 11 || yval1 == 81 || yval1 == 16 || yval1 == 117 || yval1 == 139 || yval1 == 175 || yval1 == 193 || yval1 == 244){
    setDifference=5;
    }
    else if (yval1 == 9 || yval1 == 217 || yval1 == 243){
    setDifference=10;
    }
    else if (yval1 == 188 || yval1 == 226 || yval1 == 168){
    setDifference=20;
    }
    else {
    setDifference=10;}
    //diffbeat=60000/(setDifference*4*100);
    }
  //  else if (varON == 1 || varON == 2){
  //   ydiff=setDifference;
  //   }
   //}
    
    if (syncEsp){espNowMessage = true;   EspNowMessageType = 11;  };
    updateOled(102, 56, &yval1);          
    INTERVAL7=interval7*timeArray2[random(0,6)]*timefactor3;
    updateOledFloat(88, 0, &INTERVAL7, 0); 
    T=0;
    previousMillis6 = millis();
}

for (int k=0 ; k<numsparks; k++){
if (millis() - previousMillisLN[k] >= rtAM[k]/df){
  if ((millis() - previousMillisAM[k] >= (INTERVALf[k]*timeSpeed[k]*interRun[k])) && (sF <= sFtab[k])) {
    previousMillisAM[k] = millis();
    
    if (varON == 2 && colorMode == 1){
      z[k] = random(256);
      while (z[k] >= yval1 - 30 && z[k] <= yval1 + 30){
        z[k] = random(256);}
    }

    blockArray[a[k]]=yval1;//+random(-ydiff,ydiff);
    blockArray[i[k]]=(z[k]);  
    a[k]=i[k];
        if ((tower) && (!Bees)){
            if((random(10)>5)) {
              i[k]=i[k]-offdis;
            }
            else { 
              i[k]=i[k]-offdis-1;
          }
        }
        else if ((tower) && (Bees)){
          byte RouteOfBee = random(6);
          if (RouteOfBee == 0){
          i[k]=i[k]-1;  
          }
          else if (RouteOfBee == 1){
          i[k]=i[k]+1;  
          }
          else if (RouteOfBee == 2){
          i[k]=i[k]-offdis;  
          }
          else if (RouteOfBee == 3){
          i[k]=i[k]-offdis-1;  
          }
          else if (RouteOfBee == 4){
          i[k]=i[k]+offdis;    
          }
          else if (RouteOfBee == 5){
          i[k]=i[k]+offdis+1;  
        }                             
        }
        else {
          i[k]=i[k]-1;
          if (i[k] == 80*cfactor3 || i[k] == 60*cfactor3 || i[k] == 40*cfactor3 || i[k] == 20*cfactor3){ 
          int chance = random(15);
            if (chance > 9){
              interRun[k]=1.1;
            }
            else if (chance < 5){
              interRun[k]=0.9;
            }
            else {interRun[k] = 1;}
          }
        }    
    if (i[k]<0 || i[k] >= NUM_LEDS){
      if ((tower) && (!Bees)){
        blockArray[i[k]+offdis]=yval1;//+random(-ydiff,ydiff);
        blockArray[i[k]+offdis+1]=yval1;//+random(-ydiff,ydiff);
        a[k]=NUM_LEDS; // added to remove leds being lit in tower mode
        i[k]=random(NUM_LEDS-offdis, NUM_LEDS);
      }
      else if ((tower) && (Bees)){
        if (i[k]<0){
        blockArray[0]=yval1;//+random(-ydiff,ydiff);  
        i[k]=NUM_LEDS+i[k];   
        }
        else if (i[k] >= NUM_LEDS){
        i[k]=i[k]-NUM_LEDS;  
        }
      }
      else {
        i[k]=NUM_LEDS;
        a[k]=NUM_LEDS;
        blockArray[0]=yval1;//+random(-ydiff,ydiff);
      }

      if (varON == 2 && colorMode == 5){
        z7++;
        z[k] = z7;
      }

      if ((varON == 2) && (colorMode != 5)){
        z[k] = yval1 + random(35,225);
        //Serial.println(z[k]);
      }

    interRun[k]=1.1;
    previousMillisLN[k] = millis();
    if ((tower) && (Bees)){
    rtAM[k] = 80;  
    }
    else {
    rtAM[k]= random(65536);
    }
    if (k == 0){
      num6=num6+1;
      if (num6 >= xnum){
        num6=0;
        INTERVALf[0]=changeSpeed*sF*timeArray3[random(0,6)];
        updateOledFloat(72, 56, &INTERVALf[0], 0);
    }
    }
    else if (k > 0){
          INTERVALf[k]=INTERVALf[0];
    }
    }
    }  
}
}

if (millis() - previousMillis2 >= FPS) { 
previousMillis2 = millis();  

   for(int k = 0; k < NUM_LEDS; k++ ){
      for (int j = 0; j < numsparks; j++ ){
        if (k == a[j]){
          leds[k] = CHSV(blockArray[k],qadd8(S,SF),qadd8(BRIGH,BrF));    
          break;
        }
        else {
        leds[k] = CHSV((blockArray[k]+yvar[varlu]+diff[difflu]),satval[satlu],brigh[brighlu]);
        }
      }
    
   brighlu++;
   if (brighlu >= numbrigh){brighlu = 0;}

   satlu++;
   if (satlu >= numsat){satlu = 0;}

   varlu++;
   if (varlu >= 10){varlu = 0;}

   difflu++;
   if (difflu >= 10){difflu = 0;}
   } 
    
   handleGlitter(); 
   FastLED.show();
   brighlu=0;
   satlu=0;
   difflu=0;
   varlu=0;
   }
}


void snow_flakes2(void){
if (millis() - previousMillis11 >= interval8) {
    previousMillis11 = millis();
    sF= sF+0.0675;
      if (sF >= 2.0){
        sF=1.00;
    }
}  

if (millis() - previousMillis6 >= INTERVAL7 && (!inSync)){
      
     if (colorMode == 0 && varON == 0){
      yval1=yval;
      for (int p=0; p<numsparks; p++){
      z[p]=yval;}
      }
    else if (colorMode == 0 && varON == 1){
      yval1 = yval1 + random(25,230);
      for (int p=0; p<numsparks; p++){
      z[p]=yval1;}
    }  
    else if (colorMode == 5 && varON != 2){ //varON != 2
      yval1=yval;
      for (int p=0; p<numsparks; p++){
        z[p]=z5;
        }
     }
    else {  
    yval1 = changeColourFcn2(colorMode, yval1, yval1, 50, 200);
    }
  
  if ((varON == 0) && (colorMode == 1 || colorMode == 2 || colorMode == 3 || colorMode == 4 )){ // colorMode == 2 || colorMode == 3 || colorMode == 4){
     if ((yval1 >=230 && yval1 <= 255) || (yval1 >= 0 && yval1 <= 79)){
        for (int p=0; p<numsparks; p++){
        z[p]=zr[0];}
        }
     else if (yval1 >=130 && yval1 < 168){
        for (int p=0; p<numsparks; p++){
        z[p]=zr[1];}
        }
     else if (yval1 >= 168 && yval1 < 205){
        for (int p=0; p<numsparks; p++){
        z[p]=zr[1];}
        }
     else if (yval1 >=80 && yval1 < 130){
        for (int p=0; p<numsparks; p++){
        z[p]=zr[2];}
        }
     else if (yval1 >=205 && yval1 < 230){
        for (int p=0; p<numsparks; p++){
        z[p]=zr[3];}
        }
  }
  else if ((varON == 1) && (colorMode == 1 || colorMode == 2 || colorMode == 3 || colorMode == 4 )){ // colorMode != 5
       z[0] = yval1 + random(35,225);
        for (int p=0; p<numsparks; p++){
        z[p] = z[0];}
  }
  else if ((varON == 2) && (colorMode != 5)){
        for (int p=0; p<numsparks; p++){
        z[p] = yval1 + random(35,225);
        //Serial.println(z[p]);
        }
  }
  
     
   if (varON == 0){
    if (yval1 == 11 || yval1 == 81 || yval1 == 16 || yval1 == 117 || yval1 == 139 || yval1 == 175 || yval1 == 193 || yval1 == 244){
    setDifference=5;
    }
    else if (yval1 == 9 || yval1 == 217 || yval1 == 243){
    setDifference=10;
    }
    else if (yval1 == 188 || yval1 == 226 || yval1 == 168){
    setDifference=20;
    }
    else {
    setDifference=10;}
    //diffbeat=60000/(setDifference*4*100);
    }
  //  else if (varON == 1 || varON == 2){
  //   ydiff=setDifference;
  //   }
   //}
    
    if (syncEsp){espNowMessage = true;   EspNowMessageType = 11;  };
    updateOled(102, 56, &yval1);          
    INTERVAL7=interval7*timeArray2[random(0,6)]*timefactor3;
    updateOledFloat(88, 0, &INTERVAL7, 0); 
    T=0;
    previousMillis6 = millis();
}

for (int k=0 ; k<numsparks; k++){
if (millis() - previousMillisLN[k] >= rtAM[k]/df){
  if ((millis() - previousMillisAM[k] >= (INTERVALf[k]*timeSpeed[k]*interRun[k])) && (sF <= sFtab[k])) {
    previousMillisAM[k] = millis();

    if (varON == 2 && colorMode == 1){
      z[k] = random(256);
      while (z[k] >= yval1 - 30 && z[k] <= yval1 + 30){
        z[k] = random(256);}
    }

    blockArray[NUM_LEDS/2-(a[k])]=yval1;//+random(-ydiff,ydiff);
    blockArray[NUM_LEDS/2+(a[k])]=yval1;//+random(-ydiff,ydiff);

    blockArray[NUM_LEDS/2-(i[k])]=z[k];
    blockArray[NUM_LEDS/2+(i[k])]=z[k];

    //blockArray[i[k]]=(z[k]);  
    a[k]=i[k];

    i[k] = i[k]+=1;
    if (i[k] == 40*cfactor3 || i[k] == 30*cfactor3 || i[k] == 20*cfactor3 || i[k] == 10*cfactor3){ 
    int chance = random(15);
      if (chance > 9){
        interRun[k]=1.1;
      }
      else if (chance < 5){
        interRun[k]=0.9;
      }
      else {interRun[k] = 1;}
    }
   
    if (i[k]>NUM_LEDS/2){

        i[k]=0;
        a[k]=0;
        blockArray[0]=yval1;//+random(-ydiff,ydiff);
        blockArray[NUM_LEDS-1]=yval1;

      if (varON == 2 && colorMode == 5){
        z7++;
        z[k] = z7;
      }

      if ((varON == 2) && (colorMode != 5)){
          z[k] = yval1 + random(35,225);
      }

    interRun[k]=1.1;
    previousMillisLN[k] = millis();
    if ((tower) && (Bees)){
    rtAM[k] = 80;  
    }
    else {
    rtAM[k]= random(65536);
    }
    if (k == 0){
      num6=num6+1;
      if (num6 >= xnum){
        num6=0;
        INTERVALf[0]=changeSpeed*sF*timeArray3[random(0,6)];
        updateOledFloat(72, 56, &INTERVALf[0], 0);
    }
    }
    else if (k > 0){
          INTERVALf[k]=INTERVALf[0];
    }
    }
    }  
}
}

if (millis() - previousMillis2 >= FPS) { 
previousMillis2 = millis();  

   for(int k = 0; k < NUM_LEDS; k++ ){
        for (int j = 0; j < numsparks; j++ ){
          if (blockArray[k] == z[j]){
            leds[k] = CHSV(blockArray[k],qadd8(S,SF),qadd8(BRIGH,BrF));    
            break;
          }
          else {
          leds[k] = CHSV((blockArray[k]+yvar[varlu]+diff[difflu]),satval[satlu],brigh[brighlu]);
          }
        }
    
   brighlu++;
   if (brighlu >= numbrigh){brighlu = 0;}

   satlu++;
   if (satlu >= numsat){satlu = 0;}

   varlu++;
   if (varlu >= 10){varlu = 0;}

   difflu++;
   if (difflu >= 10){difflu = 0;}
   } 
    
   handleGlitter(); 
   FastLED.show();
   brighlu=0;
   satlu=0;
   difflu=0;
   varlu=0;
   }
}


void snow_flakesR(void){
if (millis() - previousMillis11 >= interval8) {
    previousMillis11 = millis();
    sF= sF+0.0675;
      if (sF >= 2.0){
        sF=1.00;
    }
}  

if (millis() - previousMillis36 >= 500){    
    previousMillis36 = millis();
    if (varON == 1){     
      fillArrayRainbow(1);
    }
    else{
    yval1+=1*dir1;

    fillArrayGradient(1, yval1, setDifference);

    if (yval1 == ymax4-1 && dir1 == 1){
     dir1 = -1;
     rn15 = random(65536)/2;
     }
    else if (yval1 == ymin4 && dir1 == -1){
     dir1 = 1;
     rn15 = random(65536)/2;
     }
    }
  }

for (int k=0 ; k<numsparks; k++){
if (millis() - previousMillisLN[k] >= rtAM[k]/df){
  if ((millis() - previousMillisAM[k] >= (INTERVALf[k]*timeSpeed[k]*interRun[k])) && (sF <= sFtab[k])) {
    previousMillisAM[k] = millis();
    if (varON == 0 || varON == 1){
        z[k] = blockArray[i[k]]+90;
    }
    else if (varON == 2){
        z[k] = random(256);
        while (z[k] >= blockArray[i[k]] - 30 && z[k] <= blockArray[i[k]] + 30){
        z[k] = random(256);
        }   
    }
    blockArray[a[k]]=longxArray[a[k]];    
    blockArray[i[k]]=(z[k]);  
    a[k]=i[k];

    if ((tower) && (!Bees)){
        if((random(10)>5)) {
          i[k]=i[k]-offdis;
        }
        else { 
          i[k]=i[k]-offdis-1;
      }
    }
    else if ((tower) && (Bees)){
      byte RouteOfBee = random(6);
      if (RouteOfBee == 0){
      i[k]=i[k]-1;  
      }
      else if (RouteOfBee == 1){
      i[k]=i[k]+1;  
      }
      else if (RouteOfBee == 2){
      i[k]=i[k]-offdis;  
      }
      else if (RouteOfBee == 3){
      i[k]=i[k]-offdis-1;  
      }
      else if (RouteOfBee == 4){
      i[k]=i[k]+offdis;    
      }
      else if (RouteOfBee == 5){
      i[k]=i[k]+offdis+1;  
     }                             
    }
    else {
      i[k]=i[k]-1;
      if (i[k] == 80*cfactor3 || i[k] == 60*cfactor3 || i[k] == 40*cfactor3 || i[k] == 20*cfactor3){
      int chance = random(15);
        if (chance > 9){
          interRun[k]=1.1;
        }
        else if (chance < 5){
          interRun[k]=0.9;
        }
        else {interRun[k] = 1;}
      }
    }    

    if (i[k]<0 || i[k] >= NUM_LEDS){
      if ((tower) && (!Bees)){
        i[k]=random(NUM_LEDS-offdis, NUM_LEDS);
      }
      else if ((tower) && (Bees)){
        if (i[k]<0){
        i[k]=NUM_LEDS+i[k];   
        }
        else if (i[k] >= NUM_LEDS){
        i[k]=i[k]-NUM_LEDS;  
        }
      }
      else {
        i[k]=NUM_LEDS;
        a[k]=NUM_LEDS;
      }
    interRun[k]=1.1;
    blockArray[0]=longxArray[0]; 
    previousMillisLN[k] = millis();
    if ((tower) && (Bees)){
    rtAM[k] = 80;  
    }
    else {
    rtAM[k]= random(65536);
    }
    if (k == 0){
      num6=num6+1;
      if (num6 >= xnum){
        num6=0;
        INTERVALf[0]=changeSpeed*sF*timeArray3[random(0,6)];
        updateOledFloat(72, 56, &INTERVALf[0], 0);
    }
    }
    else if (k > 0){
          INTERVALf[k]=INTERVALf[0];
    }
    }
    }  
}
}

if (millis() - previousMillis2 >= FPS) { 
previousMillis2 = millis();  

   for(int k = 0; k < NUM_LEDS; k++ ){
      for (int j = 0; j < numsparks; j++ ){
        if (k == a[j]){
          leds[k] = CHSV(blockArray[k],qadd8(S,SF),qadd8(BRIGH,BrF));    
          break;
        }
        else {
        leds[k] = CHSV(blockArray[k],satval[satlu],brigh[brighlu]);
        }
      }
    
   brighlu++;
   if (brighlu >= numbrigh){brighlu = 0;}

   satlu++;
   if (satlu >= numsat){satlu = 0;}
   } 
    
   handleGlitter(); 
   FastLED.show();
   brighlu=0;
   satlu=0;
   }
}

void rainbow_4(void){
if (millis() - previousMillis1 >= changeSpeed) {
  previousMillis1 = millis();
  ysr+=1*dir1;
  fillColourArray(colour, ysr, yvarg, diff);
}
    
if (millis() - previousMillis2 >= FPS) { 
previousMillis2 = millis();
fillNUM_LEDS1(colour, NUM_LEDS);   
   }
}

void sparkling(void){
if (readyToChange){
  if (!inColourSync){
  rn6=random(0,24);
  }
  //rn6 = 12;  
    if (rn6==0){
      variant=0;
      yy=0;
      slowFactor=0;
      offmin=random(12,17)*cfactor3;
      offmax=random(12,17)*cfactor3;
      slingerSpeed=timeArray3[random(0,5)]*changeSpeed/cfactor3;
      }
    else if (rn6==1){
      variant=1;  
      yy=0;
      slowFactor=0; 
      offmax=-1;
      offmin=(random(25,32)*cfactor3)+10; 
      slingerSpeed=45/cfactor3;   
      }
    else if (rn6==2){
      variant=2;
      yy=0;
      slowFactor=0;
      offmin=-1;
      offmax=random(22,32)*cfactor3;
      slingerSpeed=timeArray3[random(0,5)]*changeSpeed/cfactor3;
      }
    else if (rn6==3){
      variant=3;
      hh=NUM_LEDS;
      slowFactor=0;
      offmin=random(12,17)*cfactor3;
      offmax=random(12,17)*cfactor3;
      slingerSpeed=timeArray3[random(0,5)]*changeSpeed/cfactor3;
      }
    else if (rn6==4){
      variant=4;
      hh=NUM_LEDS;
      slowFactor=0;
      offmax=-1;
      offmin=(random(25,32)*cfactor3)+10;; 
      slingerSpeed=45/cfactor3;
      }
    else if (rn6==5){
      variant=5;
      hh=NUM_LEDS;
      slowFactor=0;
      offmin=-1;
      offmax=random(22,32)*cfactor3;
      slingerSpeed=timeArray3[random(0,5)]*changeSpeed/cfactor3;
      }
    else if ((rn6 == 6) || (rn6 == 7)){
      variant=6;
      xx=0;
      slowFactor=0;
      offmin=random(8,14)*cfactor3;
      offmax=random(8,14)*cfactor3;
      slingerSpeed=timeArray3[random(0,5)]*changeSpeed/cfactor3;
    }
    else if (rn6 == 8 || rn6 == 9){
      variant=7;
      xx=0;
      slowFactor=0;
      offmin=random(8,14)*cfactor3;
      offmax=random(8,14)*cfactor3;
      slingerSpeed=timeArray3[random(0,5)]*changeSpeed/cfactor3;
    }
    else if (rn6 > 9 && rn6 < 13){
      variant=0;
      yy=NUM_LEDS;
    }
    else if (rn6 > 12 && rn6 < 17){
      xx=0;
      variant=8;
    }
    else if (rn6 > 16 && rn6 < 21){
      xx=0;
      variant=9;
    } 
    else if (rn6 > 20 && rn6 < 25){
      xx=0;
      variant=10;
    }      
  if (tower){
    slingerSpeed=45/cfactor3;    
  }
  readyToChange = false; 
}   
  
if ((variant == 0 || variant == 1 || variant == 2) && (!readyToChange)){
    if ((millis() - previousMillis36 >= INTERVAL7 && (!inColourSync)) || (colourSync)){ 
      outOfModus = false;
      
      if (forcedColourChange){
        if (!colourSync){
        yval1 = changeColourFcn2(colorMode, yval1, yold, 40, 210);               
        if ((syncEsp) && (colourSyncToggle)){espNowMessage = true;   EspNowMessageType = 17;  };
        }
        updateOled(102, 56, &yval1);
        forcedColourChange = false; 
      }
      if (millis() - previousMillis37 >= (slingerSpeed+slowFactor)){
        previousMillis37 = millis();
        longxArray[yy]=yval1;
        yy=yy+=offdis;
        if (yy>NUM_LEDS-(15*cfactor2)){
          slowFactor+=2;
          if (variant == 1){
          offmin-=2;
          }
        }
        if (yy>NUM_LEDS-1){ 
        yy=0;
        //slowFactor=0;
        evenOddCounter++;

        // if (variant == 0){
        //   arraypos = 0;
        //   fadeIsActive = true;
        //   yold1=yold;
        //   for (int j = 0; j < NUM_LEDS; j++){
        //     if (longxArray[j] == yold){
        //       sparkarray[arraypos]=j;
        //       arraypos++;  
        //     }
        //   }
        // }
        updateOled(44, 40, &yold); 
        yold=yval1;
        INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
        outOfModus = true;
        updateOledFloat(88, 0, &INTERVAL7, 0); 
        // if (variant != 0){
        //   fillLongxArray(yold, NUM_LEDS);
        //   }
        previousMillis36 = millis();
        T=0;
        readyToChange = true;
        forcedColourChange = true;
        colourSync = false;
        num15=0;
        }
        } 

    if ((variant == 0 && yy > 0 && yy < NUM_LEDS-1) || (variant == 1 && yy > 1+cfactor3) || (variant == 2 && yy < NUM_LEDS-(1+cfactor3))){
        if (millis() - previousMillis35 >= sparkSpeed+slowFactor) {        
        previousMillis35 = millis();

        for (int s=0; s<numsparks; s++){
        if (rr[s] > yy){
          longxArray[rr[s]] = yold;
        }
        else if (rr[s] <= yy){
         longxArray[rr[s]] = yval1;
        }          
        
        if (pos[s] < yy){
          longxArray[pos[s]] = yold;    
        }
        else if (pos[s] >= yy){
          longxArray[pos[s]] = yval1;        
        }        

        rr[s]=pos[s];

        pos[s]=random(yy-offmin, yy+offmax);
          while (pos[s] < 0 || pos[s] > NUM_LEDS-1){
            pos[s]=random(yy-offmin, yy+offmax);}
        }
    }
    }
    }
    
    if (yy == 0 && num15 <1){
    num15++;
    for (int s=0; s<numsparks; s++){
        if (variant != 0){
        longxArray[rr[s]] = yold;
        }
      rr[s]=NUM_LEDS;
      pos[s]=NUM_LEDS;
      } 
   changeColor = true;            
   }
   }

else if ((variant == 3 || variant == 4 || variant == 5) && (!readyToChange)){
     if ((millis() - previousMillis36 >= INTERVAL7 && (!inColourSync)) || (colourSync)){ 
      outOfModus = false;
      
      if (forcedColourChange){
        if (!colourSync){
        yval1 = changeColourFcn2(colorMode, yval1, yold, 40, 210);               
        //updateOled(102, 56, &yval1);
        if ((syncEsp) && (colourSyncToggle)){espNowMessage = true;   EspNowMessageType = 17;  };
        }
        updateOled(102, 56, &yval1);
        forcedColourChange = false; 
      }
        if (millis() - previousMillis37 >= (slingerSpeed+slowFactor)){ // 200 is slingerSpeed
          previousMillis37 = millis();
          longxArray[hh]=yval1;
          hh=hh-=offdis; 
          if (hh < (15*cfactor2)){
            slowFactor+=2;
            if (variant == 4){
            offmin-=2;
            }
          }
          if (hh<0){
          hh=NUM_LEDS;
          //slowFactor=0;
          evenOddCounter++;
          // if (variant == 3){
          //   fadeIsActive = true;
          //   arraypos = 0;
          //   yold1=yold;
          //   for (int j = 0; j < NUM_LEDS; j++){
          //     if (longxArray[j] == yold){
          //       sparkarray[arraypos]=j;
          //       arraypos++;  
          //       }
          //   }
          // } 
          updateOled(44, 40, &yold);         
          yold=yval1;  
          INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
          outOfModus = true;
          updateOledFloat(88, 0, &INTERVAL7, 0); 
          // if (variant != 3){
          // fillLongxArray(yold, NUM_LEDS);
          // }
          T=0;
          readyToChange = true;
          forcedColourChange = true;
          colourSync = false;
          num15=0;
          previousMillis36 = millis();
          }
          }

    if ((variant == 3 && hh > 0 && hh < NUM_LEDS-1) || (variant == 4 && hh < NUM_LEDS-(1+cfactor3)) || (variant == 5 && hh > 1+cfactor3)) {
        if (millis() - previousMillis35 >= sparkSpeed+slowFactor) {
        previousMillis35 = millis();

        for (int s=0; s<numsparks; s++){   
        if (rr[s] < hh){
          longxArray[rr[s]]=yold; 
        }
        else if (rr[s] >= hh){
          longxArray[rr[s]]=yval1;
          }
          
        if (pos[s] > hh){
          longxArray[pos[s]]=yold;
        }
        else if (pos[s] <= hh){
          longxArray[pos[s]]=yval1;
          }
    
        rr[s]=pos[s];
        
        pos[s]=random(hh-offmax, hh+offmin);
          while (pos[s] < 0 || pos[s] > NUM_LEDS-1){
            pos[s]=random(hh-offmax, hh+offmin);}
        } 
    }
    }
    }
    if (hh == NUM_LEDS && num15 <1){
        num15++;
        for (int s=0; s<numsparks; s++){
            if (variant != 3){
            longxArray[rr[s]] = yold;
            }
        rr[s]=NUM_LEDS;
        pos[s]=NUM_LEDS;  
        }
    changeColor = true;   
    }
    }

    else if ((variant == 6 || variant == 7) && (!readyToChange)){
     if ((millis() - previousMillis36 >= INTERVAL7 && (!inColourSync)) || (colourSync)){ 
      outOfModus = false;
      
      if (forcedColourChange){
        if (!colourSync){
        yval1 = changeColourFcn2(colorMode, yval1, yold, 40, 210);               
        //updateOled(102, 56, &yval1);
        if ((syncEsp) && (colourSyncToggle)){espNowMessage = true;   EspNowMessageType = 17;  };
        }
        updateOled(102, 56, &yval1);
        forcedColourChange = false; 
      }
        if (millis() - previousMillis37 >= (slingerSpeed+slowFactor)){ // 200 is slingerSpeed
          previousMillis37 = millis();
          longxArray[NUM_LEDS/2+xx]=yval1;
          longxArray[NUM_LEDS/2-xx]=yval1;
          xx++;
          if (xx > (NUM_LEDS/2-(15*cfactor2))){
          slowFactor+=2;
          }  

      if (xx>NUM_LEDS/2){
          xx=0;
          //slowFactor=0;
          evenOddCounter++;
          updateOled(44, 40, &yold);         
          yold=yval1;  
          INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
          outOfModus = true;
          updateOledFloat(88, 0, &INTERVAL7, 0); 
          //fillLongxArray(yold, NUM_LEDS);
          T=0;
          readyToChange = true;
          forcedColourChange = true;
          colourSync = false;
          num15=0;
          previousMillis36 = millis();
          }
          }

    if (xx > 0){
        if (millis() - previousMillis35 >= sparkSpeed+slowFactor) {
        previousMillis35 = millis();

        for (int s=0; s<numsparks; s++){  

          if (variant == 6){

              if ((rr[s] <= (NUM_LEDS/2)+xx) && (rr[s] >= (NUM_LEDS/2)-xx)){
                longxArray[rr[s]]=yval1;
              }
              else if ((rr[s] > (NUM_LEDS/2)+xx) || (rr[s] < (NUM_LEDS/2)-xx)){
                longxArray[rr[s]]=yold;
              }

              if ((rr2[s] <= (NUM_LEDS/2)+xx) && (rr2[s] >= (NUM_LEDS/2)-xx)){
                longxArray[rr2[s]]=yval1;
              }
              else if ((rr2[s] > (NUM_LEDS/2)+xx) || (rr2[s] < (NUM_LEDS/2)-xx)){
                longxArray[rr2[s]]=yold;
              }

              
              if ((pos[s] < (NUM_LEDS/2)+xx) && (pos[s] > (NUM_LEDS/2)-xx)){
                longxArray[pos[s]]=yold;
              }
              else if ((pos[s] >= (NUM_LEDS/2)+xx) || (pos[s] <= (NUM_LEDS/2)-xx)){
                longxArray[pos[s]]=yval1;
              }

              if ((pos7[s] < (NUM_LEDS/2)+xx) && (pos7[s] > (NUM_LEDS/2)-xx)){
                longxArray[pos7[s]]=yold;
              }
              else if ((pos7[s] >= (NUM_LEDS/2)+xx) || (pos7[s] <= (NUM_LEDS/2)-xx)){
                longxArray[pos7[s]]=yval1;
              }

          }
          else if (variant == 7){

              if ((rr[s] <= (NUM_LEDS/2)+xx) && (rr[s] >= (NUM_LEDS/2)-xx)){
                longxArray[rr[s]]=yold;
              }
              else if ((rr[s] > (NUM_LEDS/2)+xx) || (rr[s] < (NUM_LEDS/2)-xx)){
                longxArray[rr[s]]=yval1;
              }

              if ((rr2[s] <= (NUM_LEDS/2)+xx) && (rr2[s] >= (NUM_LEDS/2)-xx)){
                longxArray[rr2[s]]=yold;
              }
              else if ((rr2[s] > (NUM_LEDS/2)+xx) || (rr2[s] < (NUM_LEDS/2)-xx)){
                longxArray[rr2[s]]=yval1;
              }
            
            longxArray[pos[s]]=yval1;
            longxArray[pos7[s]]=yval1;      

          }


        rr[s]=pos[s];
        rr2[s]=pos7[s];
        
        pos[s]=random(((NUM_LEDS/2-xx)-offmax), ((NUM_LEDS/2-xx)+offmin));
          while (pos[s] < 0 || pos[s] > NUM_LEDS-1){
            pos[s]=random(NUM_LEDS);}

        pos7[s]=random(((NUM_LEDS/2+xx)-offmax), ((NUM_LEDS/2+xx)+offmin));
          while (pos7[s] < 0 || pos7[s] > NUM_LEDS-1){
            pos7[s]=random(NUM_LEDS);} 
        } 
    }
    }
    }

  if (xx == 0 && num15 <1){
      num15++;
  
      for (int s=0; s<numsparks;s++){
      // longxArray[rr[s]] = yold;
      // longxArray[rr2[s]] = yold;

      rr[s]=NUM_LEDS; 
      pos[s]=NUM_LEDS;    

      rr2[s]=NUM_LEDS; 
      pos7[s]=NUM_LEDS;     
      }

      changeColor = true;
  }    
  }

  else if ((variant == 8) && (!readyToChange)){
     if ((millis() - previousMillis36 >= INTERVAL7 && (!inColourSync)) || (colourSync)){ 
      outOfModus = false;
      
      if (forcedColourChange){
        if (!colourSync){
        yval1 = changeColourFcn2(colorMode, yval1, yold, 40, 210);               
        //updateOled(102, 56, &yval1);
        if ((syncEsp) && (colourSyncToggle)){espNowMessage = true;   EspNowMessageType = 17;  };
        }
        updateOled(102, 56, &yval1);
        forcedColourChange = false; 
      }
        if (millis() - previousMillis37 >= FPS){ // 200 is slingerSpeed
          previousMillis37 = millis();

          for (int i = 0; i <= xx; i++){
            if (i == 0){
            longxArray[(NUM_LEDS/2)] = fadeFnc(longxArray[(NUM_LEDS/2)], yval1); 
            }
            else {
            longxArray[(NUM_LEDS/2)+i] = fadeFnc(longxArray[(NUM_LEDS/2)+i], yval1); 
            longxArray[(NUM_LEDS/2)-i] = fadeFnc(longxArray[(NUM_LEDS/2)-i], yval1); 
            }
          }

          xx++;
          
          if ((longxArray[NUM_LEDS/2] == yval1) || (xx > NUM_LEDS/2)){
          xx=0;
          evenOddCounter++;
          updateOled(44, 40, &yold);         
          yold=yval1;  
          INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
          outOfModus = true;
          updateOledFloat(88, 0, &INTERVAL7, 0); 
          T=0;
          readyToChange = true;
          forcedColourChange = true;
          num15=0;
          previousMillis36 = millis();
          changeColor = true;
          colourSync = false;
          }
          }
     }
  }

    else if ((variant == 9) && (!readyToChange)){
     if ((millis() - previousMillis36 >= INTERVAL7 && (!inColourSync)) || (colourSync)){ 
      outOfModus = false;
      
      if (forcedColourChange){
        if (!colourSync){
        yval1 = changeColourFcn2(colorMode, yval1, yold, 40, 210);               
        //updateOled(102, 56, &yval1);
        if ((syncEsp) && (colourSyncToggle)){espNowMessage = true;   EspNowMessageType = 17;  };
        }
        updateOled(102, 56, &yval1);
        forcedColourChange = false; 
      }
        if (millis() - previousMillis37 >= FPS){ // 200 is slingerSpeed
          previousMillis37 = millis();

          for (int i = 0; i <= xx; i++){
            longxArray[i] = fadeFnc(longxArray[i], yval1); 
          }

          xx++;
          
          if ((longxArray[0] == yval1) || (xx >= NUM_LEDS)){
          xx=0;
          evenOddCounter++;
          updateOled(44, 40, &yold);         
          yold=yval1;  
          INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
          outOfModus = true;
          updateOledFloat(88, 0, &INTERVAL7, 0); 
          T=0;
          readyToChange = true;
          forcedColourChange = true;
          num15=0;
          previousMillis36 = millis();
          changeColor = true;
          colourSync = false;
          }
          }
     }
  }

    else if ((variant == 10) && (!readyToChange)){
     if ((millis() - previousMillis36 >= INTERVAL7 && (!inColourSync)) || (colourSync)){ 
      outOfModus = false;
      
      if (forcedColourChange){
        if (!colourSync){
        yval1 = changeColourFcn2(colorMode, yval1, yold, 40, 210);               
        //updateOled(102, 56, &yval1);
        if ((syncEsp) && (colourSyncToggle)){espNowMessage = true;   EspNowMessageType = 17;  };
        }
        updateOled(102, 56, &yval1);
        forcedColourChange = false; 
      }
        if (millis() - previousMillis37 >= FPS){ // 200 is slingerSpeed
          previousMillis37 = millis();

          for (int i = 0; i <= xx; i++){
            longxArray[(NUM_LEDS-1)-i] = fadeFnc(longxArray[(NUM_LEDS-1)-i], yval1);  
          }

          xx++;
          
          if ((longxArray[NUM_LEDS-1] == yval1) || (xx >= NUM_LEDS)){
          xx=0;
          evenOddCounter++;
          updateOled(44, 40, &yold);         
          yold=yval1;  
          INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
          outOfModus = true;
          updateOledFloat(88, 0, &INTERVAL7, 0); 
          T=0;
          readyToChange = true;
          forcedColourChange = true;
          num15=0;
          previousMillis36 = millis();
          changeColor = true;
          colourSync = false;
          }
          }
     }
  }


    if (millis() - previousMillis38 >= FPS && (changeColor)) {
      previousMillis38 = millis();

        for(int i = 0; i < NUM_LEDS; i++){
          if (longxArray[i] != yold){
            longxArray[i] = fadeFnc(longxArray[i], yold); 
          }
        }

        for(int i = 0; i < NUM_LEDS; i++){
          if (longxArray[i] != yold) { 
            changeColor = true;
            break;}
          else {
            changeColor = false;
            }
          }      
    }

    if (millis() - previousMillis2 >= FPS) { 
    previousMillis2 = millis();  

      // if (fadeIsActive){
      //   if (yold1 == yold) {
      //       fadeIsActive = false;
      //   }
      //   yold1 = fadeFnc(yold1, yold);    
      //   for (int l = 0; l < arraypos; l++){
      //   longxArray[sparkarray[l]] = yold1;
      //   }            
      //  }

         for(int i = 0; i < NUM_LEDS; i++ ){
           for (int j = 0; j < numsparks; j++ ){
              if (i == pos[j]){
                  leds[i] = CHSV(longxArray[i],qadd8(S,SF),qadd8(BRIGH,BrF));
                  break;      
              }
              else{
                  leds[i] = CHSV((longxArray[i]+yvar[varlu]+diff[difflu]),satval[satlu],brigh[brighlu]);   
              }
           }
          
         brighlu++;
         if (brighlu >= numbrigh){brighlu = 0;}

         satlu++;
         if (satlu >= numsat){satlu = 0;}

         varlu++;
         if (varlu >= 10){varlu = 0;}

         difflu++;
         if (difflu >= 10){difflu = 0;}
         }
         
         handleGlitter(); 
         FastLED.show();
         brighlu=0; 
         satlu=0;  
         varlu=0;
         difflu=0;
  }
}

void snow_storm(void){
     if ((millis() - previousMillis36 >= INTERVAL7 && (!inColourSync)) || (colourSync)){ 
      outOfModus = false;
      
      if (forcedColourChange){
        if (!colourSync){
        yval1 = changeColourFcn2(colorMode, yval1, yold, 40, 210);               
        //updateOled(102, 56, &yval1);
        if ((syncEsp) && (colourSyncToggle)){espNowMessage = true;   EspNowMessageType = 18;  };
        }
        updateOled(102, 56, &yval1);
        forcedColourChange = false; 
      }
      if (fadeIsActive){
        if (varON == 2){
          if (millis() - previousMillis38 >= 2*changeSpeed) {
          previousMillis38 = millis();
            if (yold == yval1) {
                  fadeIsActive = false;
            }
            yold = fadeFnc(yold, yval1); 
            fillLongxArray(yold, NUM_LEDS);   
          }
        }
        else if (varON != 2){
          fadeIsActive = false;
        }
      }
      else if (!fadeIsActive){
        for (int s=0; s < numsparks; s++){
          if (millis() - previousMillisLN[s] >= changeSpeedMA[s] && flakeCounter >= flakeListMode7[s] && flakeCounter <= cn) {
            previousMillisLN[s] = millis();
            num17[s]-=offdis;
            //Serial.print("flakecounter: "); Serial.println(flakeCounter);
            }
            if (num17[s] < rn[s] && flakeCounter <= cn){
              num17[s]=NUM_LEDS; // adjusted
              flakeCounter++;
              if (flakeCounter <= 10 && s == 0){
                rn[0]= random(NUM_LEDS*0.5),(NUM_LEDS*0.75);}
              else{
                //rn[s]=random(randomNumberMinimum[s], randomNumberMaximum[s]);
                //rn[s]=random((NUM_LEDS/randomNumberMinimum[s]), (NUM_LEDS)/randomNumberMaximum[s]));
                rn[s]=random(NUM_LEDS);            
              }
              num23[s]=0;
              changeSpeedMA[s]=changeSpeed*timeArray[random(0,5)];
            }
            if (flakeCounter > cn && num26[s] < 1){  // CHANGED_HERE
              num26[s]=num26[s]+1;   
              num17[s]=NUM_LEDS; // adjusted
              num23[s]=0;
              //pos[s]=NUM_LEDS; // extra line
            }
          }

        if (millis() - previousMillis37 >= changeSpeed/cfactor3 && flakeCounter > cn-(3*cfactor3)){
          //Serial.println("counting down hh");
          previousMillis37 = millis();
          longxArray[hh]=yval1;;
          if (hh < NUM_LEDS-1){
          longxArray[hh+1]=yval1;
          }
          hh=hh-1;
          if (hh<0){
              hh=NUM_LEDS;
              evenOddCounter++; 
              INTERVAL7=interval7*timeArray2[random(0,6)]*timefactor3;

              yold=yval1;  
              yval1=yval1+1;
              updateOled(44, 40, &yold);

              outOfModus = true;
              updateOledFloat(88, 0, &INTERVAL7, 0); 
              T=0;
              forcedColourChange = true;
              num15=0;
              fillLongxArray(yold, NUM_LEDS);
              for (int s=0; s < numsparks; s++){
              num17[s]=NUM_LEDS; // adjusted
              num26[s]=0;
              //rn[s]=random(randomNumberMinimum[s], randomNumberMaximum[s]);
              //rn[s]=random((NUM_LEDS/randomNumberMinimum[s]), (NUM_LEDS)/randomNumberMaximum[s]));
              rn[s]=random(NUM_LEDS);
              }
              fadeIsActive = true;
              colourSync = false;
              flakeCounter=0;
                          
              if (NUM_LEDS <= 100){
              cn=random(34,60);
              }
              else if (NUM_LEDS > 100){
              cn=random(60,93);
              }                                     
              previousMillis36 = millis();
          }
     }
    }
} 
      
if ((millis() - previousMillis36 >= INTERVAL7 && (!inColourSync)) || (colourSync)){              //&& ((num17[0] > 0) || (hh > 0 && hh < NUM_LEDS-1))
    if (millis() - previousMillis35 >= sparkSpeed) { // sparkSpeed = changeSpeed/DF
    //Serial.println("does it spark in flake mode");
    previousMillis35 = millis();

        if (hh < NUM_LEDS-1){
          if (rrhh < hh){ 
          longxArray[rrhh]=yold; 
          }
          else if (rrhh >= hh){
          longxArray[rrhh]=yval1;
          }

          if (poshh > hh){
          longxArray[poshh]=yold; 
          }
          else if (poshh <= hh){
          longxArray[poshh]=yval1;   
          }

         rrhh=poshh;  
          
         poshh=random(hh-offmax-10, hh+offmin+10);
          while (poshh < 0 || poshh > NUM_LEDS-1){
            poshh=random(hh-offmax-(12*cfactor3), hh+offmin+(12*cfactor3));
          }       
       }

    for (int s=0; s < numsparks; s++){
        if (num17[s] < NUM_LEDS-1){  
            if (rr[s] <= hh){
            longxArray[rr[s]]=yold;  
            }
            else if (rr[s] > hh){ 
            longxArray[rr[s]]=yval1;
            }
       
            if (pos[s] > hh){
            longxArray[pos[s]]=yold;  
            }
            else if (pos[s] <= hh){
            longxArray[pos[s]]=yval1;  
            }
         }
        rr[s]=pos[s];
          
        if (num17[s] < NUM_LEDS-1 && num17[s] >= NUM_LEDS-(offdis+1)){  
        pos[s]=random(num17[s]-1, num17[s]+(offdis+1));
          while (pos[s] < 0 || pos[s] > NUM_LEDS-1){ 
            pos[s]=random(num17[s]-1, num17[s]+(offdis+1));
          }
        } 
        else if (num17[s] < NUM_LEDS-(offdis+1)){  
        pos[s]=random(num17[s]-offmax, num17[s]+offmin);
          while (pos[s] < 0 || pos[s] > NUM_LEDS-1){
            pos[s]=random(num17[s]-offmax, num17[s]+offmin);
          }
        }       
     }     
   }
}

if (millis() - previousMillis39 >= FPS) { 
previousMillis39 = millis();  
   for (int s=0; s < numsparks; s++){    
        if (num17[s] == NUM_LEDS && num23[s] < 1){  // CHANGED_HERE adjusted
        num23[s]=num23[s]+1;
        if (rr[s] < hh){
        longxArray[rr[s]]=yold;
        }
        else if (rr[s] >= hh){
        longxArray[rr[s]]=yval1;            
        }
        }
    }
       
    if (hh == NUM_LEDS && num15 <1){ // CHANGED_HERE
        num15++;       
        longxArray[rrhh]=yold;     // yval1 --> yold            
        rrhh=NUM_LEDS;
        poshh=NUM_LEDS;
        for (int s=0; s < numsparks; s++){
          rr[s]=NUM_LEDS; // adjusted
          pos[s]=NUM_LEDS; // adjusted
        }
    }
}
     
    if (millis() - previousMillis2 >= FPS) { 
    previousMillis2 = millis();  

       for(int i = 0; i < NUM_LEDS; i++ ){
         for(int j = 0; j < numsparks; j++){
              if (((i == pos[j]) || (i == poshh)) && longxArray[i] == yval1){
              leds[i] = CHSV(longxArray[i],qadd8(S,SF),qadd8(BRIGH,BrF));
              break;    
              }
              else {         
              leds[i] = CHSV((longxArray[i]+yvar[varlu]+diff[difflu]),satval[satlu],brigh[brighlu]);
              }
         }        
       brighlu++;
       if (brighlu >= numbrigh){brighlu = 0;}

       satlu++;
       if (satlu >= numsat){satlu = 0;}

       varlu++;
       if (varlu >= 10){varlu = 0;}

       difflu++;
       if (difflu >= 10){difflu = 0;}
       }
       
       handleGlitter();   
       FastLED.show();
       brighlu=0;    
       satlu=0; 
       varlu=0;
       difflu=0;
  }
}

void random_led(void){  
if (millis() - previousMillis1 >= changeSpeed){
     if (colorMode == 5){
         colourChangeDelay++;
         if (colourChangeDelay >= setDifference*cfactor3){
         yval1+=10;
         colourChangeDelay=0;}
     }
     else{
     yval1 = changeColourFcn(colorMode, yval1, 0, 255);  
     }
    
     if (colorMode == 5){
          ig3=random(NUM_LEDS);
          longxArray[ig3]=yval1+random(-10,10);        
          previousMillis1 = millis();
     }
     else {
          ig3=random(NUM_LEDS);
          longxArray[ig3]=yval1;  
          previousMillis1 = millis();
      }   
}

   if (millis() - previousMillis2 >= FPS){ 
        previousMillis2 = millis();  
        
           for(int i = 0; i < NUM_LEDS; i++ ){
           leds[i] = CHSV(longxArray[i],satval[satlu],brigh[brighlu]);
            
           brighlu++;
           if (brighlu >= numbrigh){brighlu = 0;}

           satlu++;
           if (satlu >= numsat){satlu = 0;}   
           }
       handleGlitter();
       FastLED.show();
       brighlu=0;
       satlu=0;
   }  
}   

void splash(void){  
if (!fadeIsActive){
if (millis() - previousMillis1 >= changeSpeed){
     if (colorMode == 5){
         colourChangeDelay++;
         if (colourChangeDelay >= setDifference*cfactor3){
         yval1+=10;
         colourChangeDelay=0;}
     }
     else{
     yval1 = changeColourFcn(colorMode, yval1, 0, 255);  
     }
    
     if (colorMode == 5){
          ig3=random(NUM_LEDS);
          leds[ig3]=CHSV((yval1+random(-10,10)), S, BRIGH);
     }
     else {
          ig3=random(NUM_LEDS);
          leds[ig3]=CHSV(yval1, S, BRIGH);

      }
      cyclesToFade++;
      if (cyclesToFade > rn14){
          cyclesToFade=0;
          rn14=random(100, 500)*NUM_LEDS/100;
          fadeIsActive = true;
      }
      handleGlitter();
      previousMillis1 = millis();
      FastLED.show();
    }
}
else if (fadeIsActive){
    if (varON == 0){
      if (millis() - previousMillis5 > changeSpeed){
      for(int j=0; j<NUM_LEDS; j++) {
        if(random(10)>3) {
          leds[j].fadeToBlackBy(28);       
        }
      }
      cyclesToFade++;
      if (cyclesToFade > 100){
        cyclesToFade=0;
        rn14=random(100, 500)*NUM_LEDS/100;
        fadeIsActive = false;
      }
      FastLED.show();
      previousMillis5 = millis();
      }
    }
    else if (varON == 1 || varON == 2){
      if (millis() - previousMillis5 > changeSpeed){
        ig3=random(NUM_LEDS);
        leds[ig3]=CRGB::Black;
        cyclesToFade++;

        if (cyclesToFade > rn14){
          cyclesToFade=0;
          rn14=random(100, 500)*NUM_LEDS/100;
          fadeIsActive = false;
          }
        FastLED.show();
        previousMillis5 = millis();
      }
    }

    if (millis() - previousMillis36 > INTERVAL9 && colorMode == 4 && varON == 2 && inSync == false) {
      arrayn = random(arrayCount);
      updateOled(24, 40, &arrayn);
      selectcolorArray();
      if (syncEsp){espNowMessage = true;   EspNowMessageType = 7;  };   
      INTERVAL9=interval9*timeArray2[random(0,6)]*timefactor3;
      previousMillis36 = millis();
      T=0;        
    }
}
}


void strobe(void){  
if (millis() - previousMillis1 >= changeSpeed){
     if (colorMode == 5){
         colourChangeDelay++;
         if (colourChangeDelay >= setDifference*cfactor3){
         yval1+=10;
         colourChangeDelay=0;}
     }
     else{
     yval1 = changeColourFcn(colorMode, yval1, 0, 255);  
     }
    
     if (colorMode == 5){
          ig3=random(NUM_LEDS);
            leds[ig3]=CHSV((yval1+random(-10,10)), S, BRIGH);
            handleGlitter();
            previousMillis1 = millis();
     }
     else {
        ig3=random(NUM_LEDS);
        leds[ig3]=CHSV(yval1, S, BRIGH);
        handleGlitter();  
        previousMillis1 = millis();
      }   
}

if (millis() - previousMillis36 > INTERVAL7 && varON == 2 && colorMode == 4 && inSync == false) {
      arrayn = random(arrayCount);
      updateOled(24, 40, &arrayn);
      selectcolorArray();
      if (syncEsp){espNowMessage = true;   EspNowMessageType = 7;  };   
      INTERVAL7=(interval9/5)*timeArray2[random(0,6)]*timefactor3;
      updateOledFloat(88, 0, &INTERVAL7, 0); 
      previousMillis36 = millis();
      T=0;        
}

    if (millis() - previousMillis5 > FPS){
          if (changeSpeed > 30){  
          fadeToBlackBy(leds, NUM_LEDS, 16);
          }
          else if (changeSpeed <= 30){
          fadeToBlackBy(leds, NUM_LEDS, 64);
          }
          previousMillis5 = millis();
          FastLED.show();
        }
}    

void pers_color(void){ 
if (millis() - previousMillis1 >= changeSpeed && varON == 1) {
previousMillis1 = millis(); 

changePColors();
}

else if (millis() - previousMillis36 > INTERVAL7 && varON == 2) {
  if (millis() - previousMillis1 >= (changeSpeed/10)) {
  previousMillis1 = millis(); 
  
  if ((syncEsp) && (alertColor)){
    espNowMessage = true;
    EspNowMessageType = 7;
    alertColor = false;
  };   

    for (int i = 0;  i < 15; i++){
     if (colour[i] != newColour[i]) { 
       changeColor = true;
       break;}
     else{
      changeColor = false;}
    } 
         
    if (changeColor) {
        for (int i = 0; i < 15; i++){
          if (colour[i] != newColour[i]){
            colour[i] = fadeFnc(colour[i], newColour[i]); 
          }
        }      
      }
    else if ((!changeColor) && (!inSync)){
      oldArrayn = arrayn;
      arrayn = random(arrayCount);
      updateOled(24, 40, &oldArrayn);
      selectcolorArray();
      alertColor = true;
      INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
      updateOledFloat(88, 0, &INTERVAL7, 0); 
      previousMillis36 = millis();
      T=0;        
    }
  }
}

if (millis() - previousMillis2 >= FPS) {
previousMillis2 = millis(); 

     for(int i = 0; i < NUM_LEDS; i++ ){
     leds[i] = CHSV(colour[colourlu],satval[satlu],brigh[brighlu]);
      
     brighlu++;
     if (brighlu >= numbrigh){brighlu = 0;}
     
     colourlu++;
     if (colourlu >= numcolor){colourlu = 0;}
  
     satlu++;
     if (whiteON){
     if (satlu >= numcolor){satlu = 0;}
     }
     else {
      if (satlu >= numsat){satlu = 0;}
     }
     }
     
     handleGlitter();
     FastLED.show();
     brighlu=0;
     colourlu=0;
     satlu=0; 
}
}

void random_string(void){
if (millis() - previousMillis1 >= changeSpeed){
  previousMillis1 = millis();
  for (int i = 0; i < colorlength; i++){
    yval1 = changeColourFcn(colorMode, yval1, 0, 255);
    longxArray[i]=yval1;
  }
}

if (millis() - previousMillis36 > INTERVAL7 && colorMode == 4 && varON == 2 && inSync == false) {
      arrayn = random(arrayCount);
      updateOled(24, 40, &arrayn);
      selectcolorArray();
      if (syncEsp){espNowMessage = true;   EspNowMessageType = 7;  };
      INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
      updateOledFloat(88, 0, &INTERVAL7, 0); 
      previousMillis36 = millis();
      T=0;        
}


if (millis() - previousMillis2 >= FPS) { 
previousMillis2 = millis(); 
  
     for(int i = 0; i < NUM_LEDS; i++ ){
     leds[i] = CHSV(longxArray[colourlu],satval[satlu],brigh[brighlu]);
      
     brighlu++;
     if (brighlu >= numbrigh){brighlu = 0;}
     
     colourlu++;
     if (colourlu >= colorlength){colourlu = 0;}

     satlu++;
     if (satlu >= numsat){satlu = 0;}     
     }

     handleGlitter();
     FastLED.show();
     brighlu=0;
     colourlu=0;
     satlu=0;
}
}

void rainbow_5(void){
    if (millis() - previousMillis1 >= changeSpeed) {
      previousMillis1 = millis();
      yval1+=offdis*dir1;
      ysr=yval1;
    }

    if (millis() - previousMillis2 >= FPS) { 
      previousMillis2 = millis();  
      for(int i = 0; i < NUM_LEDS; i++ ){
      leds[i] = CHSV(ysr+yvar[varlu],satval[satlu],brigh[brighlu]);

      if (NUM_LEDS > 300){
        if (i % setDifference == 0){
          ysr+=1;
        }
      }
      else {
      ysr+=setDifference;
      }
      
      brighlu++;
      if (brighlu >= numbrigh){brighlu = 0;} 
      
      varlu++;
      if (varlu >= 10){varlu =0;}

      satlu++;
      if (satlu >= numsat){satlu = 0;}
      } 
       
      handleGlitter();
      FastLED.show();
      brighlu=0;
      ysr=yval1;
      varlu=0;
      satlu=0;
   }
}

void rainbow_2(void){
    if (millis() - previousMillis1 >= changeSpeed) {
      previousMillis1 = millis();

      if (varON != 2){
        yval1-=offdis*dir1;
        ysr=yval1;
        //fillRainbow2(longxArray, 1);

        for(int i = 0; i < NUM_LEDS/2; i++ ){
              longxArray[(NUM_LEDS/2)-i] = ysr;
              longxArray[(NUM_LEDS/2)+i] = ysr;

              if (NUM_LEDS > 300){
                if (i % setDifference == 0){
                  ysr+=1;
                }
              }
              else {
              ysr+=setDifference;
              }
        }
      }
      else if (varON == 2 && (!changeColor)){
        yval1-=offdis*dir1;
        ysr=yval1;

        //fillRainbow2(longxArray, rainbow2m);

        switch (rainbow2m){
          case 1: {
            for(int i = 0; i < NUM_LEDS/2; i++ ){
              longxArray[(NUM_LEDS/2)-i] = ysr;
              longxArray[(NUM_LEDS/2)+i] = ysr;

            if (NUM_LEDS > 300){
              if (i % setDifference == 0){
                ysr+=1;
              }
            }
            else {ysr+=setDifference;
            }
            }
          }
          break;
          case 2: {
            for(int i = 0; i < NUM_LEDS; i++ ){
              longxArray[i] = ysr;

              if (NUM_LEDS > 300){
                if (i % setDifference == 0){
                  ysr+=1;
                }
              }
              else {ysr+=setDifference;}
            }
          break;
          }
        }
      }
    }

    if (varON == 2){
      if (millis() - previousMillis36 >= INTERVAL7 && (!changeColor)){ 
        previousMillis36 = millis();
        rn6=random(0,4);
        INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
        changeColor = true;
        ysr = yval1; 
          if (rn6 == 0 || rn6 == 1){
            rainbow2m = 1;

            for(int i = 0; i < NUM_LEDS/2; i++ ){
              blockArray[(NUM_LEDS/2)-i] = ysr;
              blockArray[(NUM_LEDS/2)+i] = ysr;

            if (NUM_LEDS > 300){
              if (i % setDifference == 0){
                ysr+=1;
              }
            }
            else {ysr+=setDifference;
            }
            }

            if (rn6 == 0){
              dir1 = 1;
            }
            else if (rn6 == 1){
              dir1 = -1;
          }
          }
          else if (rn6 == 2 || rn6 == 3){
            rainbow2m = 2;

            for(int i = 0; i < NUM_LEDS; i++ ){
              blockArray[i] = ysr;

              if (NUM_LEDS > 300){
                if (i % setDifference == 0){
                  ysr+=1;
                }
              }
              else {ysr+=setDifference;}
            }

            if (rn6 == 2){
              dir1 = 1;
            }
            else if (rn6 == 3){
              dir1 = -1;
            }
          } 
      } 

    if (millis() - previousMillis38 >= FPS && (changeColor)) {
      previousMillis38 = millis();

        for(int i = 0; i < NUM_LEDS; i++){
          if (longxArray[i] != blockArray[i]){
            longxArray[i] = fadeFnc(longxArray[i], blockArray[i]); 
          }
        }

        for(int i = 0; i < NUM_LEDS; i++){
          if (longxArray[i] != blockArray[i]) { 
            changeColor = true;
            break;}
          else {
            changeColor = false;
            }
          }      
    }  
  }


//     if (millis() - previousMillis2 >= FPS) { 
//       previousMillis2 = millis();  
//       switch(rainbow2m){
//         case 1: {
//           for(int i = 0; i < NUM_LEDS/2; i++ ){
//             leds[(NUM_LEDS/2)-i] = CHSV(ysr+yvar[varlu],satval[satlu],brigh[brighlu]);
//             leds[(NUM_LEDS/2)+i] = leds[(NUM_LEDS/2)-i];

//             if (NUM_LEDS > 300){
//               if (i % setDifference == 0){
//                 ysr+=1;
//               }
//             }
//             else {
//             ysr+=setDifference;
//             }
            
//             brighlu++;
//             if (brighlu >= numbrigh){brighlu = 0;} 
            
//             varlu++;
//             if (varlu >= 10){varlu =0;}

//             satlu++;
//             if (satlu >= numsat){satlu = 0;}
//             } 
//         }
//         break;
//         case 2: {
//           for(int i = 0; i < NUM_LEDS; i++ ){
//             leds[i] = CHSV(ysr+yvar[varlu],satval[satlu],brigh[brighlu]);

//             if (NUM_LEDS > 300){
//               if (i % setDifference == 0){
//                 ysr+=1;
//               }
//             }
//             else {
//             ysr+=setDifference;
//             }
            
//             brighlu++;
//             if (brighlu >= numbrigh){brighlu = 0;} 
            
//             varlu++;
//             if (varlu >= 10){varlu =0;}

//             satlu++;
//             if (satlu >= numsat){satlu = 0;}
//             } 
//         }
//         break;
//       }

//       handleGlitter();
//       FastLED.show();
//       brighlu=0;
//       ysr=yval1;
//       varlu=0;
//       satlu=0;
//     }
// }

    if (millis() - previousMillis2 >= FPS) { 
      previousMillis2 = millis();  

        for(int i = 0; i < NUM_LEDS; i++ ){
            leds[i] = CHSV(longxArray[i]+yvar[varlu],satval[satlu],brigh[brighlu]);
            
            brighlu++;
            if (brighlu >= numbrigh){brighlu = 0;} 
            
            varlu++;
            if (varlu >= 10){varlu =0;}

            satlu++;
            if (satlu >= numsat){satlu = 0;}
            } 

       
      handleGlitter();
      FastLED.show();
      brighlu=0;
      ysr=yval1;
      varlu=0;
      satlu=0;
   }
}
    
void twinkle(void){ 
  if (millis() - previousMillis1 >= changeSpeed) {
    colortwinkles();
    handleGlitter();
    FastLED.show(); 
    previousMillis1 = millis();
  }
}

void static_glow_2(void){
  if (millis() - previousMillis1 > INTERVAL7){
      if (!inSync){ // && setDifference > 20
        yx = changeColourFcn(colorMode, yx, 0, 255);
        if (syncEsp){espNowMessage = true;   EspNowMessageType = 16;  };
      }
      // else if (setDifference < 21){
      //   yx = changeColourFcn(colorMode, yx, 0, 255);
      // }  
      INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
      updateOledFloat(88, 0, &INTERVAL7, 0); 
      previousMillis1 = millis();
      updateOled(102, 56, &yx);
      T=0;
  }

  if ((fadeFirst) && yval1 != yx){
    if (millis() - previousMillis36 >= changeSpeed) {
      previousMillis36 = millis();
      yval1 = fadeFnc(yval1, yx); 
    }
  }            
  else if (fadeFirst == 0) {
     yval1=yx;
  }

    if (millis() - previousMillis2 >= FPS) { 
    previousMillis2 = millis();  
    fillColourArray(colour, yval1, yvar, diff); 
    fillNUM_LEDS1(colour, NUM_LEDS);       
    }
}

void colourSplash(void){ 
if ((millis() - previousMillis1 > INTERVAL7 && (!inSync)) || (colourSync)) {
  if (millis() - previousMillis36 >= changeSpeed) {
    previousMillis36 = millis();
    if (forcedColourChange) {
      if (!colourSync){
      yval1 = yval1+=random(60, 195);
      if (syncEsp){espNowMessage = true;   EspNowMessageType = 15;  };
      }
      seedNumber = (random(10, 25))*cfactor3;
        for (int i = 0; i < seedNumber; i++){
         seedArray[i]=random(NUM_LEDS);
        }
      forcedColourChange = false;
    }
    yTrans = fadeFnc(yTrans, yval1);     
    if (yTrans == yval1) {
      colourSync = false;
      forcedColourChange = true;
      INTERVAL7=(interval9/7)*timeArray2[random(0,6)]*timefactor3;
      updateOledFloat(88, 0, &INTERVAL7, 0); 
      previousMillis1 = millis();
      T=0;        
    }
  } 
} 

    if (millis() - previousMillis2 >= FPS) {
          for(int i = 0; i < NUM_LEDS; i++ ){
            for(int j = 0; j < seedNumber; j++){
              if (i == seedArray[j]){
                leds[i]=CHSV((yval1+yvar[varlu]+diff[difflu]),satval[satlu],brigh[brighlu]);
                break;
              }
              else {          
                leds[i] = CHSV((yTrans+yvar[varlu]+diff[difflu]),satval[satlu],brigh[brighlu]);
              }
            }  
            
          brighlu++;
          if (brighlu >= numbrigh){brighlu = 0;}

          satlu++;
          if (satlu >= numsat){satlu = 0;}

          varlu++;
          if (varlu >= 10){varlu = 0;}

          difflu++;
          if (difflu >= 10){difflu = 0;}
          } 

          handleGlitter();
          FastLED.show();

          satlu=0;
          brighlu=0;
          varlu=0;
          difflu=0;
          previousMillis2 = millis();    
    }
}

void sparkling_2(void){
if (readyToChange){
  if (!inColourSync){
  rn6=random(0,5);
  }
        if (rn6 == 0){
          variant = 0;
          yy=0;
          slowFactor = 0;
          offmin = random(11,17)*cfactor3;
          offmax = random(11,17)*cfactor3;
          slingerSpeed = timeArray3[random(0,5)]*changeSpeed/cfactor3;
          }
        else if (rn6 == 1){
          variant = 0;
          yy = NUM_LEDS;
          }  
        else if (rn6 == 2){
          variant = 1;
          hh=NUM_LEDS;
          slowFactor = 0;
          offmin = random(11,17)*cfactor3;
          offmax = random(11,17)*cfactor3;
          slingerSpeed = timeArray3[random(0,5)]*changeSpeed/cfactor3;
        }
        else if (rn6 == 3){
          variant = 1;
          hh = -1;
        }
        else if (rn6 == 4){
          variant = 2;
          xx=0;
          slowFactor = 0;
          offmin = random(8,14)*cfactor3;
          offmax = random(8,14)*cfactor3;
          slingerSpeed = timeArray3[random(0,5)]*changeSpeed/cfactor3;
        }
      if (tower){
        slingerSpeed=45/cfactor3;    
      }
readyToChange = false; 
}   
  
if (variant == 0 && (!readyToChange)){
    if ((millis() - previousMillis36 >= INTERVAL7 && (!inColourSync)) || (colourSync)){ 
      outOfModus = false;
      
      if (forcedColourChange){
        if (!colourSync){
        yval1 = changeColourFcn2(colorMode, yval1, yold, 40, 210);               
        updateOled(102, 56, &yval1);
        if ((syncEsp) && (colourSyncToggle)){espNowMessage = true;   EspNowMessageType = 17;  };
        }
        forcedColourChange = false; 
      }

      if (millis() - previousMillis37 >= (slingerSpeed+slowFactor)){
        previousMillis37 = millis();
        longxArray[yy]=yval1;
        yy=yy+=offdis;
        if (yy>NUM_LEDS-50){
          slowFactor+=3;
        }
        if (yy>NUM_LEDS-1){ 
            yy=0;
            //slowFactor=0;
            evenOddCounter++;  
            updateOled(44, 40, &yold);
            yold=yval1;
            //fillLongxArray(yold, NUM_LEDS);      
            INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
            outOfModus = true;
            updateOledFloat(88, 0, &INTERVAL7, 0); 
            previousMillis36 = millis();
            T=0;
            readyToChange = true;
            forcedColourChange = true;
            colourSync = false;
            num15=0;
        }
       }
       
    if (yy > 0 && yy <NUM_LEDS-1){
        if (millis() - previousMillis35 >= sparkSpeed) { // changeSpeed/DF
        previousMillis35 = millis();

        for (int s=0; s<numsparks;s++){
        if (rr[s] > yy){ 
        longxArray[rr[s]]=yold;  
        }
        else if (rr[s] <= yy){
        longxArray[rr[s]]=yval1;
        }

        longxArray[pos[s]]=colourS[4];
        longxArray[pos1[s]]=colourS[0];
        longxArray[pos2[s]]=colourS[1]; 
        longxArray[pos3[s]]=colourS[2];     
        longxArray[pos4[s]]=colourS[3];               
    
        rr[s]=pos1[s]; 
        pos1[s]=pos2[s];
        pos2[s]=pos3[s];
        pos3[s]=pos4[s];
        pos4[s]=pos[s];                          
        
        pos[s]=random(yy-offmin, yy+offmax);
          while (pos[s] < 0 || pos[s] > NUM_LEDS-1){
            pos[s]=random(yy-offmin, yy+offmax);}
        }        
        }
    }
    }

    if (yy == 0 && num15 <1){
        num15++;

        for (int s=0; s<numsparks;s++){

        rr[s]=NUM_LEDS; 
        pos[s]=NUM_LEDS;
        pos1[s]=NUM_LEDS; 
        pos2[s]=NUM_LEDS; 
        pos3[s]=NUM_LEDS; 
        pos4[s]=NUM_LEDS;      
        }

        changeColor = true;
        }
}


else if (variant == 1 && (!readyToChange)){
     if ((millis() - previousMillis36 >= INTERVAL7 && (!inColourSync)) || (colourSync)){ 
      outOfModus = false;
      
      if (forcedColourChange){
        if (!colourSync){
        yval1 = changeColourFcn2(colorMode, yval1, yold, 40, 210);               
        updateOled(102, 56, &yval1);
        if ((syncEsp) && (colourSyncToggle)){espNowMessage = true;   EspNowMessageType = 17;  };
        }
        forcedColourChange = false; 
      }

        if (millis() - previousMillis37 >= (slingerSpeed+slowFactor)){
          previousMillis37 = millis();
          longxArray[hh]=yval1;
          hh=hh-=offdis;
          if (hh<50){
          slowFactor+=4;
          }  
          if (hh<0){
              hh=NUM_LEDS;
              //slowFactor=0;
              evenOddCounter++; 
              updateOled(44, 40, &yold);
              yold=yval1;         
              //fillLongxArray(yold, NUM_LEDS);  
              INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
              outOfModus = true;
              updateOledFloat(88, 0, &INTERVAL7, 0); 
              previousMillis36 = millis();
              T=0;
              readyToChange = true;
              forcedColourChange = true;
              colourSync = false;
              num15=0;
          }
        }

    if (hh > 0 && hh <NUM_LEDS-1){
        if (millis() - previousMillis35 >= sparkSpeed) { // sparkSpeed = changeSpeed/DF
        previousMillis35 = millis();

        for (int s=0; s<numsparks;s++){
        if (rr[s] < hh){
          longxArray[rr[s]]=yold;
        }
        else if (rr[s] >= hh){
          longxArray[rr[s]]=yval1;
        }

        longxArray[pos[s]]=colourS[4];
        longxArray[pos1[s]]=colourS[0];
        longxArray[pos2[s]]=colourS[1]; 
        longxArray[pos3[s]]=colourS[2];     
        longxArray[pos4[s]]=colourS[3];               
    
        rr[s]=pos1[s]; 
        pos1[s]=pos2[s];
        pos2[s]=pos3[s];
        pos3[s]=pos4[s];
        pos4[s]=pos[s];             
                        
        
        pos[s]=random(hh-offmax, hh+offmin);
          while (pos[s] < 0 || pos[s] > NUM_LEDS-1){
            pos[s]=random(hh-offmax, hh+offmin);}
        }        
        }
    }
  }

  if (hh == NUM_LEDS && num15 <1){
      num15++;
  
      for (int s=0; s<numsparks;s++){

      rr[s]=NUM_LEDS; 
      pos[s]=NUM_LEDS; 
      pos1[s]=NUM_LEDS; 
      pos2[s]=NUM_LEDS; 
      pos3[s]=NUM_LEDS; 
      pos4[s]=NUM_LEDS;    
      }

      changeColor = true;
      }
  }

  else if (variant == 2 && (!readyToChange)){
     if ((millis() - previousMillis36 >= INTERVAL7 && (!inColourSync)) || (colourSync)){ 
      outOfModus = false;
      
      if (forcedColourChange){
        if (!colourSync){
        yval1 = changeColourFcn2(colorMode, yval1, yold, 40, 210);               
        updateOled(102, 56, &yval1);
        if ((syncEsp) && (colourSyncToggle)){espNowMessage = true;   EspNowMessageType = 17;  };
        }
        forcedColourChange = false; 
      }

        if (millis() - previousMillis37 >= (slingerSpeed+slowFactor)){
          previousMillis37 = millis();
          longxArray[NUM_LEDS/2+xx]=yval1;
          longxArray[NUM_LEDS/2-xx]=yval1;
          xx++;
          if (xx > NUM_LEDS/2-20){
          slowFactor+=4;
          }  
          if (xx>NUM_LEDS/2){
              xx=0;
              //slowFactor=0;
              evenOddCounter++; 
              updateOled(44, 40, &yold);
              yold=yval1;         
              //fillLongxArray(yold, NUM_LEDS);  
              INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
              outOfModus = true;
              updateOledFloat(88, 0, &INTERVAL7, 0); 
              previousMillis36 = millis();
              T=0;
              readyToChange = true;
              forcedColourChange = true;
              colourSync = false;
              num15=0;
          }
        }

    if (xx > 0){
        if (millis() - previousMillis35 >= sparkSpeed) { // sparkSpeed = changeSpeed/DF
        previousMillis35 = millis();

        for (int s=0; s<numsparks;s++){
        if ((rr[s] <= (NUM_LEDS/2)+xx) && (rr[s] >= (NUM_LEDS/2)-xx)){
          longxArray[rr[s]]=yval1;
        }
        else if ((rr[s] > (NUM_LEDS/2)+xx) || (rr[s] < (NUM_LEDS/2)-xx)){
          longxArray[rr[s]]=yold;
        }

        if ((rr2[s] <= (NUM_LEDS/2)+xx) && (rr2[s] >= (NUM_LEDS/2)-xx)){
          longxArray[rr2[s]]=yval1;
        }
        else if ((rr2[s] > (NUM_LEDS/2)+xx) || (rr2[s] < (NUM_LEDS/2)-xx)){
          longxArray[rr2[s]]=yold;
        }

        longxArray[pos[s]]=colourS[4];
        longxArray[pos1[s]]=colourS[0];
        longxArray[pos2[s]]=colourS[1]; 
        longxArray[pos3[s]]=colourS[2];     
        longxArray[pos4[s]]=colourS[3];       

        longxArray[pos7[s]]=colourS[4];
        longxArray[pos8[s]]=colourS[0];
        longxArray[pos9[s]]=colourS[1]; 
        longxArray[pos10[s]]=colourS[2];     
        longxArray[pos11[s]]=colourS[3];         
    
        rr[s]=pos1[s]; 
        pos1[s]=pos2[s];
        pos2[s]=pos3[s];
        pos3[s]=pos4[s];
        pos4[s]=pos[s];

        rr2[s]=pos8[s]; 
        pos8[s]=pos9[s];
        pos9[s]=pos10[s];
        pos10[s]=pos11[s];
        pos11[s]=pos7[s];                                
        
        pos[s]=random(((NUM_LEDS/2-xx)-offmax), ((NUM_LEDS/2-xx)+offmin));
          while (pos[s] < 0 || pos[s] > NUM_LEDS-1){
            pos[s]=random(NUM_LEDS);}

        pos7[s]=random(((NUM_LEDS/2+xx)-offmax), ((NUM_LEDS/2+xx)+offmin));
          while (pos7[s] < 0 || pos7[s] > NUM_LEDS-1){
            pos7[s]=random(NUM_LEDS);}   
        }        
        }
    }
  }

  if (xx == 0 && num15 <1){
      num15++;
  
      for (int s=0; s<numsparks;s++){

      rr[s]=NUM_LEDS; 
      pos[s]=NUM_LEDS; 
      pos1[s]=NUM_LEDS; 
      pos2[s]=NUM_LEDS; 
      pos3[s]=NUM_LEDS; 
      pos4[s]=NUM_LEDS;    

      rr2[s]=NUM_LEDS; 
      pos7[s]=NUM_LEDS; 
      pos8[s]=NUM_LEDS; 
      pos9[s]=NUM_LEDS; 
      pos10[s]=NUM_LEDS; 
      pos11[s]=NUM_LEDS;       
      }

      changeColor = true;
      }
  }

if (millis() - previousMillis38 >= FPS && (changeColor)) {
  previousMillis38 = millis();

    for(int i = 0; i < NUM_LEDS; i++){
      if (longxArray[i] != yold){
        longxArray[i] = fadeFnc(longxArray[i], yold); 
      }
    }

    for(int i = 0; i < NUM_LEDS; i++){
      if (longxArray[i] != yold) { 
        changeColor = true;
        break;}
      else {
        changeColor = false;
        }
      }      
}

  //   if (millis() - previousMillis1 >= FPS) { 
  //   previousMillis1 = millis();  

  //        for(int i = 0; i < NUM_LEDS; i++ ){
  //          for (int j = 0; j < numsparks; j++ ){
  //             if ((i == pos[j]) || (i == pos1[j]) || (i == pos2[j]) || (i == pos3[j]) || (i == pos4[j])) {
  //              leds[i] = CHSV(longxArray[i],qadd8(S,SF),qadd8(BRIGH,BrF)); 
  //              break;   
  //             }
  //             else {         
  //              leds[i] = CHSV((longxArray[i]+yvar[varlu]+diff[difflu]),satval[satlu],brigh[brighlu]);
  //             }
  //         }
          
  //        brighlu++;
  //        if (brighlu >= numbrigh){brighlu = 0;}

  //        satlu++;
  //        if (satlu >= numsat){satlu = 0;}
        
  //        varlu++;
  //        if (varlu >= 10){varlu = 0;}

  //        difflu++;
  //        if (difflu >= 10){difflu = 0;}
  //        }
          
  //        handleGlitter();
  //        FastLED.show();
  //        brighlu=0; 
  //        satlu=0; 
  //        varlu=0;
  //        difflu=0;
  // }



    if (millis() - previousMillis1 >= FPS) { 
    previousMillis1 = millis();  

         for(int i = 0; i < NUM_LEDS; i++ ){
           for (int j = 0; j < numsparks; j++ ){
              if ((i == pos[j]) || (i == pos1[j]) || (i == pos2[j]) || (i == pos3[j]) || (i == pos4[j] || i == pos7[j]) || (i == pos8[j]) || (i == pos9[j]) || (i == pos10[j]) || (i == pos11[j])) {
               leds[i] = CHSV(longxArray[i],qadd8(S,SF),qadd8(BRIGH,BrF)); 
               break;   
              }
              else {         
               leds[i] = CHSV((longxArray[i]+yvar[varlu]+diff[difflu]),satval[satlu],brigh[brighlu]);
              }
          }
          
         brighlu++;
         if (brighlu >= numbrigh){brighlu = 0;}

         satlu++;
         if (satlu >= numsat){satlu = 0;}
        
         varlu++;
         if (varlu >= 10){varlu = 0;}

         difflu++;
         if (difflu >= 10){difflu = 0;}
         }
          
         handleGlitter();
         FastLED.show();
         brighlu=0; 
         satlu=0; 
         varlu=0;
         difflu=0;
  }
//}
}     

void meteor(void){
if (millis() - previousMillis36 >= INTERVAL7){
  outOfModus=false;
  for (int s=0; s<numsparks; s++){  
    if (millis() - previousMillisAM[s] >= rtAM[s]){  
        if (millis() - previousMillisLN[s] >= changeSpeedMA[s] && flakeCounter >= flakeListMode16[s] && flakeCounter <= cn) {
          previousMillisLN[s] = millis();
          pos[s]=pos[s]-1;
          num6++;
          if (rainbowPossibility[s] == true){
              longxArray[pos[s]]=yMA[s]+pos[s];
          }
          else {
              longxArray[pos[s]]=yMA[s];
          }
            
          if (num6 >= cfactor2){
            if (revPossibility[s]){
                if (changeSpeedMA[s] >= FPS+3){  
                changeSpeedMA[s] -= (int)(3/cfactor2); //6
                }
            }
            else {
              if (pos[s] < rn[s]+(25*cfactor2)){ // 20
              changeSpeedMA[s] += (int)(3/cfactor2); //6
              }
            }
          num6=0;
          }

          if (pos[s] < rn[s]){
            if (colorMode != 5){
            yMA[s] = changeColourFcn2(colorMode, yMA[s], yMA[s], 25, 230); 
            }            
            if (rainbowPossibility[s] == true){
              yMA[s]=random(256);
            }
            pos[s]=NUM_LEDS;
            flakeCounter++;

              if (flakeCounter >= (cn-((3/cfactor3)*numsparks))){
                if (endFlag == false){
                  setDifferenceMem = setDifference;
                  endFlag=true;
                }
              setDifference++;
            }

            if (s == 0){
                if (numsparks == 1){
                  rtAM[0]= random(3500, 8000)*timefactor3;
                }
                else {
                  rtAM[0]= random(5000)*timefactor3;
                }
            }
            else{
              if (endFlag){
              rtAM[s]= random(4000)*timefactor3;
              }
              else {
              rtAM[s]= random(40000)*timefactor3;
              }
            }
            rn[s] = random(0, (NUM_LEDS/2+setDifference));
            if (revPossibility[s]){
              changeSpeedMA[s]=random(60, (90+(15*cfactor2)));
            }
            else {
              changeSpeedMA[s]=(changeSpeed*timeArray[random(1,5)])/4;
            }
            previousMillisAM[s] = millis();        
            }
          }
      }
  }

          
  if (millis() - previousMillis37 >= FPS && flakeCounter > cn){ // cn-4 //cn-(4*cfactor2)
    previousMillis37 = millis();
    hh=hh-1;
    if (hh <= 0){
      if (NUM_LEDS <= 100){
      cn=random(55,85);
      }
      else if (NUM_LEDS > 100){
      cn=random(55,125);
      }
      flakeCounter=0;
      readyToChange = true;
      endFlag=false;
      setDifference = setDifferenceMem;
      hh=NUM_LEDS;
      evenOddCounter++;

      if (colorMode == 5){
          yMA[0]=yMA[0]+random(30,225);
          while ((yMA[0] >= ymin && yMA[0] <= ymax) || (yMA[0] >= ymin1 && yMA[0] <= ymax1)){
            yMA[0]=yMA[0]+random(30,225);
            }
          }

      for (int s=0; s<numsparks;s++){
        if (colorMode == 5){
          yMA[s]=yMA[0];          
        }
        else {
        yMA[s] = changeColourFcn2(colorMode, yMA[s], yMA[s], 40, 210);       
        }
        pos[s]=NUM_LEDS;
        //rn[s]=random(randomNumberMinimum[s], randomNumberMaximum[s]);
        //rn[s]=random((NUM_LEDS/randomNumberMinimum[s]), (NUM_LEDS)/randomNumberMaximum[s]));
        rn[s]=random(NUM_LEDS);

        if ((random(75)<(9/cfactor2)) && (colorMode == 1 || colorMode == 2 || colorMode == 3)){
          rainbowPossibility[s]=true;
          }
        else {
          rainbowPossibility[s]=false;
          }

        if (random(36)<(9)){ 
          revPossibility[s]=true;
          changeSpeedMA[s]=random(60, (90+(15*cfactor2)));
          }
        else { 
          revPossibility[s]=false; 
          changeSpeedMA[s]=100;
          }  
      }   
      INTERVAL7=random(20000)*timefactor3;
      updateOledFloat(88, 0, &INTERVAL7, 0);
      outOfModus=true;
      T=0;
      num15=0;                              
      previousMillis36 = millis();
    }
    }
}

//if (millis() - previousMillis35 >= FPS && (hh == NUM_LEDS || flakeCounter < cn)) {
//if (millis() - previousMillis35 >= FPS && hh == NUM_LEDS) {
if (millis() - previousMillis35 >= FPS) {
      for(int i = 0; i < NUM_LEDS; i++){
        for (int j = 0; j < numsparks; j++ ){
          if (i == pos[j]) {
            for (int k = 0; k < setDifference; k++){
              if (i-k >= 0){
                if (varON == 0){
                  leds[i-k] += CHSV(longxArray[i],S,qadd8(BRIGH,(k*10))); // tryout  
                }
                else if (varON == 1){
                  leds[i-k] = CHSV(longxArray[i],qsub8(S,(k*10)),qadd8(BRIGH,(k*10))); // original
                }
                else{
                  leds[i-k] += CHSV(longxArray[i],qsub8(S,(k*10)),qadd8(BRIGH,(k*10))); // tryout qsub8(S,(k*10))
                }
              }
            }
          break;   
          }
          else {
            if (numsparks == 1 && setDifference <= 5){
              if(random(18)<(9/cfactor2)) {
              leds[i].fadeToBlackBy(random(setDifference*2));      
              }
            }
            else {
              if(random(63)<(9/cfactor2)) {
              leds[i].fadeToBlackBy(random(setDifference+3));      
              }   
            }   
          }
      }
      }
    FastLED.show(); 
    previousMillis35 = millis();
}     
} 

void snow_flakes_2(void){ 
if (millis() - previousMillis11 >= interval8) {
    previousMillis11 = millis();
    sF= sF+0.0675;
      if (sF >= 2.0){
        sF=1.00;
    }
}  

for (int k=0 ; k<numsparks; k++){
if (millis() - previousMillisLN[k] >= rtAM[k]/df){
  if ((millis() - previousMillisAM[k] >= (INTERVALf[k]*timeSpeed[k]*interRun[k])) && (sF <= sFtab[k])) {
    previousMillisAM[k] = millis();
    longxArray[a[k]]=yold;//+random(-ydiff,ydiff); 
    longxArray[i[k]]=yval1;    
    a[k]=i[k];
    if (tower){
        if((random(10)>5)) {
          i[k]=i[k]-offdis;
        }
        else { 
          i[k]=i[k]-offdis-1;
      }
    }
    else {
      i[k]=i[k]-1;
      if (i[k] == 80*cfactor3 || i[k] == 60*cfactor3 || i[k] == 40*cfactor3 || i[k] == 20*cfactor3){
      int chance = random(15);
        if (chance > 9){
          interRun[k]=1.1;
        }
        else if (chance < 5){
          interRun[k]=0.9;
        }
        else {interRun[k] = 1;}
      }
    }
    if (i[k]<partialArrayCounter){
      if (tower){
        i[k]=random(NUM_LEDS-offdis, NUM_LEDS);
        longxArray[a[k]]=yold;//+random(-ydiff,ydiff);
        a[k]=NUM_LEDS-1;
        partialArrayCounter+=1;
      }
      else {
        i[k]=NUM_LEDS-1;
        a[k]=NUM_LEDS-1;
        partialArrayCounter+=2;
      }
    if (partialArrayCounter > numsparks){
        outOfModus = false;
    }  
      
    if (partialArrayCounter >= NUM_LEDS-1){
        for (int i = 0; i < NUM_LEDS; i++){
        longxArray[i]=yval1;//+random(-10,10);
        }
      outOfModus = true;
      forcedColourChange = true; 
      partialArrayCounter=0;
    }
    previousMillisLN[k] = millis();
    rtAM[k]= random(65536);
    if (k == 0){
      num6=num6+1;
      if (num6 >= xnum){
        num6=0;
        INTERVALf[0]=changeSpeed*sF*timeArray3[random(0,6)];
        updateOledFloat(72, 56, &INTERVALf[0], 0);
    }
    }
    else if (k > 0){
          INTERVALf[k]=INTERVALf[0];
    }
    }
    }  
}
}

if (((forcedColourChange) && (!inColourSync)) || (colourSync)){ 

    if (!colourSync){
        evenOddCounter++;
        yold=yval1;
        yval1 = changeColourFcn2(colorMode, yval1, yold, 40, 210);
        updateOled(44, 40, &yold);      
        updateOled(102, 56, &yval1);    
      if ((syncEsp) && (colourSyncToggle)){espNowMessage = true;   EspNowMessageType = 19;  };
    }
  forcedColourChange = false; 
  }

  
if (millis() - previousMillis2 >= FPS) {
    previousMillis2 = millis();  
    partialArraySize=partialArrayCounter;
    fillLongxArray(yval1, partialArraySize);
    //fillColourArray(colourR, yval1, yvar, diff);
        
       for(int i = 0; i < partialArraySize; i++ ){
       leds[i] = CHSV((longxArray[i]+yvar[varlu]+diff[difflu]),satval[satlu],brigh[brighlu]);
        
       brighlu++;
       if (brighlu >= numbrigh){brighlu = 0;}

       satlu++;
       if (satlu >= numsat){ satlu = 0;}

       varlu++;
       if (varlu >= 10){varlu = 0;}

      difflu++;
      if (difflu >= 10){difflu = 0;}
      }

      for(int i = partialArraySize; i < NUM_LEDS; i++ ){
      if (longxArray[i] == yval1){
       leds[i] = CHSV(longxArray[i],qadd8(S,SF),qadd8(BRIGH,BrF));
       }
      else {
      leds[i] = CHSV((longxArray[i]+yvar[varlu]+diff[difflu]),S,BRIGH); 
      }
        
      // brighlu++;
      // if (brighlu >= numbrigh){brighlu = 0;}

      // satlu++;
      // if (satlu >= numsat){satlu = 0;}

      varlu++;
      if (varlu >= 10){varlu = 0;}

      difflu++;
      if (difflu >= 10){difflu = 0;}
      }

       handleGlitter();
       FastLED.show();
       brighlu=0;
       colourlu=0;  
       satlu=0;
       varlu=0;
       difflu=0;  
       } 
}

void rainbow_7(void){
    if (millis() - previousMillis1 >= changeSpeed + rn15) {
    previousMillis1 = millis();
    y0r+=1*dir1;
    y01m=y0r;
    rn15=0;
    if (y0r > ymax3 && y0r < ymax3+2 && dir1 == 1){ 
      dir1 = -1;
      }
    else if (y0r < ymin3 && y0r > ymin3-2 && dir1 == -1){ 
      dir1 = 1;
      rn15=random(5000,25000)*timefactor3;
      }
    }

    if (millis() - previousMillis2 >= FPS) {     
     previousMillis2 = millis(); 
            
     for(int i = 0; i < NUM_LEDS; i++ ){
     leds[i] = CHSV(y0r,satval[satlu],brigh[brighlu]);

     colorCount++;
     if (colorCount == ledspercolor){
     colorCount=0;
     y0r++;}
      
     brighlu++;
     if (brighlu >= numbrigh){brighlu = 0;}
     
     satlu++;
     if (satlu >= numsat){satlu = 0;}     
     }

     handleGlitter();
     FastLED.show();    
     brighlu=0;
     y0r=y01m; 
     satlu=0;         
    }
}

void gradient(void){
if (varON == 1 || (varON == 2 && (!changeColor))){ 
//if (varON == 1){   
    if (millis() - previousMillis1 >= changeSpeed + rn15) {
    previousMillis1 = millis();
    rn15=0;
    
    yval1+=1*dir1;

    fillArrayGradient(1, yval1, setDifference);

    if (yval1 == ymax4-setDifference && dir1 == 1){
     dir1 = -1;
     rn15 = random(65536)/2*timefactor3;
     }
    else if (yval1 == ymin4 && dir1 == -1){
     dir1 = 1;
     rn15 = random(65536)/2*timefactor3;
     }
    }
}

if (varON == 2){
if (millis() - previousMillis36 > INTERVAL7 && (!changeColor) && (!inSync)) {
        selectColor = random(14);
        dir1=1;
        ymax4 = pgm_read_byte(&selectColor_data[selectColor].ymax4);
        ymin4 = pgm_read_byte(&selectColor_data[selectColor].ymin4);
        setDifference = pgm_read_byte(&selectColor_data[selectColor].setDifference);
        yval1=ymin4;
        dir0=1;
        if (syncEsp){espNowMessage = true;   EspNowMessageType = 9;  };
        fillArrayGradient(3, yval1, setDifference);
        changeColor = true;
        INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
        updateOledFloat(88, 0, &INTERVAL7, 0); 
        notifyClientsSingleObjectInt("SGRA", selectColor);
        notifyClientsSingleObjectInt("SDIF", setDifference);
        previousMillis36 = millis();
        T=0;        
      }

      

if (millis() - previousMillis37 >= changeSpeed && (changeColor)) {
  previousMillis37 = millis();

    for(int i = 0; i < NUM_LEDS; i++){
      if (longxArray[i] != blockArray[i]){
        longxArray[i] = fadeFnc(longxArray[i], blockArray[i]); 
      }
    }

    for(int i = 0; i < NUM_LEDS; i++){
      if (longxArray[i] != blockArray[i]) { 
        changeColor = true;
        break;}
      else {
        changeColor = false;
        }
      }      
      }
}
  
    
    if (millis() - previousMillis2 >= FPS) {     
      previousMillis2 = millis(); 
      // y0r=yval1;  
      // dir0=1;
      
       for(int i = 0; i < NUM_LEDS; i++ ){
       leds[i] = CHSV(longxArray[i],satval[satlu],brigh[brighlu]);
        
       brighlu++;
       if (brighlu >= numbrigh){brighlu = 0;}

       satlu++;
       if (satlu >= numsat){satlu = 0;}       
       
      //  y0r+=setDifference*dir0;

      //  if (((y0r > ymax4 && y0r <= ymax4+setDifference) || (y0r <= setDifference && ymax4 >= 255-setDifference)) && dir0 == 1){
      //    dir0 = -1;
      //    y0r=ymax4-(y0r-ymax4);
      //  }

      //  else if (((y0r < ymin4 && y0r >= ymin4-setDifference) || (y0r >= 255-setDifference && ymin4 <= setDifference)) && dir0 == -1){ 
      //    dir0 = 1;
      //    y0r=ymin4+(ymin4-y0r);
      //  }
       }
       handleGlitter();
       FastLED.show();
       brighlu=0;
       satlu=0;
   }
}

void rainbow_6(void){
if (millis() - previousMillis1 >= changeSpeed*m20delay) {
  previousMillis1 = millis();
  if (varON == 0){
    m20delay=1;
    m20offset=1;
    yint=0;}
  else if (varON == 1){
    m20delay=1;
    m20offset=1;
    y0rCounter++;
      if (y0rCounter > 4){
        yint++;
        y0rCounter=0;
          if (yint > 10*colorlength-1){
          yint=0;}
      }
     yintm=yint;   
  }
  else if (varON == 2){
    m20delay=15;
    m20offset=25;
    yint=0;
  }

  for (int k=0; k<10; k++){
    colour[k]=colour[k]+=m20offset;
  } 
  colourlu=0;

  for (int i = 0; i < 10*colorlength; i+=colorlength){
    for (int j = 0; j < colorlength; j++){
      blockArray[i+j]=colour[colourlu];
    }
    colourlu++;
  }
}  

if (millis() - previousMillis2 >= FPS) { 
previousMillis2 = millis();  
    
   for(int i = 0; i < NUM_LEDS; i++ ){
   leds[i] = CHSV((blockArray[yint]+yvarb[varlu]),satval[satlu],brigh[brighlu]);
   yint++;
   if (yint > 10*colorlength-1){
    yint=0;  
   }
    
   brighlu++;
   if (brighlu >= numbrigh){brighlu = 0;}
   
   satlu++;
   if (satlu >= numsat){satlu = 0;}

   varlu++;
   if (varlu >= 16){varlu = 0;}   
   }
   
   handleGlitter();
   FastLED.show();
   brighlu=0;
   satlu=0;
   varlu=0;

if (varON == 0 || varON == 2){
  yint=0;
}
else if (varON == 1){
  yint=yintm;
}
}
}

void pers_block(void){
if (millis() - previousMillis1 >= modeDelay) {
  previousMillis1 = millis();

  if (varON == 0){
    yint=0; 
    modeDelay = 1*changeSpeed;   
  }
  else if (varON == 1){
    yint++;
    if (yint > (numcolor*colorlength-1)){
    yint=0;
    }
    yintm=yint;
    modeDelay = 1*changeSpeed;   
  }
  else if (varON == 2){
    if (millis() - previousMillis36 > INTERVAL7 && colorMode != 4) {
      
      if ((syncEsp) && (alertColor)){
        espNowMessage = true;
        EspNowMessageType = 7;
        alertColor = false;
      }; 

      modeDelay = changeSpeed/10;
      newColors++;
      
      for (int i = 0;  i < 15; i++){
        if (colour[i] != newColour[i]) { 
          changeColor = true;
          break;
        }
        else{
          changeColor = false;}
      } 
            
      if (changeColor) {
          for (int i = 0; i < 15; i++){
            if (colour[i] != newColour[i]){
              colour[i] = fadeFnc(colour[i], newColour[i]); 
            }
          }      
      }
        else if ((!changeColor) && (!inSync)){
          oldArrayn = arrayn;
          arrayn = random(arrayCount);
          updateOled(24, 40, &oldArrayn);
          selectcolorArray();
          alertColor = true;
          INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
          updateOledFloat(88, 0, &INTERVAL7, 0); 
          previousMillis36 = millis();
          T=0;        
        }
      }
    else if (colorMode == 4){
      changePColors();
      modeDelay = 3*changeSpeed;    
    }
  }

  if (newColors >= 1){
  colourlu=0;

  for (int i = 0; i < (numcolor*colorlength); i+=colorlength){
    for (int j = 0; j < colorlength; j++){
      blockArray[i+j]=colour[colourlu];
    }
    colourlu++;
  }
  newColors=0;
  }
}  

if (millis() - previousMillis2 >= FPS) { 
previousMillis2 = millis();  
    
   for(int i = 0; i < NUM_LEDS; i++ ){
   leds[i] = CHSV((blockArray[yint]+yvarb[varlu]),satval[satlu],brigh[brighlu]);
   yint++;
   if (yint > (numcolor*colorlength-1)){
    yint=0;   
   }
    
   brighlu++;
   if (brighlu >= numbrigh){brighlu = 0;}
   
   satlu++;
   if (satlu >= numsat){satlu = 0;}      

   varlu++;
   if (varlu >= 16){varlu = 0;}

   }

   handleGlitter();
   FastLED.show();
   brighlu=0;
   satlu=0;
   varlu=0;
   if (varON == 0 || varON == 2){
     yint=0;
   }
   else if (varON == 1){
     yint=yintm;
}
}
}

void xmas_string(void){  
if (millis() - previousMillis1 >= changeSpeed) {
  previousMillis1 = millis();
  ysr++;
  if (ysr > numAmax){
    ysr=0;
  }
  y0r=ysr;
}

if (millis() - previousMillis2 >= FPS) { 
previousMillis2 = millis();  
    
   for(int i = 0; i < NUM_LEDS; i++ ){
   leds[i] = CHSV(longxArray[y0r]+yvar[varlu],satval[satlu],brigh[brighlu]);
    
    if (i % setDifference == 0){
          y0r++;
    }

   if (y0r > numAmax){
   y0r=0;
   }
   
   brighlu++;
   if (brighlu >= numbrigh){brighlu = 0;}
   
   varlu++;
   if (varlu >= 10){varlu =0;}

   satlu++;
   if (satlu >= numsat){satlu = 0;}  
   }

   handleGlitter();
   FastLED.show();
   brighlu=0;
   y0r=ysr; 
   varlu=0;
   satlu=0;
   }
}

void xmas_singles(void){
if (millis() - previousMillis1 >= changeSpeed) {
  previousMillis1 = millis();

   for(int i = 0; i < 10; i++ ){
   colour[i]=colour[i]+=1;
   if (colour[i] > numAmax){
   colour[i]=0;};
    }
   }

if (millis() - previousMillis2 >= FPS) { 
previousMillis2 = millis();  
    
   for(int i = 0; i < NUM_LEDS; i++ ){
   leds[i] = CHSV(longxArray[colour[colourlu]],satval[satlu],brigh[brighlu]);
   
   brighlu++;
   if (brighlu >= numbrigh){brighlu = 0;}
   
   colourlu++;
   if (colourlu > 9){colourlu = 0;}

   satlu++;
   if (satlu >= numsat){satlu = 0;}   
   }

   handleGlitter();
   FastLED.show();
   brighlu=0;
   colourlu=0;  
   satlu=0;
   }
}  

void xmas_solid(void){
if (millis() - previousMillis1 >= changeSpeed/speedFact) {
  previousMillis1 = millis();
  ysr+=1*dir1;
  
  if ((ysr < ymaxrood) || (ysr > ymingroen-10 && ysr < ymaxgroen) || (ysr > yminblauw-10 && ysr < ymaxblauw) || (ysr > yminrood-5)){
    speedFact=offdis;
  }
  else {
    speedFact=1;
  }
  fillColourArray(colour, ysr, yvarg, diff);
}
    
if (millis() - previousMillis2 >= FPS) { 
  previousMillis2 = millis();  
  fillNUM_LEDS1(colour, NUM_LEDS);       
}
}

void demo100(void){
if (millis() - previousMillis1 >= changeSpeed) {
  previousMillis1 = millis();
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, S, BRIGH);
    dothue += 32;
  }
  FastLED.show(); 
}
}

void rainbow_3(void){
    if (millis() - previousMillis1 >= changeSpeed) {
      previousMillis1 = millis();
    
       for(int i = 0; i < 10; i++ ){
       colour[i] = colour[i]+=random(0,setDifference)*dirArray[i]; 
       
       if (((colour[i] > ymax2 && colour[i] <= ymax2+setDifference) || (colour[i] <= setDifference && ymax2 >= 255-setDifference))  && dirArray[i] == 1){
         dirArray[i] = -1;
       }
       else if (((colour[i] < ymin2 && colour[i] >= ymin2-setDifference) || (colour[i] >= 255-setDifference && ymin2 <= setDifference)) && dirArray[i] == -1){ 
         dirArray[i] = 1;
       } 
       }
    }
    
    if (millis() - previousMillis2 >= FPS) { 
    previousMillis2 = millis();  
    fillNUM_LEDS1(colour, NUM_LEDS);   
   }
}

void palettes(void){
if (millis() - previousMillis1 >= changeSpeed) {
  previousMillis1 = millis();  
  y0r++;
  y01m=y0r;
}

if (millis() - previousMillis36 > INTERVAL7 && varON == 2 && (!inSync)) {
  gCurrentPaletteNumber = random(gGradientPaletteCount);
  gTargetPalette = gGradientPalettes[gCurrentPaletteNumber];
  if (syncEsp){espNowMessage = true;   EspNowMessageType = 8;  };
  INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
  updateOledFloat(88, 0, &INTERVAL7, 0);
  previousMillis36 = millis(); 
  T=0;
}
 
if (millis() - previousMillis2 >= FPS) { 
previousMillis2 = millis(); 

    if (varON == 2){
    nblendPaletteTowardPalette( gCurrentPalette, gTargetPalette, 16);
    }
    else {
    nblendPaletteTowardPalette( gCurrentPalette, gTargetPalette, 96); 
    }

   for( int i = 0; i < NUM_LEDS; i++) {
      leds[i] = ColorFromPalette(gCurrentPalette, y0r, brigh[brighlu], LINEARBLEND);
      y0r+=setDifference;
      brighlu++;
      if (brighlu >= numbrigh){brighlu = 0;}
   }
   handleGlitter();
   FastLED.show();
   brighlu=0; 
   y0r=y01m;  
}
}

void palettes_2(void){
if (millis() - previousMillis1 >= changeSpeed) {
  previousMillis1 = millis();  
  y0r++;
  y01m=y0r;
}

if (millis() - previousMillis36 > INTERVAL7) {
  gCurrentPaletteNumber = random(gGradientPaletteCount);
  gTargetPalette = gGradientPalettes[gCurrentPaletteNumber];
  INTERVAL7=interval9/7*timeArray2[random(0,6)]*timefactor3;
  updateOledFloat(88, 0, &INTERVAL7, 0);
  previousMillis36 = millis(); 
  T=0;
}
 
if (millis() - previousMillis2 >= FPS) { 
previousMillis2 = millis(); 

  nblendPaletteTowardPalette( gCurrentPalette, gTargetPalette, 32);

  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(gCurrentPalette, y0r, brigh[brighlu], LINEARBLEND);
    y0r+=setDifference;
    brighlu++;
    if (brighlu >= numbrigh){brighlu = 0;}
  }
  handleGlitter();
  FastLED.show();
  brighlu=0; 
  y0r=y01m;  
}
}

void sparklingR(void){

if (millis() - previousMillis38 >= 500){    
  previousMillis38 = millis();
  if (varON == 1){
    fillArrayRainbow(2);
  }
  else {
    yval1+=1*dir1;

    fillArrayGradient(2, yval1, setDifference);

    if (yval1 == ymax4-1 && dir1 == 1){
     dir1 = -1;
     rn15 = random(65536)/2;
     }
    else if (yval1 == ymin4 && dir1 == -1){
     dir1 = 1;
     rn15 = random(65536)/2;
     }
    }
}

if (readyToChange){
  rn6=random(0,6);  
    if (rn6==0){
      variant=0;
      offmin=13*cfactor3;
      offmax=13*cfactor3;
      slingerSpeed=changeSpeed/cfactor3;
      }
    else if (rn6==1){
      variant=1;   
      offmax=-1;
      offmin=(30*cfactor3)+10; 
      slingerSpeed=45/cfactor3;   
      }
    else if (rn6==2){
      variant=2;
      offmin=-1;
      offmax=25*cfactor3;
      slingerSpeed=changeSpeed/cfactor3;
      }
    else if (rn6==3){
      variant=3;
      offmin=13*cfactor3;
      offmax=13*cfactor3;
      slingerSpeed=changeSpeed/cfactor3;
      }
    else if (rn6==4){
      variant=4;
      offmax=-1;
      offmin=(30*cfactor3)+10;; 
      slingerSpeed=45/cfactor3;
      }
    else if (rn6==5){
      variant=5;
      offmin=-1;
      offmax=25*cfactor3;
      slingerSpeed=changeSpeed/cfactor3;
      }
  if (tower){
    slingerSpeed=45/cfactor3;    
  }
  readyToChange = false; 
}   
  
if ((variant == 0 || variant == 1 || variant == 2) && (!readyToChange)){
    void ();{
    if (millis() - previousMillis36 >= INTERVAL7){ 
      outOfModus = false;
      if (millis() - previousMillis37 >= (slingerSpeed+slowFactor)){
        previousMillis37 = millis();
        longxArray[yy]=blockArray[yy];
        yy=yy+=offdis;
        if (yy>NUM_LEDS-(15*cfactor2)){
          slowFactor+=2;
          if (variant == 1){
          offmin-=2;
          }
        }
        if (yy>NUM_LEDS-1){ 
        yy=0;
        slowFactor=0;
        evenOddCounter++;
        INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
        outOfModus = true;
        updateOledFloat(88, 0, &INTERVAL7, 0); 
        previousMillis36 = millis();
        T=0;
        readyToChange = true;
        forcedColourChange = true;
        num15=0;
        }
        }
        }
    } 

    if (millis() - previousMillis36 >= INTERVAL7 && ((variant == 0 && yy > 0 && yy < NUM_LEDS-1) || (variant == 1 && yy > 1+cfactor3) || (variant == 2 && yy < NUM_LEDS-(1+cfactor3)))){
        if (millis() - previousMillis35 >= sparkSpeed+slowFactor) {        
        previousMillis35 = millis();

        for (int s=0; s<numsparks; s++){
          longxArray[rr[s]]=blockArray[rr[s]]; 
          longxArray[pos[s]]=blockArray[pos[s]]+random(80,120);           

        rr[s]=pos[s];

        pos[s]=random(yy-offmin, yy+offmax);
          while (pos[s] < 0 || pos[s] > NUM_LEDS-1){
            pos[s]=random(yy-offmin, yy+offmax);}
        }
    }
    }
    
    if (yy == 0 && num15 <1){
    num15++;
    for (int s=0; s<numsparks; s++){
      longxArray[rr[s]] = blockArray[rr[s]];
      rr[s]=NUM_LEDS;
      pos[s]=NUM_LEDS;
      }          
   }
   }
else if ((variant==3 || variant ==4 || variant ==5) && (!readyToChange)){
     if (millis() - previousMillis36 >= INTERVAL7){ 
       outOfModus = false;
        if (millis() - previousMillis37 >= (slingerSpeed+slowFactor)){ // 200 is slingerSpeed
          previousMillis37 = millis();
          longxArray[hh]=blockArray[hh];
          hh=hh-=offdis; 
          if (hh < (15*cfactor2)){
            slowFactor+=2;
            if (variant == 4){
            offmin-=2;
            }
          }
          if (hh<0){
          hh=NUM_LEDS;
          slowFactor=0;
          evenOddCounter++;
          INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
          outOfModus = true;
          updateOledFloat(88, 0, &INTERVAL7, 0); 
          T=0;
          readyToChange = true;
          forcedColourChange = true;
          num15=0;
          previousMillis36 = millis();
          }
          }
    }

    if (millis() - previousMillis36 >= INTERVAL7 && ((variant == 3&& hh > 0 && hh < NUM_LEDS-1) || (variant == 4 && hh < NUM_LEDS-(1+cfactor3)) || (variant == 5 && hh > 1+cfactor3))) {
        if (millis() - previousMillis35 >= sparkSpeed+slowFactor) {
        previousMillis35 = millis();

        for (int s=0; s<numsparks; s++){   
        longxArray[rr[s]]=blockArray[rr[s]];
        longxArray[pos[s]]=blockArray[pos[s]]+random(80,120);
    
        rr[s]=pos[s];
        
        pos[s]=random(hh-offmax, hh+offmin);
          while (pos[s] < 0 || pos[s] > NUM_LEDS-1){
            pos[s]=random(hh-offmax, hh+offmin);}
        } 
    }
    }
    if (hh == NUM_LEDS && num15 <2){
        num15++;
        for (int s=0; s<numsparks; s++){
        longxArray[rr[s]] = blockArray[rr[s]];
        rr[s]=NUM_LEDS;
        pos[s]=NUM_LEDS;  
        }   
    }
    }

    if (millis() - previousMillis2 >= FPS) { 
    previousMillis2 = millis();  

    for(int i = 0; i < NUM_LEDS; i++ ){
      for (int j = 0; j < numsparks; j++ ){
        if (i == pos[j]){
            leds[i] = CHSV(longxArray[i],qadd8(S,SF),qadd8(BRIGH,BrF));
            break;      
        }
        else{
            leds[i] = CHSV((longxArray[i]+yvar[varlu]+diff[difflu]),satval[satlu],brigh[brighlu]);   
        }
      }
    
    brighlu++;
    if (brighlu >= numbrigh){brighlu = 0;}

    satlu++;
    if (satlu >= numsat){satlu = 0;}

    varlu++;
    if (varlu >= 10){varlu = 0;}

    difflu++;
    if (difflu >= 10){difflu = 0;}
    }
    
    handleGlitter(); 
    FastLED.show();
    brighlu=0; 
    satlu=0;  
    varlu=0;
    difflu=0;
  }
} 

void RGBmode(void){
if (millis() - previousMillis1 >= changeSpeed) {
  previousMillis1 = millis();
  fill_solid( leds, NUM_LEDS, CRGB(Red,Green,Blue));
  FastLED.show();

  if (loadHSV == true && updateHSV == true){
  CRGB rgb(Red,Green,Blue);
  CHSV hsv;
  hsv = rgb2hsv_approximate( rgb );
  byte HUE = hsv.h;
  byte SAT = hsv.s;
  byte VAL = hsv.v;
  
  if (updateHSV == true){
    for (int i = 0; i < NUM_LEDS; i+=5){
    leds[i] = CHSV(HUE, SAT, VAL);  
    //leds[i] = hsv;  
    }
  }
  FastLED.show();
//  Serial.print(hsv.h);
//  Serial.print(", "); Serial.print(hsv.s);
//  Serial.print(", "); Serial.println(hsv.v);
    notifyClientsSingleObjectByte("HHHH", HUE);
    notifyClientsSingleObjectByte("HSSS", SAT);
    notifyClientsSingleObjectByte("HVVV", VAL);
  // mergedString = "HHHH"+String(HUE); ws.textAll(mergedString);  
  // mergedString = "HSSS"+String(SAT); ws.textAll(mergedString);  
  // mergedString = "HVVV"+String(VAL); ws.textAll(mergedString);  
//  mergedString = "G"+"THSV"+String(loadHSV); ws.textAll(mergedString);  
  loadHSV = false;  
  }
  
}
}

void handleGlitter(){ // HANDLE GLITTER FUNCTION
//  if ((glitterON) && (effect_function != *meteor)){
  if (glitterON){  
    rn13=beatsin88(150, 1000, 30000);
  
    if (millis() - previousMillis52 >= 150) {
        previousMillis52 = millis();
        rn16 = random(65536);
        if (rn16 < rn13){
          ig=random(NUM_LEDS);
          leds[ig] = CHSV(60, 0, 255); // qadd8(BRIGH,BrF)
         }
     }
  }
//  leds[0] = CRGB::Black;  
  return;
}
