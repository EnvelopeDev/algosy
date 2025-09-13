#include <iostream>
#include <vector>
#include "array_set.hpp"
#include "list.hpp"
#include "barray_set.hpp"
#include "bmask_set.hpp"
//#include "test.hpp"

void arraySet();
void listSet();
void bitArraySet();
void bitMaskSet();
void inputCharArrays(char** arrays, int numArr=4);

int main(){
    //SET WITH ARRAY
    //arraySet();
    //SET WITH LIST
    //listSet();
    //SET WITH BIT ARRAY
    //bitArraySet();
    //SET WITH BIT MASK
    bitMaskSet();
    return 0;
}

void arraySet(){
    std::cout << "          _____ARRAY SET_____\n\n";
    char* sets[4] = {};
    inputCharArrays(sets);
    char* E = subtractionSets(sets[0], sets[1], sets[2], sets[3]); //subtraction of sets

    //output result array
    std::cout << "Result set: ";
    for(int i=0; i<strlen(E);i++){
        std::cout << E[i]<< ' ';
    }
    std::cout <<'\n';
    //deleting allocated memory
    for(int i=0;i<4;i++){
        delete[] sets[i];
    }
    delete[] E;
}

void listSet(){
    std::cout << "          _____LIST SET_____\n\n";
    char* sets[4] = {};
    inputCharArrays(sets);
    List<char> setA(sets[0], strlen(sets[0])), setB(sets[1], strlen(sets[1])), setC(sets[2], strlen(sets[2])), setD(sets[3], strlen(sets[3]));
    List<char>* setRes;

    setRes = setA.substractLists(setB, setC, setD);
    std::cout << "Result set: ";
    setRes->print();
    std::cout << '\n';
    for(int i=0;i<4;i++){
        delete[] sets[i];
    }
    delete setRes;
}

void bitArraySet(){
    std::cout << "          _____BIT ARRAY SET_____\n\n";
    char* sets[4] = {};
    inputCharArrays(sets);
    BitArraySet setA(sets[0]), setB(sets[1]), setC(sets[2]), setD(sets[3]);
    BitArraySet setRes = setA.subtractSets(setB, setC, setD);
    std::cout << "Result set: ";
    setRes.print();
    std::cout << '\n';
    for(int i=0;i<4;i++){
        delete[] sets[i];
    }
}

void bitMaskSet(){
    std::cout << "          _____BIT MASK SET_____\n\n";
    char* sets[4] = {};
    inputCharArrays(sets);
    BitMask setA(sets[0]), setB(sets[1]), setC(sets[2]), setD(sets[3]);
    BitMask setRes = setA.subtractSets(setB, setC, setD);
    std::cout << "Result set: ";
    setRes.print();
    std::cout << '\n';
    for(int i=0;i<4;i++){
        delete[] sets[i];
    }
}

void inputCharArrays(char** arrays, int numArr){
    int arrSize;
    bool doFullAlphabet=false;
    char userChoice;
    for(int i=0;i<numArr;i++){
        std::cout << "___________Set " << static_cast<char>('A'+i) << "___________" <<'\n';
        if(i==0){
            std::cout << "Fill set A with all latin letters? (y/n): ";
            std::cin >> userChoice;
            if(userChoice == 'y'){
                doFullAlphabet = true;
            }
        }
        if(doFullAlphabet && i==0){
            arrays[i] = new char[27];
            for(int j=0;j<26;j++){
                arrays[i][j] = 'A'+j;
            }
            arrays[i][26] = '\0';
            std::cout << "Set A filled with all latin letters\n";
        }else{
            std::cout << "Enter size of set " << static_cast<char>('A'+i) << ": ";
            std::cin >> arrSize; 
            arrays[i] = new char[arrSize+1];
            std::cout << "Enter set: ";
            std::cin >> arrays[i];
            arrays[i][arrSize] = '\0';
        }
    }
}