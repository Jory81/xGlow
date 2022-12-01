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

if (overLay > 0){
  if (overLay == 1){
    for (int i = 0; i < numbrigh; i++){
      if (i % ledOffset != 0){
      brigh[i] = 0;
      }
    }
  }
  else if (overLay == 2){
   if (millis() - previousMillis8 > overlaySpeed){ // BPS 8 is timer modifier
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
    satval[i]=beatsin8(BPMS, 0, qadd8(S,offS), ((i/2)*convSat));
  }
}

else if (satON == 10){
  for (int i = 0; i < numsat; i++){
    satval[i]=beatsin8(BPMS, 0, qadd8(S,offS), ((i/3)*convSat));
  }
}

if (effect_function == *pers_color && whiteON == true){
  satval[whitepos]=0;
}
}
