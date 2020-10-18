/*
 ALL webserver (websocket)/ client functions.

*/

void onRootRequest(AsyncWebServerRequest *request) {
  request->send(SPIFFS, "/index.html", "text/html");    // , false, processor
}

void initWebServer() {
    server.on("/", onRootRequest);
    server.serveStatic("/", SPIFFS, "/");
    server.begin();
}

void onEvent(AsyncWebSocket       *server,
             AsyncWebSocketClient *client,
             AwsEventType          type,
             void                 *arg,
             uint8_t              *data,
             size_t                len) {

    switch (type) {
        case WS_EVT_CONNECT:
            Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
            break;
        case WS_EVT_DISCONNECT:
            Serial.printf("WebSocket client #%u disconnected\n", client->id());
            break;
        case WS_EVT_DATA:
            handleWebSocketMessage(arg, data, len);
        case WS_EVT_PONG:
        case WS_EVT_ERROR:
            break;
    }
}

void initWebSocket() {
    ws.onEvent(onEvent);
    server.addHandler(&ws);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
    AwsFrameInfo *info = (AwsFrameInfo*)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
      data[len]=NULL;
      for (int i = 0; i < 4; i++){
      strval[i]=(char)data[i];
      }
      strval[4]=0;
      str=String(strval);
        if (str == "GETS"){
          str = "G";
          dataVar = (uint16_t) strtol((const char *) &data[4], NULL, 10);          
          sendMessageToClient(dataVar);
        }
        else if (str == "ssid" || str == "pass"){
            for (int i = 4; i < len+4; i++){
            stringStorage[i-4]=(char)data[i];
            }
          stringStorage[len]=0;

          dataString = String(stringStorage);
          size_t stringLength = sizeof(stringStorage);     
          processWebSocketMessageS(str, stringLength, dataString);  
        }
        else{
          dataVar = (uint16_t) strtol((const char *) &data[4], NULL, 10);  
          processWebSocketMessage(str, dataVar);
    }
}
}


void processWebSocketMessageS(String str, int stringLength, String dataString){
    if (str == "ssid"){
      uint8_t arrayPos =0;
      EEPROMposition = offsetof(storeInEEPROM, ssidStorage[0]);    
        for(int n=EEPROMposition; n < stringLength+EEPROMposition ; n++){
          EEPROM.write(n,stringStorage[arrayPos]);
          arrayPos++;
        }
        //EEPROM.write((stringLength+EEPROMposition),NULL);
        EEPROM.write((stringLength+EEPROMposition), false);
        EEPROM.commit();
        String mergedString = "HSID"+String(dataString); 
        //Serial.print("SSID "); Serial.println(mergedString);
        ws.textAll(mergedString);          
    }
    else if (str == "pass"){
      uint8_t arrayPos =0;
      EEPROMposition = offsetof(storeInEEPROM, passStorage[0]);
        for(int n= EEPROMposition; n < stringLength+EEPROMposition ; n++){
          EEPROM.write(n,stringStorage[arrayPos]);
          arrayPos++;
        } 
      //EEPROM.write((stringLength+EEPROMposition),NULL); 
      EEPROM.write((stringLength+EEPROMposition), false);   
      EEPROM.commit();
      String mergedString = "HPAS"+String(dataString); 
      //Serial.print("PASS "); Serial.println(mergedString);
      ws.textAll(mergedString);
    }   
}

