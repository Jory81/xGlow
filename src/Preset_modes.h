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
  } // do nothing
  else{
   for(int i = 0; i < 10; i++ ){
   colour[i]=colour[i]+=setDifference*dir1;     
   }
  }
}

if (millis() - previousMillis36 > INTERVAL7 && varON == 2) {
  if (millis() - previousMillis37 >= FPS) {
  previousMillis37 = millis(); 

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
    else if (!changeColor){
      byte oldArrayn = arrayn;
      arrayn = random(arrayCount);
      updateOled(24, 40, &oldArrayn);
      selectcolorArray();
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
   //leds[i] = CHSV(colour[colourlu]+yvar[varlu],S,brigh[brighlu]);
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

void rainbow_2(void){ 
if (millis() - previousMillis1 >= changeSpeed) {
  previousMillis1 = millis();

   for(int i = 0; i < 10; i++ ){
   colour[i]=colour[i]+=random(0,setDifference)*dir1;  
   }
}

if (millis() - previousMillis2 >= FPS) { 
previousMillis2 = millis();  
fillNUM_LEDS1(colour, NUM_LEDS);
   }
}

void s7_strings(void){   
for (int k=0; k<numsparks; k++){
if (millis() - previousMillisLN[0] >= INTERVAL7 && ((numsparks == 1) || (numsparks > 1))){       
if (millis() - previousMillisAM[k] >= (INTERVALf[k]*timeSpeed[k])) {
    previousMillisAM[k] = millis();
    longxArray[i[k]]=yMA[k]+random(-ydiff,ydiff);
    if (varON == 2 && i[k] > 0 && colorMode !=4){
      longxArray[i[k]-1]=z[k];
    }
    i[k]=i[k]-1;
    if (i[k]<0){
      i[k]=NUM_LEDS-1;
      yMA[k] = changeColourFcn(colorMode, yMA[k], 0, 255); 
      if (varON == 2 && colorMode !=4 ){
         if ((yMA[k] >=230 && yMA[k] <= 255) || (yMA[k] >= 0 && yMA[k] <= 79)){
            z[k]=zr[0];
         }
         else if (yMA[k] >=130 && yMA[k] < 168){
            z[k]=zr[1];
         }
         else if (yMA[k] >= 168 && yMA[k] < 205){
            z[k]=zr[1];
         }
         else if (yMA[k] >=80 && yMA[k] < 130){
            z[k]=zr[2];
         }
         else if (yMA[k] >=205 && yMA[k] < 230){
            z[k]=zr[3];
         }
      }
      if (millis() - previousMillis36 > INTERVAL9 && colorMode == 4 && varON == 2) {
      arrayn = random(arrayCount);
      updateOled(24, 40, &arrayn);
      selectcolorArray();
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
            ydiff=5;}
            else if (yval1 == 9 || yval1 == 217 || yval1 == 243){
            ydiff=10;}
            else if (yval1 == 188 || yval1 == 226 || yval1 == 168){
            ydiff=20;}
            else {
            ydiff=10;}}
            else if (varON == 1){
            ydiff=setDifference;}   
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
    ydiff=setDifference;
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

void snow_flakes(void){
if (millis() - previousMillis11 >= interval8) {
    previousMillis11 = millis();
    sF= sF+0.0675;
      if (sF >= 2.0){
        sF=1.00;
    }
}  

if (millis() - previousMillis6 >= INTERVAL7){
      
    if (colorMode == 0){
      yval1=yval;
      for (int p=0; p<numsparks; p++){
      z[p]=yval;}
      }
    else if (colorMode == 5){
      yval1=yval;
      for (int p=0; p<numsparks; p++){
        z[p]=z5;
        }
     }
    else {  
    yval1 = changeColourFcn2(colorMode, yval1, yval1, 50, 200);
    }
  
  {if ((varON == 0 || varON == 1) && (colorMode == 1 || colorMode == 2 || colorMode == 3 || colorMode == 4 )){ // colorMode == 2 || colorMode == 3 || colorMode == 4){
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
  }
     
   {if (varON == 0){
    if (yval1 == 11 || yval1 == 81 || yval1 == 16 || yval1 == 117 || yval1 == 139 || yval1 == 175 || yval1 == 193 || yval1 == 244){
    ydiff=5;}
    else if (yval1 == 9 || yval1 == 217 || yval1 == 243){
    ydiff=10;}
    else if (yval1 == 188 || yval1 == 226 || yval1 == 168){
    ydiff=20;}
    else {
    ydiff=10;}
    }
   else if (varON == 1 || varON == 2){
    ydiff=setDifference;
    }
   }
     
    updateOled(102, 56, &yval1);          
    INTERVAL7=interval7*timeArray2[random(0,6)]*timefactor3;
    //Serial.println("INT7"); Serial.println(INTERVAL7);
    updateOledFloat(88, 0, &INTERVAL7, 0); 
    T=0;
    previousMillis6 = millis();
}

for (int k=0 ; k<numsparks; k++){
if (millis() - previousMillisLN[k] >= rtAM[k]/df){
  if ((millis() - previousMillisAM[k] >= (INTERVALf[k]*timeSpeed[k]*interRun[k])) && (sF <= sFtab[k])) {
    previousMillisAM[k] = millis();
    
    if (varON == 2){
      z[k] = random(256);
      while (z[k] >= yval1 - 30 && z[k] <= yval1 + 30){
        z[k] = random(256);}
    }

    blockArray[a[k]]=yval1+random(-ydiff,ydiff);
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
          if (i[k] == 80*cfactor2 || i[k] == 60*cfactor2 || i[k] == 40*cfactor2 || i[k] == 20*cfactor2){
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
        blockArray[i[k]+offdis]=yval1+random(-ydiff,ydiff);
        blockArray[i[k]+offdis+1]=yval1+random(-ydiff,ydiff);
        i[k]=random(NUM_LEDS-offdis, NUM_LEDS);
      }
      else if ((tower) && (Bees)){
        if (i[k]<0){
        blockArray[0]=yval1+random(-ydiff,ydiff);  
        i[k]=NUM_LEDS+i[k];   
        }
        else if (i[k] >= NUM_LEDS){
        i[k]=i[k]-NUM_LEDS;  
        }
      }
      else {
        i[k]=NUM_LEDS-1;
        blockArray[0]=yval1+random(-ydiff,ydiff);
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
      if (num6 == xnum){
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

   for(int i = 0; i < NUM_LEDS; i++ ){
//   if (longxArray[i] == z[0] && varON != 2){
   if (blockArray[i] == z[0] || blockArray[i] == z[1] || blockArray[i] == z[2] || blockArray[i] == z[3] || blockArray[i] == z[4] || blockArray[i] == z[5] || blockArray[i] == z[6] || blockArray[i] == z[7] || blockArray[i] == z[8] || blockArray[i] == z[9] || blockArray[i] == z[10] || blockArray[i] == z[11] || blockArray[i] == z[12] || blockArray[i] == z[13] || blockArray[i] == z[14] || blockArray[i] == z[15] || blockArray[i] == z[16] || blockArray[i] == z[17] || blockArray[i] == z[18] || blockArray[i] == z[19] || blockArray[i] == z[20]){
   leds[i] = CHSV(blockArray[i],qadd8(S,SF),qadd8(BRIGH,BrF));    
   }
   else {
   leds[i] = CHSV(blockArray[i],satval[satlu],brigh[brighlu]);
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
    y0r++;
    hue=y0r;
     for (int i = 0; i < NUM_LEDS; i++){
     hue++;
     longxArray[i]=hue;    
     }
  }

for (int k=0 ; k<numsparks; k++){
if (millis() - previousMillisLN[k] >= rtAM[k]/df){
  if ((millis() - previousMillisAM[k] >= (INTERVALf[k]*timeSpeed[k]*interRun[k])) && (sF <= sFtab[k])) {
    previousMillisAM[k] = millis();
    if (varON == 0 || varON == 1){
        z[k] = blockArray[i[k]]+=90;
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
      if (i[k] == 80*cfactor2 || i[k] == 60*cfactor2 || i[k] == 40*cfactor2 || i[k] == 20*cfactor2){
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
        i[k]=NUM_LEDS-1;
      }
    interRun[k]=1.1;
    blockArray[0]=longxArray[a[k]]; 
    previousMillisLN[k] = millis();
    if ((tower) && (Bees)){
    rtAM[k] = 80;  
    }
    else {
    rtAM[k]= random(65536);
    }
    if (k == 0){
      num6=num6+1;
      if (num6 == xnum){
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

   for(int i = 0; i < NUM_LEDS; i++ ){
//   if (longxArray[i] == z[0] && varON != 2){
   if (blockArray[i] == z[0] || blockArray[i] == z[1] || blockArray[i] == z[2] || blockArray[i] == z[3] || blockArray[i] == z[4] || blockArray[i] == z[5] || blockArray[i] == z[6] || blockArray[i] == z[7] || blockArray[i] == z[8] || blockArray[i] == z[9] || blockArray[i] == z[10] || blockArray[i] == z[11] || blockArray[i] == z[12] || blockArray[i] == z[13] || blockArray[i] == z[14] || blockArray[i] == z[15] || blockArray[i] == z[16] || blockArray[i] == z[17] || blockArray[i] == z[18] || blockArray[i] == z[19] || blockArray[i] == z[20]){
   leds[i] = CHSV(blockArray[i],qadd8(S,SF),qadd8(BRIGH,BrF));    
   }
   else {
   leds[i] = CHSV(blockArray[i],satval[satlu],brigh[brighlu]);
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
  rn6=random(0,6);
    if (rn6==0){
      variant=0;
      offmin=13*cfactor2;
      offmax=13*cfactor2;
      slingerSpeed=changeSpeed/cfactor2;
      }
    else if (rn6==1){
      variant=1;   
      offmax=-1;
      offmin=(30*cfactor2)+10; 
      slingerSpeed=45/cfactor2;   
      }
    else if (rn6==2){
      variant=2;
      offmin=-1;
      offmax=25*cfactor2;
      slingerSpeed=changeSpeed/cfactor2;
      }
    else if (rn6==3){
      variant=3;
      offmin=13*cfactor2;
      offmax=13*cfactor2;
      slingerSpeed=changeSpeed/cfactor2;
      }
    else if (rn6==4){
      variant=4;
      offmax=-1;
      offmin=(30*cfactor2)+10;; 
      slingerSpeed=45/cfactor2;
      }
    else if (rn6==5){
      variant=5;
      offmin=-1;
      offmax=25*cfactor2;
      slingerSpeed=changeSpeed/cfactor2;
      }
  if (tower){
    slingerSpeed=45/cfactor2;    
  }
  readyToChange = false; 
}   
  
if ((variant == 0 || variant == 1 || variant == 2) && (!readyToChange)){
    void ();{
    if (millis() - previousMillis36 >= INTERVAL7){ 
      num50=1;
      if (millis() - previousMillis37 >= (slingerSpeed+slowFactor)){
        previousMillis37 = millis();
        //longxArray[yy]=yval1+random(-7,7);
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
        slowFactor=0;
        evenOddCounter++;

        if (variant == 0){
          arraypos = 0;
          fadeIsActive = true;
          yold1=yold;
          for (int j = 0; j < NUM_LEDS; j++){
            if (longxArray[j] == yold){
              sparkarray[arraypos]=j;
              arraypos++;  
            }
          }
        } 
        yold=yval1;
        yval1 = changeColourFcn2(colorMode, yval1, yold, 40, 210);               
        updateOled(44, 40, &yold);
        updateOled(102, 56, &yval1); 
        INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
        updateOledFloat(88, 0, &INTERVAL7, 0); 
        previousMillis36 = millis();
        T=0;
        readyToChange = true;
        num50=0;
        num15=0;
        }
        }
        }
    } 

    if (millis() - previousMillis36 >= INTERVAL7 && ((variant == 0 && yy > 0 && yy < NUM_LEDS-1) || (variant == 1 && yy > 1+cfactor2) || (variant == 2 && yy < NUM_LEDS-(1+cfactor2)))){
        if (millis() - previousMillis35 >= sparkSpeed+slowFactor) {        
        previousMillis35 = millis();

        for (int s=0; s<numsparks; s++){
        if (rr[s] > yy){
          //longxArray[rr[s]] = yold+random(-7,7);  
          longxArray[rr[s]] = yold;
        }
        else if (rr[s] <= yy){
         //longxArray[rr[s]] = yval1+random(-7,7);
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
    
    if (yy == 0 && num15 <1){
    num15++;
    for (int s=0; s<numsparks; s++){
      //longxArray[rr[s]] = yold+random(-7,7);  
      longxArray[rr[s]] = yold;
      rr[s]=NUM_LEDS;
      pos[s]=NUM_LEDS;
      }          
   }
   }
else if ((variant==3 || variant ==4 || variant ==5) && (!readyToChange)){
     if (millis() - previousMillis36 >= INTERVAL7){ 
      num50=1; 
        if (millis() - previousMillis37 >= (slingerSpeed+slowFactor)){ // 200 is slingerSpeed
          previousMillis37 = millis();
          //longxArray[hh]=yval1+random(-7,7);
          longxArray[hh]=yval1;
          hh=hh-=offdis; 
          if (hh < (15*cfactor2)){
            slowFactor+=2;
            if (variant == 4){
            offmin-=2;
            }
          }
          if (hh<0){
          hh=NUM_LEDS-1;
          slowFactor=0;
          evenOddCounter++;
          if (variant == 3){
            fadeIsActive = true;
            arraypos = 0;
            yold1=yold;
            for (int j = 0; j < NUM_LEDS; j++){
              if (longxArray[j] == yold){
                sparkarray[arraypos]=j;
                arraypos++;  
                }
            }
          }          
          yold=yval1;
          yval1 = changeColourFcn2(colorMode, yval1, yold, 40, 210);  
          updateOled(44, 40, &yold);
          updateOled(102, 56, &yval1);   
          INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
          updateOledFloat(88, 0, &INTERVAL7, 0); 
          T=0;
          readyToChange = true;
          num15=0;
          num50=0;
          previousMillis36 = millis();
          }
          }
    }

    if (millis() - previousMillis36 >= INTERVAL7 && ((variant == 3&& hh > 0 && hh < NUM_LEDS-1) || (variant == 4 && hh < NUM_LEDS-(1+cfactor2)) || (variant == 5 && hh > 1+cfactor2))) {
        if (millis() - previousMillis35 >= sparkSpeed+slowFactor) {
        previousMillis35 = millis();

        for (int s=0; s<numsparks; s++){   
        if (rr[s] < hh){
          //longxArray[rr[s]]=yold+random(-7,7);  
          longxArray[rr[s]]=yold; 
        }
        else if (rr[s] >= hh){
          //longxArray[rr[s]]=yval1+random(-7,7);
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
    if (hh == NUM_LEDS-1 && num15 <2){
        num15++;
        for (int s=0; s<numsparks; s++){
         //longxArray[rr[s]] = yold+random(-7,7);
         longxArray[rr[s]] = yold;
        rr[s]=NUM_LEDS;
        pos[s]=NUM_LEDS;  
        }   
    }
    }
  
  if (num50 == 0){  
    if (millis() - previousMillis2 >= FPS) { 
    previousMillis2 = millis();  
      if (fadeIsActive){
        if (yold1 == yold) {
            fadeIsActive = false;
        }
        yold1 = fadeFnc(yold1, yold);    
        for (int l = 0; l < arraypos; l++){
        longxArray[sparkarray[l]] = yold1;
        }            
       }

       fillColourArray(colourR, yold, yvar, diff);  
        
       for(int i = 0; i < NUM_LEDS; i++ ){
         if ((fadeIsActive) && longxArray[i] == yold1){
         leds[i] = CHSV((longxArray[i]+yvar[varlu]+diff[difflu]),satval[satlu],brigh[brighlu]);
         }
         else {
         leds[i] = CHSV(colourR[colourlu],satval[satlu],brigh[brighlu]);
         }
        
       brighlu++;
       if (brighlu >= numbrigh){brighlu = 0;}
       
       colourlu++;
       if (colourlu > 9){colourlu = 0;}

       satlu++;
       if (satlu >= numsat){satlu=0;}

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
else if (num50 != 0){
    if (millis() - previousMillis2 >= FPS) { 
    previousMillis2 = millis();  

         for(int i = 0; i < NUM_LEDS; i++ ){
         if (i == pos[0] || i == pos[1] || i == pos[2] || i == pos[3] || i == pos[4] || i == pos[5] || i == pos[6] || i == pos[7] || i == pos[8] || i == pos[9] || i == pos[10] || i == pos[11] || i == pos[12]  || i == pos[13] ||  i == pos[14] || i == pos[15] || i == pos[16] || i == pos[17] || i == pos[18] || i == pos[19] || i == pos[20] || i == pos[21] || i == pos[22] || i == pos[23] || i == pos[24] || i == pos[25] || i == pos[26] || i == pos[27]  || i == pos[28] || i == pos[29]){
         leds[i] = CHSV(longxArray[i],qadd8(S,SF),qadd8(BRIGH,BrF));    
         }
         else {         
        // leds[i] = CHSV(longxArray[i],satval[satlu],brigh[brighlu]); // adjusted varlu + difflu
         leds[i] = CHSV((longxArray[i]+yvar[varlu]+diff[difflu]),satval[satlu],brigh[brighlu]); // adjusted varlu + difflu
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
}

void snow_storm(void){
     if (millis() - previousMillis36 >= INTERVAL7){
      if (fadeIsActive){
        if (varON == 2){
          if (millis() - previousMillis38 >= 2*changeSpeed) {
          previousMillis38 = millis();
            if (yold == yval1 ) {
                  fadeIsActive = false;
                  fillLongxArray(yold);
            }
            yold = fadeFnc(yold, yval1);    
          }
        }
        else if (varON != 2){
          fadeIsActive = false;
        }
      }
      else if (!fadeIsActive){
      num50=1;
        for (int s=0; s < numsparks; s++){
          if (millis() - previousMillisLN[s] >= changeSpeedMA[s] && flakeCounter >= flakeListMode7[s] && flakeCounter <= cn) {
            previousMillisLN[s] = millis();
            num17[s]-=offdis;}
            if (num17[s] < rn[s] && flakeCounter <= cn){
              num17[s]=NUM_LEDS; // adjusted
              flakeCounter++;
              if (flakeCounter <= 10 && s == 0){
                rn[0]= random(55,75);}
              else{
                rn[s]= random(randomNumberMinimum[s], randomNumberMaximum[s]);             
              }
              num23[s]=0;
              changeSpeedMA[s]=changeSpeed*timeArray[random(0,5)];
            }
            if (flakeCounter > cn && num26[s] < 1){  // CHANGED_HERE
              num26[s]=num26[s]+1;   
              num17[s]= NUM_LEDS; // adjusted
              num23[s]=0;
            }
          }

        if (millis() - previousMillis37 >= changeSpeed/cfactor2 && flakeCounter > cn-(3*cfactor2)){
          previousMillis37 = millis();
          //longxArray[hh]=yval1+random(-setDifference,setDifference);
          longxArray[hh]=yval1;;
          if (hh < NUM_LEDS-1){
          //longxArray[hh+1]=yval1+random(-setDifference,setDifference);
          longxArray[hh+1]=yval1;
          }
          hh=hh-1;
          if (hh<0){
              hh=NUM_LEDS-1;
              evenOddCounter++; 
              yold=yval1;
              yval1 = changeColourFcn2(colorMode, yval1, yold, 40, 210);         
              updateOled(44, 40, &yold);
              updateOled(102, 56, &yval1);                
              INTERVAL7=interval7*timeArray2[random(0,6)]*timefactor3;
              updateOledFloat(88, 0, &INTERVAL7, 0); 
              T=0;
              num50=0;
              num15=0;
              for (int s=0; s < numsparks; s++){
              num17[s]=NUM_LEDS; // adjusted
              num26[s]=0;
              rn[s]=random(randomNumberMinimum[s], randomNumberMaximum[s]);
              }
              fadeIsActive = true;
              flakeCounter=0;
                          
              if (NUM_LEDS <= 100){
              cn=random(34,60);
              }
              else if (NUM_LEDS > 100){
              cn=random(60,111);
              }                                     
              previousMillis36 = millis();
          }
     }
    }
} 
      
if (millis() - previousMillis36 >= INTERVAL7 && ((num17[0] > 0) || (hh > 0 && hh <NUM_LEDS-1))){             
    if (millis() - previousMillis35 >= sparkSpeed) { // sparkSpeed = changeSpeed/DF
    previousMillis35 = millis();

        if (hh < NUM_LEDS-1){
          if (rrhh < hh){
          //longxArray[rrhh]=yold+random(-7,7);  
          longxArray[rrhh]=yold; 
          }
          else if (rrhh >= hh){
          //longxArray[rrhh]=yval1+random(-7,7); 
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
            poshh=random(hh-offmax-(12*cfactor2), hh+offmin+(12*cfactor2));
          }       
       }

    for (int s=0; s < numsparks; s++){
        if (num17[s] < NUM_LEDS-1){  
            if (rr[s] <= hh){
            //longxArray[rr[s]]=yold+random(-7,7); 
            longxArray[rr[s]]=yold;  
            }
            else if (rr[s] > hh){
            //longxArray[rr[s]]=yval1+random(-7,7);  
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

   for (int s=0; s < numsparks; s++){    
        if (num17[s] == NUM_LEDS-1 && num23[s] < 1){  // CHANGED_HERE
        num23[s]=num23[s]+1;
        if (rr[s] < hh){
        //longxArray[rr[s]]=yold+random(-7,7);   
        longxArray[rr[s]]=yold;
        }
        else if (rr[s] >= hh){
        //longxArray[rr[s]]=yval1+random(-7,7);
        longxArray[rr[s]]=yval1;            
        }
        }
    }
       
    if (hh == NUM_LEDS-1 && num15 <1){ // CHANGED_HERE
        num15++;
        //longxArray[rrhh]=yold+random(-7,7);     // yval1 --> yold         
        longxArray[rrhh]=yold;     // yval1 --> yold            
        rrhh=NUM_LEDS-1;
        poshh=NUM_LEDS-1;
        for (int s=0; s < numsparks; s++){
          rr[s]=NUM_LEDS; // adjusted
          pos[s]=NUM_LEDS; // adjusted
        }
    }
     
  if (num50 == 0){  
    if (millis() - previousMillis2 >= FPS) { 
    previousMillis2 = millis();  
    fillColourArray(colourR, yold, yvar, diff); 
    fillNUM_LEDS1(colourR, NUM_LEDS);       
    }
  }
  else if (num50 != 0){
    if (millis() - previousMillis2 >= FPS) { 
    previousMillis2 = millis();  

       for(int i = 0; i < NUM_LEDS; i++ ){
//       if (i == poshh || i == pos[0] || i == pos[1] || i == pos[2] || i == pos[3] || i == pos[4] || i == pos[5] || i == pos[6] || i == pos[7] || i == pos[8] || i == pos[9] || i == pos[10] || i == pos[11] || i == pos[12]  || i == pos[13] ||  i == pos[14] || i == pos[15] || i == pos[16] || i == pos[17] || i == pos[18] || i == pos[19] || i == pos[20] || i == pos[21] || i == pos[22] || i == pos[23] || i == pos[24] || i == pos[25] || i == pos[26] || i == pos[27]  || i == pos[28] || i == pos[29]){
       if (longxArray[i] == yval1){
       leds[i] = CHSV(longxArray[i],qadd8(S,SF),qadd8(BRIGH,BrF));    
       }
       else {         
       // leds[i] = CHSV(longxArray[i],satval[satlu],brigh[brighlu]);  
       leds[i] = CHSV((longxArray[i]+yvar[varlu]+diff[difflu]),satval[satlu],brigh[brighlu]);
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
} 

void random_led(void){  
if (millis() - previousMillis1 >= changeSpeed){
     if (colorMode == 5){
         colourChangeDelay++;
         if (colourChangeDelay >= setDifference*cfactor2){
         yval1+=10;
         colourChangeDelay=0;}
     }
     else{
     yval1 = changeColourFcn(colorMode, yval1, 0, 255);  
     }
    
     if (colorMode == 5){
          ig3=random(NUM_LEDS);
            if (varON == 0){
            longxArray[ig3]=yval1+random(-10,10);        
            }
            else{
            leds[ig3]=CHSV((yval1+random(-10,10)), S, BRIGH);
            handleGlitter();
            if (!fadeIsActive){
            FastLED.show(); 
            }
          }
          previousMillis1 = millis();
     }
     else {
          ig3=random(NUM_LEDS);
            if (varON == 0){
            longxArray[ig3]=yval1;  
            }
            else{
            leds[ig3]=CHSV(yval1, S, BRIGH);
            handleGlitter();
            if (!fadeIsActive){
            FastLED.show(); 
            }  
          }
          previousMillis1 = millis();
      }   
}

   if (varON == 0 && millis() - previousMillis2 >= FPS){ 
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
   else if (varON == 1 && millis() - previousMillis36 > rn14){
        if (num30 < 1){
        fadeIsActive = true;
        num30++;
        }
        if (millis() - previousMillis5 > FPS){
            if (changeSpeed > 30){
            fadeOutSpeed=16;
            fadeToBlackBy(leds, 250, fadeOutSpeed);
            }
            else if (changeSpeed <= 30){
            fadeOutSpeed=35;
            fadeToBlackBy(leds, 250, fadeOutSpeed);
            }
        FastLED.show();
        previousMillis5 = millis();
        cyclesToFade++;
        }
        if (cyclesToFade > 250){
          cyclesToFade=0;
          previousMillis36 = millis();
          rn14=(random(18000, 30000)/cfactor1);
          fadeIsActive = false;
          num30=0;
        }
    }   
    else if (varON == 2 && millis() - previousMillis5 > FPS){
        fadeIsActive = true;
          if (changeSpeed > 30){  
          fadeOutSpeed=16;
          fadeToBlackBy(leds, 250, fadeOutSpeed);
          }
          else if (changeSpeed <= 30){
          fadeOutSpeed=35;
          fadeToBlackBy(leds, 250, fadeOutSpeed);
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
    else if (!changeColor){
      oldArrayn = arrayn;
      arrayn = random(arrayCount);
      updateOled(24, 40, &oldArrayn);
      selectcolorArray();
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

if (millis() - previousMillis36 > INTERVAL7 && colorMode == 4 && varON == 2) {
      arrayn = random(arrayCount);
      updateOled(24, 40, &arrayn);
      selectcolorArray();
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
      yval1+=setDifference*dir1;
      ysr=yval1;
    }

    if (millis() - previousMillis2 >= FPS) { 
      previousMillis2 = millis();  
      for(int i = 0; i < NUM_LEDS; i++ ){
      leds[i] = CHSV(ysr+yvar[varlu],satval[satlu],brigh[brighlu]);
      ysr+=offdis;
       
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
  if (millis() - previousMillis1 >= INTERVAL7){
     yx = changeColourFcn(colorMode, yx, 0, 255);
     INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
     updateOledFloat(88, 0, &INTERVAL7, 0); 
     previousMillis1 = millis();
     updateOled(102, 56, &yx);
     T=0;
  }

  if (fadeFirst == 1 && yval1 != yx){
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

void blendEffect(void){ 

if (millis() - previousMillis1 > INTERVAL7) {
  if (millis() - previousMillis36 >= FPS) {
    previousMillis36 = millis();
    if (yTrans == yval1) {
      yval1 = random(256);
      seedNumber = random(6, 18)*cfactor2;
        for (int i = 0; i < seedNumber; i++){
         seedArray[i]=random(NUM_LEDS);
        }
    }
    yTrans = fadeFnc(yTrans, yval1);   
    fillColourArray(colour, yTrans, yvar, diff);   
      if (yTrans == yval1) {
        INTERVAL7=(interval9/6)*timeArray2[random(0,6)]*timefactor3;
        updateOledFloat(88, 0, &INTERVAL7, 0); 
        previousMillis1 = millis();
        T=0;        
      }
  } 
} 

    if (millis() - previousMillis2 >= FPS) { 
          for(int i = 0; i < NUM_LEDS; i++ ){
          leds[i] = CHSV(colour[colourlu],satval[satlu],brigh[brighlu]);
            
          brighlu++;
          if (brighlu >= numbrigh){brighlu = 0;}
          
          colourlu++;
          if (colourlu > 9){colourlu = 0;}

          satlu++;
          if (satlu >= numsat){satlu = 0;}
          } 

          for (int i = 0; i < seedNumber; i++){
          leds[seedArray[i]]=CHSV(yval1,satval[satlu],brigh[brighlu]);
          }

          handleGlitter();
          FastLED.show();

          satlu=0;
          brighlu=0;
          colourlu=0;
          previousMillis2 = millis();    
    }
}

void sparkling_2(void){
if (dir == 2 && (readyToChange)){
  rn6=random(0,2);
    if (rn6==0){
      variant=0;
      offmin=13*cfactor2;
      offmax=13*cfactor2;
      slingerSpeed=changeSpeed/cfactor2;
      }
    else if (rn6==1){
      variant=3;
      offmin=13*cfactor2;
      offmax=13*cfactor2;
      slingerSpeed=changeSpeed/cfactor2;
    }
  if (tower){
    slingerSpeed=45/cfactor2;    
  }
  readyToChange = false; 
  }
else if (dir == 1 && (readyToChange)){
  variant=variant;
  readyToChange = false;
  if (tower){
    slingerSpeed=45/cfactor2;    
  }
}   
  
if (variant==0 && (!readyToChange)){
    if (millis() - previousMillis36 >= INTERVAL7){ 
      num50=1;
      if (millis() - previousMillis37 >= (slingerSpeed+slowFactor)){
        previousMillis37 = millis();
        //longxArray[yy]=yval1+random(-7,7);
        longxArray[yy]=yval1;
        yy=yy+=offdis;
        if (yy>NUM_LEDS-50){
          slowFactor+=4;
        }
        if (yy>NUM_LEDS-1){ 
            yy=0;
            slowFactor=0;
            evenOddCounter++;  
            yold=yval1;
            yval1 = changeColourFcn2(colorMode, yval1, yold, 40, 210);

            updateOled(44, 40, &yold);
            updateOled(102, 56, &yval1);       
            INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
            updateOledFloat(88, 0, &INTERVAL7, 0); 
            previousMillis36 = millis();
            T=0;
            readyToChange = true;
            num50=0;
            num15=0;
        }
       }
    }
       
    if (millis() - previousMillis36 >= INTERVAL7 && yy > 0 && yy <NUM_LEDS-1){
        if (millis() - previousMillis35 >= sparkSpeed) { // changeSpeed/DF
        previousMillis35 = millis();

        for (int s=0; s<numsparks;s++){
        if (rr[s] > yy){
        //longxArray[rr[s]]=yold+random(-7,7);  
        longxArray[rr[s]]=yold;  
        }
        else if (rr[s] <= yy){
        //longxArray[rr[s]]=yval1+random(-7,7); 
        longxArray[rr[s]]=yval1;
        }

        longxArray[pos[s]]=colour[4];
        if (numcolor > 1){longxArray[pos1[s]]=colour[0];} // leds[pos1[s]] = CHSV(colour[0],S,qadd8(BRIGH,BrF));}
        if (numcolor > 2){longxArray[pos2[s]]=colour[1];} // leds[pos2[s]] = CHSV(colour[1],S,qadd8(BRIGH,BrF));}
        if (numcolor > 3){longxArray[pos3[s]]=colour[2];} // leds[pos3[s]] = CHSV(colour[2],S,qadd8(BRIGH,BrF));}    
        if (numcolor > 4){longxArray[pos4[s]]=colour[3];} // leds[pos4[s]] = CHSV(colour[3],S,qadd8(BRIGH,BrF));}              
    
        if (numcolor == 1){
          rr[s]=pos[s];
        }
        else if (numcolor == 2){
         rr[s]=pos1[s]; 
         pos1[s]=pos[s];
        }
        else if (numcolor == 3){
         rr[s]=pos1[s]; 
         pos1[s]=pos2[s];
         pos2[s]=pos[s];
        }   
        else if (numcolor == 4){
         rr[s]=pos1[s]; 
         pos1[s]=pos2[s];
         pos2[s]=pos3[s];
         pos3[s]=pos[s];
        } 
        else if (numcolor == 5){
         rr[s]=pos1[s]; 
         pos1[s]=pos2[s];
         pos2[s]=pos3[s];
         pos3[s]=pos4[s];
         pos4[s]=pos[s];
        }                         
        
        pos[s]=random(yy-offmin, yy+offmax);
          while (pos[s] < 0 || pos[s] > NUM_LEDS-1){
            pos[s]=random(yy-offmin, yy+offmax);}
        }        
        }
    }

    if (yy == 0 && num15 <1){
        num15++;

        for (int s=0; s<numsparks;s++){
        //longxArray[rr[s]]=yold+random(-7,7);
        //longxArray[pos[s]]=yold+random(-7,7);
        longxArray[rr[s]]=yold;
        longxArray[pos[s]]=yold;

        if (numcolor > 1){longxArray[pos1[s]]=yold+random(-7,7);}  //  leds[pos1[s]] = CHSV((yold+random(-7,7)),S,BRIGH);}       
        if (numcolor > 2){longxArray[pos2[s]]=yold+random(-7,7);}  //  leds[pos2[s]] = CHSV((yold+random(-7,7)),S,BRIGH);}
        if (numcolor > 3){longxArray[pos3[s]]=yold+random(-7,7);}  //  leds[pos3[s]] = CHSV((yold+random(-7,7)),S,BRIGH);}
        if (numcolor > 4){longxArray[pos4[s]]=yold+random(-7,7);}  //  leds[pos4[s]] = CHSV((yold+random(-7,7)),S,BRIGH);}

        rr[s]=NUM_LEDS; // adjusted
        pos[s]=NUM_LEDS; // adjusted
        pos1[s]=NUM_LEDS; // adjusted
        pos2[s]=NUM_LEDS; // adjusted
        pos3[s]=NUM_LEDS; // adjusted
        pos4[s]=NUM_LEDS; // adjusted     
        }
        }
}
else if (variant==3 && (!readyToChange)){
     if (millis() - previousMillis36 >= INTERVAL7){ 
      num50=1; 
        if (millis() - previousMillis37 >= (slingerSpeed+slowFactor)){
          previousMillis37 = millis();
          //longxArray[hh]=yval1+random(-7,7);
          longxArray[hh]=yval1;
          hh=hh-=offdis;
          if (hh<50){
          slowFactor+=4;
          }  
          if (hh<0){
              hh=NUM_LEDS-1;
              slowFactor=0;
              evenOddCounter++; 
              yold=yval1;
              yval1 = changeColourFcn2(colorMode, yval1, yold, 40, 210);
              
              updateOled(44, 40, &yold);
              updateOled(102, 56, &yval1);      
              INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
              updateOledFloat(88, 0, &INTERVAL7, 0); 
              previousMillis36 = millis();
              T=0;
              readyToChange = true;
              num50=0;
              num15=0;
          }
        }
     }

    if (millis() - previousMillis36 >= INTERVAL7 && hh > 0 && hh <NUM_LEDS-1){
        if (millis() - previousMillis35 >= sparkSpeed) { // sparkSpeed = changeSpeed/DF
        previousMillis35 = millis();

        for (int s=0; s<numsparks;s++){
        if (rr[s] < hh){
          //longxArray[rr[s]]=yold+random(-7,7);
          longxArray[rr[s]]=yold;
        }
        else if (rr[s] >= hh){
          //longxArray[rr[s]]=yval1+random(-7,7);
          longxArray[rr[s]]=yval1;
        }            

        longxArray[pos[s]]=colour[4];
        if (numcolor > 1){longxArray[pos1[s]]=colour[0];} // leds[pos1[s]] = CHSV(colour[0],S,qadd8(BRIGH,BrF));}
        if (numcolor > 2){longxArray[pos2[s]]=colour[1];} // leds[pos2[s]] = CHSV(colour[1],S,qadd8(BRIGH,BrF));}
        if (numcolor > 3){longxArray[pos3[s]]=colour[2];} // leds[pos3[s]] = CHSV(colour[2],S,qadd8(BRIGH,BrF));}    
        if (numcolor > 4){longxArray[pos4[s]]=colour[3];} // leds[pos4[s]] = CHSV(colour[3],S,qadd8(BRIGH,BrF));}              
    
        if (numcolor == 1){
          rr[s]=pos[s];
        }
        else if (numcolor == 2){
         rr[s]=pos1[s]; 
         pos1[s]=pos[s];
        }
        else if (numcolor == 3){
         rr[s]=pos1[s]; 
         pos1[s]=pos2[s];
         pos2[s]=pos[s];
        }   
        else if (numcolor == 4){
        rr[s]=pos1[s]; 
        pos1[s]=pos2[s];
        pos2[s]=pos3[s];
        pos3[s]=pos[s];
        } 
        else if (numcolor == 5){
        rr[s]=pos1[s]; 
        pos1[s]=pos2[s];
        pos2[s]=pos3[s];
        pos3[s]=pos4[s];
        pos4[s]=pos[s];
        }                         
        
        pos[s]=random(hh-offmax, hh+offmin);
          while (pos[s] < 0 || pos[s] > NUM_LEDS-1){
            pos[s]=random(hh-offmax, hh+offmin);}
        }        
        }
    }

  if (hh == NUM_LEDS-1 && num15 <1){
      num15++;
  
      for (int s=0; s<numsparks;s++){
      //longxArray[rr[s]]=yold+random(-7,7);
      //longxArray[pos[s]]=yold+random(-7,7);
      longxArray[rr[s]]=yold;
      longxArray[pos[s]]=yold;
      if (numcolor > 1){longxArray[pos1[s]]=yold+random(-7,7);}  //  leds[pos1[s]] = CHSV((yold+random(-7,7)),S,BRIGH);}       
      if (numcolor > 2){longxArray[pos2[s]]=yold+random(-7,7);}  //  leds[pos2[s]] = CHSV((yold+random(-7,7)),S,BRIGH);}
      if (numcolor > 3){longxArray[pos3[s]]=yold+random(-7,7);}  //  leds[pos3[s]] = CHSV((yold+random(-7,7)),S,BRIGH);}
      if (numcolor > 4){longxArray[pos4[s]]=yold+random(-7,7);}  //  leds[pos4[s]] = CHSV((yold+random(-7,7)),S,BRIGH);}

      rr[s]=NUM_LEDS; // adjusted
      pos[s]=NUM_LEDS; // adjusted
      pos1[s]=NUM_LEDS; // adjusted
      pos2[s]=NUM_LEDS; // adjusted
      pos3[s]=NUM_LEDS; // adjusted
      pos4[s]=NUM_LEDS; // adjusted     
      }
  }
}

if (num50 == 0){  
    if (millis() - previousMillis1 >= FPS) { 
        previousMillis1 = millis();  
        fillColourArray(colourR, yold, yvar, diff); 
        fillNUM_LEDS1(colourR, NUM_LEDS);    
        }
  }
else if (num50 != 0){
    if (millis() - previousMillis1 >= FPS) { 
    previousMillis1 = millis();  

         for(int i = 0; i < NUM_LEDS; i++ ){
         if ( i == pos[0] || i == pos[1] || i == pos[2] || i == pos[3] || i == pos[4] || i == pos[5] || i == pos[6] || i == pos[7] || i == pos[7] || i == pos[8] || i == pos[9] || i == pos[10] || i == pos[11] || i == pos[12]  || i == pos[13] ||  i == pos[14] || i == pos[15] || i == pos[16] || i == pos[17] || i == pos[18] || i == pos[19] ||
              i == pos1[0] || i == pos1[1] || i == pos1[2] || i == pos1[3] || i == pos1[4] || i == pos1[5] || i == pos1[6] || i == pos1[7] || i == pos1[7] || i == pos1[8] || i == pos1[9] || i == pos1[10] || i == pos1[11] || i == pos1[12]  || i == pos1[13] ||  i == pos1[14] || i == pos1[15] || i == pos1[16] || i == pos1[17] || i == pos1[18] || i == pos1[19] || 
              i == pos2[0] || i == pos2[1] || i == pos2[2] || i == pos2[3] || i == pos2[4] || i == pos2[5] || i == pos2[6] || i == pos2[7] || i == pos2[7] || i == pos2[8] || i == pos2[9] || i == pos2[10] || i == pos2[11] || i == pos2[12]  || i == pos2[13] ||  i == pos2[14] || i == pos2[15] || i == pos2[16] || i == pos2[17] || i == pos2[18] || i == pos2[19] || 
              i == pos3[0] || i == pos3[1] || i == pos3[2] || i == pos3[3] || i == pos3[4] || i == pos3[5] || i == pos3[6] || i == pos3[7] || i == pos3[7] || i == pos3[8] || i == pos3[9] || i == pos3[10] || i == pos3[11] || i == pos3[12]  || i == pos3[13] ||  i == pos3[14] || i == pos3[15] || i == pos3[16] || i == pos3[17] || i == pos3[18] || i == pos3[19] || 
              i == pos4[0] || i == pos4[1] || i == pos4[2] || i == pos4[3] || i == pos4[4] || i == pos4[5] || i == pos4[6] || i == pos4[7] || i == pos4[7] || i == pos4[8] || i == pos4[9] || i == pos4[10] || i == pos4[11] || i == pos4[12]  || i == pos4[13] ||  i == pos4[14] || i == pos4[15] || i == pos4[16] || i == pos4[17] || i == pos4[18] || i == pos4[19]){
         
         leds[i] = CHSV(longxArray[i],qadd8(S,SF),qadd8(BRIGH,BrF));    
         }
         else {         
         //leds[i] = CHSV(longxArray[i],satval[satlu],brigh[brighlu]);
         leds[i] = CHSV((longxArray[i]+yvar[varlu]+diff[difflu]),satval[satlu],brigh[brighlu]);
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
}     

void meteor(void){
if (millis() - previousMillis36 >= INTERVAL7){
      num50=1;  
        for (int s=0; s<numsparks; s++){  
        if (millis() - previousMillisAM[s] >= rtAM[s]/df){  
        if (millis() - previousMillisLN[s] >= changeSpeed && flakeCounter >= flakeListMode16[s] && flakeCounter <= cn) {
          previousMillisLN[s] = millis();
          if ((tower) && num17[s] != NUM_LEDS){
          num17[s]=num17[s]-y[s];
          // Serial.print("num17"); Serial.println(num17[0]); 
          }       
          else if ((tower) && num17[s] == NUM_LEDS){
             num17[s]=random(NUM_LEDS-offdis, NUM_LEDS);            
          }
          else{
          num17[s]=num17[s]-1;
          }
          }

          if (tower){
              if (num17[s] < 0 && flakeCounter <= cn){
//            Serial.print("s "); Serial.print(s); Serial.print(" num17 "); Serial.println(num17[s]);
              num17[s]=NUM_LEDS;
              flakeCounter++;
              rtAM[s]= random(65536);
              previousMillisAM[s] = millis();
                if((random(10)>5)) {
                  y[s]=offdis;
                }
                else { 
                  y[s]=offdis+1;
                }           
            }
          }  
          else if (!tower) {
            if (num17[s] < rn[s] && flakeCounter <= cn){
  //            Serial.print("s "); Serial.print(s); Serial.print(" num17 "); Serial.println(num17[s]);
              num17[s]=NUM_LEDS;
              flakeCounter++;
              rtAM[s]= random(65536);
              previousMillisAM[s] = millis();
              if (flakeCounter <= 10 && s == 0){
                rn[0]= random(55,75);}
              else{
              rn[s]= random(randomNumberMinimum[s], randomNumberMaximum[s]);             
              }
            }
          }
          if(flakeCounter > cn && num26[s] <2){
          num26[s]=num26[s]+1;   
          num17[s]=NUM_LEDS;
          }
        }
        }
             
        if (millis() - previousMillis37 >= changeSpeed && flakeCounter > cn-4){ // cn-4 //cn-(4*cfactor2)
          previousMillis37 = millis();
          hh=hh-1;
//          Serial.print("hh: "); Serial.println(hh);
          if (hh <= 0){
          hh=NUM_LEDS-1;
//          Serial.print("hh: "); Serial.println(hh);
          evenOddCounter++;
          for (int s=0; s<numsparks;s++){
            if (colorMode == 4){
               if (s == 0){ yMA[0]=yMA[0]+random(50,200);
               }
               yMA[s]=yMA[0];      
            }
            else if (colorMode == 5){
               if (s == 0){ yMA[0]=yMA[0]+random(50,200);
               while ((yMA[0] >= ymin && yMA[0] <= ymax) || (yMA[0] >= ymin1 && yMA[0] <= ymax1)){yMA[0]=yMA[0]+random(50,200);}
               }
               yMA[s]=yMA[0];          
            }
            else {
            yMA[s] = changeColourFcn2(colorMode, yMA[s], yMA[s], 40, 220);       
            }  
          }              
          INTERVAL7=random(20000);
          T=0;
//          Serial.println("does it enter here?");
//          Serial.println(num15);
          num50=0;
          num15=0;
          for (int s=0; s<numsparks;s++){
          num17[s]=NUM_LEDS;
          rn[s]= random(randomNumberMinimum[s], randomNumberMaximum[s]); 
          }         
          flakeCounter=0;
          if (NUM_LEDS <= 100){
          cn=random(55,85);
          }
          else if (NUM_LEDS > 100){
          cn=random(55,125);
          }                      
          previousMillis36 = millis();
          }
          }
}
      
if (millis() - previousMillis36 >= INTERVAL7 && ((num17[0] > 0) || (hh > 0 && hh <NUM_LEDS-1))){            
        if (millis() - previousMillis35 >= changeSpeed) {
        previousMillis35 = millis();
        
        if (changeSpeed >= 61 && changeSpeed <= 70){
          fadeOutSpeed=60;
        }
        else if (changeSpeed <= 30){
          fadeOutSpeed=17;
        }
        else {
          fadeOutSpeed=35;
        }

        if (hh == NUM_LEDS-1){
            for(int j=0; j<NUM_LEDS; j++) {
              if((random(10)>5)) {
                leds[j].fadeToBlackBy(60);       
              }
            }
        }
       
        else if (hh > 0 && hh < NUM_LEDS-1){
          if (colorMode == 1){
              for (int s=0; s<numsparks;s++){
              yMA[s]=random(256);
              }                     
              }              
          else if (colorMode == 2){
              yMA[0]=yMA[0]+random(256);
                while ((yMA[0] >= ymin && yMA[0] <= ymax) || (yMA[0] >= ymin1 && yMA[0] <= ymax1)){
                  yMA[0]=yMA[0]+random(256);
                }            
         }
  
        leds[p1] = CHSV(yMA[0],qadd8(S,SF),qadd8(BRIGH,BrF));
        p1=random(NUM_LEDS);
        leds[p2] = CHSV(yMA[0],qadd8(S,SF),qadd8(BRIGH,BrF));
        p2=random(NUM_LEDS);
        if (colorMode == 4 || colorMode == 5){
          leds[p3] = CHSV(yMA[0],qadd8(S,SF),qadd8(BRIGH,BrF));
          p3=random(NUM_LEDS);                        
        }
        }

        if (hh < NUM_LEDS-1){
          leds[poshh] = CHSV(yMA[0],qadd8(S,SF),qadd8(BRIGH,BrF));
        }

        // sparkle pos settings
                    
      if (varON == 0){
        if (hh < NUM_LEDS-1){
        poshh=random(hh-offmax-10, hh+offmin+10);
          while (poshh < 0 || poshh > NUM_LEDS-1){
            poshh=random(hh-offmax-(12*cfactor2), hh+offmin+(12*cfactor2));}
            }
        for (int s=0; s<numsparks; s++){
        if (num17[s] == NUM_LEDS-2 || num17[s] == NUM_LEDS-3){  
        pos[s]=random(num17[s]-1, num17[s]+3);
          while (pos[s] < 0 || pos[s] > NUM_LEDS-1){ 
            pos[s]=random(num17[s]-1, num17[s]+3);}} 
        
        else if (num17[s] < NUM_LEDS-3){  
        pos[s]=random(num17[s]-offmax, num17[s]+offmin);
          while (pos[s] < 0 || pos[s] > NUM_LEDS-1){
            pos[s]=random(num17[s]-offmax, num17[s]+offmin);}}
        }           
        }           
        else{
          poshh = hh;
          for (int s=0; s<numsparks; s++){
            pos[s]=num17[s];     
            Serial.print("pos"); Serial.println(pos[0]);    
        }
        }

        for (int s=0; s<numsparks; s++){
        if (num17[s] < NUM_LEDS){ 
          leds[pos[s]] = CHSV(yMA[s+1],qadd8(S,SF),qadd8(BRIGH,BrF));
//          Serial.print("leds pos "); Serial.println(leds[pos[s]]);
            if (varON == 2 && (!tower)){
            leds[pos[s]-1] = CHSV(yMA[s+1],S-50,qadd8(BRIGH,50));              
            }
        }
        }
        
        handleGlitter();
        FastLED.show();
        }
}
             
if (millis() - previousMillis5 >= 70 && hh == NUM_LEDS-1 && num15 <75){
        previousMillis5 = millis();   
        poshh=NUM_LEDS-1;
//        Serial.print("num15 "); Serial.println(num15);        
        for (int s=0; s<numsparks; s++){
          pos[s]=NUM_LEDS;
        } 
        num15++;        
        
        if (num15 > 25){
//            Serial.println(num15);
//            Serial.println("debug fade");
            fadeToBlackBy(leds, NUM_LEDS, fadeOutSpeed);
            FastLED.show();
            }
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
    longxArray[a[k]]=yold+random(-ydiff,ydiff); // random(-ydiff,ydiff);
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
      if (i[k] == 80*cfactor2 || i[k] == 60*cfactor2 || i[k] == 40*cfactor2 || i[k] == 20*cfactor2){
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
        longxArray[a[k]]=yold+random(-ydiff,ydiff);
        a[k]=NUM_LEDS-1;
        partialArrayCounter+=1;
      }
      else {
        i[k]=NUM_LEDS-1;
        a[k]=NUM_LEDS-1;
        partialArrayCounter+=2;
      }
      
    if (partialArrayCounter >= NUM_LEDS-1){
      fillLongxArray(yval1);
      forcedColourChange = true; 
      partialArrayCounter=0;
    }
    previousMillisLN[k] = millis();
    rtAM[k]= random(65536);
    if (k == 0){
      num6=num6+1;
      if (num6 == xnum){
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

if (forcedColourChange){ 
    evenOddCounter++;
    yold=yval1;
    yval1 = changeColourFcn2(colorMode, yval1, yold, 40, 210);
    updateOled(44, 40, &yold);      
    updateOled(102, 56, &yval1);    
    forcedColourChange = false;        
    }
  
if (millis() - previousMillis2 >= FPS) {
    previousMillis2 = millis();  
    partialArraySize=partialArrayCounter;
    fillColourArray(colourR, yval1, yvar, diff);
        
       for(int i = 0; i < partialArraySize; i++ ){
       leds[i] = CHSV(colourR[colourlu],satval[satlu],brigh[brighlu]);
        
       brighlu++;
       if (brighlu >= numbrigh){brighlu = 0;}
       
       colourlu++;
       if (colourlu > 9){colourlu = 0;}

       satlu++;
       if (satlu >= numsat){ satlu = 0;}
       }

       for(int i = partialArraySize; i < NUM_LEDS; i++ ){
       if (longxArray[i] == yval1){
        leds[i] = CHSV(longxArray[i],qadd8(S,SF),qadd8(BRIGH,BrF));
//          if (glowON == 0 || glowON == 1 || glowON == 2){
//            leds[i] = CHSV(longxArray[i],qadd8(S,SF),qadd8(BRIGH,BrF));
//            }
//            else{
//            leds[i] = CHSV(longxArray[i],satval[satlu],brigh[brighlu]);      
//            }
        }
       else {
       leds[i] = CHSV(longxArray[i],S,BRIGH); // brigh[brighlu]
       }
        
       brighlu++;
       if (brighlu >= numbrigh){brighlu = 0;}

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

void flowercolors(void){
    if (millis() - previousMillis1 >= changeSpeed + rn15) {
    previousMillis1 = millis();
    y0r+=1*dir1;
    y01m=y0r;
    rn15=0;
    if (y0r > ymax3 && y0r < ymax3+2 && dir1 == 1){ // && y < ymax+2
      dir1 = -1;
      rn15=random(5000,25000);
      }
    else if (y0r < ymin3 && y0r > ymin3-2 && dir1 == -1){ // && y > ymin-2
      dir1 = 1;
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
if (varON == 1){  
    if (millis() - previousMillis1 >= changeSpeed + rn15) {
    previousMillis1 = millis();
    rn15=0;
    
    yval1+=1*dir1;

    if (yval1 == ymax4-setDifference && dir1 == 1){
     dir1 = -1;
     rn15 = random(65536)/2;
     }
    else if (yval1 == ymin4 && dir1 == -1){
     dir1 = 1;
     rn15 = random(65536)/2;
     }
    }
}
    
    if (millis() - previousMillis2 >= FPS) {     
      previousMillis2 = millis(); 
      y0r=yval1;  
      dir0=1;
      
       for(int i = 0; i < NUM_LEDS; i++ ){
       leds[i] = CHSV(y0r,satval[satlu],brigh[brighlu]);
        
       brighlu++;
       if (brighlu >= numbrigh){brighlu = 0;}

       satlu++;
       if (satlu >= numsat){satlu = 0;}       
       
       y0r+=setDifference*dir0;

       if (((y0r > ymax4 && y0r <= ymax4+setDifference) || (y0r <= setDifference && ymax4 >= 255-setDifference)) && dir0 == 1){
         dir0 = -1;
         y0r=ymax4-(y0r-ymax4);
       }
  
       //else if (((y0r < ymin4 && y0r >= ymin4-setDifference) || ((y0r < ymin4 || y0r >= 255-setDifference) && ymin4 >= 0 && ymin4 < setDifference)) && dir0 == -1){
       else if (((y0r < ymin4 && y0r >= ymin4-setDifference) || (y0r >= 255-setDifference && ymin4 <= setDifference)) && dir0 == -1){ 
         dir0 = 1;
         y0r=ymin4+(ymin4-y0r);
       }
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
   leds[i] = CHSV((blockArray[yint]+yvar[varlu]),satval[satlu],brigh[brighlu]);
   yint++;
   if (yint > 10*colorlength-1){
    yint=0;  
   }
    
   brighlu++;
   if (brighlu >= numbrigh){brighlu = 0;}
   
   satlu++;
   if (satlu >= numsat){satlu = 0;}

   varlu++;
   if (varlu >= 10){varlu = 0;}   
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
if (millis() - previousMillis1 >= changeSpeed*m21delay) {
  previousMillis1 = millis();

  if (varON == 0){
    yint=0; 
    m21delay=1;   
  }
  else if (varON == 1){
    yint++;
    if (yint > (numcolor*colorlength-1)){
    yint=0;
    }
    yintm=yint;
    m21delay=1; 
    }    
  else if (varON == 2){
    changePColors();
    m21delay=3;     
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
   leds[i] = CHSV((blockArray[yint]+yvar[varlu]),satval[satlu],brigh[brighlu]);
   yint++;
   if (yint > (numcolor*colorlength-1)){
    yint=0;   
   }
    
   brighlu++;
   if (brighlu >= numbrigh){brighlu = 0;}
   
   satlu++;
   if (satlu >= numsat){satlu = 0;}      

   varlu++;
   if (varlu >= 10){varlu = 0;}

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
   y0r++;
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

if (millis() - previousMillis36 > INTERVAL7 && varON == 2) {
  //gCurrentPaletteNumber = addmod8( gCurrentPaletteNumber, 1, gGradientPaletteCount); 
  gCurrentPaletteNumber = random(gGradientPaletteCount);
  //gCurrentPalette =( gGradientPalettes[gCurrentPaletteNumber] );
  gTargetPalette = gGradientPalettes[gCurrentPaletteNumber];
  INTERVAL7=interval9*timeArray2[random(0,6)]*timefactor3;
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

void pacifica(void){
if (millis() - previousMillis1 >= changeSpeed) {

  static uint16_t sCIStart1, sCIStart2, sCIStart3, sCIStart4;
  static uint32_t sLastms = 0;
  uint32_t ms = GET_MILLIS();
  uint32_t deltams = ms - sLastms;
  sLastms = ms;
  uint16_t speedfactor1 = beatsin16(3, 179, 269);
  uint16_t speedfactor2 = beatsin16(4, 179, 269);
  uint32_t deltams1 = (deltams * speedfactor1) / 256;
  uint32_t deltams2 = (deltams * speedfactor2) / 256;
  uint32_t deltams21 = (deltams1 + deltams2) / 2;
  sCIStart1 += (deltams1 * beatsin88(1011,10,13));
  sCIStart2 -= (deltams21 * beatsin88(777,8,11));
  sCIStart3 -= (deltams1 * beatsin88(501,5,7));
  sCIStart4 -= (deltams2 * beatsin88(257,4,6));

  // Clear out the LED array to a dim background blue-green
  fill_solid( leds, NUM_LEDS, CRGB( 2, 6, 10));

  // Render each of four layers, with different scales and speeds, that vary over time
  pacifica_one_layer( pacifica_palette_1, sCIStart1, beatsin16( 3, 11 * 256, 14 * 256), beatsin8( 10, 70, 130), 0-beat16( 301) );
  pacifica_one_layer( pacifica_palette_2, sCIStart2, beatsin16( 4,  6 * 256,  9 * 256), beatsin8( 17, 40,  80), beat16( 401) );
  pacifica_one_layer( pacifica_palette_3, sCIStart3, 6 * 256, beatsin8( 9, 10,38), 0-beat16(503));
  pacifica_one_layer( pacifica_palette_3, sCIStart4, 5 * 256, beatsin8( 8, 10,28), beat16(601));

  // Add brighter 'whitecaps' where the waves lines up more
  pacifica_add_whitecaps();

  // Deepen the blues and greens a bit
  pacifica_deepen_colors();
  FastLED.show();
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
  mergedString = "HHHH"+String(HUE); ws.textAll(mergedString);  
  mergedString = "HSSS"+String(SAT); ws.textAll(mergedString);  
  mergedString = "HVVV"+String(VAL); ws.textAll(mergedString);  
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
