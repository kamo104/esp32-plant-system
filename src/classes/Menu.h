#ifndef MENU_H
#define MENU_H

#include <Arduino.h>

#include "Page.h"
#include "../numbers/BoundedNumber.h"
#include "../misc/list.h"

// responsible for presenting pages when asked to
class Menu{
    Page* pages;

    DataTypes::List<BoundedNumber> navigationList;
    
    public:
    
    Page* currentPage(){
        
        int nestedTimes = this->navigationList.currentPos();
        Page* page = &pages[int(this->navigationList.list[0].value())];

        for(int i=1;i<=nestedTimes;i++) page = &page->subpages[int(this->navigationList.list[i].value())];

        return page;
    }

    void nestNavigation(){
        Page* page = this->currentPage();
        if(page->subpagesNum<=0) return;

        BoundedNumber nav(0,0,page->subpagesNum-1,1);
        this->navigationList.push(nav);
    }

    void denestNavigation(){
        if(this->navigationList.currentPos()!=0) this->navigationList.pop();
        return;
    }

    Page* nextPage(){
        this->navigationList.list[this->navigationList.currentPos()]+=1;
        return this->currentPage();
    }

    Page* previousPage(){
        this->navigationList.list[this->navigationList.currentPos()]-=1;
        return this->currentPage();
    }

    Menu(Page* pages, uint8_t pagesNum){
        this->pages = pages;
        BoundedNumber startingPageNavigator(0,0,pagesNum-1,1);
        navigationList.push(startingPageNavigator);
    };
};

#endif