void processWebSocketMessage(String str, int dataVar){
      if (str == "SHUE"){yval = dataVar; forcedColourChange = true; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, yval), yval);  EEPROM.commit();};}
      else if (str == "SBRI"){BRIGH = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, BRIGH), BRIGH);  EEPROM.commit();};}
      else if (str == "SSAT"){S = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, S), S);  EEPROM.commit();};}
      else if (str == "SPGM"){programMode = dataVar; cycleT=0;  previousMillis44 = millis();  previousMillis45 = millis(); if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, programMode), programMode);  EEPROM.commit();}; strcpy_P(buffer, (char*)pgm_read_dword(&(string_table[programMode]))); str=String(buffer);  ws.textAll("0"+str); changeState();} 
      else if (str == "SBSM"){BriSPreset = dataVar; readBriSData(BriSPreset);}
      else if (str == "SGLO"){glowON = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, glowON), glowON);  EEPROM.commit();};}
      else if (str == "SSTM"){satON = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, satON), satON);  EEPROM.commit();};}
      else if (str == "SSTN"){numsat = dataVar; if (maintainWaveForm){convSat=waveTimeS/numsat;}; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, numsat), numsat);  EEPROM.commit();};}
      else if (str == "SCOM"){colorMode = dataVar-1; procesColourMode();} // memoryByte = 'c'; processChange();} // THIS ONE
      else if (str == "SVAR"){varON = dataVar; for (int p=0; p<10; p++){if (varON == 0){yvar[p]= 0; yvarg[p]= 0;} else {yvar[p]=yvarC[p]; yvarg[p]=yvargC[p];};} if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, varON), varON);  EEPROM.commit();};}
      else if (str == "SNBR"){numbrigh = dataVar; if (maintainWaveForm){convBrigh=waveTimeBr/numbrigh;}; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, numbrigh), numbrigh);  EEPROM.commit();};}
      else if (str == "SNSP"){numsparks = dataVar;}
      else if (str == "SSBR"){BrF = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, BrF), BrF);  EEPROM.commit();};}
      else if (str == "SSSF"){SF = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, SF), SF);  EEPROM.commit();};}
      else if (str == "SDIF"){setDifference = dataVar; fillxmasArray(); diffbeat=60000/(setDifference*4*100); diffbeat2=diffbeat/2;  setDifference2 = setDifference+5; } // diff[0]=0;     x = 1;  num = 0;        diff[1]=0;     xn = 1;    num7 = 0; }
      else if (str == "SLSP"){changeSpeed = dataVar;}
      else if (str == "SNLD"){NUM_LEDS = dataVar; EEPROM.put(offsetof(storeInEEPROM, NUM_LEDS), NUM_LEDS);  EEPROM.commit();}
      else if (str == "SCAR"){arrayn = dataVar;     selectcolorArray();    newColors++;}  // THIS ONE
      else if (str == "SPAL"){gCurrentPaletteNumber = dataVar; gTargetPalette =( gGradientPalettes[gCurrentPaletteNumber] );}
      else if (str == "SGRA"){selectColor = dataVar;   dir1=1;    ymax4 = pgm_read_byte(&selectColor_data[selectColor].ymax4);  ymin4 = pgm_read_byte(&selectColor_data[selectColor].ymin4);   setDifference = pgm_read_byte(&selectColor_data[selectColor].setDifference);    yval1=ymin4;   dir0=1;   if (effect_function == *rainbow_3){setDifference = 4;  }}
      else if (str == "SNCO"){numcolor = dataVar;   newColors++;    if (whiteON){for (int t=0; t<15; t++){satval[t]=S; satval[0]=0;}}      else if (!whiteON){for (int t=0; t<15; t++){satval[t]=S;}}}
      else if (str == "SNCL"){colorlength = dataVar; newColors++;}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, colorlength), colorlength);  EEPROM.commit();};}
      else if (str == "SSCO"){z5 = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, z5), z5);  EEPROM.commit();};}
      else if (str == "SOFF"){offdis = dataVar; if (tower && (effect_function == *snow_flakes || effect_function == *snow_flakes_2)){offdisC = offdis; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, offdisC), offdisC);  EEPROM.commit();};};} //  || effect_function == *meteor
      else if (str == "SCTM"){cycleTime = dataVar*1000; if (cycleTime == 0){cycleTime = 60000;} if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, cycleTime), cycleTime);  EEPROM.commit();};}
      else if (str == "SBWS"){waveTimeBr = dataVar; convBrigh = waveTimeBr/numbrigh; if (maintainWaveForm){BPMB=60000/waveTimeBr; mergedString = "GSSBS"+String(BPMB); ws.textAll(mergedString);}; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, waveTimeBr), waveTimeBr); EEPROM.put(offsetof(storeInEEPROM, BPMB), BPMB);  EEPROM.commit();};}
      else if (str == "SSWS"){waveTimeS = dataVar; convSat = waveTimeS/numsat; if (maintainWaveForm){BPMS=60000/waveTimeS; mergedString = "GSSSS"+String(BPMS); ws.textAll(mergedString);}; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, waveTimeS), waveTimeS); EEPROM.put(offsetof(storeInEEPROM, BPMS), BPMS);  EEPROM.commit();};}      
      else if (str == "SLPS"){timefactor3 = dataVar; timefactor3 = timefactor3/100; Serial.println(timefactor3); if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, timefactor3), timefactor3);  EEPROM.commit();};}
      else if (str == "SSBS"){BPMB = dataVar; if (maintainWaveForm){waveTimeBr=60000/BPMB; convBrigh=waveTimeBr/numbrigh; mergedString = "GSBWS"+String(waveTimeBr); ws.textAll(mergedString);}; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, BPMB), BPMB);  EEPROM.put(offsetof(storeInEEPROM, waveTimeBr), waveTimeBr); EEPROM.commit(); };}      
      else if (str == "SSSS"){BPMS = dataVar; if (maintainWaveForm){waveTimeS=60000/BPMS; convSat=waveTimeS/numsat; mergedString = "GSSWS"+String(waveTimeS); ws.textAll(mergedString);}; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, BPMS), BPMS); EEPROM.put(offsetof(storeInEEPROM, waveTimeS), waveTimeS);  EEPROM.commit();};} 
      else if (str == "SOBR"){offBr = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, offBr), offBr);  EEPROM.commit();};}   
      else if (str == "SOST"){offS = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, offS), offS);  EEPROM.commit();};}    
      else if (str == "SRED"){Red = dataVar; loadHSV = true; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Red), Red);  EEPROM.commit();};} 
      else if (str == "SGRE"){Green = dataVar; loadHSV = true; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Green), Green);  EEPROM.commit();};}   
      else if (str == "SBLU"){Blue = dataVar; loadHSV = true; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Blue), Blue);  EEPROM.commit();};}    
      else if (str == "TCON"){cycle = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, cycle), cycle);  EEPROM.commit();};} // EEPROM
      else if (str == "TCFA"){fadeFirst = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, fadeFirst), fadeFirst);  EEPROM.commit();};} // EEPROM
      else if (str == "TCRA"){randomCycle = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, randomCycle), randomCycle);  EEPROM.commit();};} // EEPROM
      else if (str == "TCEX"){excludeModes = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, excludeModes), excludeModes);  EEPROM.commit();};} // EEPROM
      else if (str == "TCAC"){enableMode();}  // THIS ONE
      else if (str == "TGLI"){glitterON = dataVar; initializeGlitter();}
      else if (str == "TCAC"){enableMode();} 
