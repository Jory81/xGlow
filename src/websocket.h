/*
 ALL webserver (websocket)/ client functions.

*/

void onRootRequest(AsyncWebServerRequest *request) {
  request->send(SPIFFS, "/index.html", "text/html");    // , false, processor
}

void initWebServer() {
    server.on("/", onRootRequest);
    server.serveStatic("/", SPIFFS, "/");
    AsyncElegantOTA.begin(&server);   // Start ElegantOTA
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

      if (json.containsKey("TLSE")){sendProgramInfo(1); sendProgramInfo(2); sendProgramInfo(3); DEBUG_PRINTLN("enters here in TLSE"); notifyClientsSingleObject("TLSE", false);}
      //else if (json.containsKey("TLSX")){sendProgramInfo(2); DEBUG_PRINTLN("enters here in TLSX"); }

      else if (json.containsKey("ssid")){String wifiID = json["ssid"]; EEPROMposition = offsetof(storeInEEPROM, ssidStorage[0]); writeStringToEEPROM(EEPROMposition, wifiID); notifyClientsSingleString("wifiID", wifiID);}
      else if (json.containsKey("pass")){String wifiPASS = json["pass"]; EEPROMposition = offsetof(storeInEEPROM, passStorage[0]); writeStringToEEPROM(EEPROMposition, wifiPASS); notifyClientsSingleString("wifiPASS", wifiPASS);}
      
      else if (json.containsKey("SPGM")){programMode = json["SPGM"]; selectPreset(); if (syncEsp){espNowMessage = true;   EspNowMessageType = 0;}; cycleT=0;  previousMillis44 = millis();  previousMillis45 = millis(); if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, programMode), programMode);  EEPROM.commit();};  changeState();} 
      else if (json.containsKey("SBSM")){BriSPreset = json["SBSM"]; readBriSData(BriSPreset); sendProgramInfo(1); if (syncEsp){espNowMessage = true;   EspNowMessageType = 1;  }; }

      else if (json.containsKey("SHUE")){yval = json["SHUE"]; forcedColourChange = true; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, yval), yval);  EEPROM.commit();}; if (syncEsp){espNowMessage = true;   EspNowMessageType = 2;  }; }

      else if (json.containsKey("SBRI")){BRIGH = json["SBRI"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, BRIGH), BRIGH);  EEPROM.commit();}; if (syncEsp){espNowMessage = true;   EspNowMessageType = 22;  };}
      else if (json.containsKey("SGLO")){glowON = json["SGLO"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, glowON), glowON);  EEPROM.commit();}; if (syncEsp){espNowMessage = true;   EspNowMessageType = 22;  };}
      else if (json.containsKey("SNBR")){numbrigh = json["SNBR"]; if (maintainWaveForm){convBrigh=waveTimeBr/numbrigh;}; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, numbrigh), numbrigh);  EEPROM.commit();}; if (syncEsp){espNowMessage = true;   EspNowMessageType = 22;  };}
      else if (json.containsKey("SSBR")){BrF = json["SSBR"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, BrF), BrF);  EEPROM.commit();}; if (syncEsp){espNowMessage = true;   EspNowMessageType = 22;  };}
      else if (json.containsKey("SBWS")){waveTimeBr = json["SBWS"]; convBrigh = waveTimeBr/numbrigh; if (maintainWaveForm){BPMB=60000/waveTimeBr; notifyClientsSingleObjectByte("SSBS", BPMB);}; if (syncEsp){espNowMessage = true;   EspNowMessageType = 22;  };}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, waveTimeBr), waveTimeBr); EEPROM.put(offsetof(storeInEEPROM, BPMB), BPMB);  EEPROM.commit();};}
      else if (json.containsKey("SSBS")){BPMB = json["SSBS"]; if (maintainWaveForm){waveTimeBr=60000/BPMB; convBrigh=waveTimeBr/numbrigh; notifyClientsSingleObjectInt("SBWS", waveTimeBr);}; if (syncEsp){espNowMessage = true;   EspNowMessageType = 22;  };}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, BPMB), BPMB);  EEPROM.put(offsetof(storeInEEPROM, waveTimeBr), waveTimeBr); EEPROM.commit(); };}      
      else if (json.containsKey("SOBR")){offBr = json["SOBR"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, offBr), offBr);  EEPROM.commit();}; if (syncEsp){espNowMessage = true;   EspNowMessageType = 22;  };}   
      
      else if (json.containsKey("SSAT")){S = json["SSAT"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, S), S);  EEPROM.commit();}; if (syncEsp){espNowMessage = true;   EspNowMessageType = 23;  };}
      else if (json.containsKey("SSTM")){satON = json["SSTM"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, satON), satON);  EEPROM.commit();}; if (syncEsp){espNowMessage = true;   EspNowMessageType = 23;  };}
      else if (json.containsKey("SSTN")){numsat = json["SSTN"]; if (maintainWaveForm){convSat=waveTimeS/numsat;}; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, numsat), numsat);  EEPROM.commit();}; if (syncEsp){espNowMessage = true;   EspNowMessageType = 23;  };}
      else if (json.containsKey("SSSF")){SF = json["SSSF"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, SF), SF);  EEPROM.commit();}; if (syncEsp){espNowMessage = true;   EspNowMessageType = 23;  };}
      else if (json.containsKey("SSWS")){waveTimeS = json["SSWS"]; convSat = waveTimeS/numsat; if (maintainWaveForm){BPMS=60000/waveTimeS; notifyClientsSingleObjectByte("SSSS", BPMS);}; if (syncEsp){espNowMessage = true;   EspNowMessageType = 23;  };}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, waveTimeS), waveTimeS); EEPROM.put(offsetof(storeInEEPROM, BPMS), BPMS);  EEPROM.commit();};}      
      else if (json.containsKey("SSSS")){BPMS = json["SSSS"]; if (maintainWaveForm){waveTimeS=60000/BPMS; convSat=waveTimeS/numsat; notifyClientsSingleObjectInt("SSWS", waveTimeS);}; if (syncEsp){espNowMessage = true;   EspNowMessageType = 23;  };}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, BPMS), BPMS); EEPROM.put(offsetof(storeInEEPROM, waveTimeS), waveTimeS);  EEPROM.commit();};} 
      else if (json.containsKey("SOST")){offS = json["SOST"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, offS), offS);  EEPROM.commit();}; if (syncEsp){espNowMessage = true;   EspNowMessageType = 23;  };}    

      else if (json.containsKey("SCOM")){colorMode = json["SCOM"]; colorMode = colorMode-1; procesColourMode(); if (syncEsp){espNowMessage = true;   EspNowMessageType = 3;  }; } // memoryByte = 'c'; processChange();} // THIS ONE
      else if (json.containsKey("SVAR")){varON = json["SVAR"]; for (int p=0; p<10; p++){if (varON == 0){yvar[p]= 0; yvarg[p]= 0;} else {yvar[p]=yvarC[p]; yvarg[p]=yvargC[p];};} if (syncEsp){espNowMessage = true;   EspNowMessageType = 4;  }; } //if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, varON), varON);  EEPROM.commit();};
      else if (json.containsKey("SNSP")){numsparks = json["SNSP"];}
      else if (json.containsKey("SDIF")){setDifference = json["SDIF"]; fillxmasArray(); setDifference2 = setDifference+5;if (syncEsp){espNowMessage = true;   EspNowMessageType = 5;  }; } // diff[0]=0;     x = 1;  num = 0;        diff[1]=0;     xn = 1;    num7 = 0; } diffbeat=60000/(setDifference*4*100); diffbeat2=diffbeat/2;
      else if (json.containsKey("SLSP")){changeSpeed = json["SLSP"];if (syncEsp){espNowMessage = true;   EspNowMessageType = 6;  }; }

      else if (json.containsKey("SNLD")){NUM_LEDS = json["SNLD"]; EEPROM.put(offsetof(storeInEEPROM, NUM_LEDS), NUM_LEDS);  EEPROM.commit();}
      else if (json.containsKey("SCAR")){arrayn = json["SCAR"];     selectcolorArray();    newColors++; if (syncEsp){espNowMessage = true;   EspNowMessageType = 7;  }; }  // THIS ONE
      else if (json.containsKey("SPAL")){gCurrentPaletteNumber = json["SPAL"]; gTargetPalette =( gGradientPalettes[gCurrentPaletteNumber] ); if (syncEsp){espNowMessage = true;   EspNowMessageType = 8;  }; }
      else if (json.containsKey("SGRA")){selectColor = json["SGRA"];   dir1=1;    ymax4 = pgm_read_byte(&selectColor_data[selectColor].ymax4);  ymin4 = pgm_read_byte(&selectColor_data[selectColor].ymin4);   setDifference = pgm_read_byte(&selectColor_data[selectColor].setDifference);    yval1=ymin4;   dir0=1;    if (effect_function == *rainbow_3){setDifference = 4;  }if (syncEsp){espNowMessage = true;   EspNowMessageType = 9;  }; sendProgramInfo(1); }
      else if (json.containsKey("SNCO")){numcolor = json["SNCO"];   newColors++; if (syncEsp){espNowMessage = true;   EspNowMessageType = 12;  };    if (whiteON){for (int t=0; t<15; t++){satval[t]=S; satval[0]=0;}}      else if (!whiteON){for (int t=0; t<15; t++){satval[t]=S;}}}
      else if (json.containsKey("SNCL")){colorlength = json["SNCL"]; newColors++; if (syncEsp){espNowMessage = true;   EspNowMessageType = 13;  };}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, colorlength), colorlength);  EEPROM.commit();};}
      else if (json.containsKey("SSCO")){z5 = json["SSCO"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, z5), z5);  EEPROM.commit();}; if (syncEsp){espNowMessage = true;   EspNowMessageType = 14;  };}
      else if (json.containsKey("SOFF")){offdis = json["SOFF"]; if (tower && (effect_function == *snow_flakes || effect_function == *snow_flakes_2 || effect_function == *snow_flakesR)){offdisC = offdis; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, offdisC), offdisC);  EEPROM.commit();};};} //  || effect_function == *meteor
      
      else if (json.containsKey("SCTM")){cycleTime = json["SCTM"]; cycleTime = cycleTime*1000; if (cycleTime == 0){cycleTime = 60000;} if (saveToEEPROM){saveCycleParamToEEPROM();};}
      else if (json.containsKey("SLPS")){timefactor3 = json["SLPS"]; if (saveToEEPROM){saveCycleParamToEEPROM();};}
      else if (json.containsKey("SRED")){Red = json["SRED"]; loadHSV = true; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Red), Red);  EEPROM.commit();}; if (syncEsp){espNowMessage = true;   EspNowMessageType = 10;  }; } 
      else if (json.containsKey("SGRE")){Green = json["SGRE"]; loadHSV = true; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Green), Green);  EEPROM.commit();}; if (syncEsp){espNowMessage = true;   EspNowMessageType = 10;  }; }   
      else if (json.containsKey("SBLU")){Blue = json["SBLU"]; loadHSV = true; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Blue), Blue);  EEPROM.commit();}; if (syncEsp){espNowMessage = true;   EspNowMessageType = 10;  }; }    
      else if (json.containsKey("TCON")){cycle = json["TCON"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, cycle), cycle);  EEPROM.commit();};} // EEPROM
      else if (json.containsKey("TCPM")){saveForAllModes = json["TCPM"];} // EEPROM
      else if (json.containsKey("TCFA")){fadeFirst = json["TCFA"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, fadeFirst), fadeFirst);  EEPROM.commit();};} // EEPROM
      else if (json.containsKey("TCRA")){randomCycle = json["TCRA"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, randomCycle), randomCycle);  EEPROM.commit();};} // EEPROM
      else if (json.containsKey("TCEX")){excludeModes = json["TCEX"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, excludeModes), excludeModes);  EEPROM.commit();};} // EEPROM
      //else if (json.containsKey("TCAC")){enableMode();}  // THIS ONE
      else if (json.containsKey("TGLI")){glitterON = json["TGLI"]; initializeGlitter();}
      else if (json.containsKey("TCAC")){enableMode();} 
     
      else if (json.containsKey("SPST")){selectedPreset[programMode] = json["SPST"]; selectPreset(); if (syncEsp){espNowMessage = true;   EspNowMessageType = 0;  }; cycleT=0;   previousMillis44 = millis();  previousMillis45 = millis();  if (saveToEEPROM){int offsetPosition = offsetof(storeInEEPROM, selectedPreset[0]); EEPROM.put((offsetPosition + programMode), selectedPreset[programMode]);  EEPROM.commit();} changeState();}
      else if (json.containsKey("TSCM")){saveCurrentPresetToEEPROM(); sendDelayWSMessage=true; message = 1; previousMillis14=millis(); }
      else if (json.containsKey("TSBM")){saveCurrentBriSPresetToEEPROM(); sendDelayWSMessage=true; message = 5; previousMillis14=millis(); }
      
      else if (json.containsKey("TRBO")){rainbowON = json["TRBO"];}
      else if (json.containsKey("TRVO")){reverseON = json["TRVO"];}
      else if (json.containsKey("TWHO")){whiteON = json["TWHO"];  if (whiteON){for (int t=0; t<15; t++){satval[t]=S;   satval[0]=0;}} else if (!whiteON){for (int t=0; t<15; t++){satval[t]=S;}}}
      else if (json.containsKey("TSBS")){switchBrS = json["TSBS"];}
      else if (json.containsKey("TDIR")){xdir = json["TDIR"];  if (xdir == 1){dir = 2; dir1 = 1;} else {dir = 1; dir1 = -1;}}
      else if (json.containsKey("TSTE")){saveToEEPROM = json["TSTE"];}
      else if (json.containsKey("TTWO")){tower = json["TTWO"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, tower), tower);  EEPROM.commit();};} // EEPROM
      else if (json.containsKey("THSV")){updateHSV = json["THSV"];}
      else if (json.containsKey("TBEE")){Bees = json["TBEE"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Bees), Bees);  EEPROM.commit();};} // EEPROM
      else if (json.containsKey("TMWF")){maintainWaveForm = json["TMWF"];}
      else if (json.containsKey("TSET")){saveEverythingToEEPROM(); sendDelayWSMessage=true; message = 2; previousMillis14=millis();}
      else if (json.containsKey("TSED")){int eeAddress=0; EEPROM.put(eeAddress, customVar); EEPROM.commit(); FastLED.delay(1000); ESP.restart();}
      else if (json.containsKey("SETT")){RGBCOLOR = json["SETT"]; EEPROM.put((offsetof(storeInEEPROM, rgbcolor)), RGBCOLOR); EEPROM.commit();}//Serial.println(RGBCOLOR);}
      else if (json.containsKey("TAAM")){ActiveModesToEEPROM(); sendDelayWSMessage=true; message = 3; previousMillis14=millis();}
      else if (json.containsKey("TDAM")){DeactiveModesToEEPROM(); sendDelayWSMessage=true; message = 4; previousMillis14=millis();}
      else if (json.containsKey("SRMI")){yminrood = json["SRMI"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);} if (syncEsp){espNowMessage = true;   EspNowMessageType = 26;  }; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, yminrood), yminrood);  EEPROM.commit();};}
      else if (json.containsKey("SRMA")){ymaxrood = json["SRMA"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);} if (syncEsp){espNowMessage = true;   EspNowMessageType = 26;  }; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymaxrood), ymaxrood);  EEPROM.commit();};}
      else if (json.containsKey("SGMI")){ymingroen = json["SGMI"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);} if (syncEsp){espNowMessage = true;   EspNowMessageType = 26;  }; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymingroen), ymingroen);  EEPROM.commit();};}
      else if (json.containsKey("SGMA")){ymaxgroen = json["SGMA"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);} if (syncEsp){espNowMessage = true;   EspNowMessageType = 26;  }; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymaxgroen), ymaxgroen);  EEPROM.commit();};}
      else if (json.containsKey("SBMI")){yminblauw = json["SBMI"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);} if (syncEsp){espNowMessage = true;   EspNowMessageType = 26;  }; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, yminblauw), yminblauw);  EEPROM.commit();};}
      else if (json.containsKey("SBMA")){ymaxblauw = json["SBMA"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);} if (syncEsp){espNowMessage = true;   EspNowMessageType = 26;  }; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymaxblauw), ymaxblauw);  EEPROM.commit();};}          
      else if (json.containsKey("SYMI")){ymin = json["SYMI"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymin), ymin);  EEPROM.commit();};}
      else if (json.containsKey("SYMA")){ymax = json["SYMA"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymax), ymax);  EEPROM.commit();};}
      else if (json.containsKey("SMI1")){ymin1 = json["SMI1"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymin1), ymin1);  EEPROM.commit();};}
      else if (json.containsKey("SMA1")){ymax1 = json["SMA1"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymax1), ymax1);  EEPROM.commit();};}
      else if (json.containsKey("SMI2")){ymin2 = json["SMI2"]; dir1 = 1; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymin2), ymin2);  EEPROM.commit();};}
      else if (json.containsKey("SMA2")){ymax2 = json["SMA2"]; dir1 = 1; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymax2), ymax2);  EEPROM.commit();};}     
      else if (json.containsKey("SMI3")){ymin3 = json["SMI3"]; dir1 = 1; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymin3), ymin3);  EEPROM.commit();};}
      else if (json.containsKey("SMA3")){ymax3 = json["SMA3"]; dir1 = 1; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymax3), ymax3);  EEPROM.commit();};}
      else if (json.containsKey("SMI4")){ymin4 = json["SMI4"]; yval1=ymin4; dir0=1; dir1=1;}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymin4), ymin4);  EEPROM.commit();};}
      else if (json.containsKey("SMA4")){ymax4 = json["SMA4"]; yval1=ymin4; dir0=1; dir1=1;}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, ymax4), ymax4);  EEPROM.commit();};}
      else if (json.containsKey("SM3R")){range = json["SM3R"]; ledspercolor=NUM_LEDS/range; if (ledspercolor > 3){ledspercolor=3;} else if (ledspercolor < 1){ledspercolor = 1;} if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, range), range);  EEPROM.commit();};}
      //else if (json.containsKey("ESP")){num_esp = json["ESP"]; EEPROM.put(offsetof(storeInEEPROM, num_esp), num_esp);  EEPROM.commit();}
      else if (json.containsKey("mac1")){for (int i = 0; i < 6; i++){Mac[i] = json["mac1"][i];} writeMacTooEEPROM(0);}
      else if (json.containsKey("mac2")){for (int i = 6; i < 12; i++){Mac[i] = json["mac2"][i%6];} writeMacTooEEPROM(1);}
      else if (json.containsKey("mac3")){for (int i = 12; i < 18; i++){Mac[i] = json["mac3"][i%6];} writeMacTooEEPROM(2);}
      else if (json.containsKey("mac4")){for (int i = 18; i < 24; i++){Mac[i] = json["mac4"][i%6];} writeMacTooEEPROM(3);}
      else if (json.containsKey("mac5")){for (int i = 24; i < 30; i++){Mac[i] = json["mac5"][i%6];} writeMacTooEEPROM(4);}
      else if (json.containsKey("mac6")){for (int i = 30; i < 36; i++){Mac[i] = json["mac6"][i%6];} writeMacTooEEPROM(5);}
      else if (json.containsKey("mac7")){for (int i = 36; i < 42; i++){Mac[i] = json["mac7"][i%6];} writeMacTooEEPROM(6);}
      else if (json.containsKey("mac8")){for (int i = 42; i < 48; i++){Mac[i] = json["mac8"][i%6];} writeMacTooEEPROM(7);}
      else if (json.containsKey("mac9")){for (int i = 48; i < 54; i++){Mac[i] = json["mac9"][i%6];} writeMacTooEEPROM(8);}
      else if (json.containsKey("mac10")){for (int i = 54; i < 60; i++){Mac[i] = json["mac10"][i%6];} writeMacTooEEPROM(9);}
      else if (json.containsKey("TSYN")){syncEsp = json["TSYN"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, syncEsp), syncEsp);  EEPROM.commit();} if (!syncEsp){espNowMessage = true;   EspNowMessageType = 20;};}
      else if (json.containsKey("TSCN")){colourSyncToggle = json["TSCN"]; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, colourSyncToggle), colourSyncToggle);  EEPROM.commit();} if (!colourSyncToggle){espNowMessage = true;   EspNowMessageType = 21;}}
      else if (json.containsKey("m1c")){macConnected[0] = json["m1c"]; inSyncCounter[0] = 0; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, macConnected[0]), macConnected[0]); EEPROM.commit();};}
      else if (json.containsKey("m2c")){macConnected[1] = json["m2c"]; inSyncCounter[1] = 0; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, macConnected[1]), macConnected[1]); EEPROM.commit();};}
      else if (json.containsKey("m3c")){macConnected[2] = json["m3c"]; inSyncCounter[2] = 0; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, macConnected[2]), macConnected[2]); EEPROM.commit();};}
      else if (json.containsKey("m4c")){macConnected[3] = json["m4c"]; inSyncCounter[3] = 0; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, macConnected[3]), macConnected[3]); EEPROM.commit();};}
      else if (json.containsKey("m5c")){macConnected[4] = json["m5c"]; inSyncCounter[4] = 0; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, macConnected[4]), macConnected[4]); EEPROM.commit();};}
      else if (json.containsKey("m6c")){macConnected[5] = json["m6c"]; inSyncCounter[5] = 0; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, macConnected[5]), macConnected[5]); EEPROM.commit();};}
      else if (json.containsKey("m7c")){macConnected[6] = json["m7c"]; inSyncCounter[6] = 0; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, macConnected[6]), macConnected[6]); EEPROM.commit();};}
      else if (json.containsKey("m8c")){macConnected[7] = json["m8c"]; inSyncCounter[7] = 0; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, macConnected[7]), macConnected[7]); EEPROM.commit();};}
      else if (json.containsKey("m9c")){macConnected[8] = json["m9c"]; inSyncCounter[8] = 0; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, macConnected[8]), macConnected[8]); EEPROM.commit();};}
      else if (json.containsKey("m10c")){macConnected[9] = json["m10c"]; inSyncCounter[9] = 0; if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, macConnected[9]), macConnected[9]); EEPROM.commit();};}
      else if (json.containsKey("SBOF")){ledOffset = json["SBOF"]; if (syncEsp){espNowMessage = true;   EspNowMessageType = 24;  };}
      else if (json.containsKey("SBOV")){overLay = json["SBOV"]; if (syncEsp){espNowMessage = true;   EspNowMessageType = 24;  };}
      else if (json.containsKey("SOSS")){overlaySpeed = json["SOSS"]; if (syncEsp){espNowMessage = true;   EspNowMessageType = 24;  };}
      
      else if (json.containsKey("SSOF")){ledOffsetS = json["SSOF"]; if (syncEsp){espNowMessage = true;   EspNowMessageType = 25;  };}
      else if (json.containsKey("SSOV")){overLayS = json["SSOV"]; if (syncEsp){espNowMessage = true;   EspNowMessageType = 25;  };}
      else if (json.containsKey("SOSP")){overlaySpeedS = json["SOSP"]; if (syncEsp){espNowMessage = true;   EspNowMessageType = 25;  };}

      else if (json.containsKey("BOOT")){ESP.restart();};
      notifyClientsSingleObject("recMsg", true);
    }
}

  void writeMacTooEEPROM(uint8_t mac){
    for (int i = mac*6; i < (mac*6)+6; i++){
      int offsetPosition = (offsetof(storeInEEPROM, Mac[0]));
      //uint8_t macAds = Mac[i];
      //Serial.print("offsetposition"); Serial.println(offsetPosition+i);
      EEPROM.put((offsetPosition+i), Mac[i]);  
    }
    EEPROM.commit();
  }

