#ifndef VARIABLES_INIT_H
#define VARIABLES_INIT_H

#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <time.h>


#include "definitions.h"

#include "../numbers/DisplayNumber.h"

// current time numbers
DisplayNumber* currentHour;
DisplayNumber* currentMinute;

// sunrise and sunset numbers
DisplayNumber* sunriseStartHour;
DisplayNumber* sunriseStartMinute;
DisplayNumber* sunriseEndHour;
DisplayNumber* sunriseEndMinute;

DisplayNumber* sunsetStartHour;
DisplayNumber* sunsetStartMinute;
DisplayNumber* sunsetEndHour;
DisplayNumber* sunsetEndMinute;

DisplayNumber* sunBrightness;


unsigned long lastMilightChange=0;
unsigned long lastMilightSave=0;


// led numbers
DisplayNumber* brightnessNumber;
DisplayNumber* redNumber;
DisplayNumber* greenNumber;
DisplayNumber* blueNumber;


// dht numbers
DisplayNumber* temperatureNumber;
DisplayNumber* humidityNumber;


DisplayNumber* backlightNumber = new DisplayNumber(1,0,1,1,1,0,0,1);

DHT* dht = new DHT(DHTPIN, DHTTYPE);
LiquidCrystal_I2C* lcd = new LiquidCrystal_I2C(0x27,LCD_WIDTH,LCD_HEIGHT);



#endif