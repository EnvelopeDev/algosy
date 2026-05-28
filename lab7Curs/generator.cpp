#include "generator.hpp"

Generator::Generator(){
    std::random_device rd;
    rng = std::mt19937(rd());
}

Generator::~Generator(){}

unsigned long Generator::generateSet(size_t minSize, size_t maxSize){
    unsigned long used = 0UL, mask = 1UL;
    unsigned long randChar;
    bool flag=false;
    size_t setSize = randomInt(minSize, maxSize);
    if(setSize>MAX_SET_SIZE*2/3){
        for(size_t currSetSize=0; currSetSize!=setSize;currSetSize++){
            flag=false;
            mask = 1UL;
            randChar = randomInt(0, MAX_SET_SIZE-1);
            mask = mask<<randChar;
            if(!(mask & used)){
                used = used|mask;
            }
            else{
                for(int i=randChar+1;i<MAX_SET_SIZE && !flag;i++){
                    mask = 1UL;
                    mask = mask<<i;
                    if(!(mask & used)){
                        used = used|mask;
                        flag=true;
                    }
                }
                for(int i=randChar-1;i>-1 && !flag;i--){
                    mask = 1UL;
                    mask = mask<<i;
                    if(!(mask & used)){
                        used = used|mask;
                        flag=true;
                    }
                }
            }
        }
    }
    else{
        for(size_t currSetSize=0; currSetSize!=setSize;){
            mask = 1UL;
            randChar = randomInt(0, MAX_SET_SIZE-1);
            mask = mask<<randChar;
            if(!(mask & used)){
                used = used|mask;
                currSetSize++;
            }
        }
    }
    return used;
}

int Generator::randomInt(int min, int max){
    return (rng()%(max+1-min))+min;
}
