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
    bool isWifiApConfigurationValid();
    bool isWifiStationConfigurationValid();
    bool isMqttConfigurationValid();
    bool isMqttEnabled();
    void writeConfiguration(const char* configuration);

};

#endif
