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

        DEBUG_PRINTLN(F("received JSON message: "));
        for (int i = 0; i < len; i++){
        //strval[i]=(char)data[i];    
        DEBUG_PRINT((char)data[i]);
        }
        DEBUG_PRINTLN(" ");

        //const uint8_t size = JSON_OBJECT_SIZE(1);
        StaticJsonDocument<200> json;
        DeserializationError err = deserializeJson(json, data);
        if (err) {
            DEBUG_PRINT(F("deserializeJson() failed with code "));
            DEBUG_PRINTLN(err.c_str());
            return;
        }

      if (json.containsKey("TLSE")){sendProgramInfo(); notifyClientsSingleObject("TLSE", false);}
      
      else if (json.containsKey("ssid")){String wifiID = json["ssid"]; EEPROMposition = offsetof(storeInEEPROM, ssidStorage[0]); writeStringToEEPROM(EEPROMposition, wifiID); notifyClientsSingleString("wifiID", wifiID);}
      else if (json.containsKey("pass")){String wifiPASS = json["pass"]; EEPROMposition = offsetof(storeInEEPROM, passStorage[0]); writeStringToEEPROM(EEPROMposition, wifiPASS); notifyClientsSingleString("wifiPASS", wifiPASS);}
      
      else if (json.containsKey("SHUE")){yval = json["SHUE"]; forcedColourChange = true; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, yval), yval);  EEPROM.commit();};}
      else if (json.containsKey("SBRI")){BRIGH = json["SBRI"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, BRIGH), BRIGH);  EEPROM.commit();};}
      else if (json.containsKey("SSAT")){S = json["SSAT"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, S), S);  EEPROM.commit();};}
      else if (json.containsKey("SPGM")){programMode = json["SPGM"]; cycleT=0;  previousMillis44 = millis();  previousMillis45 = millis(); if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, programMode), programMode);  EEPROM.commit();};  changeState();} 
      else if (json.containsKey("SBSM")){BriSPreset = json["SBSM"]; readBriSData(BriSPreset); sendProgramInfo();}
      else if (json.containsKey("SGLO")){glowON = json["SGLO"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, glowON), glowON);  EEPROM.commit();};}
      else if (json.containsKey("SSTM")){satON = json["SSTM"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, satON), satON);  EEPROM.commit();};}

      else if (json.containsKey("SSTN")){numsat = json["SSTN"]; if (maintainWaveForm){convSat=waveTimeS/numsat;}; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, numsat), numsat);  EEPROM.commit();};}
      else if (json.containsKey("SCOM")){colorMode = json["SCOM"]; colorMode = colorMode-1; procesColourMode();} // memoryByte = 'c'; processChange();} // THIS ONE
      else if (json.containsKey("SVAR")){varON = json["SVAR"]; for (int p=0; p<10; p++){if (varON == 0){yvar[p]= 0; yvarg[p]= 0;} else {yvar[p]=yvarC[p]; yvarg[p]=yvargC[p];};} if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, varON), varON);  EEPROM.commit();};}
      else if (json.containsKey("SNBR")){numbrigh = json["SNBR"]; if (maintainWaveForm){convBrigh=waveTimeBr/numbrigh;}; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, numbrigh), numbrigh);  EEPROM.commit();};}
      else if (json.containsKey("SNSP")){numsparks = json["SNSP"];}
      
      else if (json.containsKey("SSBR")){BrF = json["SSBR"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, BrF), BrF);  EEPROM.commit();};}
      else if (json.containsKey("SSSF")){SF = json["SSSF"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, SF), SF);  EEPROM.commit();};}
      else if (json.containsKey("SDIF")){setDifference = json["SDIF"]; fillxmasArray(); diffbeat=60000/(setDifference*4*100); diffbeat2=diffbeat/2;  setDifference2 = setDifference+5;} // diff[0]=0;     x = 1;  num = 0;        diff[1]=0;     xn = 1;    num7 = 0; }
      else if (json.containsKey("SLSP")){changeSpeed = json["SLSP"];}


      else if (json.containsKey("SNLD")){NUM_LEDS = json["SNLD"]; EEPROM.put(offsetof(storeInEEPROM, NUM_LEDS), NUM_LEDS);  EEPROM.commit();}
      else if (json.containsKey("SCAR")){arrayn = json["SCAR"];     selectcolorArray();    newColors++;}  // THIS ONE
      else if (json.containsKey("SPAL")){gCurrentPaletteNumber = json["SPAL"]; gTargetPalette =( gGradientPalettes[gCurrentPaletteNumber] );}
      else if (json.containsKey("SGRA")){selectColor = json["SGRA"];   dir1=1;    ymax4 = pgm_read_byte(&selectColor_data[selectColor].ymax4);  ymin4 = pgm_read_byte(&selectColor_data[selectColor].ymin4);   setDifference = pgm_read_byte(&selectColor_data[selectColor].setDifference);    yval1=ymin4;   dir0=1;   if (effect_function == *rainbow_3){setDifference = 4;  }}
      else if (json.containsKey("SNCO")){numcolor = json["SNCO"];   newColors++;    if (whiteON){for (int t=0; t<15; t++){satval[t]=S; satval[0]=0;}}      else if (!whiteON){for (int t=0; t<15; t++){satval[t]=S;}}}
      else if (json.containsKey("SNCL")){colorlength = json["SNCL"]; newColors++;}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, colorlength), colorlength);  EEPROM.commit();};}
      else if (json.containsKey("SSCO")){z5 = json["SSCO"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, z5), z5);  EEPROM.commit();};}
      else if (json.containsKey("SOFF")){offdis = json["SOFF"]; if (tower && (effect_function == *snow_flakes || effect_function == *snow_flakes_2 || effect_function == *snow_flakesR)){offdisC = offdis; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, offdisC), offdisC);  EEPROM.commit();};};} //  || effect_function == *meteor
      else if (json.containsKey("SCTM")){cycleTime = json["SCTM"]; cycleTime = cycleTime*1000; if (cycleTime == 0){cycleTime = 60000;} if (saveToEEPROM){saveCycleParamToEEPROM();};}
      else if (json.containsKey("SBWS")){waveTimeBr = json["SBWS"]; convBrigh = waveTimeBr/numbrigh; if (maintainWaveForm){BPMB=60000/waveTimeBr; notifyClientsSingleObjectByte("SSBS", BPMB);}; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, waveTimeBr), waveTimeBr); EEPROM.put(offsetof(storeInEEPROM, BPMB), BPMB);  EEPROM.commit();};}
      else if (json.containsKey("SSWS")){waveTimeS = json["SSWS"]; convSat = waveTimeS/numsat; if (maintainWaveForm){BPMS=60000/waveTimeS; notifyClientsSingleObjectByte("SSSS", BPMS);}; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, waveTimeS), waveTimeS); EEPROM.put(offsetof(storeInEEPROM, BPMS), BPMS);  EEPROM.commit();};}      
      else if (json.containsKey("SLPS")){timefactor3 = json["SLPS"]; timefactor3 = timefactor3/100; Serial.println(timefactor3); if (saveToEEPROM){saveCycleParamToEEPROM();};}
      else if (json.containsKey("SSBS")){BPMB = json["SSBS"]; if (maintainWaveForm){waveTimeBr=60000/BPMB; convBrigh=waveTimeBr/numbrigh; notifyClientsSingleObjectInt("SBWS", waveTimeBr);}; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, BPMB), BPMB);  EEPROM.put(offsetof(storeInEEPROM, waveTimeBr), waveTimeBr); EEPROM.commit(); };}      
      else if (json.containsKey("SSSS")){BPMS = json["SSSS"]; if (maintainWaveForm){waveTimeS=60000/BPMS; convSat=waveTimeS/numsat; notifyClientsSingleObjectInt("SSWS", waveTimeS);}; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, BPMS), BPMS); EEPROM.put(offsetof(storeInEEPROM, waveTimeS), waveTimeS);  EEPROM.commit();};} 
      else if (json.containsKey("SOBR")){offBr = json["SOBR"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, offBr), offBr);  EEPROM.commit();};}   
      else if (json.containsKey("SOST")){offS = json["SOST"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, offS), offS);  EEPROM.commit();};}    
      else if (json.containsKey("SRED")){Red = json["SRED"]; loadHSV = true; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Red), Red);  EEPROM.commit();};} 
      else if (json.containsKey("SGRE")){Green = json["SGRE"]; loadHSV = true; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Green), Green);  EEPROM.commit();};}   
      else if (json.containsKey("SBLU")){Blue = json["SBLU"]; loadHSV = true; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Blue), Blue);  EEPROM.commit();};}    
      else if (json.containsKey("TCON")){cycle = json["TCON"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, cycle), cycle);  EEPROM.commit();};} // EEPROM
      else if (json.containsKey("TCPM")){saveForAllModes = json["TCPM"];} // EEPROM
      else if (json.containsKey("TCFA")){fadeFirst = json["TCFA"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, fadeFirst), fadeFirst);  EEPROM.commit();};} // EEPROM
      else if (json.containsKey("TCRA")){randomCycle = json["TCRA"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, randomCycle), randomCycle);  EEPROM.commit();};} // EEPROM
      else if (json.containsKey("TCEX")){excludeModes = json["TCEX"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, excludeModes), excludeModes);  EEPROM.commit();};} // EEPROM
      //else if (json.containsKey("TCAC")){enableMode();}  // THIS ONE
      else if (json.containsKey("TGLI")){glitterON = json["TGLI"]; initializeGlitter();}
      else if (json.containsKey("TCAC")){enableMode();} 
