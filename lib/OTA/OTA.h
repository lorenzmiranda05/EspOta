#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

void setupOTA(const char* nameprefix, const char* ssid, const char* password)
{
    // Configure the hostname
    uint16_t maxlen = strlen(nameprefix) + 7;
    char *fullhostname = new char[maxlen];
    uint8_t mac[6];
    WiFi.macAddress(mac);
    snprintf(fullhostname, maxlen, "%s-%02x%02x%02x", nameprefix, mac[3], mac[4], mac[5]);
    ArduinoOTA.setHostname(fullhostname);
    Serial.println("Full Host Name: ");
    Serial.println(fullhostname);
    Serial.println("WiFi MAC Address: ");
    Serial.println(WiFi.macAddress());
    delete[] fullhostname;

    // Configure and start the WiFi station
    WiFi.mode(WIFI_STA); // Station Mode: the ESP32 connects to an access point
    WiFi.begin(ssid, password);

    // Wait for connection
    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }

    ArduinoOTA.onStart([]()
    {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH)
            type = "sketch";
        else // U_SPIFFS
            type = "filesystem";

        Serial.println("Start updating " + type);
    });
    
    ArduinoOTA.onEnd([]()
    {
        Serial.println("\nEnd");
    });
    
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
    {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    
    ArduinoOTA.onError([](ota_error_t error)
    {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("\nAuth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("\nBegin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("\nConnect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("\nReceive Failed");
        else if (error == OTA_END_ERROR) Serial.println("\nEnd Failed");
    });

    ArduinoOTA.begin();

    Serial.println("ESPOTA READY");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}