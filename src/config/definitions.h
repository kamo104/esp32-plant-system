#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <Arduino.h>
#include "../numbers/BoundedNumber.h"
#include "../numbers/DisplayNumber.h"
#include "../numbers/TimeOfTheDay.h"

// lcd definitions
#define LCD_WIDTH (uint8_t)16
#define LCD_HEIGHT (uint8_t)2

unsigned long lastHumanInteraction = 0;
unsigned long lcdTurnOffTimeout = 1000*60*2;
DisplayNumber* lcdTurnOffAfter;
unsigned long lcdCheckTurnoffFrequency = 1000*15;

#define REFRESH_RATE (uint8_t)40
unsigned long refreshRate = 100;

unsigned long lastDisplayUpdate=0;

// dht setup
#define DHTPIN 25
#define DHTTYPE DHT11

unsigned long lastDhtRead=0;
unsigned long dhtReadInterval=2000;

// input setup
#define NUM_BUTTONS (uint8_t)4
#define LEFT_BUTTON_PIN (uint8_t)34
#define RIGHT_BUTTON_PIN (uint8_t)35
#define ENTER_BUTTON_PIN (uint8_t)32
#define BACK_BUTTON_PIN (uint8_t)33

// LED setup
#define RED_PIN (uint8_t)19
#define GREEN_PIN (uint8_t)18
#define BLUE_PIN (uint8_t)23

const int freq = 1000;
const int redLedChannel = 0;
const int greenLedChannel = 1;
const int blueLedChannel = 2;
const int resolution = 16;
const int maxLedNumber = int(pow(2,8)-1);
const float maxDutyCycleValue = int(pow(2,resolution))-1;
const float ledScalingFactor = int(pow(2,resolution-8))+1; // experiments with increasing accuracy at low brightness levels

// start eeprom and set up the operating values for leds
    // 0 == brightness
    // 1 == red
    // 2 == green
    // 3 == blue
    // 4 == sunriseStartMinute
    // 5 == sunriseStartHour
    // 6 == sunriseEndMinute
    // 7 == sunriseEndHour
    // 8 == sunsetStartMinute
    // 9 == sunsetStartHour
    // 10 == sunsetEndMinute
    // 11 == sunsetEndHour
    // 12 == sunBrightness
#define EEPROM_SIZE 13

unsigned long lastLedChange = 0;
unsigned long lastLedStateSave = 0;
unsigned long memorySaveFrequency = 15000;

#define MAIN_PAGES_NUM 4

// for hid
volatile bool buttonPresses[4];



// config for ntp and wifi
const char* ssid       = "WIFI_SSID";
const char* password   = "PASSWORD";

const char* ntpServer = "time1.google.com";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

bool connectionMode=1; // connect to wifi or not

// global time variable
tm globalTime;
TimeOfTheDay globalTimeOfTheDay;


// config for milight controll
uint8_t milightColor[3] = {255,106,0};
DisplayNumber milighthubBrightness(0,0,255,1,1,0,0,1);


unsigned long milightRoutineFrequency = 10000;

// sunrise
TimeOfTheDay sunriseStartTime;
TimeOfTheDay sunriseEndTime;

// sunset
TimeOfTheDay sunsetStartTime;
TimeOfTheDay sunsetEndTime;

#endif