void sendProgramInfo(byte message){
//StaticJsonDocument<2000> doc; // 2500
DynamicJsonDocument doc(2000);
    switch (message){
      case 1: {
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
        doc["TSBS"] = switchBrS;
        doc["TDIR"] = xdir;
        doc["SOFF"] = offdis; 
        doc["SSCO"] = z5;
        doc["SSTM"] = satON;
        doc["SSTN"] = numsat;
        doc["SBWS"] = waveTimeBr;// convBrigh = dataVar/numbrigh;}
        doc["SSWS"] = waveTimeS;// convSat = dataVar/numsat;}
        doc["SSBS"] = BPMB;      
        doc["SSSS"] = BPMS;                   
        doc["SLPS"] = String(timefactor3,2);// timefactor3 = dataVar/100;}            
        doc["SPGM"] = programMode; 
        doc["TCAC"] = cmode[programMode]; // 37
        doc["TSTE"] = saveToEEPROM;
        doc["TTWO"] = tower;
        
        doc["SPST"] = selectedPreset[programMode];
        doc["SPSV"] = selectedPresetVariable;

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
        //doc["TPMO"] = personalizedModes;   
        doc["TCPM"] = saveForAllModes;
        doc["HCOL"] = RGBCOLOR;
        doc["TSYN"] = syncEsp;
        doc["TSCN"] = colourSyncToggle;

        doc["SBOF"] = ledOffset;
        doc["SBOV"] = overLay;
        doc["SOSS"] = overlaySpeed;

        doc["SSOF"] = ledOffsetS;
        doc["SSOV"] = overLayS;
        doc["SOSP"] = overlaySpeedS;
      }
      break;
      case 2:{
      doc["BSMP"][0] = modeCount;

      for (int m = 1; m <= modeCount; m++){
      int offsetPosition = (offsetof(storeInEEPROM, BriSPreset[0])) + m-1;  
      uint8_t BriSPresetVal = EEPROM.read(offsetPosition);
      //DEBUG_PRINTLN(BriSPresetVal);
      doc["BSMP"][m] = BriSPresetVal;
      }

      doc["BSMY"][0] = modeCount;
      for (int m = 1; m <= modeCount; m++){
      int offsetPosition = (offsetof(storeInEEPROM, BriSPreset2[0])) + m-1;  
      uint8_t BriSPresetVal = EEPROM.read(offsetPosition);
      //DEBUG_PRINTLN(BriSPresetVal);
      doc["BSMY"][m] = BriSPresetVal;
      }

      doc["BSMX"][0] = modeCount;
      for (int m = 1; m <= modeCount; m++){
      int offsetPosition = (offsetof(storeInEEPROM, BriSPreset3[0])) + m-1;  
      uint8_t BriSPresetVal = EEPROM.read(offsetPosition);
      //DEBUG_PRINTLN(BriSPresetVal);
      doc["BSMX"][m] = BriSPresetVal;
      } 
    }
    break;
    case 3:{
      #ifdef ESP8266
      doc["MAC"] = macAdress;
      // DEBUG_PRINTLN(WiFi.macAddress().c_str());
      #else
      doc["MAC"] = WiFi.macAddressDec().c_str();
      #endif
      //doc["n_esp"] = num_esp;
      for (int n = 0; n < 10; n++){
        switch (n){
          case 0: {
            for (int m = n*6; m < (n*6)+6; m++){
              doc["mac1"][m%6] = Mac[m];
              }
          }
          break;
          case 1: {
            for (int m = n*6; m < (n*6)+6; m++){
              doc["mac2"][m%6] = Mac[m];
              }
          }
          break;
          case 2: {
            for (int m = n*6; m < (n*6)+6; m++){
              doc["mac3"][m%6] = Mac[m];
              }
          }
          break;
          case 3: {
            for (int m = n*6; m < (n*6)+6; m++){
              doc["mac4"][m%6] = Mac[m];
              }
          }
          break;
          case 4: {
            for (int m = n*6; m < (n*6)+6; m++){
              doc["mac5"][m%6] = Mac[m];
              }
          }
          break;
          case 5: {
            for (int m = n*6; m < (n*6)+6; m++){
              doc["mac6"][m%6] = Mac[m];
              }
          }
          break;
          case 6: {
            for (int m = n*6; m < (n*6)+6; m++){
              doc["mac7"][m%6] = Mac[m];
              }
          }
          break;
          case 7: {
            for (int m = n*6; m < (n*6)+6; m++){
              doc["mac8"][m%6] = Mac[m];
              }
          }
          break;
          case 8: {
            for (int m = n*6; m < (n*6)+6; m++){
              doc["mac9"][m%6] = Mac[m];
              }
          }
          break;
          case 9: {
            for (int m = n*6; m < (n*6)+6; m++){
              doc["mac10"][m%6] = Mac[m];
              }
          }
          break;                                                                   
        }
      }
      for (int n = 0; n < 10; n++){  
        doc["macC"][n] = macConnected[n];
      }
  }
  break;
  }
                                
char data[2000]; // 2500
size_t len = serializeJson(doc, data);

    DEBUG_PRINT(F("sending JSON message: ")); DEBUG_PRINTLN(len);
    for (int i = 0; i < len;  i++){
    DEBUG_PRINT(data[i]);
    }
    DEBUG_PRINTLN(" ");

ws.textAll(data, len);
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
        case 5: {notifyClientsSingleObject("TSBM", false);} break; //ws.textAll("GTDAM0");} break;
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

void saveCurrentPresetToEEPROM(){
if (selectedPreset[programMode] == 1){
  DEBUG_PRINTLN("save to position 1");
int offsetPosition = offsetof(storeInEEPROM, BriSPreset[0]);
EEPROM.put((offsetPosition+programMode), BriSPreset); 
offsetPosition = offsetof(storeInEEPROM, changeSpeed[0]);
EEPROM.put((offsetPosition+(programMode*sizeof(unsigned long))), changeSpeed); 
offsetPosition = offsetof(storeInEEPROM, setDifference[0]);
EEPROM.put((offsetPosition+(programMode*sizeof(int))), setDifference);
offsetPosition = offsetof(storeInEEPROM, colorMode[0]);
EEPROM.put((offsetPosition+(programMode*sizeof(int))), colorMode);
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

if (effect_function == gradient || effect_function == sparklingR || effect_function == snow_flakesR){
  offsetPosition = offsetof(storeInEEPROM, arrayn[0]);
  EEPROM.put((offsetPosition+programMode), selectColor); 
}
else {
  offsetPosition = offsetof(storeInEEPROM, arrayn[0]);
  EEPROM.put((offsetPosition+programMode), arrayn); 
}
}

else if (selectedPreset[programMode] == 2){
  DEBUG_PRINTLN("save to position 2");
int offsetPosition = offsetof(storeInEEPROM, BriSPreset2[0]);
EEPROM.put((offsetPosition+programMode), BriSPreset); 

offsetPosition = offsetof(storeInEEPROM, changeSpeed2[0]);
EEPROM.put((offsetPosition+(programMode*sizeof(unsigned long))), changeSpeed); 

offsetPosition = offsetof(storeInEEPROM, setDifference2[0]);
EEPROM.put((offsetPosition+(programMode*sizeof(int))), setDifference);

offsetPosition = offsetof(storeInEEPROM, colorMode2[0]);
EEPROM.put((offsetPosition+(programMode*sizeof(int))), colorMode); 

// offsetPosition = offsetof(storeInEEPROM, arrayn2[0]);
// EEPROM.put((offsetPosition+programMode), arrayn); 

offsetPosition = offsetof(storeInEEPROM, numsparks2[0]);
EEPROM.put((offsetPosition+programMode), numsparks); 

offsetPosition = offsetof(storeInEEPROM, varON2[0]);
EEPROM.put((offsetPosition+programMode), varON);

offsetPosition = offsetof(storeInEEPROM, glitterON2[0]);
EEPROM.put((offsetPosition+programMode), glitterON);

if (effect_function == pers_color){
EEPROM.put(offsetof(storeInEEPROM, numcolor12), numcolor); 
}
else if (effect_function == pers_block){
EEPROM.put(offsetof(storeInEEPROM, numcolor22), numcolor); 
EEPROM.put(offsetof(storeInEEPROM, colorlengthm2[2]), colorlength); 
}
else if (effect_function == static_glow && programMode == 0){
EEPROM.put(offsetof(storeInEEPROM, yval2), yval);
}
else if (effect_function == static_glow && programMode == 2){
EEPROM.put(offsetof(storeInEEPROM, yvalm22), yval);
}
else if (effect_function == static_glow && programMode == 3){
EEPROM.put(offsetof(storeInEEPROM, yvalm32), yval);
}
else if (effect_function == palettes){
EEPROM.put(offsetof(storeInEEPROM, gCurrentPaletteNumber2), gCurrentPaletteNumber);
}
else if (effect_function == rainbow_6){
EEPROM.put(offsetof(storeInEEPROM, colorlengthm2[0]), colorlength);
}
else if (effect_function == random_string){
EEPROM.put(offsetof(storeInEEPROM, colorlengthm2[1]), colorlength);
}
if (effect_function == gradient || effect_function == sparklingR || effect_function == snow_flakesR){
  offsetPosition = offsetof(storeInEEPROM, arrayn2[0]);
  EEPROM.put((offsetPosition+programMode), selectColor); 
}
else {
  offsetPosition = offsetof(storeInEEPROM, arrayn2[0]);
  EEPROM.put((offsetPosition+programMode), arrayn); 
}
}

else if (selectedPreset[programMode] == 3){
  DEBUG_PRINTLN("save to position 3");
int offsetPosition = offsetof(storeInEEPROM, BriSPreset3[0]);
EEPROM.put((offsetPosition+programMode), BriSPreset); 

offsetPosition = offsetof(storeInEEPROM, changeSpeed3[0]);
EEPROM.put((offsetPosition+(programMode*sizeof(unsigned long))), changeSpeed); 

offsetPosition = offsetof(storeInEEPROM, setDifference3[0]);
EEPROM.put((offsetPosition+(programMode*sizeof(int))), setDifference);

offsetPosition = offsetof(storeInEEPROM, colorMode3[0]);
EEPROM.put((offsetPosition+(programMode*sizeof(int))), colorMode); 

// offsetPosition = offsetof(storeInEEPROM, arrayn3[0]);
// EEPROM.put((offsetPosition+programMode), arrayn); 

offsetPosition = offsetof(storeInEEPROM, numsparks3[0]);
EEPROM.put((offsetPosition+programMode), numsparks); 

offsetPosition = offsetof(storeInEEPROM, varON3[0]);
EEPROM.put((offsetPosition+programMode), varON);

offsetPosition = offsetof(storeInEEPROM, glitterON3[0]);
EEPROM.put((offsetPosition+programMode), glitterON);

if (effect_function == pers_color){
EEPROM.put(offsetof(storeInEEPROM, numcolor13), numcolor); 
}
else if (effect_function == pers_block){
EEPROM.put(offsetof(storeInEEPROM, numcolor23), numcolor); 
EEPROM.put(offsetof(storeInEEPROM, colorlengthm3[2]), colorlength); 
}
else if (effect_function == static_glow && programMode == 0){
EEPROM.put(offsetof(storeInEEPROM, yval3), yval);
}
else if (effect_function == static_glow && programMode == 2){
EEPROM.put(offsetof(storeInEEPROM, yvalm23), yval);
}
else if (effect_function == static_glow && programMode == 3){
EEPROM.put(offsetof(storeInEEPROM, yvalm33), yval);
}
else if (effect_function == palettes){
EEPROM.put(offsetof(storeInEEPROM, gCurrentPaletteNumber3), gCurrentPaletteNumber);
}
else if (effect_function == rainbow_6){
EEPROM.put(offsetof(storeInEEPROM, colorlengthm3[0]), colorlength);
}
else if (effect_function == random_string){
EEPROM.put(offsetof(storeInEEPROM, colorlengthm3[1]), colorlength);
}
if (effect_function == gradient || effect_function == sparklingR || effect_function == snow_flakesR){
  offsetPosition = offsetof(storeInEEPROM, arrayn3[0]);
  EEPROM.put((offsetPosition+programMode), selectColor); 
}
else {
  offsetPosition = offsetof(storeInEEPROM, arrayn3[0]);
  EEPROM.put((offsetPosition+programMode), arrayn); 
}
}
EEPROM.commit();
}

void saveCurrentBriSPresetToEEPROM(){
uint8_t offsetInArray = BriSPreset;
int offsetPosition = offsetof(storeInEEPROM, waveTimeBr[0]);
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

#ifdef ESP8266 
int offsetPosition = offsetof(storeInEEPROM, cycleTime[0]) + (programMode*sizeof(unsigned long));   
EEPROM.get(offsetPosition, cycleTime);
 
offsetPosition = offsetof(storeInEEPROM, timefactor3[0]) + (programMode*sizeof(float));  
EEPROM.get(offsetPosition, timefactor3); 

#else
int offsetPosition = offsetof(storeInEEPROM, cycleTime[0]) + (programMode*sizeof(unsigned long));  
cycleTime = EEPROM.readLong(offsetPosition); 

offsetPosition = offsetof(storeInEEPROM, timefactor3[0]) + (programMode*sizeof(float));  
timefactor3 = EEPROM.readFloat(offsetPosition); 
#endif

if (selectedPresetVariable == 1){
  DEBUG_PRINTLN("load from position 1");
    int offsetPosition = (offsetof(storeInEEPROM, BriSPreset[0])) + programMode;  
    BriSPreset = EEPROM.read(offsetPosition);
    offsetPosition = (offsetof(storeInEEPROM, varON[0])) + programMode; 
    varON = EEPROM.read(offsetPosition); for (int p=0; p<10; p++){if (varON == 0){yvar[p]= 0; yvarg[p]= 0;} else {yvar[p]=yvarC[p]; yvarg[p]=yvargC[p];};}
    offsetPosition = (offsetof(storeInEEPROM, numsparks[0])) + programMode; 
    numsparks = EEPROM.read(offsetPosition);
    offsetPosition = (offsetof(storeInEEPROM, glitterON[0])) + programMode; 
    glitterON = EEPROM.read(offsetPosition);

    #ifdef ESP8266 
    offsetPosition = offsetof(storeInEEPROM, changeSpeed[0]) + (programMode*sizeof(unsigned long));  
    EEPROM.get(offsetPosition, changeSpeed);
    // offsetPosition = offsetof(storeInEEPROM, cycleTime[0]) + (programMode*sizeof(unsigned long));  
    // EEPROM.get(offsetPosition, cycleTime);
    // offsetPosition = offsetof(storeInEEPROM, timefactor3[0]) + (programMode*sizeof(float));  
    // EEPROM.get(offsetPosition, timefactor3);
    offsetPosition = offsetof(storeInEEPROM, setDifference[0]) + (programMode*sizeof(int));  
    EEPROM.get(offsetPosition, setDifference);
    offsetPosition = offsetof(storeInEEPROM, colorMode[0]) + (programMode*sizeof(int));  
    EEPROM.get(offsetPosition, colorMode);
    #else
    offsetPosition = offsetof(storeInEEPROM, changeSpeed[0]) + (programMode*sizeof(unsigned long));  
    changeSpeed = EEPROM.readLong(offsetPosition); 

    // offsetPosition = offsetof(storeInEEPROM, cycleTime[0]) + (programMode*sizeof(unsigned long));  
    // cycleTime = EEPROM.readLong(offsetPosition); 

    // offsetPosition = offsetof(storeInEEPROM, timefactor3[0]) + (programMode*sizeof(float));  
    // timefactor3 = EEPROM.readFloat(offsetPosition); 

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
    if (effect_function == gradient || effect_function == sparklingR || effect_function == snow_flakesR){
    offsetPosition = (offsetof(storeInEEPROM, arrayn[0])) + programMode;
    selectColor = EEPROM.read(offsetPosition);
    }
    else {
    offsetPosition = (offsetof(storeInEEPROM, arrayn[0])) + programMode; 
    arrayn = EEPROM.read(offsetPosition);
    }
  }
  else if (selectedPresetVariable == 2){
    DEBUG_PRINTLN("load from position 2");
    int offsetPosition = (offsetof(storeInEEPROM, BriSPreset2[0])) + programMode;  
    BriSPreset = EEPROM.read(offsetPosition);
    // offsetPosition = (offsetof(storeInEEPROM, arrayn2[0])) + programMode; 
    // arrayn = EEPROM.read(offsetPosition);
    offsetPosition = (offsetof(storeInEEPROM, varON2[0])) + programMode; 
    varON = EEPROM.read(offsetPosition); for (int p=0; p<10; p++){if (varON == 0){yvar[p]= 0; yvarg[p]= 0;} else {yvar[p]=yvarC[p]; yvarg[p]=yvargC[p];};}
    offsetPosition = (offsetof(storeInEEPROM, numsparks2[0])) + programMode; 
    numsparks = EEPROM.read(offsetPosition);
    offsetPosition = (offsetof(storeInEEPROM, glitterON2[0])) + programMode; 
    glitterON = EEPROM.read(offsetPosition);

    #ifdef ESP8266 
    offsetPosition = offsetof(storeInEEPROM, changeSpeed2[0]) + (programMode*sizeof(unsigned long));  
    EEPROM.get(offsetPosition, changeSpeed);
    // offsetPosition = offsetof(storeInEEPROM, cycleTime[0]) + (programMode*sizeof(unsigned long));  
    // EEPROM.get(offsetPosition, cycleTime);
    // offsetPosition = offsetof(storeInEEPROM, timefactor3[0]) + (programMode*sizeof(float));  
    // EEPROM.get(offsetPosition, timefactor3);
    offsetPosition = offsetof(storeInEEPROM, setDifference2[0]) + (programMode*sizeof(int));  
    EEPROM.get(offsetPosition, setDifference);
    offsetPosition = offsetof(storeInEEPROM, colorMode2[0]) + (programMode*sizeof(int));  
    EEPROM.get(offsetPosition, colorMode);
    #else
    offsetPosition = offsetof(storeInEEPROM, changeSpeed2[0]) + (programMode*sizeof(unsigned long));  
    changeSpeed = EEPROM.readLong(offsetPosition); 

    // offsetPosition = offsetof(storeInEEPROM, cycleTime[0]) + (programMode*sizeof(unsigned long));  
    // cycleTime = EEPROM.readLong(offsetPosition); 

    // offsetPosition = offsetof(storeInEEPROM, timefactor3[0]) + (programMode*sizeof(float));  
    // timefactor3 = EEPROM.readFloat(offsetPosition); 

    offsetPosition = offsetof(storeInEEPROM, setDifference2[0]) + (programMode*sizeof(int));
    setDifference = EEPROM.readInt(offsetPosition);

    offsetPosition = offsetof(storeInEEPROM, colorMode2[0]) + (programMode*sizeof(int));  
    colorMode = EEPROM.readInt(offsetPosition);
    #endif

    if (effect_function == pers_color){
    numcolor = EEPROM.read(offsetof(storeInEEPROM, numcolor12));
    }
    else if (effect_function == pers_block){
    numcolor = EEPROM.read(offsetof(storeInEEPROM, numcolor22));
    colorlength = EEPROM.read(offsetof(storeInEEPROM, colorlengthm2[2]));
    }
    else if (effect_function == static_glow && programMode == 0){
    yval = EEPROM.read(offsetof(storeInEEPROM, yval2));
    }
    else if (effect_function == static_glow && programMode == 2){
    yval = EEPROM.read(offsetof(storeInEEPROM, yvalm22));
    }
    else if (effect_function == static_glow && programMode == 3){
    yval = EEPROM.read(offsetof(storeInEEPROM, yvalm32));
    }
    else if (effect_function == palettes){
    gCurrentPaletteNumber = EEPROM.read(offsetof(storeInEEPROM, gCurrentPaletteNumber2));
    }
    else if (effect_function == rainbow_6){
    colorlength = EEPROM.read(offsetof(storeInEEPROM, colorlengthm2[0]));
    }
    else if (effect_function == random_string){
    colorlength = EEPROM.read(offsetof(storeInEEPROM, colorlengthm2[1]));
    }
    if (effect_function == gradient || effect_function == sparklingR || effect_function == snow_flakesR){
    offsetPosition = (offsetof(storeInEEPROM, arrayn2[0])) + programMode;
    selectColor = EEPROM.read(offsetPosition);
    }
    else {
    offsetPosition = (offsetof(storeInEEPROM, arrayn2[0])) + programMode; 
    arrayn = EEPROM.read(offsetPosition);
    }
    

  }

  else if (selectedPresetVariable == 3){
    DEBUG_PRINTLN("load from position 3");
        int offsetPosition = (offsetof(storeInEEPROM, BriSPreset3[0])) + programMode;  
    BriSPreset = EEPROM.read(offsetPosition);
    offsetPosition = (offsetof(storeInEEPROM, arrayn3[0])) + programMode; 
    arrayn = EEPROM.read(offsetPosition);
    offsetPosition = (offsetof(storeInEEPROM, varON3[0])) + programMode; 
    varON = EEPROM.read(offsetPosition); for (int p=0; p<10; p++){if (varON == 0){yvar[p]= 0; yvarg[p]= 0;} else {yvar[p]=yvarC[p]; yvarg[p]=yvargC[p];};}
    offsetPosition = (offsetof(storeInEEPROM, numsparks3[0])) + programMode; 
    numsparks = EEPROM.read(offsetPosition);
    offsetPosition = (offsetof(storeInEEPROM, glitterON3[0])) + programMode; 
    glitterON = EEPROM.read(offsetPosition);

    #ifdef ESP8266 
    offsetPosition = offsetof(storeInEEPROM, changeSpeed3[0]) + (programMode*sizeof(unsigned long));  
    EEPROM.get(offsetPosition, changeSpeed);
    // offsetPosition = offsetof(storeInEEPROM, cycleTime[0]) + (programMode*sizeof(unsigned long));  
    // EEPROM.get(offsetPosition, cycleTime);
    // offsetPosition = offsetof(storeInEEPROM, timefactor3[0]) + (programMode*sizeof(float));  
    // EEPROM.get(offsetPosition, timefactor3);
    offsetPosition = offsetof(storeInEEPROM, setDifference3[0]) + (programMode*sizeof(int));  
    EEPROM.get(offsetPosition, setDifference);
    offsetPosition = offsetof(storeInEEPROM, colorMode3[0]) + (programMode*sizeof(int));  
    EEPROM.get(offsetPosition, colorMode);
    #else
    offsetPosition = offsetof(storeInEEPROM, changeSpeed3[0]) + (programMode*sizeof(unsigned long));  
    changeSpeed = EEPROM.readLong(offsetPosition); 

    // offsetPosition = offsetof(storeInEEPROM, cycleTime[0]) + (programMode*sizeof(unsigned long));  
    // cycleTime = EEPROM.readLong(offsetPosition); 

    // offsetPosition = offsetof(storeInEEPROM, timefactor3[0]) + (programMode*sizeof(float));  
    // timefactor3 = EEPROM.readFloat(offsetPosition); 

    offsetPosition = offsetof(storeInEEPROM, setDifference3[0]) + (programMode*sizeof(int));
    setDifference = EEPROM.readInt(offsetPosition);

    offsetPosition = offsetof(storeInEEPROM, colorMode3[0]) + (programMode*sizeof(int));  
    colorMode = EEPROM.readInt(offsetPosition);
    #endif

    if (effect_function == pers_color){
    numcolor = EEPROM.read(offsetof(storeInEEPROM, numcolor13));
    }
    else if (effect_function == pers_block){
    numcolor = EEPROM.read(offsetof(storeInEEPROM, numcolor23));
    colorlength = EEPROM.read(offsetof(storeInEEPROM, colorlengthm3[2]));
    }
    else if (effect_function == static_glow && programMode == 0){
    yval = EEPROM.read(offsetof(storeInEEPROM, yval3));
    }
    else if (effect_function == static_glow && programMode == 2){
    yval = EEPROM.read(offsetof(storeInEEPROM, yvalm23));
    }
    else if (effect_function == static_glow && programMode == 3){
    yval = EEPROM.read(offsetof(storeInEEPROM, yvalm33));
    }
    else if (effect_function == palettes){
    gCurrentPaletteNumber = EEPROM.read(offsetof(storeInEEPROM, gCurrentPaletteNumber3));
    }
    else if (effect_function == rainbow_6){
    colorlength = EEPROM.read(offsetof(storeInEEPROM, colorlengthm3[0]));
    }
    else if (effect_function == random_string){
    colorlength = EEPROM.read(offsetof(storeInEEPROM, colorlengthm3[1]));
    }
    
    if (effect_function == gradient || effect_function == sparklingR || effect_function == snow_flakesR){
    offsetPosition = (offsetof(storeInEEPROM, arrayn3[0])) + programMode;
    selectColor = EEPROM.read(offsetPosition);
    }
    else {
    offsetPosition = (offsetof(storeInEEPROM, arrayn3[0])) + programMode; 
    arrayn = EEPROM.read(offsetPosition);
    }

  }
if (effect_function == gradient || effect_function == sparklingR || effect_function == snow_flakesR){
  dir1=1;
  ymax4 = pgm_read_byte(&selectColor_data[selectColor].ymax4);
  ymin4 = pgm_read_byte(&selectColor_data[selectColor].ymin4);
  //setDifference = pgm_read_byte(&selectColor_data[selectColor].setDifference);
  yval1=ymin4;
  dir0=1;
  //notifyClientsSingleObjectInt("SGRA", selectColor);
} 

selectcolorArray();
readBriSData(BriSPreset);
}

void readBriSData(byte preset){
  if (switchBrS){
    if (selectedPresetVariable == 0){
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
  else if (selectedPresetVariable != 0){
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
        //DEBUG_PRINTLN(F("sending JSON uint32_t: "));
        for (int i = 0; i < len;  i++){
        //DEBUG_PRINT(data[i]);
        }
        //DEBUG_PRINTLN(F(" "));
    ws.textAll(data, len); 
}

void notifyClientsSingleObjectSignedInt(String object, int32_t value) {
    StaticJsonDocument<50> doc;
    String key = object;
    int32_t Value = value;
    doc[key] = Value; 

    char data[50];
    size_t len = serializeJson(doc, data);
        //DEBUG_PRINTLN(F("sending JSON int32_t: "));
        for (int i = 0; i < len;  i++){
        //DEBUG_PRINT(data[i]);
        }
        //DEBUG_PRINTLN(F(" "));
    ws.textAll(data, len); 
}

void printEEPROM(){

int offsetPosition;

EEPROM_PRINTLN("setdifference values: "); // int
EEPROM_PRINTLN("setDifference: ");
for (int k = 0; k < modeCount; k++){  
offsetPosition = (offsetof(storeInEEPROM, setDifference[0])) + (k*sizeof(int)); 
//BriSPreset = EEPROM.read(offsetPosition);
#ifdef ESP8266 
int printvalue;
EEPROM_PRINT(EEPROM.get(offsetPosition, printvalue));
//EEPROM.get(offsetPosition, setDifference);
#else
EEPROM_PRINT(EEPROM.readInt(offsetPosition));
#endif

EEPROM_PRINT(", ");
}
EEPROM_PRINTLN(" ");

EEPROM_PRINTLN("setDifference2: ");
for (int k = 0; k < modeCount; k++){  
offsetPosition = (offsetof(storeInEEPROM, setDifference2[0])) + (k*sizeof(int)); 
//BriSPreset = EEPROM.read(offsetPosition);
#ifdef ESP8266 
int printvalue;
EEPROM_PRINT(EEPROM.get(offsetPosition, printvalue));
#else
EEPROM_PRINT(EEPROM.readInt(offsetPosition))
#endif
;
EEPROM_PRINT(", ");
}
EEPROM_PRINTLN(" ");

EEPROM_PRINTLN("setDifference3: ");
for (int k = 0; k < modeCount; k++){  
offsetPosition = (offsetof(storeInEEPROM, setDifference3[0])) + (k*sizeof(int)); 
//BriSPreset = EEPROM.read(offsetPosition);
#ifdef ESP8266 
int printvalue;
EEPROM_PRINT(EEPROM.get(offsetPosition, printvalue));
#else
EEPROM_PRINT(EEPROM.readInt(offsetPosition));
#endif

EEPROM_PRINT(", ");
}
EEPROM_PRINTLN(" ");

EEPROM_PRINTLN("changeSpeed values: "); // unsigned long
EEPROM_PRINTLN("changeSpeed: ");
for (int k = 0; k < modeCount; k++){  
offsetPosition = (offsetof(storeInEEPROM, changeSpeed[0])) + (k*sizeof(unsigned long)); 
//BriSPreset = EEPROM.read(offsetPosition);
#ifdef ESP8266 
long printvalue;
EEPROM_PRINT(EEPROM.get(offsetPosition, printvalue));
#else
EEPROM_PRINT(EEPROM.readLong(offsetPosition));
#endif

EEPROM_PRINT(", ");
}
EEPROM_PRINTLN(" ");

EEPROM_PRINTLN("changeSpeed2: ");
for (int k = 0; k < modeCount; k++){  
offsetPosition = (offsetof(storeInEEPROM, changeSpeed2[0])) + (k*sizeof(unsigned long)); 
//BriSPreset = EEPROM.read(offsetPosition);
#ifdef ESP8266 
long printvalue;
EEPROM_PRINT(EEPROM.get(offsetPosition, printvalue));
#else
EEPROM_PRINT(EEPROM.readLong(offsetPosition));
#endif

EEPROM_PRINT(", ");
}
EEPROM_PRINTLN(" ");

EEPROM_PRINTLN("changeSpeed3: ");
for (int k = 0; k < modeCount; k++){  
offsetPosition = (offsetof(storeInEEPROM, changeSpeed3[0])) + (k*sizeof(unsigned long)); 
//BriSPreset = EEPROM.read(offsetPosition);
#ifdef ESP8266 
long printvalue;
EEPROM_PRINT(EEPROM.get(offsetPosition, printvalue));
#else
EEPROM_PRINT(EEPROM.readLong(offsetPosition));
#endif

EEPROM_PRINT(", ");
}
EEPROM_PRINTLN(" ");

EEPROM_PRINTLN("varON values: "); // byte
EEPROM_PRINTLN("varON: ");
for (int k = 0; k < modeCount; k++){  
offsetPosition = (offsetof(storeInEEPROM, varON[0])) + k; 
//BriSPreset = EEPROM.read(offsetPosition);
EEPROM_PRINT(EEPROM.read(offsetPosition));

EEPROM_PRINT(", ");
}
EEPROM_PRINTLN(" ");

EEPROM_PRINTLN("varON2: ");
for (int k = 0; k < modeCount; k++){  
offsetPosition = (offsetof(storeInEEPROM, varON2[0])) + k; 
//BriSPreset = EEPROM.read(offsetPosition);
EEPROM_PRINT(EEPROM.read(offsetPosition));
EEPROM_PRINT(", ");
}
EEPROM_PRINTLN(" ");

EEPROM_PRINTLN("varON3: ");
for (int k = 0; k < modeCount; k++){  
offsetPosition = (offsetof(storeInEEPROM, varON3[0])) + k; 
//BriSPreset = EEPROM.read(offsetPosition);
EEPROM_PRINT(EEPROM.read(offsetPosition));
EEPROM_PRINT(", ");
}
EEPROM_PRINTLN(" ");


EEPROM_PRINTLN("colorMode values: "); // int
EEPROM_PRINTLN("colorMode: ");
for (int k = 0; k < modeCount; k++){  
offsetPosition = (offsetof(storeInEEPROM, colorMode[0])) + (k*sizeof(int)); 
//BriSPreset = EEPROM.read(offsetPosition);

#ifdef ESP8266 
int printvalue;
EEPROM_PRINT(EEPROM.get(offsetPosition, printvalue));
#else
EEPROM_PRINT(EEPROM.readInt(offsetPosition));
#endif
EEPROM_PRINT(", ");
}
EEPROM_PRINTLN(" ");

EEPROM_PRINTLN("colorMode2: ");
for (int k = 0; k < modeCount; k++){  
offsetPosition = (offsetof(storeInEEPROM, colorMode2[0])) + (k*sizeof(int)); 
//BriSPreset = EEPROM.read(offsetPosition);
#ifdef ESP8266 
int printvalue;
EEPROM_PRINT(EEPROM.get(offsetPosition, printvalue));
#else
EEPROM_PRINT(EEPROM.readInt(offsetPosition));
#endif

EEPROM_PRINT(", ");
}
EEPROM_PRINTLN(" ");

EEPROM_PRINTLN("colorMode3: ");
for (int k = 0; k < modeCount; k++){  
offsetPosition = (offsetof(storeInEEPROM, colorMode3[0])) + (k*sizeof(int)); 
//BriSPreset = EEPROM.read(offsetPosition);
#ifdef ESP8266 
int printvalue;
EEPROM_PRINT(EEPROM.get(offsetPosition, printvalue));
#else
EEPROM_PRINT(EEPROM.readInt(offsetPosition));
#endif

EEPROM_PRINT(", ");
}
EEPROM_PRINTLN(" ");


EEPROM_PRINTLN("BriS preset values: "); // uint8_t
EEPROM_PRINTLN("BriS preset: ");
for (int k = 0; k < modeCount; k++){  
offsetPosition = (offsetof(storeInEEPROM, BriSPreset[0])) + k; 
//BriSPreset = EEPROM.read(offsetPosition);
EEPROM_PRINT(EEPROM.read(offsetPosition));
EEPROM_PRINT(", ");
}
EEPROM_PRINTLN(" ");

EEPROM_PRINTLN("BriS preset2: ");
for (int k = 0; k < modeCount; k++){  
offsetPosition = (offsetof(storeInEEPROM, BriSPreset2[0])) + k; 
//BriSPreset = EEPROM.read(offsetPosition);
EEPROM_PRINT(EEPROM.read(offsetPosition));
EEPROM_PRINT(", ");
}
EEPROM_PRINTLN(" ");

EEPROM_PRINTLN("BriS preset3: ");
for (int k = 0; k < modeCount; k++){  
offsetPosition = (offsetof(storeInEEPROM, BriSPreset3[0])) + k; 
//BriSPreset = EEPROM.read(offsetPosition);
EEPROM_PRINT(EEPROM.read(offsetPosition));
EEPROM_PRINT(", ");
}
EEPROM_PRINTLN(" ");


EEPROM_PRINTLN("numsparks preset values: "); // byte
EEPROM_PRINTLN("numsparks preset: ");
for (int k = 0; k < modeCount; k++){  
offsetPosition = (offsetof(storeInEEPROM, numsparks[0])) + k; 
//BriSPreset = EEPROM.read(offsetPosition);
EEPROM_PRINT(EEPROM.read(offsetPosition));
EEPROM_PRINT(", ");
}
EEPROM_PRINTLN(" ");

EEPROM_PRINTLN("numsparks preset2: ");
for (int k = 0; k < modeCount; k++){  
offsetPosition = (offsetof(storeInEEPROM, numsparks2[0])) + k; 
//BriSPreset = EEPROM.read(offsetPosition);
EEPROM_PRINT(EEPROM.read(offsetPosition));
EEPROM_PRINT(", ");
}
EEPROM_PRINTLN(" ");

EEPROM_PRINTLN("numsparks preset3: ");
for (int k = 0; k < modeCount; k++){  
offsetPosition = (offsetof(storeInEEPROM, numsparks3[0])) + k; 
//BriSPreset = EEPROM.read(offsetPosition);
EEPROM_PRINT(EEPROM.read(offsetPosition));
EEPROM_PRINT(", ");
}
EEPROM_PRINTLN(" ");


EEPROM_PRINTLN("arrayn (color) preset values: "); // byte
EEPROM_PRINTLN("arrayn (color) preset: ");
for (int k = 0; k < modeCount; k++){  
offsetPosition = (offsetof(storeInEEPROM, arrayn[0])) + k; 
//BriSPreset = EEPROM.read(offsetPosition);
EEPROM_PRINT(EEPROM.read(offsetPosition));
EEPROM_PRINT(", ");
}
EEPROM_PRINTLN(" ");

EEPROM_PRINTLN("arrayn (color) preset2: ");
for (int k = 0; k < modeCount; k++){  
offsetPosition = (offsetof(storeInEEPROM, arrayn2[0])) + k; 
//BriSPreset = EEPROM.read(offsetPosition);
EEPROM_PRINT(EEPROM.read(offsetPosition));
EEPROM_PRINT(", ");
}
EEPROM_PRINTLN(" ");

EEPROM_PRINTLN("arrayn (color) preset3: ");
for (int k = 0; k < modeCount; k++){  
offsetPosition = (offsetof(storeInEEPROM, arrayn3[0])) + k; 
//BriSPreset = EEPROM.read(offsetPosition);
EEPROM_PRINT(EEPROM.read(offsetPosition));
EEPROM_PRINT(", ");
}

EEPROM_PRINTLN(" ");


}
#ifdef ESP8266
void onDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
   DEBUG_PRINTLN("Message received.");
   // We don't use mac to verify the sender
   // Let us transform the incomingData into our message structure
        memcpy(&dataEspNow, incomingData, sizeof(dataEspNow));
        dataEspNow[len] = 0;
        for (int i = 0; i < len; i++){
          //Serial.print(dataEspNow[i]);
        }
        //Serial.print("Bytes received: ");
        //Serial.println(len);
        inSync = true;
        previousMillis15 = millis();
//         incomingMessage = true;
// }

        DEBUG_PRINTLN(F("received JSON espnow message: "));
        for (int i = 0; i < len; i++){
        //strval[i]=(char)data[i];    
        DEBUG_PRINT((char)incomingData[i]);
        }
        DEBUG_PRINTLN(" ");

        StaticJsonDocument<255> json;
        //DeserializationError err = deserializeJson(json, incomingData);
        DeserializationError err = deserializeJson(json, dataEspNow);
        if (err) {
            DEBUG_PRINT(F("deserializeJson() failed with code "));
            DEBUG_PRINTLN(err.c_str());
            return;
        }
        // JsonObject object = json.to<JsonObject>();

        // for (int i = 0; i < object.size(); i++){
          JsonObject root = json.as<JsonObject>();

        // using C++11 syntax (preferred):
        for (JsonPair kv : root) {
            String variable = kv.key().c_str();
        //     Serial.println(kv.key().c_str());
        //     Serial.println(kv.value().as<char*>());
        // }
      
          if (variable == "SPST"){selectedPreset[programMode] = json["SPST"]; selectedPresetVariable = selectedPreset[programMode];}// Serial.println("selectbrispreset"); cycleT=0;  previousMillis44 = millis();  previousMillis45 = millis();  if (saveToEEPROM){int offsetPosition = offsetof(storeInEEPROM, selectedPreset[0]); EEPROM.put((offsetPosition + programMode), selectedPresetVariable);  EEPROM.commit();} changeState();}
      
          else if (variable == "SBSM"){BriSPreset = json["SBSM"]; readBriSData(BriSPreset);}// sendProgramInfo(1);}
          else if (variable == "SRED"){Red = json["SRED"]; loadHSV = true;}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Red), Red);  EEPROM.commit();};} 
          else if (variable == "SGRE"){Green = json["SGRE"]; loadHSV = true;}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Green), Green);  EEPROM.commit();};}   
          else if (variable == "SBLU"){Blue = json["SBLU"]; loadHSV = true;}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Blue), Blue);  EEPROM.commit();};}
          
          else if (variable == "TCON"){cycle = json["TCON"]; } // Serial.println("cycle to false"); if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, cycle), cycle);  EEPROM.commit();};} // EEPROM
          else if (variable == "SGRA"){selectColor = json["SGRA"];   dir1=1;    ymax4 = pgm_read_byte(&selectColor_data[selectColor].ymax4);  ymin4 = pgm_read_byte(&selectColor_data[selectColor].ymin4);   setDifference = pgm_read_byte(&selectColor_data[selectColor].setDifference);    yval1=ymin4;   dir0=1;     fillArrayGradient(3, yval1, setDifference); changeColor = true;   if (effect_function == *rainbow_3){setDifference = 4;} sendProgramInfo(1);}
          else if (variable == "SPAL"){gCurrentPaletteNumber = json["SPAL"]; gTargetPalette =( gGradientPalettes[gCurrentPaletteNumber] );}
          else if (variable == "SCAR"){arrayn = json["SCAR"];     selectcolorArray();    newColors++;    if (colorMode != 4){for (int n = 0; n < 15; n++){newColour[n] = json["YV"][n];};};}  // THIS ONE
          
          else if (variable == "SDIF"){setDifference = json["SDIF"]; fillxmasArray();  setDifference2 = setDifference+5;} // diff[0]=0;     x = 1;  num = 0;        diff[1]=0;     xn = 1;    num7 = 0; } diffbeat=60000/(setDifference*4*100); diffbeat2=diffbeat/2;
          else if (variable == "SLSP"){changeSpeed = json["SLSP"];}
          else if (variable == "SVAR"){varON = json["SVAR"]; for (int p=0; p<10; p++){if (varON == 0){yvar[p]= 0; yvarg[p]= 0;} else {yvar[p]=yvarC[p]; yvarg[p]=yvargC[p];};};}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, varON), varON);  EEPROM.commit();};}
          else if (variable == "SCOM"){colorMode = json["SCOM"]; colorMode = colorMode-1; procesColourMode();} // memoryByte = 'c'; processChange();} // THIS ONE
          else if (variable == "SHUE"){yval = json["SHUE"]; forcedColourChange = true;}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, yval), yval);  EEPROM.commit();};}
          else if (variable == "TSYN"){syncEsp = json["TSYN"];}
          else if (variable == "TSCN"){colourSyncToggle = json["TSCN"];}
          else if (variable == "SHUY"){yval1 = json["SHUY"];}
          else if (variable == "SYOL"){yold = json["SYOL"];}
          else if (variable == "ZVAL"){for (int n = 0; n < 30; n++){z[n] = json["ZVAL"][n];};}
          else if (variable == "SNCO"){numcolor = json["SNCO"];   newColors++; if (whiteON){for (int t=0; t<15; t++){satval[t]=S; satval[0]=0;}}      else if (!whiteON){for (int t=0; t<15; t++){satval[t]=S;}}}
          else if (variable == "SNCL"){colorlength = json["SNCL"]; newColors++; }// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, colorlength), colorlength);  EEPROM.commit();};}
          else if (variable == "SSCO"){z5 = json["SSCO"]; }
          else if (variable == "CSYN"){colourSync = json["CSYN"];}
          else if (variable == "SHYX"){yx = json["SHYX"];}
          else if (variable == "SHYY"){y0r = json["SHYY"];}
          else if (variable == "SHYR"){ysr = json["SHYR"];}
          else if (variable == "rdy"){readyToChange = json["rdy"];}
          else if (variable == "rn6"){rn6 = json["rn6"];}// fillLongxArray(yold, NUM_LEDS);}
          else if (variable == "SHYS"){yval1 = json["SHYS"]; inColourSync = true; }
          else if (variable == "cn"){cn = json["cn"];}// fillLongxArray(yold, NUM_LEDS);}
          else if (variable == "SHYT"){yval1 = json["SHYT"]; inColourSync = true; hh=NUM_LEDS;  flakeCounter=0;  for (int s=0; s < numsparks; s++){num17[s]=NUM_LEDS; num26[s]=0; rn[s]=random(NUM_LEDS);}}
          else if (variable == "SHYP"){yval1 = json["SHYP"]; inColourSync = true; partialArrayCounter=0;}
          else if (variable == "SYNE"){inSync = json["SYNE"];}
          else if (variable == "SYNC"){inColourSync = json["SYNC"];} 
          else if (variable == "dir1"){dir1 = json["dir1"];}
          else if (variable == "SPGM"){programMode = json["SPGM"]; cycleT=0;  previousMillis44 = millis();  previousMillis45 = millis(); changeState();} //Serial.print("containsprogramMode"); Serial.println(programMode); // if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, programMode), programMode);  EEPROM.commit();};          
 
          else if (variable == "SBRI"){BRIGH = json["SBRI"];}
          else if (variable == "SGLO"){glowON = json["SGLO"];}
          else if (variable == "SOBR"){offBr = json["SOBR"];}
          else if (variable == "SNBR"){numbrigh = json["SNBR"];}
          else if (variable == "SBWS"){waveTimeBr = json["SBWS"];}
          else if (variable == "SSBS"){BPMB = json["SSBS"];}
          else if (variable == "SSBR"){BrF = json["SSBR"];}
          else if (variable == "CONB"){convBrigh = json["CONB"];}

          else if (variable == "SSAT"){S = json["SSAT"];}
          else if (variable == "SSTM"){satON = json["SSTM"];}
          else if (variable == "SOST"){offS = json["SOST"];}
          else if (variable == "SSTN"){numsat = json["SSTN"];}
          else if (variable == "SSWS"){waveTimeS = json["SSWS"];}
          else if (variable == "SSSS"){BPMS = json["SSSS"];}
          else if (variable == "SSSF"){SF = json["SSSF"];}
          else if (variable == "CONS"){convSat = json["CONS"];}

          else if (variable == "SBOF"){ledOffset = json["SBOF"];}
          else if (variable == "SBOV"){overLay = json["SBOV"];}
          else if (variable == "SOSS"){overlaySpeed = json["SOSS"];} 

          else if (variable == "SSOF"){ledOffsetS = json["SSOF"];}
          else if (variable == "SSOV"){overLayS = json["SSOV"];}
          else if (variable == "SOSP"){overlaySpeedS = json["SOSP"];}  

          else if (variable == "YMIR"){yminrood = json["YMIR"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);};}
          else if (variable == "YMAR"){ymaxrood = json["YMAR"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);};}
          else if (variable == "YMIG"){ymingroen = json["YMIG"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);};}
          else if (variable == "YMAG"){ymaxgroen = json["YMAG"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);};}
          else if (variable == "YMIB"){yminblauw = json["YMIB"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);};}
          else if (variable == "YMAB"){ymaxblauw = json["YMAB"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);};}          
        }
}
#else

