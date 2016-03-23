#include <map>
#include <string>

#ifndef Configuration_h
#define Configuration_h

class Configuration
{
  public:
    void read();
    void write();
    bool isWifiApEnabled();
    bool isWifiStationEnabled();
    char* getWifiApSsid();
    char* getWifiApPassword();
    char* getWifiStationSsid();
    char* getWifiStationPassword();
    char* getMqttServer();
    int getMqttPort();
    char* getMqttPassword();
    char* getMqttUser();
    void setWifiApSsid(char* ssid);
    void setWifiApPassword(char* password);
    void setWifiStationSsid(char* ssid);
    void setWifiStationPassword(char* password);
    void setMqttServer(char* server);
    void setMqttPort(int port);
    void setMqttPassword(char* password);
    void setMqttUser(char* user);
    bool isWifiApConfigurationValid();
    bool isWifiStationConfigurationValid();
    bool isMqttConfigurationValid();
    bool isMqttEnabled();
    void writeConfiguration(const char* configuration);

};

#endif