//      else if (str == "TVNB"){varNumbrigh = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, varNumbrigh), varNumbrigh);  EEPROM.commit();};} // EEPROM
//      else if (str == "TVBB"){varBPMB = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, varBPMB), varBPMB);  EEPROM.commit();};} // EEPROM
//      else if (str == "TVNS"){varNumsat = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, varNumsat), varNumsat);  EEPROM.commit();};} // EEPROM
//      else if (str == "TVBS"){varBPMS = dataVar; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, varBPMS), varBPMS);  EEPROM.commit();};} // EEPROM      
      else if (json.containsKey("TPMO")){personalizedModes = json["TPMO"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, personalizedModes), personalizedModes);  EEPROM.commit();};}
      else if (json.containsKey("TSCM")){saveCurrentModeToEEPROM(); sendDelayWSMessage=true; message = 1; previousMillis14=millis(); }
      else if (json.containsKey("TRBO")){rainbowON = json["TRBO"];}
      else if (json.containsKey("TRVO")){reverseON = json["TRVO"];}
      else if (json.containsKey("TWHO")){whiteON = json["TWHO"];  if (whiteON){for (int t=0; t<15; t++){satval[t]=S;   satval[0]=0;}} else if (!whiteON){for (int t=0; t<15; t++){satval[t]=S;}}}
      else if (json.containsKey("TDIR")){xdir = json["TDIR"];  if (xdir == 1){dir = 2; dir1 = 1;} else {dir = 1; dir1 = -1;}}
      else if (json.containsKey("TSTE")){saveToEEPROM = json["TSTE"];}
      else if (json.containsKey("TTWO")){tower = json["TTWO"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, tower), tower);  EEPROM.commit();};} // EEPROM
      else if (json.containsKey("THSV")){updateHSV = json["THSV"];}
      else if (json.containsKey("TBEE")){Bees = json["TBEE"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Bees), Bees);  EEPROM.commit();};} // EEPROM
      else if (json.containsKey("TMWF")){maintainWaveForm = json["TMWF"];}
      else if (json.containsKey("TSET")){saveEverythingToEEPROM(); sendDelayWSMessage=true; message = 2; previousMillis14=millis();}
      else if (json.containsKey("TSED")){int eeAddress=0; EEPROM.put(eeAddress, customVar); EEPROM.commit(); FastLED.delay(1000); ESP.restart();}
      else if (json.containsKey("SETT")){EEPROM.put((offsetof(storeInEEPROM, rgbcolor)), json["SSET"]); EEPROM.commit(); RGBCOLOR = json["SETT"]; Serial.println(RGBCOLOR);}
      else if (json.containsKey("TAAM")){ActiveModesToEEPROM(); sendDelayWSMessage=true; message = 3; previousMillis14=millis();}
      else if (json.containsKey("TDAM")){DeactiveModesToEEPROM(); sendDelayWSMessage=true; message = 4; previousMillis14=millis();}
      else if (json.containsKey("SRMI")){yminrood = json["SRMI"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);} if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, yminrood), yminrood);  EEPROM.commit();};}
      else if (json.containsKey("SRMA")){ymaxrood = json["SRMA"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);} if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymaxrood), ymaxrood);  EEPROM.commit();};}
      else if (json.containsKey("SGMI")){ymingroen = json["SGMI"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);} if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymingroen), ymingroen);  EEPROM.commit();};}
      else if (json.containsKey("SGMA")){ymaxgroen = json["SGMA"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);} if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymaxgroen), ymaxgroen);  EEPROM.commit();};}
      else if (json.containsKey("SBMI")){yminblauw = json["SBMI"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);} if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, yminblauw), yminblauw);  EEPROM.commit();};}
      else if (json.containsKey("SBMA")){ymaxblauw = json["SBMA"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);} if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymaxblauw), ymaxblauw);  EEPROM.commit();};}          
      else if (json.containsKey("SYMI")){ymin = json["SYMI"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymin), ymin);  EEPROM.commit();};}
      else if (json.containsKey("SYMA")){ymax = json["SYMA"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymax), ymax);  EEPROM.commit();};}
      else if (json.containsKey("SMI1")){ymin1 = json["SMI1"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymin1), ymin1);  EEPROM.commit();};}
      else if (json.containsKey("SMA1")){ymax1 = json["SMA1"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymax1), ymax1);  EEPROM.commit();};}
      else if (json.containsKey("SMI2")){ymin2 = json["SMI2"]; dir1 = 1; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymin2), ymin2);  EEPROM.commit();};}
      else if (json.containsKey("SMA2")){ymax2 = json["SMA2"]; dir1 = 1; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymax2), ymax2);  EEPROM.commit();};}     
      else if (json.containsKey("SMI3")){ymin3 = json["SMI3"]; dir1 = 1; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymin3), ymin3);  EEPROM.commit();};}
      else if (json.containsKey("SMA3")){ymax3 = json["SMA3"]; dir1 = 1; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymax3), ymax3);  EEPROM.commit();};}
      else if (json.containsKey("SMI4")){ymin4 = json["SMI4"]; yval1=ymin4; dir0=1; dir1=1; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymin4), ymin4);  EEPROM.commit();};}
      else if (json.containsKey("SMA4")){ymax4 = json["SMA4"]; yval1=ymin4; dir0=1; dir1=1; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymax4), ymax4);  EEPROM.commit();};}
      else if (json.containsKey("SM3R")){range = json["SM3R"]; ledspercolor=NUM_LEDS/range; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, range), range);  EEPROM.commit();};}
      else if (json.containsKey("BOOT")){ESP.restart();};
      notifyClientsSingleObject("recMsg", true);
    }
}

