#include <FS.h>
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson
//#include <GpioPwm.h>
//#include <list>

#ifndef Esp8266Configuration_h
#define Esp8266Configuration_h

// Wifi ap js/json parameter naming
const String PARAM_WIFI_AP_SSID          = "wifi_ap_ssid";
const String PARAM_WIFI_AP_PASSWORD      = "wifi_ap_password";
const String PARAM_WIFI_AP_ENABLED       = "wifi_ap_enabled";

// Wifi station js/json parameter naming
const String PARAM_WIFI_STATION_SSID     = "wifi_station_ssid";
const String PARAM_WIFI_STATION_PASSWORD = "wifi_station_password";
const String PARAM_WIFI_STATION_ENABLED  = "wifi_station_enabled";

// mqtt js/json parameter naming
const String PARAM_MQTT_ENABLED          = "mqtt_enabled";
const String PARAM_MQTT_HOST             = "mqtt_host";
const String PARAM_MQTT_USER             = "mqtt_user";
const String PARAM_MQTT_PASSWORD         = "mqtt_password";
const String PARAM_MQTT_DEVICE_NAME      = "mqtt_device_name";
const String PARAM_MQTT_PORT             = "mqtt_port";

const String CONFIG_FILE_NAME            = "configuration.json";

class Esp8266Configuration
{
  //std::list<GpioPwm> mapTest;

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
  char* mqtt_device_name = new char[255];
  int mqtt_port = 1883;

  public:
    // read configuration from spiffs
    void read();

    // write configuration to spiffs
    void write();

    // set wifi ap ssid (changes will not be stored until write is called)
    void setWifiApSsid(char* ssid);

    // set wifi ap password (changes will not be stored until write is called)
    void setWifiApPassword(char* password);

    // set wifi station ssid (changes will not be stored until write is called)
    void setWifiStationSsid(char* ssid);

    // set wifi station password (changes will not be stored until write is called)
    void setWifiStationPassword(char* password);

    // set mqtt server name or ip (changes will not be stored until write is called)
    void setMqttServer(char* server);

    // set mqtt server port (changes will not be stored until write is called)
    void setMqttPort(int port);

    // set mqtt users password (changes will not be stored until write is called)
    void setMqttPassword(char* password);

    // set mqtt username (changes will not be stored until write is called)
    void setMqttUser(char* user);

    // set mqtt device name (changes will not be stored until write is called)
    void setMqttDeviceName(char* deviceName);

    // write configuration to spiffs
    void writeConfiguration(const char* configuration);

    void readParameter(String parameterName, char* variable, JsonObject& json);

    void readParameter(String parameterName, int variable, JsonObject& json);

    // check if wifi ap is configured to be enabled
    bool isWifiApEnabled();

    // check if wifi station is configured to be enabled
    bool isWifiStationEnabled();

    // get the configured mqtt port
    int getMqttPort();

    // get the wifi ap ssid
    char* getWifiApSsid();

    // get the wifi ap password
    char* getWifiApPassword();

    // get the wifi station ssid
    char* getWifiStationSsid();

    // get the wifi station password
    char* getWifiStationPassword();

    // get the mqtt server name or ip
    char* getMqttServer();

    // get the mqtt users password
    char* getMqttPassword();

    // get the mqtt username
    char* getMqttUser();

    // get the mqtt device name
    char* getMqttDeviceName();

    // check if wifi ap configuration is valid
    bool isWifiApConfigurationValid();

    // check if wifi station configuration is valid
    bool isWifiStationConfigurationValid();

    // check if mqtt configuration is valid
    bool isMqttConfigurationValid();

    // check if mqtt is configured to be enabled
    bool isMqttEnabled();

};

#endif
