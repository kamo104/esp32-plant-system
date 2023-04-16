#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>
#include <time.h>

uint8_t numberLength(int number){
	if(number<10) return 0;
	uint8_t i=0;
	while(number/=10){
		i++;
	}
	return i;
}



#endif