void sendProgramInfo(){
//StaticJsonDocument<2000> doc; // 2500
DynamicJsonDocument doc(2000);
    strcpy_P(buffer, (char*)pgm_read_dword(&(string_table[programMode])));
    doc["progn"] = buffer;
    doc["SHUE"] = yval;
    doc["SBRI"] = BRIGH; 
    doc["SSAT"] = S;
    doc["SGLO"] = glowON;
    doc["SCOM"] = colorMode;
    doc["SVAR"] = varON;
    doc["SNBR"] = numbrigh;
    doc["SNSP"] = numsparks;
    doc["SSBR"] = BrF;
    doc["SDIF"] = setDifference;
    doc["SLSP"] = changeSpeed;
    doc["SCTM"] = cycleTime/1000;
    doc["SCAR"] = arrayn;
    doc["SPAL"] = gCurrentPaletteNumber;
    doc["SGRA"] = selectColor;
    doc["SNCO"] = numcolor;
    doc["SNCL"] = colorlength;
    doc["TCON"] = cycle;
    doc["TCFA"] = fadeFirst;
    doc["TCRA"] = randomCycle;
    doc["TCEX"] = excludeModes;
    doc["TGLI"] = glitterON;
    doc["TRBO"] = rainbowON;
    doc["TRVO"] = reverseON;
    doc["TWHO"] = whiteON;
    doc["TDIR"] = xdir;
    doc["SOFF"] = offdis; 
    doc["SSCO"] = z5;
    doc["SSTM"] = satON;
    doc["SSTN"] = numsat;
    doc["SBWS"] = waveTimeBr;// convBrigh = dataVar/numbrigh;}
    doc["SSWS"] = waveTimeS;// convSat = dataVar/numsat;}
    doc["SSBS"] = BPMB;      
    doc["SSSS"] = BPMS;                   
    doc["SLPS"] = timefactor3*100;// timefactor3 = dataVar/100;}            
    doc["SPGM"] = programMode; 
    doc["TCAC"] = cmode[programMode]; // 37
    doc["TSTE"] = saveToEEPROM;
    doc["TTWO"] = tower;
    doc["SOBR"] = offBr;
    doc["SOST"] = offS;
    doc["SRED"] = Red;
    doc["SGRE"] = Green;
    doc["SBLU"] = Blue;
    doc["THSV"] = updateHSV;   
    doc["SSSF"] = SF;
    doc["HNUM"] = NUM_LEDS; 
    doc["TMWF"] = maintainWaveForm; 
    doc["TBEE"] = Bees; 
    doc["SRMI"] = yminrood;
    doc["SRMA"] = ymaxrood;
    doc["SGMI"] = ymingroen;
    doc["SGMA"] = ymaxgroen;
    doc["SBMI"] = yminblauw;
    doc["SBMA"] = ymaxblauw;
    doc["SYMI"] = ymin;
    doc["SYMA"] = ymax;
    doc["SMI1"] = ymin1;
    doc["SMA1"] = ymax1;
    doc["SMI3"] = ymin3;
    doc["SMA3"] = ymax3;
    doc["SMI4"] = ymin4;
    doc["SMA4"] = ymax4;
    doc["SMI2"] = ymin2;
    doc["SMA2"] = ymax2;      
    doc["SM3R"] = range;
    doc["SBSM"] = BriSPreset;   
    doc["TPMO"] = personalizedModes;   
    doc["TCPM"] = saveForAllModes;
    doc["HCOL"] = RGBCOLOR; 

                                
char data[2000]; // 2500
size_t len = serializeJson(doc, data);

    DEBUG_PRINT(F("sending JSON message: ")); DEBUG_PRINTLN(len);
    for (int i = 0; i < len;  i++){
    DEBUG_PRINT(data[i]);
    }
    DEBUG_PRINTLN(" ");

ws.textAll(data, len);
return;
}

