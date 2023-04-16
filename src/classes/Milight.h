#pragma once

#include <cstring>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <Arduino.h>
#include <ArduinoJson.h>



void addSlash(char* destination){
    if(destination[strlen(destination)-1] != '/') strcat(destination,"/");
}


class Milight{
    // const char* gatewayAddress = "http://192.168.1.50"; // gateways/0x1235/rgb_cct/1
    // const char* deviceId = "0x1235";
    // const char* remoteType = "rgb_cct";
    // const char* controllGroup = "1";

    const char* controllAddress = "http://192.168.1.50/gateways/0x1235/rgb_cct/1";


    public:
    int controllLight(uint8_t rgb[3], uint8_t brightness){
        WiFiClient client;
        HTTPClient http;
        

        http.begin(client,this->controllAddress);
        http.addHeader("Content-Type", "application/json");

        DynamicJsonDocument doc(1024);
        doc["state"] = "ON";
        doc["brightness"] = brightness;
        doc["color"]["r"] = rgb[0];
        doc["color"]["g"] = rgb[1];
        doc["color"]["b"] = rgb[2];

        String sending;
        serializeJson(doc,sending);

        int http_response_code = http.PUT(sending);

        http.end();
        return(http_response_code);
    }

    Milight(){

    }
};