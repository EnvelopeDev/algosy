#include "generator.hpp"

using namespace std;

//init the generator of random nums
random_device rd;
mt19937 rng(rd());

void generatorInterface(){
    cout << "\n==============[TEST GENERATOR]==============\n";
    int numArrays;
    size_t minSizeA, maxSizeA;

    //request params from the user
    cout << "Enter a number of tests to generate: ";
    cin >> numArrays;
    cout << "Enter maximum size of set A (maximum 26): ";
    cin >> maxSizeA;
    //maximum size limit
    if(maxSizeA>26){
        maxSizeA=26;
    }
    cout << "Enter minimum size of set A (minimum 4): ";
    cin >> minSizeA;
    //minimum size limit
    if(minSizeA < 4){
        minSizeA=4;
    }
    cout << "\nGenerating tests...\n";
    //call the function of generator
    generateArraysToCSV(numArrays, minSizeA, maxSizeA);
    cout << "Generation completed!\n";
    cout << "============================================\n\n";
}

void generateArraysToCSV(int numArrays, size_t minSizeA, size_t maxSizeA){
    ofstream fout("data/input.csv");
    //set min and max size of subsets B, C, D (quarter of A sizes)
    size_t minSubSetSize = minSizeA/4 + 1, maxSubSetSize = maxSizeA/4 + 1;

    //check if the file is opened
    if(!fout.is_open()){
        cout << "Error opening file input.csv\n";
        return;
    }
    char* set = new char[MAX_SET_SIZE+1]; //allocating memory for array-set
    bool fillWithAllLetters = true; //flag to check if it`s need to fill the set A with all latin letters (20% of all tests)
    for(int i=0;i<numArrays;i++){
        //changing flag in 20% of the generator
        if(i==numArrays/5){
            fillWithAllLetters = false;
        }
        //generating sets, output to input.csv
        for(int j=0; j<NUM_SETS;j++){
            if(j==0){
                //generate the set A
                generateSet(set, minSizeA, maxSizeA, fillWithAllLetters);
            }
            else{
                //generate the subsets
                generateSet(set, minSubSetSize, maxSubSetSize, false);
            }
            //output generated set to file
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
    //fill the set with all the alphabet and return the function
    if(fillWithAllLetters){
        for(int i=0;i<MAX_SET_SIZE;i++){
            set[i] = 'A'+i;
        }
        set[MAX_SET_SIZE] = '\0';
        return;
    }

    unsigned long long used = 0ULL, mask = 1ULL; //mask of used chars, mask to check if the char is used
    char randChar; //generated random char
    bool flag=false; //flag to check if 
    size_t setSize = randomInt(minSize, maxSize);
    if(setSize>MAX_SET_SIZE/2){
        //if we need to generate more than a half of the max size of the set
        //do a forward search - if we`ve got a used char, first do a check of bits on the right of that bit
        //if we haven`t found free bit, do a check on the left
        for(size_t currSetSize=0; currSetSize!=setSize;currSetSize++){
            flag=false;
            mask = 1ULL;
            randChar = randomInt(0, MAX_SET_SIZE-1);
            mask = mask<<randChar;
            //if char wasn`t used - add it to the set
            if(!(mask & used)){
                set[currSetSize] = 'A'+randChar;
                used = used|mask;
            }
            else{
                //search on the right
                for(int i=randChar+1;i<MAX_SET_SIZE && !flag;i++){
                    mask = 1ULL;
                    mask = mask<<i;
                    if(!(mask & used)){
                        set[currSetSize] = 'A'+i;
                        used = used|mask;
                        flag=true;
                    }
                }
                //search on the left
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
        //if we need to generate less than a half of the max size of the set,
        //just generate a random position, until it will be filled
        for(size_t currSetSize=0; currSetSize!=setSize;){
            mask = 1ULL;
            randChar = randomInt(0, MAX_SET_SIZE-1); //generate a char
            mask = mask<<randChar;
            //if char wasn`t used - add it to the set
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