//      else if (str == "TVNB"){varNumbrigh = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, varNumbrigh), varNumbrigh);  EEPROM.commit();};} // EEPROM
//      else if (str == "TVBB"){varBPMB = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, varBPMB), varBPMB);  EEPROM.commit();};} // EEPROM
//      else if (str == "TVNS"){varNumsat = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, varNumsat), varNumsat);  EEPROM.commit();};} // EEPROM
//      else if (str == "TVBS"){varBPMS = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, varBPMS), varBPMS);  EEPROM.commit();};} // EEPROM      
      else if (str == "TPMO"){personalizedModes = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, personalizedModes), personalizedModes);  EEPROM.commit();};}
      else if (str == "TSCM"){saveCurrentModeToEEPROM(); sendDelayWSMessage=true; message = 1; previousMillis14=millis(); }
      else if (str == "TRBO"){rainbowON = dataVar;}
      else if (str == "TRVO"){reverseON = dataVar;}
      else if (str == "TWHO"){whiteON = dataVar;  if (whiteON){for (int t=0; t<15; t++){satval[t]=S;   satval[0]=0;}} else if (!whiteON){for (int t=0; t<15; t++){satval[t]=S;}}}
      else if (str == "TDIR"){xdir = dataVar;  if (xdir == 1){dir = 2; dir1 = 1;} else {dir = 1; dir1 = -1;}}
      else if (str == "TSTE"){saveToEEPROM = dataVar;}
      else if (str == "TTWO"){tower = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, tower), tower);  EEPROM.commit();};} // EEPROM
      else if (str == "THSV"){updateHSV = dataVar;}
      else if (str == "TBEE"){Bees = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Bees), Bees);  EEPROM.commit();};} // EEPROM
      else if (str == "TMWF"){maintainWaveForm = dataVar;}
      else if (str == "TSET"){saveEverythingToEEPROM(); sendDelayWSMessage=true; message = 2; previousMillis14=millis();}
      else if (str == "TSED"){int eeAddress=0; EEPROM.put(eeAddress, customVar); EEPROM.commit(); FastLED.delay(1000); ESP.restart();}
      else if (str == "SETT"){EEPROM.put((offsetof(storeInEEPROM, rgbcolor)), dataVar); EEPROM.commit(); Serial.println(dataVar);}
      else if (str == "TAAM"){ActiveModesToEEPROM(); sendDelayWSMessage=true; message = 3; previousMillis14=millis();}
      else if (str == "TDAM"){DeactiveModesToEEPROM(); sendDelayWSMessage=true; message = 4; previousMillis14=millis();}
      else if (str == "SRMI"){yminrood = dataVar; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);} if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, yminrood), yminrood);  EEPROM.commit();};}
      else if (str == "SRMA"){ymaxrood = dataVar; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);} if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymaxrood), ymaxrood);  EEPROM.commit();};}
      else if (str == "SGMI"){ymingroen = dataVar; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);} if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymingroen), ymingroen);  EEPROM.commit();};}
      else if (str == "SGMA"){ymaxgroen = dataVar; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);} if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymaxgroen), ymaxgroen);  EEPROM.commit();};}
      else if (str == "SBMI"){yminblauw = dataVar; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);} if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, yminblauw), yminblauw);  EEPROM.commit();};}
      else if (str == "SBMA"){ymaxblauw = dataVar; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);} if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymaxblauw), ymaxblauw);  EEPROM.commit();};}          
      else if (str == "SYMI"){ymin = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymin), ymin);  EEPROM.commit();};}
      else if (str == "SYMA"){ymax = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymax), ymax);  EEPROM.commit();};}
      else if (str == "SMI1"){ymin1 = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymin1), ymin1);  EEPROM.commit();};}
      else if (str == "SMA1"){ymax1 = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymax1), ymax1);  EEPROM.commit();};}
      else if (str == "SMI2"){ymin2 = dataVar; dir1 = 1; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymin2), ymin2);  EEPROM.commit();};}
      else if (str == "SMA2"){ymax2 = dataVar; dir1 = 1; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymax2), ymax2);  EEPROM.commit();};}     
      else if (str == "SMI3"){ymin3 = dataVar; dir1 = 1; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymin3), ymin3);  EEPROM.commit();};}
      else if (str == "SMA3"){ymax3 = dataVar; dir1 = 1; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymax3), ymax3);  EEPROM.commit();};}
      else if (str == "SMI4"){ymin4 = dataVar; yval1=ymin4; dir0=1; dir1=1; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymin4), ymin4);  EEPROM.commit();};}
      else if (str == "SMA4"){ymax4 = dataVar; yval1=ymin4; dir0=1; dir1=1; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymax4), ymax4);  EEPROM.commit();};}
      else if (str == "SM3R"){range = dataVar; ledspercolor=NUM_LEDS/range; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, range), range);  EEPROM.commit();};}
      else if (str == "BOOT"){ESP.restart();};
}

