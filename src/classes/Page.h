#ifndef PAGE_H
#define PAGE_H

#include <Arduino.h>
#include "../numbers/DisplayNumber.h"

class Page{
    public:
    uint8_t index;

    const char* title;

    DisplayNumber* displayValues;
    uint8_t displayValuesNum;

    Page* parentPage;
    Page* subpages;
    uint8_t subpagesNum;
    
    void setParentPage(Page* page){
        this->parentPage = page;
    }

    // parentPage: page from which this page is nested
    //
    // title: page title that is displayed in left top right
    //
    // displayValuesNum: number of values to display on a given page
    //
    // values: said values that can be displayed
    Page(uint8_t index, const char* title, DisplayNumber* values, uint8_t displayValuesNum, Page* parentPage, Page* subpages, uint8_t subpagesNum){
        this->index = index;
        
        this->title = title;

        this->displayValues = values;
        this->displayValuesNum = displayValuesNum;

        this->parentPage = parentPage;
        this->subpages = subpages;
        this->subpagesNum = subpagesNum;
    };
    Page(){}
};

#endif