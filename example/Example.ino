#include <FS.h>
#include <ESP8266WiFi.h>

#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson
#include <PubSubClient.h>
#include <Esp8266Configuration.h>
#include <ESP8266mDNS.h>

Esp8266Configuration configuration;
WiFiClient espClient;
PubSubClient client(espClient);

// retries til wfi station connection will be aborted
int wifiRetries = 30;

// setup the wifi station connection
void setup_wifi() {
  Serial.print("Connecting to ");
  Serial.println(configuration.getWifiStationSsid());
  Serial.println(configuration.getWifiStationPassword());
  WiFi.enableSTA(true);
  WiFi.begin(configuration.getWifiStationSsid(),configuration.getWifiStationPassword());

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    wifiRetries--;
    if (wifiRetries < 1) {
      Serial.println("WiFi failed");
      return;
    }
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");

  // read configuration from spiffs
  configuration.read();

  //
  configuration.setWifiStationSsid("BLA");
  configuration.setWifiStationPassword("12345678");
  configuration.setWifiApSsid("RTAWTSF");
  configuration.setMqttServer("faramir");
  configuration.setMqttPort(1883);
  configuration.write();
  configuration.read();

  Serial.println("Config is loaded. Going on to start up");

// primitive validation and logging
  if (configuration.isWifiApConfigurationValid() == false) {
    Serial.println("ap config is wrong");
  }
  if (configuration.isWifiStationConfigurationValid() == false) {
    Serial.println("station config is wrong");
  }


  // define which wifi mode should be used. May be added as helper function to configuration in future
  bool enableAp = false;
  bool enableStation = false;
  if (configuration.isWifiStationEnabled() && configuration.isWifiStationConfigurationValid()) {
    enableStation = true;
  } else {
    enableAp;
  }
  if (configuration.isWifiApEnabled()) {
    enableAp;
  }
  if (enableAp) {
    if (enableStation) {
      WiFi.mode(WIFI_AP_STA);
    } else {
      WiFi.mode(WIFI_AP);
    }
  } else if (enableStation) {
    WiFi.mode(WIFI_STA);
  }

  // if a wifi ap should be started, then do it
  if (enableAp){
    Serial.print("Starting Wifi AP ");
    if (configuration.isWifiApConfigurationValid()){
      Serial.println("using custom settings");
      Serial.println(configuration.getWifiApSsid());
      WiFi.softAP(configuration.getWifiApSsid(), configuration.getWifiApPassword());
    } else {
      Serial.println("using default settings");
      uint8_t mac[WL_MAC_ADDR_LENGTH];
      WiFi.softAPmacAddress(mac);
      String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
      String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
      macID.toUpperCase();
      String AP_NameString = "ESP8266 " + macID;
      char AP_NameChar[AP_NameString.length() + 1];
      memset(AP_NameChar, 0, AP_NameString.length() + 1);
      for (int i=0; i<AP_NameString.length(); i++)
      AP_NameChar[i] = AP_NameString.charAt(i);
      Serial.println(AP_NameChar);
      WiFi.softAP(AP_NameChar);
    }
  }

  // if a wifi station should connect to an ap, do this
  if (enableStation){
    setup_wifi();
  } else {
    Serial.println("Config is not active");
  }

  if (configuration.isMqttEnabled() && configuration.isMqttConfigurationValid()) {
    client.setServer(configuration.getMqttServer(), configuration.getMqttPort());
  }

}

// mqtt connect, reconnect handling
void reconnect() {
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("testdevice")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      Serial.printf("using server: ");
      Serial.println(configuration.getMqttServer());
      delay(2000);
    }
  }
}

void loop() {
  if (configuration.isMqttEnabled() && !client.connected() && configuration.isMqttConfigurationValid()) {
    reconnect();
  }
  client.loop(); // mqtt: consume new messages

  // post ip for testings
  Serial.printf("WiFi station ip ");
  Serial.println(WiFi.localIP() );
  Serial.println(configuration.getWifiStationSsid() );
  Serial.println(configuration.getWifiStationPassword() );
  Serial.println(WiFi.localIP() );
  delay(1000);
}
