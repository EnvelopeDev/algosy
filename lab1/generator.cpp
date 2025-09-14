#include "generator.hpp"

using namespace std;

random_device rd;
mt19937 rng(rd());

void generatorInterface(){
    cout << "=== Test Generator ===\n\n";
    int numArrays;
    size_t minSizeA, maxSizeA;
    cout << "Enter a number of tests to generate: ";
    cin >> numArrays;
    cout << "Enter maximum size of set A (maximum 26): ";
    cin >> maxSizeA;
    if(maxSizeA>26){
        maxSizeA=26;
    }
    cout << "Enter minimum size of set A (minimum 4): ";
    cin >> minSizeA;
    if(minSizeA < 4){
        minSizeA=4;
    }
    cout << "\nGenerating tests...\n";
    generateArraysToCSV(numArrays, minSizeA, maxSizeA);
    cout << "\n=== Program Completed ===\n";
    cout << "Sets saved to input.csv\n";
}

void generateArraysToCSV(int numArrays, size_t minSizeA, size_t maxSizeA){
    ofstream fout("input.csv");
    size_t minSubSetSize = minSizeA/4, maxSubSetSize = maxSizeA/4;

    if(!fout.is_open()){
        cout << "Error opening file input.csv\n";
        return;
    }
    char* set = new char[MAX_SET_SIZE+1];
    bool fillWithAllLetters = true;
    for(int i=0;i<numArrays;i++){
        if(i==numArrays/5){
            fillWithAllLetters = false;
        }
        for(int j=0; j<NUM_SETS;j++){
            if(j==0){
                generateSet(set, minSizeA, maxSizeA, fillWithAllLetters);
            }
            else{
                generateSet(set, minSubSetSize, maxSubSetSize, false);
            }
            fout << strlen(set) << ';';
            for(int l=0;l<strlen(set);l++){
                fout << set[l];
                if(l!=strlen(set)-1){
                    fout << ',';
                }
            }
            fout << ';';
        }
        fout << '\n';
    }
    fout.close();
    delete[] set;
}

void generateSet(char* set, size_t minSize, size_t maxSize, bool fillWithAllLetters){
    if(fillWithAllLetters){
        for(int i=0;i<MAX_SET_SIZE;i++){
            set[i] = 'A'+i;
        }
        set[MAX_SET_SIZE] = '\0';
        return;
    }
    unsigned long long used = 0ULL, mask = 1ULL;
    char randChar;
    bool flag=false;
    size_t setSize = randomInt(minSize, maxSize);
    if(setSize>MAX_SET_SIZE/2){
        for(size_t currSetSize=0; currSetSize!=setSize;currSetSize++){
            flag=false;
            mask = 1ULL;
            randChar = randomInt(0, MAX_SET_SIZE-1);
            mask = mask<<randChar;
            if(!(mask & used)){
                set[currSetSize] = 'A'+randChar;
                used = used|mask;
            }
            else{
                for(int i=randChar+1;i<MAX_SET_SIZE && !flag;i++){
                    mask = 1ULL;
                    mask = mask<<i;
                    if(!(mask & used)){
                        set[currSetSize] = 'A'+i;
                        used = used|mask;
                        flag=true;
                    }
                }
                for(int i=randChar-1;i>-1 && !flag;i--){
                    mask = 1ULL;
                    mask = mask<<i;
                    if(!(mask & used)){
                        set[currSetSize] = 'A'+i;
                        used = used|mask;
                        flag=true;
                    }
                }
            }
        }
        set[setSize] = '\0';
    }
    else{
        for(size_t currSetSize=0; currSetSize!=setSize;){
            mask = 1ULL;
            randChar = randomInt(0, MAX_SET_SIZE-1);
            mask = mask<<randChar;
            if(!(mask & used)){
                set[currSetSize] = 'A'+randChar;
                used = used|mask;
                currSetSize++;
            }
        }
        set[setSize] = '\0';
    }
}

int randomInt(int min, int max){
    return (rng()%(max+1-min))+min;
}