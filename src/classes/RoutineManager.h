#ifndef ROUTINE_MANAGER_H
#define ROUTINE_MANAGER_H

#include "../config/definitions.h"
#include "../misc/list.h"

struct Routine{
    void (*function)(unsigned long tickTime, Routine* self);
    unsigned long* lastVariableUpdate;
    unsigned long* updateIntervalLength;
};



class RoutineManager{
    DataTypes::List<Routine*> routines;
    public:
    
    void addRoutine(Routine* routine){
        this->routines.push(routine);
    }

    void tick(unsigned long tickTime){
        // execute each function with ticktime and a pointer to itself
        for(uint8_t i=0;i<this->routines.currentPos()+1;i++){
            if(tickTime - *(this->routines[i]->lastVariableUpdate) > *this->routines[i]->updateIntervalLength){
                (this->routines[i]->function)(tickTime, this->routines[i]);
            }
            
        } 
    }
    RoutineManager(){}

    RoutineManager(DataTypes::List<Routine*> routines){
        this->routines = routines;
    }
};



#endif