void writeStringToEEPROM(int addrOffset, const String &strToWrite){
  if (strToWrite == NULL){
      //Serial.println("this string is empty");
  }
  else{  
    byte length = strToWrite.length();
    //Serial.print("len "); Serial.println(len);
    //Serial.print("addr offset ");Serial.println(addrOffset);
    //EEPROM.write(addrOffset, len);
    for (int i = 0; i < length; i++){
        //EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
        EEPROM.write(addrOffset + i, strToWrite[i]);
        DEBUG_PRINT(strToWrite[i]);
    }
    DEBUG_PRINTLN(" ");
    EEPROM.write((length+addrOffset),'\0');
    //EEPROM.write((length+addrOffset),NULL);
    EEPROM.commit();
  }
return;
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
// EEPROM.put(offsetof(storeInEEPROM, timefactor3[0]), timefactor3[0]);
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
        case 1: {notifyClientsSingleObject("TSCM", false);} break; // ws.textAll("GTSCM0");} break;
        case 2: {notifyClientsSingleObject("TSET", false);} break; //ws.textAll("GTSET0");} break;
        case 3: {notifyClientsSingleObject("TAAM", false);} break; //ws.textAll("GTAAM0");} break;
        case 4: {notifyClientsSingleObject("TDAM", false);} break; //ws.textAll("GTDAM0");} break;
      }        
      sendDelayWSMessage=false;
      message=0;
    }
  }
}

