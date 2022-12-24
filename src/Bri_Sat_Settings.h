/*
 * handles all the glow modes. 
 */


void handleBrightnessSettings(){ // HANDLE BRIGHTNESS SETTINGS 
  
if (glowON == 0 || lastBRIGH != BRIGH){
  BRIGH=BRIGH;
  for (int i=0 ; i<numbrigh ; i++){brigh[i]=BRIGH;}
  lastBRIGH=BRIGH;
}
else if (glowON == 1){
  for (int i = 0; i < numbrigh; i++){
      int ii = i % 16;
      brigh[i] = beatsin8(brivalbpm[ii], qsub8(BRIGH,offBr),qadd8(BRIGH,offBr));  
  }
}
  
else if (glowON == 2){   
    for (int i = 0; i < numbrigh; i++){
      int ii = i % 16;
      brigh[i] = beatsin8(brivalbpm[ii], qsub8(BRIGH,offBr),qadd8(BRIGH,offBr)); 
  }
}

else if (glowON == 3){
 for (int i=0 ; i<numbrigh ; i++){
 if (millis() - previousMillisGlow3[i] >= rtGlow3[i]/2){ // BPS 2 is timer modifier
  if (numGlow3[i] == 0){
    timeFactorGlow3[i] = millis(); 
    numGlow3[i]=1;  
    cycleGlow3[i] = 0;
    }
  brigh[i] = map(sin16((millis()-timeFactorGlow3[i])*BPMB),0,32767,offBr,BRIGH); // glowfactor 16 is speed setting
  if (brigh[i] >= BRIGH-3){cycleGlow3[i] = 1;}
  if (brigh[i] <= offBr+3 && cycleGlow3[i] == 1){
    rtGlow3[i]=random(waveTimeBr*cfactor3);
    previousMillisGlow3[i] = millis();
    numGlow3[i]=0;
  }  
 }
 else{brigh[i] = offBr;}
 }
} 

else if (glowON == 4){
 for (int i=0 ; i<numbrigh ; i++){
 if (millis() - previousMillisGlow3[i] >= rtGlow3[i]/2){ // BPS 2 is timer modifier
  if (numGlow3[i] == 0){
    timeFactorGlow3[i] = millis(); 
    numGlow3[i]=1;  
    cycleGlow3[i] = 0;
    }
  brigh[i] = map(sin16((millis()-timeFactorGlow3[i])*BPMB),0,32767,BRIGH, offBr); // glowfactor 16 is speed setting
  if (brigh[i] <= offBr+3){cycleGlow3[i] = 1;} 
  if (brigh[i] >= BRIGH-3 && cycleGlow3[i] == 1){
    rtGlow3[i]=random(waveTimeBr*cfactor3);
    previousMillisGlow3[i] = millis();
    numGlow3[i]=0;
  }  
 }
 else{brigh[i] = BRIGH;} // making this offbr makes it sparkly
 }
}

else if (glowON == 5){
  for (int i = 0; i < numbrigh; i++){
    brigh[i]=beatsin8(BPMB, qsub8(BRIGH,offBr), qadd8(BRIGH,offBr), ((i+1)*convBrigh));
  }
}

else if (glowON == 6){
  for (int i = 0; i < numbrigh; i++){
    brigh[i]=beatsin8(BPMB, qsub8(BRIGH,offBr), qadd8(BRIGH,offBr),0, (100+(i*100)));
  }
}

else if (glowON == 7){
  for (int i = 0; i < numbrigh; i++){
    brigh[i]=beatsin8(BPMB, 0, qadd8(BRIGH,offBr), ((i+1)*(convBrigh/2)));
  }
}  

else if (glowON == 8){
  for (int i = 0; i < numbrigh; i++){
    brigh[i]=beatsin8(BPMB, 0, qadd8(BRIGH,offBr), ((i+1)*convBrigh));
  }
}

else if (glowON == 9){
  for (int i = 0; i < numbrigh; i++){
    brigh[i]=beatsin8(BPMB, 0, qadd8(BRIGH,offBr), ((i/ledOffset)*convBrigh));
  }
}

else if (glowON == 10){
  for (int i = 0; i < numbrigh; i++){
     if (millis() - previousMillisGlow3[i] > rtGlow3[i]){ // BPS 2 is timer modifier
        previousMillisGlow3[i] = millis();
        brigh[i]=random8(offBr, BRIGH);
        rtGlow3[i]=random(waveTimeBr, waveTimeBr*3);
    }
  }
}
else if (glowON == 11){
  for (int k=0; k < cfactor3*7; k++){       
  if (millis() - previousMillisGlow3[k] > (rtGlow3[k]*timeSpeed[k])) {
      previousMillisGlow3[k] = millis();

      brigh[numGlow3[k]] = bMA[k];
      numGlow3[k]=numGlow3[k]-1;

      if (numGlow3[k]<0){
        numGlow3[k]=NUM_LEDS-1;
        bMA[k] = random8(offBr, BRIGH);
        if (random8(25*cfactor3) == 1){
          rtGlow3[0]=125*timeArray[random(0,5)];
        }
        rtGlow3[k]=rtGlow3[0];
      }
  }
  }
}


if (overLay > 0){
  if (overLay == 1){
    for (int i = 0; i < numbrigh; i++){
      if (i % ledOffset != 0){
      brigh[i] = 0;
      }
    }
  }
  else if (overLay == 2){
   if (millis() - previousMillis8 > overlaySpeed){
    previousMillis8 = millis(); 
    blackPos++;
    if (blackPos >= ledOffset){
      blackPos = 0;
    }
   }
    for (int i = 0; i < numbrigh; i++){
      if (i % ledOffset == blackPos){
      brigh[i] = 0;
      }
    }
  }
}
}

