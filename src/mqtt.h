// ------------------------------------------------------------
// // Publish Home Assistant discovery config (retained once)
// // ======= Publish Home Assistant discovery config (retained once) =======
// void publishDiscovery() {
//     StaticJsonDocument<256> doc;
//     doc["name"] = String(DEVICE_NAME) + " IP";
//     doc["state_topic"] = stateTopic;
//     doc["unique_id"] = String(DEVICE_ID) + "_ip";
//     doc["availability_topic"] = aliveTopic;
//     doc["value_template"] = "{{ value_json.ip }}";

//     JsonObject device = doc.createNestedObject("device");
//     device["identifiers"] = DEVICE_ID;
//     device["name"] = DEVICE_NAME;
//     device["manufacturer"] = "DIY";
//     device["model"] = "ESP32 FastLED Controller";

//     char buffer[256];
//     serializeJson(doc, buffer);

//     mqtt.publish(discoveryTopic.c_str(), buffer); // ✅ works
// }

// void publishAlive() {
//     mqtt.publish(aliveTopic.c_str(), "online");  // no retained
// }


// // ------------------------------------------------------------
// void connectMqtt() {
//   while (!mqtt.connected()) {
//     Serial.print("Connecting to MQTT...");
//     if (mqtt.connect(DEVICE_ID, MQTT_USER, MQTT_PASS)) { // ✅ only supported args
//       Serial.println(" connected");
//       publishDiscovery();
//       publishIP();
//       publishAlive();
//     } else {
//       Serial.print(" failed, rc=");
//       Serial.print(mqtt.state());
//       Serial.println(" retrying in 5 seconds");
//       delay(5000);
//     }
//   }
// }