void sendMessageToClient (int dataVar){
            if (dataVar == 0){mergedString = str+"SHUE"+String(yval);}
            else if (dataVar == 1){mergedString = str+"SBRI"+String(BRIGH);} 
            else if (dataVar == 2){mergedString = str+"SSAT"+String(S);}
            else if (dataVar == 3){mergedString = str+"SGLO"+String(glowON);}
            else if (dataVar == 4){mergedString = str+"SCOM"+String(colorMode);}
            else if (dataVar == 5){mergedString = str+"SVAR"+String(varON);}
            else if (dataVar == 6){mergedString = str+"SNBR"+String(numbrigh);}
            else if (dataVar == 7){mergedString = str+"SNSP"+String(numsparks);}
            else if (dataVar == 8){mergedString = str+"SSBR"+String(BrF);}
            else if (dataVar == 9){mergedString = str+"SDIF"+String(setDifference);}
            else if (dataVar == 10){mergedString = str+"SLSP"+String(changeSpeed);}
            else if (dataVar == 11){mergedString = str+"SCTM"+String(cycleTime/1000);}
            else if (dataVar == 12){mergedString = str+"SCAR"+String(arrayn);}
            else if (dataVar == 13){mergedString = str+"SPAL"+String(gCurrentPaletteNumber);}
            else if (dataVar == 14){mergedString = str+"SGRA"+String(selectColor);}
            else if (dataVar == 15){mergedString = str+"SNCO"+String(numcolor);}
            else if (dataVar == 16){mergedString = str+"SNCL"+String(colorlength);}
            else if (dataVar == 17){mergedString = str+"TCON"+String(cycle);}
            else if (dataVar == 18){mergedString = str+"TCFA"+String(fadeFirst);}
            else if (dataVar == 19){mergedString = str+"TCRA"+String(randomCycle);}
            else if (dataVar == 20){mergedString = str+"TCEX"+String(excludeModes);}
            else if (dataVar == 21){mergedString = str+"TGLI"+String(glitterON);}
            else if (dataVar == 22){mergedString = str+"TRBO"+String(rainbowON);}
            else if (dataVar == 23){mergedString = str+"TRVO"+String(reverseON);}
            else if (dataVar == 24){mergedString = str+"TWHO"+String(whiteON);}
            else if (dataVar == 25){mergedString = str+"TDIR"+String(xdir);}
            else if (dataVar == 26){mergedString = str+"SOFF"+String(offdis);} 
            else if (dataVar == 27){mergedString = str+"SSCO"+String(z5);}
            else if (dataVar == 28){mergedString = str+"SSTM"+String(satON);}
            else if (dataVar == 29){mergedString = str+"SSTN"+String(numsat);}
            else if (dataVar == 30){mergedString = str+"SBWS"+String(waveTimeBr);}// convBrigh = dataVar/numbrigh;}
            else if (dataVar == 31){mergedString = str+"SSWS"+String(waveTimeS);}// convSat = dataVar/numsat;}
            else if (dataVar == 32){mergedString = str+"SSBS"+String(BPMB);}      
            else if (dataVar == 33){mergedString = str+"SSSS"+String(BPMS);}                   
            else if (dataVar == 34){mergedString = str+"SLPS"+String(timefactor3*100, 0);}// timefactor3 = dataVar/100;}            
            else if (dataVar == 35){strcpy_P(buffer, (char*)pgm_read_dword(&(string_table[programMode]))); mergedString = str+"0"+String(buffer);}
            else if (dataVar == 36){mergedString = str+"SPGM"+String(programMode);} 
            else if (dataVar == 37){mergedString = str+"TCAC"+String(cmode[programMode]);} // 37
            else if (dataVar == 38){mergedString = str+"TSTE"+String(saveToEEPROM);}
            else if (dataVar == 39){mergedString = str+"TTWO"+String(tower);}
            else if (dataVar == 40){mergedString = str+"SOBR"+String(offBr);}
            else if (dataVar == 41){mergedString = str+"SOST"+String(offS);}
            else if (dataVar == 42){mergedString = str+"SRED"+String(Red);}
            else if (dataVar == 43){mergedString = str+"SGRE"+String(Green);}
            else if (dataVar == 44){mergedString = str+"SBLU"+String(Blue);}
            else if (dataVar == 45){mergedString = str+"THSV"+String(updateHSV);}   
            else if (dataVar == 46){mergedString = str+"SSSF"+String(SF);}
            else if (dataVar == 47){mergedString = str+"HNUM"+String(NUM_LEDS);} 
            else if (dataVar == 48){mergedString = str+"TMWF"+String(maintainWaveForm);} 
            else if (dataVar == 49){mergedString = str+"TBEE"+String(Bees);} 
            else if (dataVar == 50){mergedString = str+"SRMI"+String(yminrood);}
            else if (dataVar == 51){mergedString = str+"SRMA"+String(ymaxrood);}
            else if (dataVar == 52){mergedString = str+"SGMI"+String(ymingroen);}
            else if (dataVar == 53){mergedString = str+"SGMA"+String(ymaxgroen);}
            else if (dataVar == 54){mergedString = str+"SBMI"+String(yminblauw);}
            else if (dataVar == 55){mergedString = str+"SBMA"+String(ymaxblauw);}
            else if (dataVar == 56){mergedString = str+"SYMI"+String(ymin);}
            else if (dataVar == 57){mergedString = str+"SYMA"+String(ymax);}
            else if (dataVar == 58){mergedString = str+"SMI1"+String(ymin1);}
            else if (dataVar == 59){mergedString = str+"SMA1"+String(ymax1);}
            else if (dataVar == 60){mergedString = str+"SMI3"+String(ymin3);}
            else if (dataVar == 61){mergedString = str+"SMA3"+String(ymax3);}
            else if (dataVar == 62){mergedString = str+"SMI4"+String(ymin4);}
            else if (dataVar == 63){mergedString = str+"SMA4"+String(ymax4);}
            else if (dataVar == 64){mergedString = str+"SMI2"+String(ymin2);}
            else if (dataVar == 65){mergedString = str+"SMA2"+String(ymax2);}      
            else if (dataVar == 66){mergedString = str+"SM3R"+String(range);}
            else if (dataVar == 67){mergedString = str+"SBSM"+String(BriSPreset);}   
            else if (dataVar == 68){mergedString = str+"TPMO"+String(personalizedModes);}   

                                
//            else if (dataVar == 50){mergedString = str+"TVNB"+String(varNumbrigh);} 
//            else if (dataVar == 51){mergedString = str+"TVBB"+String(varBPMB);}                         
//            else if (dataVar == 52){mergedString = str+"TVNS"+String(varNumsat);} 
//            else if (dataVar == 53){mergedString = str+"TVBS"+String(varBPMS);}             
            //Serial.println(mergedString);
            ws.textAll(mergedString);                
}

