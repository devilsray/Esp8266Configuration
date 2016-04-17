
#include "Esp8266Configuration.h"


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

void Esp8266Configuration::setMqttDeviceName(char* deviceName){
  mqtt_device_name = deviceName;
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

char* Esp8266Configuration::getMqttDeviceName() {
  return mqtt_device_name;
}

char* Esp8266Configuration::getMqttPassword() {
  return mqtt_password;
}

void Esp8266Configuration::write(){
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json[PARAM_WIFI_AP_SSID]      = wifi_ap_ssid;
  json[PARAM_WIFI_AP_PASSWORD]  = wifi_ap_password;
  json[PARAM_WIFI_AP_ENABLED]   = wifi_ap_enabled;

  json[PARAM_WIFI_STATION_SSID]     = wifi_station_ssid;
  json[PARAM_WIFI_STATION_PASSWORD] = wifi_station_password;
  json[PARAM_WIFI_STATION_ENABLED]  = wifi_station_enabled;

  json[PARAM_MQTT_ENABLED]      = mqtt_enabled;
  json[PARAM_MQTT_HOST]         = mqtt_host;
  json[PARAM_MQTT_PORT]         = mqtt_port;
  json[PARAM_MQTT_USER]         = mqtt_user;
  json[PARAM_MQTT_PASSWORD]     = mqtt_password;
  json[PARAM_MQTT_DEVICE_NAME]  = mqtt_device_name;
  //
  File configFile = SPIFFS.open("/configuration.json", "w");
  if (!configFile) {
    Serial.println("failed to open config file for writing");
  }
  //
  json.printTo(Serial);
  json.printTo(configFile);
  configFile.close();
};

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
  if ( mqtt_host == NULL) return false;
  if ( mqtt_device_name == NULL) return false;
  if (mqtt_port < 1000) return false;
  if (mqtt_port > 30000) return false;
  return true;
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
          // reading wifi ap configuration
          readParameter(PARAM_WIFI_AP_SSID, wifi_ap_ssid, json);
          readParameter(PARAM_WIFI_AP_PASSWORD, wifi_ap_password, json);
          // reading wifi station configuration
          readParameter(PARAM_WIFI_STATION_SSID, wifi_station_ssid, json);
          readParameter(PARAM_WIFI_STATION_PASSWORD, wifi_station_password, json);
          // reading mqtt configuration
          readParameter(PARAM_MQTT_HOST, mqtt_host, json);
          readParameter(PARAM_MQTT_PORT, mqtt_user, json);
          readParameter(PARAM_MQTT_USER, mqtt_user, json);
          readParameter(PARAM_MQTT_PASSWORD, mqtt_password, json);
          readParameter(PARAM_MQTT_DEVICE_NAME, mqtt_device_name, json);
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

void Esp8266Configuration::readParameter(String parameterName, char* variable, JsonObject& json){
  if (json.containsKey(parameterName)) {
    const char* value = json[parameterName];
    if (value != NULL) {
      strcpy(variable, value);
    }
  }
}

void Esp8266Configuration::readParameter(String parameterName, int variable, JsonObject& json){
  if (json.containsKey(parameterName)) {
    const char* value = json[parameterName];
    if (value != NULL) {
      variable = atoi(value);
    }
  }
}
