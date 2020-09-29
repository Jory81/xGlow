/*
 * This fucntion displays the oled screen
 */

void handleProgramTimer(){ // HANDLE PROGRAM TIMER
if (millis() - previousMillis20 >= 1000 && (INTERVAL7/1000-T > -100)) {
    previousMillis20 = millis();
    T++;
    int time0 = INTERVAL7/1000-T;
    mergedString = "HPTI"+String(time0); ws.textAll(mergedString);
//    display.setCursor (96,0);    display.print ("    ");   display.setCursor (96,0);    display.print((INTERVAL7/1000-T), 0); display.display();
    colourTimerActive = true;
    }
    else if (INTERVAL7/1000-T <= -100 && (colourTimerActive)){
    colourTimerActive = false;  
    mergedString = "HPTINA"; ws.textAll(mergedString);
    }
}

void handleCycleTimer(){ // HANDLE CYCLE TIMER
if (millis() - previousMillis44 >= 1000 && (cycle)) { // 60000 for updating ever minute instead of every second.
    previousMillis44 = millis();
    cycleT+=1;
    int time1 = cycleTime/1000-cycleT;
    mergedString = "HCTI"+String(time1); ws.textAll(mergedString);
//    display.setCursor (0,56);    display.print ("    ");   display.setCursor (0,56);    display.print(cycleTime/1000-cycleT); display.display();
    }
 }   

void displayOled(){
if (colorNumber == 0){
     display.clearDisplay();
     display.setCursor(0,0); if (!excludeModes){display.print("-");} display.print(programMode); if (!cmode[programMode]){display.print(F("*"));}; display.print(F(":")); 
     strcpy_P(buffer, (char*)pgm_read_dword(&(string_table[programMode]))); display.print(buffer);if (glitterON){display.print(F("+"));};
     display.setCursor(0,8); display.print(F("LED speed (ms):  ")); display.println (changeSpeed); display.print(F("LED  variation:  ")); display.println(setDifference); display.print(F("variation mode:  ")); display.println(varON);  display.print(F("#bri: ")); display.print(numbrigh); display.setCursor(54,32); display.print(F(" glow:  ")); display.println(glowON); 
     display.print (F("HSV ")); 
     if (colorMode == 4){
     display.setCursor(24,40); display.print (colorMode); display.setCursor(38,40); display.print (arrayn); display.setCursor(50,40); display.print("/"); display.print(arrayCount-1); 
     }
     else if (effect_function == *gradient || effect_function == *rainbow_3){
     display.setCursor(24,40); display.print(ymin4); display.setCursor(44,40); display.print("/"); display.print(ymax4);  
     }
     else if (effect_function == *pers_color || effect_function == *rainbow_6 || effect_function == *pers_block){
     display.setCursor(24,40); display.print(arrayn); display.setCursor(38,40); display.print("/"); display.print(arrayCount-1); if (whiteON){display.print("_W");} else if (!whiteON) {display.print("_");}; display.setCursor(94,56); display.print(numcolor); display.print("/"); display.print(colorlength);
     }
     else{
     display.setCursor(24,40); display.print (colorMode); display.setCursor(44,40); display.print(yval); 
     }
     display.setCursor(74,40); display.print(S); display.setCursor(102,40); display.println(BRIGH); 
     if (numsparks > 0){display.print (F("sparks: ")); display.print (numsparks); display.setCursor(64,48); display.print(F("sbri:")); display.setCursor(102,48); display.println(BrF);}  
     display.setCursor(0,56); if (cycle){display.print(F("C"));}; display.setCursor(36,56); display.print(F("/")); display.print(cycleTime/1000); if (fadeFirst){display.print(F("F"));} else if (!fadeFirst){display.print(F("_"));}; if (randomCycle){display.print(F("R"));} else if (!randomCycle) {display.print("_");}; display.setCursor(72,56); display.print(INTERVAL, 0);
     display.display();
}
else if (colorNumber > 0){  
     display.clearDisplay();
     display.setCursor(0,0); display.print(F("EEPROM SETTINGS*"));
     display.setCursor(0,8);  display.print (F("yred:"));    display.setCursor(56,8);    display.print (yminrood);   if (colorNumber == 1){display.print(F("*"));}; display.print(F("-")); display.setCursor(96,8);  display.print (ymaxrood); if (colorNumber == 2){display.print(F("*"));};
     display.setCursor(0,16);  display.print (F("ygreen:"));  display.setCursor(56,16);  display.print (ymingroen);  if (colorNumber == 3){display.print(F("*"));}; display.print(F("-")); display.setCursor(96,16); display.print (ymaxgroen); if (colorNumber == 4){display.print(F("*"));};
     display.setCursor(0,24); display.print (F("yblue:"));   display.setCursor(56,24);   display.print (yminblauw);  if (colorNumber == 5){display.print(F("*"));}; display.print(F("-")); display.setCursor(96,24); display.print (ymaxblauw); if (colorNumber == 6){display.print(F("*"));};
     display.setCursor(0,32); display.print (F("ygap:"));    display.setCursor(56,32);   display.print (ymin);       if (colorNumber == 7){display.print(F("*"));}; display.print(F("-")); display.setCursor(96,32); display.print (ymax); if (colorNumber == 8){display.print(F("*"));};
     display.setCursor(0,40); display.print (F("ygap1:"));   display.setCursor(56,40);   display.print (ymin1);      if (colorNumber == 9){display.print(F("*"));}; display.print(F("-")); display.setCursor(96,40); display.print (ymax1); if (colorNumber == 10){display.print(F("*"));};
     display.setCursor(0,48); if (colorNumber == 11 || colorNumber == 12) display.print (F("NUM_LEDS: ")); display.print(NUM_LEDS);
//     display.setCursor(0,56); display.print ("colorOrder: "); display.print(rgbORDER);
     display.display();
}
return;
}

void updateOled(byte xAxis, byte yAxis, uint8_t* variable){
    if (*variable == arrayn || *variable == oldArrayn){
      mergedString = "SCAR"+String(*variable); ws.textAll(mergedString);
    }
    else if (*variable == yval1){
      mergedString = "HY1N"+String(*variable); ws.textAll(mergedString);
    }
    else if (*variable == yold){
      mergedString = "HY1O"+String(*variable); ws.textAll(mergedString);
    }
//  display.setCursor(xAxis,yAxis);
//  if (*variable == arrayn){
//  display.print("  ");  
//  }
//  else{
//  display.print("    ");
//  }
//  display.setCursor(xAxis,yAxis);
//  display.print(*variable);
//  display.display();
  return;
}
void updateOledFloat(byte xAxis, byte yAxis, float* variable, int decimal){
     if (*variable == INTERVAL7){
      mergedString = "HPTT"+String(*variable/1000, decimal); ws.textAll(mergedString);
    }
    else if (*variable == INTERVALf[0]){
      mergedString = "HSPE"+String(*variable, decimal); ws.textAll(mergedString);
    } 
//  display.setCursor(xAxis,yAxis);
//  display.print("    ");
//  display.setCursor(xAxis,yAxis);
//  display.print((*variable), decimal);
//  display.display();
  return;
}
