#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <littleFS.h>

const char *ssid = "HommeInternetBox";
const char *password = "***********";

const int led = 2;
const int brightness = 0;

AsyncWebServer server(80);

void setup() {
  // -----------------------------------------------------Serial
  Serial.begin(115200);
  while(!serial){
    Serial.println("\n");
  }
  // -----------------------------------------------------GPIO
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  pinMode(brightness, INPUT);
  // -----------------------------------------------------littleFC
  if(!LittleFS.begin()){
    Serial.println("LittleFS Mount Failed");
    while(1){}
  }

  File root = LittleFS.open("/");
  File file = root.openNextFile();
  while(file){
    Serial.print("File: ");
    Serial.println(file.name());
    file.close();
    file = root.openNextFile();
  }
  // -----------------------------------------------------Wifi
  Wifi.begin(ssid, password);
  Serial.println("connexion wifi start ...");
  while(!Wifi.isConnected()){
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nconnexion wifi ok");
  Serial.println("IP: ");
  Serial.println(Wifi.localIP());

  // -----------------------------------------------------Server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });
  server.on("/W3-style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/W3-style.css", "text/css");
  });
  server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/main.js", "text/javascript");
  });
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });
  server.on("/brightness", HTTP_GET, [](AsyncWebServerRequest *request){
    int val analogRead(brightness);
    String brightness = String(val)
    request->send(200,  "text/plain", brightness);
  });
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(led, HIGH);
    request->send(200);
  });
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(led, LOW);
    request->send(200);
  });
  server.begin();
  Serial.println("server start ...");

}

void loop() {
  // put your main code here, to run repeatedly:
}