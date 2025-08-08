#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Harshdip";
const char* password = "harshu123";

float tempVal = 0.0, lightVal = 0.0, gasVal = 0.0;


unsigned long lastSendTime = 0;
const unsigned long sendInterval = 5000; 

void setup() {
  Serial.begin(9600); 
  Serial.flush();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Read and parse serial input from STM32 continuously
  while (Serial.available()) {
    String input = Serial.readStringUntil('\n'); 
    input.trim();
    Serial.println(input); // debug print

 
    int sep = input.indexOf(':');
    if (sep != -1) {
      String name = input.substring(0, sep);
      String val = input.substring(sep + 1);
      val.trim();

      if (name.indexOf("LM-35") != -1) tempVal = val.toFloat();
      else if (name.indexOf("LDR") != -1) lightVal = val.toFloat();
      else if (name.indexOf("MQ-132") != -1) gasVal = val.toFloat();
    }
  }


  if (millis() - lastSendTime >= sendInterval) {
    lastSendTime = millis();

    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient wifiClient;
      HTTPClient http;

    
      String jsonBody = String("{\"location\":\"Indrayani\",") +
                        "\"temperature\":" + String(tempVal, 2) + "," +
                        "\"light\":" + String(lightVal, 2) + "," +
                        "\"gas\":" + String(gasVal, 2) + "}";

      Serial.println(jsonBody); 

      http.begin(wifiClient, "http://10.123.88.131:4000/sensors");
      http.addHeader("Content-Type", "application/json");

      int status = http.POST(jsonBody);
      Serial.printf("HTTP Status: %d\n", status);
      http.end();
    }
  }
}