void saveCycleParamToEEPROM(){
if (saveForAllModes){
  int offsetPositionCt = offsetof(storeInEEPROM, cycleTime[0]); 
  int offsetPositionTf = offsetof(storeInEEPROM, timefactor3[0]); 
  for (int m = 0; m < modeCount; m++){
  EEPROM.put((offsetPositionCt+(m*sizeof(unsigned long))), cycleTime);
  EEPROM.put((offsetPositionTf+(m*sizeof(float))), timefactor3); 
  }
}  
else {
uint8_t offsetInArray = programMode;
int offsetPosition = offsetof(storeInEEPROM, cycleTime[0]);
EEPROM.put((offsetPosition+(offsetInArray*sizeof(unsigned long))), cycleTime); 
offsetPosition = offsetof(storeInEEPROM, timefactor3[0]);
EEPROM.put((offsetPosition+(offsetInArray*sizeof(float))), timefactor3);
}
EEPROM.commit();
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
offsetPosition = offsetof(storeInEEPROM, numsparks[0]);
EEPROM.put((offsetPosition+programMode), numsparks); 
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

uint8_t offsetInArray = BriSPreset;
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
varON = EEPROM.read(offsetPosition); for (int p=0; p<10; p++){if (varON == 0){yvar[p]= 0; yvarg[p]= 0;} else {yvar[p]=yvarC[p]; yvarg[p]=yvargC[p];};}
offsetPosition = (offsetof(storeInEEPROM, numsparks[0])) + programMode; 
numsparks = EEPROM.read(offsetPosition);
offsetPosition = (offsetof(storeInEEPROM, glitterON[0])) + programMode; 
glitterON = EEPROM.read(offsetPosition);

#ifdef ESP8266 
offsetPosition = offsetof(storeInEEPROM, changeSpeed[0]) + (programMode*sizeof(unsigned long));  
EEPROM.get(offsetPosition, changeSpeed);
offsetPosition = offsetof(storeInEEPROM, cycleTime[0]) + (programMode*sizeof(unsigned long));  
EEPROM.get(offsetPosition, cycleTime);
offsetPosition = offsetof(storeInEEPROM, timefactor3[0]) + (programMode*sizeof(float));  
EEPROM.get(offsetPosition, timefactor3);
offsetPosition = offsetof(storeInEEPROM, setDifference[0]) + (programMode*sizeof(int));  
EEPROM.get(offsetPosition, setDifference);
offsetPosition = offsetof(storeInEEPROM, colorMode[0]) + (programMode*sizeof(int));  
EEPROM.get(offsetPosition, colorMode);
#else
offsetPosition = offsetof(storeInEEPROM, changeSpeed[0]) + (programMode*sizeof(unsigned long));  
changeSpeed = EEPROM.readLong(offsetPosition); 

offsetPosition = offsetof(storeInEEPROM, cycleTime[0]) + (programMode*sizeof(unsigned long));  
cycleTime = EEPROM.readLong(offsetPosition); 

offsetPosition = offsetof(storeInEEPROM, timefactor3[0]) + (programMode*sizeof(float));  
timefactor3 = EEPROM.readFloat(offsetPosition); 

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
  if (!personalizedModes){
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
  }
  else if (personalizedModes){
      uint8_t offsetInArray = preset;
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




void notifyClientsSingleString(String object, String &message) {
        // String objectString = object;
    //const uint8_t size = JSON_OBJECT_SIZE(1);
    StaticJsonDocument<50> doc;
    String key = object;
    String Value = message;
    doc[key] = Value; 

    //serializeJson(doc, Serial);

    char data[50];
    size_t len = serializeJson(doc, data);
    DEBUG_PRINTLN(F("sending JSON string: "));
        for (int i = 0; i < len;  i++){
        DEBUG_PRINT(data[i]);
        }
        DEBUG_PRINTLN(F(" "));
    ws.textAll(data, len); 

}

void notifyClientsSingleObject(String object, boolean value) {
    StaticJsonDocument<50> doc;
    String key = object;
    boolean Value = value;
    doc[key] = Value; 

    char data[50];
    size_t len = serializeJson(doc, data);
    DEBUG_PRINTLN(F("sending JSON boolean: "));
        for (int i = 0; i < len;  i++){
        DEBUG_PRINT(data[i]);
        }
        DEBUG_PRINTLN(F(" "));
    ws.textAll(data, len); 
}

void notifyClientsSingleObjectByte(String object, byte value) {
    StaticJsonDocument<50> doc;
    String key = object;
    byte Value = value;
    doc[key] = Value; 

    char data[50];
    size_t len = serializeJson(doc, data);
        DEBUG_PRINTLN(F("sending JSON byte: "));
        for (int i = 0; i < len;  i++){
        DEBUG_PRINT(data[i]);
        }
        DEBUG_PRINTLN(F(" "));
    ws.textAll(data, len); 
}

void notifyClientsSingleObjectInt(String object, uint32_t value) {
    StaticJsonDocument<50> doc;
    String key = object;
    uint32_t Value = value;
    doc[key] = Value; 

    char data[50];
    size_t len = serializeJson(doc, data);
        DEBUG_PRINTLN(F("sending JSON uint32_t: "));
        for (int i = 0; i < len;  i++){
        DEBUG_PRINT(data[i]);
        }
        DEBUG_PRINTLN(F(" "));
    ws.textAll(data, len); 
}

void notifyClientsSingleObjectSignedInt(String object, int32_t value) {
    StaticJsonDocument<50> doc;
    String key = object;
    int32_t Value = value;
    doc[key] = Value; 

    char data[50];
    size_t len = serializeJson(doc, data);
        DEBUG_PRINTLN(F("sending JSON int32_t: "));
        for (int i = 0; i < len;  i++){
        DEBUG_PRINT(data[i]);
        }
        DEBUG_PRINTLN(F(" "));
    ws.textAll(data, len); 
}
  