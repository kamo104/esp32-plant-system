#ifndef PROGRAM_CLASSES_INIT_H
#define PROGRAM_CLASSES_INIT_H


#include "../classes/InputManager.h"
#include "../classes/Director.h"
#include "../classes/Menu.h"
#include "../classes/Display.h"
#include "../classes/RoutineManager.h"
#include "../classes/Milight.h"

#include "../initialization/InitPages.h"

Display* display;
Menu* menu;
Director* director;
InputManager* inputManager;
RoutineManager* routineManager;
Milight milight;



void classesInit(){
    

    display = new Display(LCD_WIDTH,LCD_HEIGHT,lcd);
    menu = new Menu(initPages(),MAIN_PAGES_NUM);
    director = new Director(menu, display);
    inputManager = new InputManager(director);
    routineManager = new RoutineManager();
}

#endif