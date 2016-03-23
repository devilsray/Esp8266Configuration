#include <FS.h>
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson
#include "Esp8266Configuration.h"
#include <map>

// wifi ap variables
char* wifi_ap_ssid = new char[255];
char* wifi_ap_password = new char[255];
bool wifi_ap_enabled = new char[255];

// wifi station variables
char* wifi_station_ssid = new char[255];
char* wifi_station_password = new char[255];
bool wifi_station_enabled = new char[255];

// mqtt configuration variables
bool mqtt_enabled = new char[255];
char* mqtt_host = new char[255];
char* mqtt_user = new char[255];
char* mqtt_password = new char[255];
int mqtt_port = 1883;

void Esp8266Configuration::setWifiApSsid(char* ssid){
  wifi_ap_ssid = ssid;
}
void Esp8266Configuration::setWifiApPassword(char* password){
  wifi_ap_password = password;
}
void Esp8266Configuration::setWifiStationSsid(char* ssid){
  wifi_station_ssid = ssid;
}
void Esp8266Configuration::setWifiStationPassword(char* password){
  wifi_station_password = password;
}
void Esp8266Configuration::setMqttServer(char* server){
  mqtt_host = server;
}
void Esp8266Configuration::setMqttPort(int port){
  mqtt_port = port;
}
void Esp8266Configuration::setMqttPassword(char* password){
  mqtt_password = password;
}
void Esp8266Configuration::setMqttUser(char* user){
  mqtt_user = user;
}

char* Esp8266Configuration::getWifiApSsid(){
  return wifi_ap_ssid;
}
char* Esp8266Configuration::getWifiApPassword(){
  return wifi_ap_password;
}
char* Esp8266Configuration::getWifiStationSsid(){
  return wifi_station_ssid;
}
char* Esp8266Configuration::getWifiStationPassword(){
  return wifi_station_password;
}

char* Esp8266Configuration::getMqttServer(){
  return mqtt_host;
}

int Esp8266Configuration::getMqttPort(){
  return mqtt_port;
}

char* Esp8266Configuration::getMqttUser() {
  return mqtt_user;
}

char* Esp8266Configuration::getMqttPassword() {
  return mqtt_password;
}

void Esp8266Configuration::write(){
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["wifi_ap_ssid"] = wifi_ap_ssid;
  json["wifi_ap_password"] = wifi_ap_password;
  json["wifi_ap_enabled"] = wifi_ap_enabled;
  json["wifi_station_ssid"] = wifi_station_ssid;
  json["wifi_station_password"] = wifi_station_password;
  json["wifi_station_enabled"] = wifi_station_enabled;

  json["mqtt_enabled"] = mqtt_enabled;
  json["mqtt_host"] = mqtt_host;
  json["mqtt_port"] = mqtt_port;
  json["mqtt_user"] = mqtt_user;
  json["mqtt_password"] = mqtt_password;
  //
  File configFile = SPIFFS.open("/configuration.json", "w");
  if (!configFile) {
    Serial.println("failed to open config file for writing");
  }
  //
  json.printTo(Serial);
  json.printTo(configFile);
  configFile.close();
}


bool Esp8266Configuration::isWifiApConfigurationValid(){

  return (
    wifi_ap_password != NULL &&
    strlen(wifi_ap_password) > 7 &&
    wifi_ap_ssid != NULL &&
    strlen(wifi_ap_ssid) >2
  );
}

bool Esp8266Configuration::isWifiStationConfigurationValid(){

  return (
    wifi_station_password != NULL &&
    strlen(wifi_station_password) > 7 &&
    wifi_station_ssid != NULL &&
    strlen(wifi_station_ssid) >2
  );
}

bool Esp8266Configuration::isWifiApEnabled(){
  return wifi_ap_enabled;
}

bool Esp8266Configuration::isWifiStationEnabled(){
  return wifi_station_enabled;
}

bool Esp8266Configuration::isMqttEnabled() {
  return mqtt_enabled;
}

bool Esp8266Configuration::isMqttConfigurationValid(){

  return (
    mqtt_host != NULL &&
    sizeof mqtt_host > 3 &&
    mqtt_port > 1000 &&
    mqtt_port < 30000
  );
}

void Esp8266Configuration::writeConfiguration(const char* configuration){
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(configuration);
  json.printTo(Serial);
  File configFile = SPIFFS.open("/configuration.json", "w");
  if (!configFile) {
    Serial.println("failed to open config file for writing");
  }
  //
  json.printTo(configFile);
  configFile.close();
}

void Esp8266Configuration::read(){
  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/configuration.json")) {
      //     //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/configuration.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          Serial.println("\nparsed json");
          Serial.println("trying wifi_ap_ssid");
          if (json.containsKey("wifi_ap_ssid")) {
            const char* value = json["wifi_ap_ssid"];
            Serial.println(value);
            if (value != NULL) {
              Serial.println(value);
              strcpy(wifi_ap_ssid, value);
            }
          }
          Serial.println("trying wifi_ap_password");
          if (json.containsKey("wifi_ap_password")) {
            const char* value = json["wifi_ap_password"];
            if (value != NULL) {
              Serial.println(value);
              strcpy(wifi_ap_password, value);
            }
          }
          Serial.println("trying wifi_station_ssid");
          if (json.containsKey("wifi_station_ssid")) {
            const char* value = json["wifi_station_ssid"];
            if (value != NULL) {
              Serial.println(value);
              strcpy(wifi_station_ssid, value);
            }
          }
          Serial.println("trying wifi_station_password");
          if (json.containsKey("wifi_station_password")) {
            const char* value = json["wifi_station_password"];
            if (value != NULL) {
              Serial.println(value);
              strcpy(wifi_station_password, value);
            }
          }
          Serial.println("trying mqtt_host");
          if (json.containsKey("mqtt_host")) {
            const char* value = json["mqtt_host"];
            if (value != NULL) {
              Serial.println(value);
              strcpy(mqtt_host, value);
            }
          }
          Serial.println("trying mqtt_port");
          if (json.containsKey("mqtt_port")) {
            const char* value = json["mqtt_port"];
            if (value != NULL) {
              Serial.println(value);
              mqtt_port = atoi(value);
            }
          }
          Serial.println("trying mqtt_user");
          if (json.containsKey("mqtt_user")) {
            const char* value = json["mqtt_user"];
            if (value != NULL) {
              Serial.println(value);
              strcpy(mqtt_user, value);
            }
          }
          Serial.println("trying mqtt_password");
          if (json.containsKey("mqtt_password")) {
            const char* value = json["mqtt_password"];
            if (value != NULL) {
              Serial.println(value);
              strcpy(mqtt_password, value);
            }
          }
        } else {
          Serial.println("failed to load json config");
        }
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
  //end read
}
