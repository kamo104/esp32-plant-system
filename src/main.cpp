#include <Arduino.h>


#include <DHT.h>
#include <Adafruit_Sensor.h>

#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

#include <time.h>
#include <WiFi.h>

#include "config/definitions.h"
#include "config/variablesInit.h"


#include "initialization/programClassesInit.h"
#include "initialization/InitPages.h"
#include "initialization/ledInit.h"
#include "initialization/interruptsInit.h"
#include "initialization/RoutinesInit.h"





void setup() {
    Serial.begin(9600);


    // connect to WiFi
    Serial.printf("Connecting to %s ", ssid);
    float timeToConnect=0;
    if(connectionMode == true) WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500); timeToConnect +=0.5;
        Serial.print(".");

        if(timeToConnect>=10){
            connectionMode=false;
            break;
        }
    }
    if(connectionMode == true) Serial.println(" CONNECTED");
    
    //init and get the time
    if(connectionMode == true) configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    // print the local time
    if(connectionMode == true ) if(!getLocalTime(&globalTime)){
        Serial.println("Failed to obtain time");
        return;
    }
    Serial.println(&globalTime, "%A, %B %d %Y %H:%M:%S");

    

    // start eeprom and set up the operating values for leds
    // 0 == brightness
    // 1 == red
    // 2 == green
    // 3 == blue
    // 4 == milightStartMinute
    // 5 == milightStartHour
    // 6 == milightEndMinute
    // 7 == milightEndHour
    EEPROM.begin(EEPROM_SIZE);


    // initialize the classes
    dht->begin();

    lcd->init();
    lcd->backlight();

    classesInit();

    display->createDegreesSymbol();
    

    // input buttons pins
    for(int i=0;i<NUM_BUTTONS;i++) pinMode(buttonConfig[i],INPUT_PULLUP);


    // initialize the led functions
    ledInit();

    // create the interrupts
    interruptsInit();


    onBrightnessChange(brightnessNumber->value());
    lastLedChange = lastLedStateSave; // otherwise we would trigger settings save inside a routine from onBrightnessChange after changing the led state

    // create the routines
    routinesInit();
}

void loop() {
    for(uint8_t i=0;i<NUM_BUTTONS;i++){
        ButtonEvent ev;
        ev.buttonIndex = i;
        ev.timestamp = millis();
        if(buttonPresses[i]){
            buttonPresses[i] = false;
            ev.buttonState = LOW;
        } 
        else ev.buttonState = digitalRead(buttonConfig[i]);
        
        inputManager->registerButtonEvent(ev);
    }
    
    routineManager->tick(millis());
}