void saveEverythingToEEPROM(){
EEPROM.put(offsetof(storeInEEPROM, yval), yval);
EEPROM.put(offsetof(storeInEEPROM, BRIGH[0]), BRIGH);
EEPROM.put(offsetof(storeInEEPROM, S[0]), S);
EEPROM.put(offsetof(storeInEEPROM, programMode), programMode);
EEPROM.put(offsetof(storeInEEPROM, glowON[0]), glowON);
EEPROM.put(offsetof(storeInEEPROM, satON[0]), satON);
EEPROM.put(offsetof(storeInEEPROM, numsat[0]), numsat);
EEPROM.put(offsetof(storeInEEPROM, varON), varON);
EEPROM.put(offsetof(storeInEEPROM, numbrigh[0]), numbrigh);
EEPROM.put(offsetof(storeInEEPROM, BrF[0]), BrF);
EEPROM.put(offsetof(storeInEEPROM, SF[0]), SF);
//EEPROM.put(offsetof(storeInEEPROM, colorlength), colorlength);
EEPROM.put(offsetof(storeInEEPROM, z5), z5);
EEPROM.put(offsetof(storeInEEPROM, cycleTime), cycleTime);
EEPROM.put(offsetof(storeInEEPROM, waveTimeBr[0]), waveTimeBr);
EEPROM.put(offsetof(storeInEEPROM, waveTimeS[0]), waveTimeS);  
EEPROM.put(offsetof(storeInEEPROM, timefactor3), timefactor3);
EEPROM.put(offsetof(storeInEEPROM, BPMB[0]), BPMB); 
EEPROM.put(offsetof(storeInEEPROM, BPMS[0]), BPMS);
EEPROM.put(offsetof(storeInEEPROM, offBr[0]), offBr);
EEPROM.put(offsetof(storeInEEPROM, offS[0]), offS);
EEPROM.put(offsetof(storeInEEPROM, fadeFirst), fadeFirst);
EEPROM.put(offsetof(storeInEEPROM, randomCycle), randomCycle);
EEPROM.put(offsetof(storeInEEPROM, excludeModes), excludeModes);
EEPROM.put(offsetof(storeInEEPROM, tower), tower); 
EEPROM.put(offsetof(storeInEEPROM, Bees), Bees);
EEPROM.put(offsetof(storeInEEPROM, yminrood), yminrood); 
EEPROM.put(offsetof(storeInEEPROM, ymaxrood), ymaxrood); 
EEPROM.put(offsetof(storeInEEPROM, ymingroen), ymingroen); 
EEPROM.put(offsetof(storeInEEPROM, ymaxgroen), ymaxgroen); 
EEPROM.put(offsetof(storeInEEPROM, yminblauw), yminblauw); 
EEPROM.put(offsetof(storeInEEPROM, ymaxblauw), ymaxblauw);           
EEPROM.put(offsetof(storeInEEPROM, ymin), ymin); 
EEPROM.put(offsetof(storeInEEPROM, ymax), ymax); 
EEPROM.put(offsetof(storeInEEPROM, ymin1), ymin1); 
EEPROM.put(offsetof(storeInEEPROM, ymax1), ymax1); 
EEPROM.put(offsetof(storeInEEPROM, ymin2), ymin2); 
EEPROM.put(offsetof(storeInEEPROM, ymax2), ymax2);      
EEPROM.put(offsetof(storeInEEPROM, ymin3), ymin3); 
EEPROM.put(offsetof(storeInEEPROM, ymax3), ymax3); 
EEPROM.put(offsetof(storeInEEPROM, ymin4), ymin4); 
EEPROM.put(offsetof(storeInEEPROM, ymax4), ymax4); 
EEPROM.put(offsetof(storeInEEPROM, range), range);
EEPROM.commit();
}