void handleSaturationSettings(){ // HANDLE BRIGHTNESS SETTINGS

if (satON == 0 || lastS != S){
  S=S;
  for (int i=0; i<numsat; i++){satval[i]=S;}
  lastS=S;
}

else if (satON == 1){ 
  for (int i = 0; i < numsat; i++){
      int ii = i % 16;
      satval[i] = beatsin8(satvalbpm[ii], satvalmin[i], 255);
    // if (i < 16){
    // satval[i] = beatsin8(satvalbpm[i], satvalmin[i], 255);
    // }
    // else{
    // satval[i] = satval[i-16];     
    // } 
  }
}
  
else if (satON == 2){ 
  for (int i = 0; i < numsat; i++){
      int ii = i % 16;
      satval[i] = beatsin8(satvalbpm[ii], satvalmin[i], 255);
    // if (i < 16){
    // satval[i] = beatsin8(satvalbpm[i], qsub8(S,offS),qadd8(S,offS));
    // }
    // else{
    // satval[i] = satval[i-16];     
    // } 
  }
}
  
else if (satON == 3){
 if (glowON == 3 && numbrigh == numsat){
   for (int i = 0; i<numsat; i++){
    satval[i]=brigh[i];
   }
 }
 else{
 for (int i=0 ; i<numsat ; i++){
 if (millis() - previousMillisSat3[i] >= rtSat3[i]/2){ // BPS 8 is timer modifier
  if (numSat3[i] == 0){
    timeFactorSat3[i] = millis(); 
    numSat3[i]=1;  
    cycleSat3[i] = 0;
    }
  satval[i] = map(sin16((millis()-timeFactorSat3[i])*BPMS),0,32767,offS,S); // glowfactor 16 is speed setting
  if (satval[i] >= S-3){cycleSat3[i] = 1;}
  if (satval[i] <= offS+3 && cycleSat3[i] == 1){
    rtSat3[i]=random(waveTimeS*cfactor3);
    previousMillisSat3[i] = millis();
    numSat3[i]=0;
  }  
 }
 else{satval[i] = offS;}
 }
} 
}

else if (satON == 4){
 for (int i=0 ; i<numsat ; i++){
 if (millis() - previousMillisSat3[i] >= rtSat3[i]/2){ // BPS 8 is timer modifier
  if (numSat3[i] == 0){
    timeFactorSat3[i] = millis(); 
    numSat3[i]=1;  
    cycleSat3[i] = 0;
    }
  satval[i] = map(sin16((millis()-timeFactorSat3[i])*BPMS),0,32767,S,offS); // glowfactor 16 is speed setting
  if (satval[i] <= offS+3){cycleSat3[i] = 1;} //+3
  if (satval[i] >= S-3 && cycleSat3[i] == 1){ // -3
    rtSat3[i]=random(waveTimeS*cfactor3);
    previousMillisSat3[i] = millis();
    numSat3[i]=0;
  }  
 }
 else{satval[i] = S;}
 }
} 

else if (satON == 5){
  for (int i = 0; i < numsat; i++){
    satval[i]=beatsin8(BPMS, qsub8(S,offS), qadd8(S,offS), ((i+1)*convSat));
  }
}

else if (satON == 6){
  for (int i = 0; i < numsat; i++){
    satval[i]=beatsin8(BPMS, qsub8(S,offS), qadd8(S,offS),0, (100+(i*100)));
  }
}

else if (satON == 7){
  for (int i = 0; i < numsat; i++){
    satval[i]=beatsin8(BPMS, qsub8(S,offS), qadd8(S,offS), ((i+1)*(convSat/2)));
  }
}  

else if (satON == 8){
  for (int i = 0; i < numsat; i++){
    satval[i]=beatsin8(BPMS, 0, qadd8(S,offS), ((i+1)*convSat));
  }
}

else if (satON == 9){
  for (int i = 0; i < numsat; i++){
    satval[i]=beatsin8(BPMS, 0, qadd8(S,offS), ((i/ledOffsetS)*convSat));
  }
}

else if (satON == 10){
  for (int i = 0; i < numsat; i++){
     if (millis() - previousMillisSat3[i] > rtSat3[i]){ // BPS 2 is timer modifier
        previousMillisSat3[i] = millis();
        satval[i]=random8(offS, S);
        rtSat3[i]=random(waveTimeS, waveTimeS*3);
    }
  }
}

else if (satON == 11){
  for (int k=0; k < cfactor3*7; k++){       
  if (millis() - previousMillisSat3[k] > (rtSat3[k]*timeSpeed[k])) {
      previousMillisSat3[k] = millis();

      satval[numSat3[k]] = sMA[k];
      numSat3[k]=numSat3[k]-1;

      if (numSat3[k]<0){
        numSat3[k]=NUM_LEDS-1;
        sMA[k] = random8(offS, S);
        if (random8(25*cfactor3) == 1){
          rtSat3[0]=125*timeArray[random(0,5)];
        }
        rtSat3[k]=rtSat3[0];
      }
  }
  }
}

if (overLayS > 0){
  if (overLayS == 1){
    for (int i = 0; i < numsat; i++){
      if (i % ledOffsetS != 0){
      satval[i] = 255;
      }
    }
  }
  else if (overLayS == 2){
   if (millis() - previousMillis9 > overlaySpeedS){
    previousMillis9 = millis(); 
    satPos++;
    if (satPos >= ledOffset){
      blackPos = 0;
    }
   }
    for (int i = 0; i < numsat; i++){
      if (i % ledOffsetS == satPos){
      satval[i] = 255;
      }
    }
  }
}

if (effect_function == *pers_color && whiteON == true){
  satval[whitepos]=0;
}
}