// Callback when data is received

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
        DEBUG_PRINTLN("Message received.");
        memcpy(&dataEspNow, incomingData, sizeof(dataEspNow));
        dataEspNow[len] = 0;
        for (int i = 0; i < len; i++){
          //Serial.print(dataEspNow[i]);
        }
        //Serial.print("Bytes received: ");
        //Serial.println(len);
        inSync = true;
        previousMillis15 = millis();
//         incomingMessage = true;
// }

        DEBUG_PRINTLN(F("received JSON espnow message: "));
        for (int i = 0; i < len; i++){
        //strval[i]=(char)data[i];    
        DEBUG_PRINT((char)incomingData[i]);
        }
        DEBUG_PRINTLN(" ");

        StaticJsonDocument<255> json;
        //DeserializationError err = deserializeJson(json, incomingData);
        DeserializationError err = deserializeJson(json, dataEspNow);
        if (err) {
            DEBUG_PRINT(F("deserializeJson() failed with code "));
            DEBUG_PRINTLN(err.c_str());
            return;
        }
        // JsonObject object = json.to<JsonObject>();

        // for (int i = 0; i < object.size(); i++){
          JsonObject root = json.as<JsonObject>();

        // using C++11 syntax (preferred):
        for (JsonPair kv : root) {
            String variable = kv.key().c_str();
        //     Serial.println(kv.key().c_str());
        //     Serial.println(kv.value().as<char*>());
        // }
      
          if (variable == "SPST"){selectedPreset[programMode] = json["SPST"]; selectedPresetVariable = selectedPreset[programMode];}// Serial.println("selectbrispreset"); cycleT=0;  previousMillis44 = millis();  previousMillis45 = millis();  if (saveToEEPROM){int offsetPosition = offsetof(storeInEEPROM, selectedPreset[0]); EEPROM.put((offsetPosition + programMode), selectedPresetVariable);  EEPROM.commit();} changeState();}
      
          else if (variable == "SBSM"){BriSPreset = json["SBSM"]; readBriSData(BriSPreset);}// sendProgramInfo(1);}
          else if (variable == "SRED"){Red = json["SRED"]; loadHSV = true;}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Red), Red);  EEPROM.commit();};} 
          else if (variable == "SGRE"){Green = json["SGRE"]; loadHSV = true;}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Green), Green);  EEPROM.commit();};}   
          else if (variable == "SBLU"){Blue = json["SBLU"]; loadHSV = true;}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, Blue), Blue);  EEPROM.commit();};}
          
          else if (variable == "TCON"){cycle = json["TCON"]; } // Serial.println("cycle to false"); if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, cycle), cycle);  EEPROM.commit();};} // EEPROM
          else if (variable == "SGRA"){selectColor = json["SGRA"];   dir1=1;    ymax4 = pgm_read_byte(&selectColor_data[selectColor].ymax4);  ymin4 = pgm_read_byte(&selectColor_data[selectColor].ymin4);   setDifference = pgm_read_byte(&selectColor_data[selectColor].setDifference);    yval1=ymin4;   dir0=1;     fillArrayGradient(3, yval1, setDifference); changeColor = true;   if (effect_function == *rainbow_3){setDifference = 4;} sendProgramInfo(1);}
          else if (variable == "SPAL"){gCurrentPaletteNumber = json["SPAL"]; gTargetPalette =( gGradientPalettes[gCurrentPaletteNumber] );}
          else if (variable == "SCAR"){arrayn = json["SCAR"];     selectcolorArray();    newColors++;    if (colorMode != 4){for (int n = 0; n < 15; n++){newColour[n] = json["YV"][n];};};}  // THIS ONE
          
          else if (variable == "SDIF"){setDifference = json["SDIF"]; fillxmasArray();  setDifference2 = setDifference+5;} // diff[0]=0;     x = 1;  num = 0;        diff[1]=0;     xn = 1;    num7 = 0; } diffbeat=60000/(setDifference*4*100); diffbeat2=diffbeat/2;
          else if (variable == "SLSP"){changeSpeed = json["SLSP"];}
          else if (variable == "SVAR"){varON = json["SVAR"]; for (int p=0; p<10; p++){if (varON == 0){yvar[p]= 0; yvarg[p]= 0;} else {yvar[p]=yvarC[p]; yvarg[p]=yvargC[p];};};}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, varON), varON);  EEPROM.commit();};}
          else if (variable == "SCOM"){colorMode = json["SCOM"]; colorMode = colorMode-1; procesColourMode();} // memoryByte = 'c'; processChange();} // THIS ONE
          else if (variable == "SHUE"){yval = json["SHUE"]; forcedColourChange = true;}// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, yval), yval);  EEPROM.commit();};}
          else if (variable == "TSYN"){syncEsp = json["TSYN"];}
          else if (variable == "TSCN"){colourSyncToggle = json["TSCN"];}
          else if (variable == "SHUY"){yval1 = json["SHUY"];}
          else if (variable == "SYOL"){yold = json["SYOL"];}
          else if (variable == "ZVAL"){for (int n = 0; n < 30; n++){z[n] = json["ZVAL"][n];};}
          else if (variable == "SNCO"){numcolor = json["SNCO"];   newColors++; if (whiteON){for (int t=0; t<15; t++){satval[t]=S; satval[0]=0;}}      else if (!whiteON){for (int t=0; t<15; t++){satval[t]=S;}}}
          else if (variable == "SNCL"){colorlength = json["SNCL"]; newColors++; }// if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, colorlength), colorlength);  EEPROM.commit();};}
          else if (variable == "SSCO"){z5 = json["SSCO"]; }
          else if (variable == "CSYN"){colourSync = json["CSYN"];}
          else if (variable == "SHYX"){yx = json["SHYX"];}
          else if (variable == "SHYY"){y0r = json["SHYY"];}
          else if (variable == "SHYR"){ysr = json["SHYR"];}
          else if (variable == "rdy"){readyToChange = json["rdy"];}
          else if (variable == "rn6"){rn6 = json["rn6"];}// fillLongxArray(yold, NUM_LEDS);}
          else if (variable == "SHYS"){yval1 = json["SHYS"]; inColourSync = true; }
          else if (variable == "cn"){cn = json["cn"];}// fillLongxArray(yold, NUM_LEDS);}
          else if (variable == "SHYT"){yval1 = json["SHYT"]; inColourSync = true; hh=NUM_LEDS;  flakeCounter=0;  for (int s=0; s < numsparks; s++){num17[s]=NUM_LEDS; num26[s]=0; rn[s]=random(NUM_LEDS);}}
          else if (variable == "SHYP"){yval1 = json["SHYP"]; inColourSync = true; partialArrayCounter=0;}
          else if (variable == "SYNE"){inSync = json["SYNE"];}
          else if (variable == "SYNC"){inColourSync = json["SYNC"];} 
          else if (variable == "dir1"){dir1 = json["dir1"];}
          else if (variable == "SPGM"){programMode = json["SPGM"]; cycleT=0;  previousMillis44 = millis();  previousMillis45 = millis(); changeState();} //Serial.print("containsprogramMode"); Serial.println(programMode); // if (saveToEEPROM){EEPROM.put(offsetof(storeInEEPROM, programMode), programMode);  EEPROM.commit();};          
 
          else if (variable == "SBRI"){BRIGH = json["SBRI"];}
          else if (variable == "SGLO"){glowON = json["SGLO"];}
          else if (variable == "SOBR"){offBr = json["SOBR"];}
          else if (variable == "SNBR"){numbrigh = json["SNBR"];}
          else if (variable == "SBWS"){waveTimeBr = json["SBWS"];}
          else if (variable == "SSBS"){BPMB = json["SSBS"];}
          else if (variable == "SSBR"){BrF = json["SSBR"];}
          else if (variable == "CONB"){convBrigh = json["CONB"];}

          else if (variable == "SSAT"){S = json["SSAT"];}
          else if (variable == "SSTM"){satON = json["SSTM"];}
          else if (variable == "SOST"){offS = json["SOST"];}
          else if (variable == "SSTN"){numsat = json["SSTN"];}
          else if (variable == "SSWS"){waveTimeS = json["SSWS"];}
          else if (variable == "SSSS"){BPMS = json["SSSS"];}
          else if (variable == "SSSF"){SF = json["SSSF"];}
          else if (variable == "CONS"){convSat = json["CONS"];}

          else if (variable == "SBOF"){ledOffset = json["SBOF"];}
          else if (variable == "SBOV"){overLay = json["SBOV"];}
          else if (variable == "SOSS"){overlaySpeed = json["SOSS"];}     

          else if (variable == "SSOF"){ledOffsetS = json["SSOF"];}
          else if (variable == "SSOV"){overLayS = json["SSOV"];}
          else if (variable == "SOSP"){overlaySpeedS = json["SOSP"];}  

          else if (variable == "YMIR"){yminrood = json["YMIR"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);};}
          else if (variable == "YMAR"){ymaxrood = json["YMAR"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);};}
          else if (variable == "YMIG"){ymingroen = json["YMIG"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);};}
          else if (variable == "YMAG"){ymaxgroen = json["YMAG"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);};}
          else if (variable == "YMIB"){yminblauw = json["YMIB"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);};}
          else if (variable == "YMAB"){ymaxblauw = json["YMAB"]; fillxmasArray(); ysr=0; for (int i = 0; i < 10; i++){colour[i]=(numAmax/10*i);};}   
}
}
#endif
// Callback when data is sent

  #ifdef ESP8266
  void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {

  //     for (int i = 0; i < 6; i++ ){
  // DEBUG_PRINTLN((uint8_t)mac_addr[i]);
  // }
  //Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    DEBUG_PRINTLN("Delivery success");
      for (int i = 0; i < 10; i++){
          if (Mac[i*6] == macMem[0] && Mac[(i*6)+1] == macMem[1] && Mac[(i*6)+2] == macMem[2] && Mac[(i*6)+3] == macMem[3] && Mac[(i*6)+4] == macMem[4] && Mac[(i*6)+5] == macMem[5]) {
            inSyncCounter[i] = 0;
          }
        }
      espNowMessage = false;
  }
  else{
    DEBUG_PRINTLN("Delivery fail");
      for (int i = 0; i < 10; i++){
          if (Mac[i*6] == macMem[0] && Mac[(i*6)+1] == macMem[1] && Mac[(i*6)+2] == macMem[2] && Mac[(i*6)+3] == macMem[3] && Mac[(i*6)+4] == macMem[4] && Mac[(i*6)+5] == macMem[5]) {
            inSyncCounter[i]++;
            if (inSyncCounter[i] > 10){
              macConnected[i] = false;
              //sendProgramInfo(3);
            }
          }
        }
      if ((!macConnected[0]) && (!macConnected[1]) && (!macConnected[2]) && (!macConnected[3]) && (!macConnected[4]) && (!macConnected[5]) && (!macConnected[6]) && (!macConnected[7]) && (!macConnected[8]) && (!macConnected[9])){
        espNowMessage = false;
      }
      else {  
        espNowMessage = true;
      }
  }
}
  #else
  void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  // DEBUG_PRINT("\r\nLast Packet Send Status:\t");
  // DEBUG_PRINTLN(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");

  //   Serial.print("\r\nLast Packet Send Status:\t");
  // Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
    for (int i = 0; i < 6; i++){
    macMem[i] = (uint8_t)mac_addr[i];
    DEBUG_PRINT((uint8_t)mac_addr[i]);
    DEBUG_PRINT(" ");
    }
    DEBUG_PRINTLN(" ");

  if (status == ESP_NOW_SEND_SUCCESS){
    DEBUG_PRINTLN("Delivery success");
      for (int i = 0; i < 10; i++){
          if (Mac[i*6] == macMem[0] && Mac[(i*6)+1] == macMem[1] && Mac[(i*6)+2] == macMem[2] && Mac[(i*6)+3] == macMem[3] && Mac[(i*6)+4] == macMem[4] && Mac[(i*6)+5] == macMem[5]) {
            inSyncCounter[i] = 0;
          }
        }
      espNowMessage = false;
  }
  else {
    DEBUG_PRINTLN("Delivery fail");
      for (int i = 0; i < 10; i++){
          if (Mac[i*6] == macMem[0] && Mac[(i*6)+1] == macMem[1] && Mac[(i*6)+2] == macMem[2] && Mac[(i*6)+3] == macMem[3] && Mac[(i*6)+4] == macMem[4] && Mac[(i*6)+5] == macMem[5]) {
            inSyncCounter[i]++;
            if (inSyncCounter[i] > 10){
              macConnected[i] = false;
              //sendProgramInfo(3);
            }
          }
        }
      if ((!macConnected[0]) && (!macConnected[1]) && (!macConnected[2]) && (!macConnected[3]) && (!macConnected[4]) && (!macConnected[5]) && (!macConnected[6]) && (!macConnected[7]) && (!macConnected[8]) && (!macConnected[9])){
        espNowMessage = false;
      }
      else {  
        espNowMessage = true;
      }        
      } 
  }
  #endif