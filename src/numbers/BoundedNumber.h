#ifndef BOUNDED_NUMBER_H
#define BOUNDED_NUMBER_H


void noFunction(float){};

class BoundedNumber{

    volatile float val;
    volatile float lastVal; // value before change
    float startingVal;
    float step;
    
    void markLastValue(){
        this->lastVal = this->val;
    }

    void (*onValueChange)(float amountAfterChange) = noFunction;

    public:
    
    float minLimit;
    float maxLimit;

    void setOnValueChange(void(*func_ptr)(float)){
        this->onValueChange = func_ptr;
    }

    BoundedNumber& operator+=(float number){
        this->markLastValue();
        this->addValue(number);
        this->onValueChange(this->val);

        return *this;
    }
    BoundedNumber& operator++(){
        this->markLastValue();
        this->addValue(this->step);
        this->onValueChange(this->val);

        return *this;
    }
    BoundedNumber& operator+(float number){
        this->markLastValue();
        this->addValue(number);
        this->onValueChange(this->val);

        return *this;
    }

    BoundedNumber& operator-=(float number){
        this->markLastValue();
        this->addValue(-number);
        this->onValueChange(this->val);

        return *this;
    }
    BoundedNumber& operator--(){
        this->markLastValue();
        this->addValue(-this->step);
        this->onValueChange(this->val);

        return *this;
    }
    BoundedNumber& operator-(float number){
        this->markLastValue();
        this->addValue(-number);
        this->onValueChange(this->val);

        return *this;
    }

    void resetValue(){
        this->markLastValue();
        this->val = this->startingVal;
        this->onValueChange(this->val);
    }

    void stepOnce(){
        this->markLastValue();
        this->addValue(this->step);
        this->onValueChange(this->val);

    }

    void setStep(float step){
        this->step = step;
        this->onValueChange(this->val);
        
    }

    float lastValue(){
        return this->lastVal;
    }

    float value(){
        return(this->val);
    }

    float setValue(float val){
        this->markLastValue();
        this->addValue(val-this->val);
        this->onValueChange(this->val);

        return this->val;
    }

    float addValue(float val){
        this->markLastValue();
        float result = this->val + val;
        if(result<=this->maxLimit && result >=this->minLimit){
            this->val=result;
        }
        else if(this->val!=this->maxLimit && this->val!=this->minLimit){
            if(val>0){
                this->val=this->maxLimit;
            }
            else{
                this->val=this->minLimit;
            }
        }

        this->onValueChange(this->val);
        return(this->val);
    }

    BoundedNumber( float startingValue, float minLimit, float maxLimit, float step){
        this->minLimit = minLimit;
        this->maxLimit = maxLimit;
        this->step = step;
        if(startingValue>=minLimit && startingValue<=maxLimit){
            this->val = startingValue;
        }
        else{
            if(startingValue-maxLimit>startingValue-minLimit){
                this->val = minLimit;
            }
            else{
                this->val = maxLimit;
            }
        }
        this->lastVal = this->val;
        this->startingVal = this->val;
        this->onValueChange = noFunction;
    }

    BoundedNumber(){
        this->minLimit = 0;
        this->maxLimit = 0;
        this->val = 0;
        this->step = 1;
        this->lastVal = this->val;
        this->startingVal = this->val;
    }
};

#endif