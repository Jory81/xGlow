/*
 * handles all the glow modes. Some mode can likely be put in for loops, but that didn't work yet.
 */


void handleBrightnessSettings(){ // HANDLE BRIGHTNESS SETTINGS 
  
if (glowON == 0 || lastBRIGH != BRIGH){
  BRIGH=BRIGH;
  for (int i=0 ; i<numbrigh ; i++){brigh[i]=BRIGH;}
  lastBRIGH=BRIGH;
}
else if (glowON == 1){
  brigh[0] = beatsin8(12,135,255);
  brigh[1] = beatsin8(23,75,205);
  brigh[2] = beatsin8(7,75,255);
  brigh[3] = beatsin8(63,175,255);
  brigh[4] = beatsin8(37,75,255);
  brigh[5] = beatsin8(14,95,205);
  brigh[6] = beatsin8(24,105,255);
  brigh[7] = beatsin8(26,125,205);
  brigh[8] = beatsin8(58,135,255);
  brigh[9] = beatsin8(32,175,205);
  brigh[10] = beatsin8(7,75,255);
  brigh[11] = beatsin8(62,175,255);
  brigh[12] = beatsin8(38,75,255);
  brigh[13] = beatsin8(13,95,205); 
  brigh[14] = beatsin8(57,135, 255);
  brigh[15] = beatsin8(31,175,205); 
  brigh[16] = brigh[0];
  brigh[17] = brigh[1];
  brigh[18] = brigh[2];
  brigh[19] = brigh[3];
  brigh[20] = brigh[4];
  brigh[21] = brigh[5];
  brigh[22] = brigh[6];
  brigh[23] = brigh[7];
  brigh[24] = brigh[8];
  brigh[25] = brigh[9];
  brigh[26] = brigh[10];
  brigh[27] = brigh[11];
  brigh[28] = brigh[12];
  brigh[29] = brigh[13]; 
  brigh[30] = brigh[14];
  brigh[31] = brigh[15];
  }
  
else if (glowON == 2){   
  brigh[0]=beatsin8(12,qsub8(BRIGH,offBr),qadd8(BRIGH,offBr));
  brigh[1]=beatsin8(23,qsub8(BRIGH,offBr),qadd8(BRIGH,offBr));
  brigh[2]=beatsin8(7,qsub8(BRIGH,offBr),qadd8(BRIGH,offBr));
  brigh[3]=beatsin8(63,qsub8(BRIGH,offBr),qadd8(BRIGH,offBr));
  brigh[4]=beatsin8(37,qsub8(BRIGH,offBr),qadd8(BRIGH,offBr));
  brigh[5]=beatsin8(14,qsub8(BRIGH,offBr),qadd8(BRIGH,offBr));
  brigh[6]=beatsin8(24,qsub8(BRIGH,offBr),qadd8(BRIGH,offBr));
  brigh[7]=beatsin8(26,qsub8(BRIGH,offBr),qadd8(BRIGH,offBr));
  brigh[8]=beatsin8(58,qsub8(BRIGH,offBr),qadd8(BRIGH,offBr));
  brigh[9]=beatsin8(32,qsub8(BRIGH,offBr),qadd8(BRIGH,offBr));
  brigh[10]=beatsin8(11,qsub8(BRIGH,offBr),qadd8(BRIGH,offBr));
  brigh[11]=beatsin8(62,qsub8(BRIGH,offBr),qadd8(BRIGH,offBr));
  brigh[12]=beatsin8(43,qsub8(BRIGH,offBr),qadd8(BRIGH,offBr));
  brigh[13]=beatsin8(13,qsub8(BRIGH,offBr),qadd8(BRIGH,offBr));
  brigh[14]=beatsin8(51,qsub8(BRIGH,offBr),qadd8(BRIGH,offBr));
  brigh[15]=beatsin8(31,qsub8(BRIGH,offBr),qadd8(BRIGH,offBr));
  brigh[16] = brigh[0];
  brigh[17] = brigh[1];
  brigh[18] = brigh[2];
  brigh[19] = brigh[3];
  brigh[20] = brigh[4];
  brigh[21] = brigh[5];
  brigh[22] = brigh[6];
  brigh[23] = brigh[7];
  brigh[24] = brigh[8];
  brigh[25] = brigh[9];
  brigh[26] = brigh[10];
  brigh[27] = brigh[11];
  brigh[28] = brigh[12];
  brigh[29] = brigh[13]; 
  brigh[30] = brigh[14];
  brigh[31] = brigh[15];  
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
  if (brigh[i] >= BRIGH-5){cycleGlow3[i] = 1;}
  if (brigh[i] <= offBr+5 && cycleGlow3[i] == 1){
    rtGlow3[i]=random(waveTimeBr);
    previousMillisGlow3[i] = millis();
    numGlow3[i]=0;
  }  
 }
 else{brigh[i] = offBr;}
 }
} 

else if (glowON == 4){
  for (int i = 0; i < numbrigh; i++){
    brigh[i]=beatsin8(BPMB, qsub8(BRIGH,offBr), qadd8(BRIGH,offBr), ((i+1)*convBrigh));
  }
}