void handleWebsocketUpdate(){
  if (sendDelayWSMessage){
    if (millis() - previousMillis14 > 1000) {
      switch (message){
        case 1: {ws.textAll("GTSCM0");} break;
        case 2: {ws.textAll("GTSET0");} break;
        case 3: {ws.textAll("GTAAM0");} break;
        case 4: {ws.textAll("GTDAM0");} break;
      }        
      sendDelayWSMessage=false;
      message=0;
    }
  }
}

void saveCurrentModeToEEPROM(){

int offsetPosition = offsetof(storeInEEPROM, BriSPreset[0]);
EEPROM.put((offsetPosition+programMode), BriSPreset); 
offsetPosition = offsetof(storeInEEPROM, changeSpeed[0]);
EEPROM.put((offsetPosition+(programMode*sizeof(unsigned long))), changeSpeed); 
offsetPosition = offsetof(storeInEEPROM, setDifference[0]);
EEPROM.put((offsetPosition+(programMode*sizeof(int))), setDifference);
offsetPosition = offsetof(storeInEEPROM, colorMode[0]);
EEPROM.put((offsetPosition+(programMode*sizeof(int))), colorMode); 
offsetPosition = offsetof(storeInEEPROM, arrayn[0]);
EEPROM.put((offsetPosition+programMode), arrayn); 
offsetPosition = offsetof(storeInEEPROM, varON[0]);
EEPROM.put((offsetPosition+programMode), varON);
offsetPosition = offsetof(storeInEEPROM, glitterON[0]);
EEPROM.put((offsetPosition+programMode), glitterON);


if (effect_function == pers_color){
EEPROM.put(offsetof(storeInEEPROM, numcolor1), numcolor); 
}
else if (effect_function == pers_block){
EEPROM.put(offsetof(storeInEEPROM, numcolor2), numcolor); 
EEPROM.put(offsetof(storeInEEPROM, colorlengthm[2]), colorlength); 
}
else if (effect_function == static_glow && programMode == 0){
EEPROM.put(offsetof(storeInEEPROM, yval), yval);
}
else if (effect_function == static_glow && programMode == 2){
EEPROM.put(offsetof(storeInEEPROM, yvalm2), yval);
}
else if (effect_function == static_glow && programMode == 3){
EEPROM.put(offsetof(storeInEEPROM, yvalm3), yval);
}
else if (effect_function == palettes){
EEPROM.put(offsetof(storeInEEPROM, gCurrentPaletteNumber), gCurrentPaletteNumber);
}
else if (effect_function == rainbow_6){
EEPROM.put(offsetof(storeInEEPROM, colorlengthm[0]), colorlength);
}
else if (effect_function == random_string){
EEPROM.put(offsetof(storeInEEPROM, colorlengthm[1]), colorlength);
}

if (BriSPreset > 20 && BriSPreset <=25){
uint8_t offsetInArray = BriSPreset - 20;

offsetPosition = offsetof(storeInEEPROM, waveTimeBr[0]);
EEPROM.put((offsetPosition+(offsetInArray*sizeof(unsigned long))), waveTimeBr); 
offsetPosition = offsetof(storeInEEPROM, waveTimeS[0]);
EEPROM.put((offsetPosition+(offsetInArray*sizeof(unsigned long))), waveTimeS);
offsetPosition = offsetof(storeInEEPROM, BPMB[0]);
EEPROM.put((offsetPosition+offsetInArray), BPMB);
offsetPosition = offsetof(storeInEEPROM, BPMS[0]);
EEPROM.put((offsetPosition+offsetInArray), BPMS);
offsetPosition = offsetof(storeInEEPROM, BRIGH[0]);
EEPROM.put((offsetPosition+offsetInArray), BRIGH);
offsetPosition = offsetof(storeInEEPROM, S[0]);
EEPROM.put((offsetPosition+offsetInArray), S);
offsetPosition = offsetof(storeInEEPROM, offBr[0]);
EEPROM.put((offsetPosition+offsetInArray), offBr);
offsetPosition = offsetof(storeInEEPROM, offS[0]);
EEPROM.put((offsetPosition+offsetInArray), offS);
offsetPosition = offsetof(storeInEEPROM, glowON[0]);
EEPROM.put((offsetPosition+offsetInArray), glowON);
offsetPosition = offsetof(storeInEEPROM, satON[0]);
EEPROM.put((offsetPosition+offsetInArray), satON);
offsetPosition = offsetof(storeInEEPROM, BrF[0]);
EEPROM.put((offsetPosition+offsetInArray), BrF);
offsetPosition = offsetof(storeInEEPROM, SF[0]);
EEPROM.put((offsetPosition+offsetInArray), SF);
offsetPosition = offsetof(storeInEEPROM, numbrigh[0]);
EEPROM.put((offsetPosition+offsetInArray), numbrigh);
offsetPosition = offsetof(storeInEEPROM, numsat[0]);
EEPROM.put((offsetPosition+offsetInArray), numsat);
}
EEPROM.commit();
}

