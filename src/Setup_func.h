void serialMonitor(){
    Serial.begin(115200); 
}

void oledDisplay(){
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
    }
    display.display();
    FastLED.delay(200); // Pause for 200 milliseconds
    display.clearDisplay();
    display.setTextSize(1); 
    display.setTextColor(WHITE,BLACK);  
    display.setCursor (0,0);
}

void spiffs(){
    if( !SPIFFS.begin()){
      Serial.println("Error mounting SPIFFS");
      while(1);
    }
}

void eeprom(){
      EEPROM.begin(3200);
}

void initializeEEPROM(){
    #ifdef ESP8266
    int check;
    EEPROM.get(0, check);
    #else
    int check  = EEPROM.readInt(0);
    #endif

    Serial.print(F("size of EEPROM: ")); Serial.println(sizeof(customVar));
    
    if (check == 11223){
    display.print(F("code: ")); display.println(check);
    display.println(F("EEPROM SET"));
    display.display();
    printEEPROM();
    initializeEEPROMvariables(); // functio in global_variables.h at the bottom.    
    cfactor2=NUM_LEDS/100;
    cfactor3=NUM_LEDS/100;
    //cfactor1=300/NUM_LEDS;//
    convBrigh=waveTimeBr/numbrigh;
    convSat=waveTimeS/numsat;
      if (cfactor2 > 3){cfactor2 = 3;} 
      else if (cfactor2 < 1){
        cfactor2 = 1;
        cfactor3 = 1;
        }; 
    Serial.print(F("NUM_LEDS: ")); Serial.println(NUM_LEDS);
    FastLED.delay(1000);
    }
    
    else if (check != 11223){
    display.println(F("EEPROM not initialized"));
    display.println(F("Writing to EEPROM...."));
    display.display();
    FastLED.delay(2500);
    int eeAddress=0;
    EEPROM.put(eeAddress, customVar);
    EEPROM.commit();
    display.println(F("EEPROM is initialized"));
    display.display();
    FastLED.delay(2500);
    ESP.restart();
    }
    display.clearDisplay();
}

void wifi(){
  int wifiCounter=0;
  
  #ifdef ESP8266
  WiFi.hostname("xglow");
  #else
  #endif
  
  WiFi.mode(WIFI_STA);

  #ifdef ESP32
  String hostname = "xglow";
  WiFi.setHostname(hostname.c_str()); //define hostname
  #else
  #endif
 
  const char *WIFI_SSID = &wifiID[0];
  const char *WIFI_PASS = &wifiPASS[0];
  WiFi.begin(WIFI_SSID, WIFI_PASS);  
  Serial.printf("Trying to connect [%s] ", WiFi.macAddress().c_str());

  while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
       display.clearDisplay();
      display.setCursor(0,0);
      display.println(F("connecting to wifi..."));
      display.display();
      delay(500);
      wifiCounter++;
      if (wifiCounter > 30){
      break;  
      }
  }
  if (wifiCounter >30){
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(WIFI_SSID_AP, WIFI_PASS_AP);
  Serial.println(F("soft-AP IP:"));
  display.println(F("soft-AP IP:"));
  Serial.println(WiFi.softAPIP());
  display.println(WiFi.softAPIP());
  Serial.printf(" %s\n", WiFi.softAPIP().toString().c_str());
  display.display();    
  }
  else {
    Serial.printf(" %s\n", WiFi.localIP().toString().c_str());
  }  
    
  initWebSocket();
  initWebServer();
}

void espNow(){
  // Initilize ESP-NOW
  #ifdef ESP8266
    // Initializing the ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Problem during ESP-NOW init");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  // Register the peer
    for (int i = 0; i < num_esp; i++){
    uint8_t broadcastAddress[6] = {Mac[i*6], Mac[(i*6)+1], Mac[(i*6)+2], Mac[(i*6)+3], Mac[(i*6)+4], Mac[(i*6)+5]};
      Serial.println("Registering a peer");
      esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
    }

    Serial.println("Registering send callback function");
    esp_now_register_send_cb(onSent);
    //esp_now_register_send_cb(OnDataSent);

    //esp_now_register_recv_cb(OnDataRecv);

  #else
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  for (int i = 0; i < num_esp; i++){
    uint8_t broadcastAddress[6] = {Mac[i*6], Mac[(i*6)+1], Mac[(i*6)+2], Mac[(i*6)+3], Mac[(i*6)+4], Mac[(i*6)+5]};
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;
    Serial.print("added peer: ");// Serial.print(i); Serial.print(" "); Serial.print(broadcastAddress[0]); Serial.print(" "); Serial.print(broadcastAddress[1]); Serial.print(" "); Serial.print(broadcastAddress[2]); Serial.print(" "); Serial.print(broadcastAddress[3]); Serial.print(" "); Serial.print(broadcastAddress[4]); Serial.print(" "); Serial.println(broadcastAddress[5]);
    
    // Add peer        
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
      Serial.println("Failed to add peer");
      return;
    }
  }

      // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
  #endif
//}
}

void LED_properties(){
    #ifdef ESP8266
    EEPROM.get(offsetof(storeInEEPROM, rgbcolor), RGBCOLOR);
    const byte rgbcolor = RGBCOLOR;
    RGBCOLOR = rgbcolor;
    #else
    const byte rgbcolor =  EEPROM.readByte(offsetof(storeInEEPROM, rgbcolor)); 
    RGBCOLOR = rgbcolor;
    #endif

    switch (rgbcolor){
      case 0: FastLED.addLeds<WS2811,DATA_PIN, RGB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); break; // RGB is also COL_ORD[0] - old definition.
      case 1: FastLED.addLeds<WS2811,DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); break;
      case 2: FastLED.addLeds<WS2811,DATA_PIN, BRG>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); break;
      case 3: FastLED.addLeds<WS2811,DATA_PIN, BGR>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); break;
      case 4: FastLED.addLeds<WS2811,DATA_PIN, RBG>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); break;
      case 5: FastLED.addLeds<WS2811,DATA_PIN, GBR>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); break;
      default: FastLED.addLeds<WS2811,DATA_PIN, RGB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); break;
    } 

}

void initialize_preset(){
    changeModus = true;
    Serial.print("progMode: "); Serial.println(programMode);
    handleModeInitialization();
}

void seedRandomNumbers(){
    uint32_t randomSeedNumber = ESP.getCycleCount();
    Serial.print(F("seednumber ")); Serial.println(randomSeedNumber);
    randomSeed(randomSeedNumber);
}


void endSetup(){
      display.clearDisplay();
    display.setCursor(0,0);
  
    display.printf(" %s\n", WiFi.localIP().toString().c_str());
    display.printf(" %s\n", WiFi.softAPIP().toString().c_str());    

    display.println(F("setup complete"));
  //    display.println(F("mDNS: esp32.local/"));
    display.display();  
    
    delay(1000); 
}
