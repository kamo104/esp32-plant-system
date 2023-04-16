#ifndef DATATYPES_LIST_H
#define DATATYPES_LIST_H

#define DEFAULT_LIST_SIZE 10

namespace DataTypes{
template <class T>
class List{
    
    int lastPos;
    int elementsNum;

    public:
    T* list;


    T& operator[](int place){
        if(place<0 || place>=this->elementsNum) return this->list[0];

        return this->list[place];
    }

    int size(){
        return this->elementsNum;
    }
    int currentPos(){
        return this->lastPos;
    }

    void push(T element){
        if(this->lastPos+1>=this->elementsNum) return;
        this->lastPos+=1;
        this->list[this->lastPos] = element;
    }

    void pop(){
        if(this->lastPos<0) throw 1;
        // delete this->list[this->lastPos];
        this->lastPos-=1;
    }
    bool empty(){
        if(this->lastPos==-1) return 1;
        return 0;
    }
    T top(){
        if(this->lastPos<0) throw 1;
        return this->list[this->lastPos];
    }

    List(int size){
        this->elementsNum = size;
        this->list = new T[size];
        this->lastPos = -1;
        this->currentSize = 0;
    }
    List(){
        this->elementsNum = DEFAULT_LIST_SIZE;
        this->list = new T[DEFAULT_LIST_SIZE];
        this->lastPos = -1;
    }
};
}

#endif