void ActiveModesToEEPROM(){
int offsetPosition = offsetof(storeInEEPROM, cmode[0]); 
for (int m = 0; m < modeCount; m++){
EEPROM.put((offsetPosition+m), 1);
cmode[m]=true;    
}
EEPROM.commit();
}

void DeactiveModesToEEPROM(){
programMode = EEPROM.read(offsetof(storeInEEPROM, programMode));  
int offsetPosition = offsetof(storeInEEPROM, cmode[0]); 
for (int m = 0; m < modeCount; m++){
  if (m == programMode){
  EEPROM.put(offsetPosition, 1); 
  cmode[m]=true;   
  }
  else{
  EEPROM.put((offsetPosition+m), 0);
  cmode[m]=false;
  }
}
EEPROM.commit();
}

void enableMode(){
  #ifdef ESP8266
    int offsetPosition = offsetof(storeInEEPROM, cmode[0]);
    if (cmode[programMode]){cmode[programMode]=false; EEPROM.put((offsetPosition+programMode), false);}
    else if (!cmode[programMode]){cmode[programMode]=true; EEPROM.put((offsetPosition+programMode), true);}
    EEPROM.commit();
      
  #else
    int offsetPosition = offsetof(storeInEEPROM, cmode[0]);  
    if (cmode[programMode]){cmode[programMode]=false; EEPROM.writeByte((offsetPosition+programMode), false);}
    else if (!cmode[programMode]){cmode[programMode]=true; EEPROM.writeByte((offsetPosition+programMode), true);}
    EEPROM.commit();
  #endif
}


void loadPersonalSettings(){
int offsetPosition = (offsetof(storeInEEPROM, BriSPreset[0])) + programMode;  
BriSPreset = EEPROM.read(offsetPosition);
offsetPosition = (offsetof(storeInEEPROM, arrayn[0])) + programMode; 
arrayn = EEPROM.read(offsetPosition);
offsetPosition = (offsetof(storeInEEPROM, varON[0])) + programMode; 
varON = EEPROM.read(offsetPosition);
offsetPosition = (offsetof(storeInEEPROM, glitterON[0])) + programMode; 
glitterON = EEPROM.read(offsetPosition);

#ifdef ESP8266 
offsetPosition = offsetof(storeInEEPROM, changeSpeed[0]) + (programMode*sizeof(unsigned long));  
EEPROM.get(offsetPosition, changeSpeed);
offsetPosition = offsetof(storeInEEPROM, setDifference[0]) + (programMode*sizeof(int));  
EEPROM.get(offsetPosition, setDifference);
offsetPosition = offsetof(storeInEEPROM, colorMode[0]) + (programMode*sizeof(int));  
EEPROM.get(offsetPosition, colorMode);
#else
offsetPosition = offsetof(storeInEEPROM, changeSpeed[0]) + (programMode*sizeof(unsigned long));  
changeSpeed = EEPROM.readLong(offsetPosition); 

offsetPosition = offsetof(storeInEEPROM, setDifference[0]) + (programMode*sizeof(int));
setDifference = EEPROM.readInt(offsetPosition);

offsetPosition = offsetof(storeInEEPROM, colorMode[0]) + (programMode*sizeof(int));  
colorMode = EEPROM.readInt(offsetPosition);
#endif

if (effect_function == pers_color){
numcolor = EEPROM.read(offsetof(storeInEEPROM, numcolor1));
}
else if (effect_function == pers_block){
numcolor = EEPROM.read(offsetof(storeInEEPROM, numcolor2));
colorlength = EEPROM.read(offsetof(storeInEEPROM, colorlengthm[2]));
}
else if (effect_function == static_glow && programMode == 0){
yval = EEPROM.read(offsetof(storeInEEPROM, yval));
}
else if (effect_function == static_glow && programMode == 2){
yval = EEPROM.read(offsetof(storeInEEPROM, yvalm2));
}
else if (effect_function == static_glow && programMode == 3){
yval = EEPROM.read(offsetof(storeInEEPROM, yvalm3));
}
else if (effect_function == palettes){
gCurrentPaletteNumber = EEPROM.read(offsetof(storeInEEPROM, gCurrentPaletteNumber));
}
else if (effect_function == rainbow_6){
colorlength = EEPROM.read(offsetof(storeInEEPROM, colorlengthm[0]));
}
else if (effect_function == random_string){
colorlength = EEPROM.read(offsetof(storeInEEPROM, colorlengthm[1]));
}

selectcolorArray();
readBriSData(BriSPreset);
}

