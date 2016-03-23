#include <map>
#include <string>

#ifndef Configuration_h
#define Configuration_h

class Configuration
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
