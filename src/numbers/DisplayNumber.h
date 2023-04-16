#ifndef DISPLAY_NUMBER_H
#define DISPLAY_NUMBER_H

#include <Arduino.h>
#include "BoundedNumber.h"

class DisplayNumber : public BoundedNumber{
    public:
    // 0:normal number
    // 1:temperature in C
    // 2:humidity (%)
    uint8_t valueType;
    bool editable=true;
    uint8_t widthPosition=0;
    uint8_t heightPosition=1;
    DisplayNumber(float startingValue, float minLimit, float maxLimit, float step, bool editable, uint8_t valueType, uint8_t widthPosition=0, uint8_t heightPosition=1): BoundedNumber(startingValue, minLimit, maxLimit, step){
        this->valueType = valueType;
        this->editable = editable;
        this->widthPosition = widthPosition;
        this->heightPosition = heightPosition;
    }
    DisplayNumber(){}
};  

#endif