void readBriSData(byte preset)
{
    if (preset == 0){
      #ifdef ESP8266  
      // EEPROM.get(offsetof(storeInEEPROM, BPMB), BPMB);
      // EEPROM.get(offsetof(storeInEEPROM, BPMS), BPMS);
      EEPROM.get(offsetof(storeInEEPROM, waveTimeBr[0]), waveTimeBr);
      EEPROM.get(offsetof(storeInEEPROM, waveTimeS[0]), waveTimeS);
      #else
      waveTimeBr = EEPROM.readLong(offsetof(storeInEEPROM, waveTimeBr[0]));
      waveTimeS = EEPROM.readLong(offsetof(storeInEEPROM, waveTimeS[0]));
      #endif
      BPMB = EEPROM.read(offsetof(storeInEEPROM, BPMB[0]));
      BPMS = EEPROM.read(offsetof(storeInEEPROM, BPMS[0]));
      BRIGH = EEPROM.read(offsetof(storeInEEPROM, BRIGH[0]));
      offBr = EEPROM.read(offsetof(storeInEEPROM, offBr[0]));
      glowON = EEPROM.read(offsetof(storeInEEPROM, glowON[0]));
      BrF = EEPROM.read(offsetof(storeInEEPROM, BrF[0]));
      offS = EEPROM.read(offsetof(storeInEEPROM, offS[0]));
      S = EEPROM.read(offsetof(storeInEEPROM, S[0]));
      SF = EEPROM.read(offsetof(storeInEEPROM, SF[0]));
      satON = EEPROM.read(offsetof(storeInEEPROM, satON[0]));
      numsat = EEPROM.read(offsetof(storeInEEPROM, numsat[0]));
      numbrigh = EEPROM.read(offsetof(storeInEEPROM, numbrigh[0]));
    }
    else if (preset <= 20) {
      BRIGH = pgm_read_byte(&selectPresetB_data[preset].BRIGH);
      BrF = pgm_read_byte(&selectPresetB_data[preset].BrF);
      glowON = pgm_read_byte(&selectPresetB_data[preset].glowON);
      offBr = pgm_read_byte(&selectPresetB_data[preset].offBr);
      numbrigh = pgm_read_byte(&selectPresetB_data[preset].numbrigh);
      BPMB = pgm_read_byte(&selectPresetB_data[preset].BPMB);
      waveTimeBr = pgm_read_dword(&selectPresetB_data[preset].waveTimeBr);
      S = pgm_read_byte(&selectPresetB_data[preset].S);
      SF = pgm_read_byte(&selectPresetB_data[preset].SF);
      satON = pgm_read_byte(&selectPresetB_data[preset].satON);
      offS = pgm_read_byte(&selectPresetB_data[preset].offS);
      numsat = pgm_read_byte(&selectPresetB_data[preset].numsat);
      BPMS = pgm_read_byte(&selectPresetB_data[preset].BPMS);
      waveTimeS = pgm_read_dword(&selectPresetB_data[preset].waveTimeS);
      //Serial.print("wavetimeBR :"); Serial.println(waveTimeBr);
      //Serial.print("wavetimeS :"); Serial.println(waveTimeS);
    }
    else if (preset > 20 && preset <= 25){
      uint8_t offsetInArray = preset - 20;
      // Serial.println(offsetInArray);
      int offsetPosition = (offsetof(storeInEEPROM, BRIGH[0])) + offsetInArray; 
      BRIGH = EEPROM.read(offsetPosition);
      offsetPosition = (offsetof(storeInEEPROM, S[0])) + offsetInArray; 
      S = EEPROM.read(offsetPosition);
      offsetPosition = (offsetof(storeInEEPROM, offBr[0])) + offsetInArray; 
      offBr = EEPROM.read(offsetPosition);   
      offsetPosition = (offsetof(storeInEEPROM, offS[0])) + offsetInArray; 
      offS = EEPROM.read(offsetPosition);        
      offsetPosition = (offsetof(storeInEEPROM, BrF[0])) + offsetInArray; 
      BrF = EEPROM.read(offsetPosition);   
      offsetPosition = (offsetof(storeInEEPROM, SF[0])) + offsetInArray; 
      SF = EEPROM.read(offsetPosition);  
      offsetPosition = (offsetof(storeInEEPROM, glowON[0])) + offsetInArray; 
      glowON = EEPROM.read(offsetPosition);   
      offsetPosition = (offsetof(storeInEEPROM, satON[0])) + offsetInArray; 
      satON = EEPROM.read(offsetPosition);    
      offsetPosition = (offsetof(storeInEEPROM, numbrigh[0])) + offsetInArray; 
      numbrigh = EEPROM.read(offsetPosition);  
      offsetPosition = (offsetof(storeInEEPROM, numsat[0])) + offsetInArray; 
      numsat = EEPROM.read(offsetPosition);  
      offsetPosition = (offsetof(storeInEEPROM, BPMB[0])) + offsetInArray; 
      BPMB = EEPROM.read(offsetPosition); 
      offsetPosition = (offsetof(storeInEEPROM, BPMS[0])) + offsetInArray; 
      BPMS = EEPROM.read(offsetPosition);      

      #ifdef ESP8266  
      offsetPosition = offsetof(storeInEEPROM, waveTimeBr[0]) + (offsetInArray*sizeof(unsigned long));
      EEPROM.get(offsetPosition, waveTimeBr);  
      offsetPosition = offsetof(storeInEEPROM, waveTimeS[0]) + (offsetInArray*sizeof(unsigned long)); 
      EEPROM.get(offsetPosition, waveTimeS);
      #else
      offsetPosition = offsetof(storeInEEPROM, waveTimeBr[0]) + (offsetInArray*sizeof(unsigned long));  
      waveTimeBr = EEPROM.readLong(offsetPosition);
      offsetPosition = offsetof(storeInEEPROM, waveTimeS[0]) + (offsetInArray*sizeof(unsigned long)); 
      waveTimeS = EEPROM.readLong(offsetPosition);
      #endif        
    }
    convBrigh = waveTimeBr/numbrigh;
    convSat = waveTimeS/numsat;
}