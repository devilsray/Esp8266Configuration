#include <map>
#include <string>

#ifndef Esp8266Configuration_h
#define Esp8266Configuration_h

class Esp8266Configuration
{
  public:
    void read();
    void write();
    void setWifiApSsid(char* ssid);
    void setWifiApPassword(char* password);
    void setWifiStationSsid(char* ssid);
    void setWifiStationPassword(char* password);
    void setMqttServer(char* server);
    void setMqttPort(int port);
    void setMqttPassword(char* password);
    void setMqttUser(char* user);
    void writeConfiguration(const char* configuration);
    bool isWifiApEnabled();
    bool isWifiStationEnabled();
    int getMqttPort();
    char* getWifiApSsid();
    char* getWifiApPassword();
    char* getWifiStationSsid();
    char* getWifiStationPassword();
    char* getMqttServer();
    char* getMqttPassword();
    char* getMqttUser();
    bool isWifiApConfigurationValid();
    bool isWifiStationConfigurationValid();
    bool isMqttConfigurationValid();
    bool isMqttEnabled();

};

#endif
