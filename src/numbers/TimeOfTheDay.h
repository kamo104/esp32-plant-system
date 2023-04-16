#pragma once

#include <time.h>

class TimeOfTheDay{
    
    time_t cachedSecondsOfTheDay;
    bool isCached=false;
    tm date;

    time_t cacheSecondsOfTheDay(){
        this->isCached = true;

        time_t output=0;

        output+=this->date.tm_hour*60*60;
        output+=this->date.tm_min*60;
        output+=this->date.tm_sec;

        this->cachedSecondsOfTheDay = output;
        return output;
    }

    public:
    void setDate(tm date){
        this->date = date;
        this->cacheSecondsOfTheDay();
    }

    void setSeconds(uint8_t seconds){
        this->date.tm_sec = seconds;
        this->cacheSecondsOfTheDay();
    }
    void setMinute(uint8_t minute){
        this->date.tm_min = minute;
        this->cacheSecondsOfTheDay();
    }
    void setHour(uint8_t hour){
        this->date.tm_hour = hour;
        this->cacheSecondsOfTheDay();
    }

    tm getDate(){
        return this->date;
    }

    time_t toSeconds(){

        if(this->isCached) return this->cachedSecondsOfTheDay;
        else return this->cacheSecondsOfTheDay();
        
    }

    bool isBetween(TimeOfTheDay windowStart,TimeOfTheDay windowEnd){
        time_t t1 = this->toSeconds();
        time_t t2 = windowStart.toSeconds();
        time_t t3 = windowEnd.toSeconds();

        if(t2<=t3) return t1<=t3 && t1>=t2;
        if(t2>t3) return t1>t2 || t1<=t3;

        return false;
    
    }
    time_t differenceInSeconds(TimeOfTheDay time){
        return this->toSeconds()-time.toSeconds();
    }


    TimeOfTheDay(tm date){
        this->date = date;
        this->cacheSecondsOfTheDay();
    }
    TimeOfTheDay(){}
};