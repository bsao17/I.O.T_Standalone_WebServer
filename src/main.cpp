#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

const char *ssid = "*********";
const char *password = "*********";

const int led = 2;
const int brightness = 34;

AsyncWebServer server(80);

void setup() {
  // -----------------------------------------------------Serial
  Serial.begin(115200);
  while(!Serial){
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

  File root = LittleFS.open("/", "r");
  File file = root.openNextFile();

  while(file){
    Serial.print("File: ");
    Serial.println(file.name());
    file.close();
    file = root.openNextFile();
  }
  // -----------------------------------------------------Wifi
  WiFi.begin(ssid, password);
  Serial.println("connexion wifi start ...");

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println("\n connexion wifi ok");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());

  // -----------------------------------------------------Server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", "text/html");
  });
  server.on("/W3-style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/W3-style.css", "text/css");
  });
  server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/main.js", "text/javascript");
  });
  server.on("/brightness", HTTP_GET, [](AsyncWebServerRequest *request){
    int val = analogRead(brightness);
    String brightness = String(val);
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