else if (glowON == 5){
  for (int i = 0; i < numbrigh; i++){
    brigh[i]=beatsin8(BPMB, qsub8(BRIGH,offBr), qadd8(BRIGH,offBr),0, (100+(i*100)));
  }
}

else if (glowON == 6){
  for (int i = 0; i < numbrigh; i++){
    brigh[i]=beatsin8(BPMB, 0, qadd8(BRIGH,offBr), ((i+1)*(convBrigh/2)));
  }
}  

else if (glowON == 7){
  for (int i = 0; i < numbrigh; i++){
    brigh[i]=beatsin8(BPMB, 0, qadd8(BRIGH,offBr), ((i+1)*convBrigh));
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
  satval[0] = beatsin8(7,135,255);
  satval[1] = beatsin8(11,75,255);
  satval[2] = beatsin8(4,75,255);
  satval[3] = beatsin8(5,175,255);
  satval[4] = beatsin8(3,75,255);
  satval[5] = beatsin8(12,95,255);
  satval[6] = beatsin8(9,105,255);
  satval[7] = beatsin8(8,125,255);
  satval[8] = beatsin8(2,135,255);
  satval[9] = beatsin8(6,175,255);
  satval[10] = beatsin8(5,75,255);
  satval[11] = beatsin8(3,175,255);
  satval[12] = beatsin8(7,75,255);
  satval[13] = beatsin8(8,95,255); 
  satval[14] = beatsin8(9,135, 255);
  satval[15] = beatsin8(2,175,255); 
  satval[16] = satval[0];
  satval[17] = satval[1];
  satval[18] = satval[2];
  satval[19] = satval[3];
  satval[20] = satval[4];
  satval[21] = satval[5];
  satval[22] = satval[6];
  satval[23] = satval[7];
  satval[24] = satval[8];
  satval[25] = satval[9];
  satval[26] = satval[10];
  satval[27] = satval[11];
  satval[28] = satval[12];
  satval[29] = satval[13]; 
  satval[30] = satval[14];
  satval[31] = satval[15];    
  }
  
else if (satON == 2){ 
  satval[0]=beatsin8(7,qsub8(S,offS),qadd8(S,offS));
  satval[1]=beatsin8(11,qsub8(S,offS),qadd8(S,offS));
  satval[2]=beatsin8(4,qsub8(S,offS),qadd8(S,offS));
  satval[3]=beatsin8(5,qsub8(S,offS),qadd8(S,offS));
  satval[4]=beatsin8(3,qsub8(S,offS),qadd8(S,offS));
  satval[5]=beatsin8(12,qsub8(S,offS),qadd8(S,offS));
  satval[6]=beatsin8(9,qsub8(S,offS),qadd8(S,offS));
  satval[7]=beatsin8(8,qsub8(S,offS),qadd8(S,offS));
  satval[8]=beatsin8(2,qsub8(S,offS),qadd8(S,offS));
  satval[9]=beatsin8(6,qsub8(S,offS),qadd8(S,offS));
  satval[10]=beatsin8(5,qsub8(S,offS),qadd8(S,offS));
  satval[11]=beatsin8(3,qsub8(S,offS),qadd8(S,offS));
  satval[12]=beatsin8(7,qsub8(S,offS),qadd8(S,offS));
  satval[13]=beatsin8(8,qsub8(S,offS),qadd8(S,offS));
  satval[14]=beatsin8(9,qsub8(S,offS),qadd8(S,offS));
  satval[15]=beatsin8(2,qsub8(S,offS),qadd8(S,offS));
  satval[16] = satval[0];
  satval[17] = satval[1];
  satval[18] = satval[2];
  satval[19] = satval[3];
  satval[20] = satval[4];
  satval[21] = satval[5];
  satval[22] = satval[6];
  satval[23] = satval[7];
  satval[24] = satval[8];
  satval[25] = satval[9];
  satval[26] = satval[10];
  satval[27] = satval[11];
  satval[28] = satval[12];
  satval[29] = satval[13]; 
  satval[30] = satval[14];
  satval[31] = satval[15];      
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
  if (satval[i] >= S-5){cycleSat3[i] = 1;}
  if (satval[i] <= offS+5 && cycleSat3[i] == 1){
    rtSat3[i]=random(waveTimeS);
    previousMillisSat3[i] = millis();
    numSat3[i]=0;
  }  
 }
 else{satval[i] = offS;}
 }
} 
}

else if (satON == 4){
  for (int i = 0; i < numsat; i++){
    satval[i]=beatsin8(BPMS, qsub8(S,2*offS), qadd8(S,offS), ((i+1)*convSat));
  }
}

else if (satON == 5){
  for (int i = 0; i < numsat; i++){
    satval[i]=beatsin8(BPMS, qsub8(S,offS), qadd8(S,offS),0, (100+(i*100)));
  }
}

else if (satON == 6){
  for (int i = 0; i < numsat; i++){
    satval[i]=beatsin8(BPMS, qsub8(S,offS), qadd8(S,offS), ((i+1)*(convSat/2)));
  }
}  

else if (satON == 7){
  for (int i = 0; i < numsat; i++){
    satval[i]=beatsin8(BPMS, 0, qadd8(S,offS), ((i+1)*convSat));
  }
}

if (effect_function == *pers_color && whiteON == true){
  satval[whitepos]=0;
}
}
