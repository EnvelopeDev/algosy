#include <iostream>
#include <vector>
#include "array_set.hpp"
#include "list.hpp"
//#include "barray_set.hpp"
//#include "bmask_set.hpp"
//#include "test.hpp"
const char A[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','\0'}; //array with all latin letters
void arraySet();
void listSet();
void inputCharArrays(char** arrays, int numArr=3);


int main(){
    //DOING SET WITH ARRAY
    //arraySet();
    //DOING SET WITH LIST
    listSet();
    return 0;
}

void arraySet(){
    std::cout << "          _____ARRAY SET_____\n\n";
    char* B, *C, *D;
    char* arrs[3] = {B, C, D};
    inputCharArrays(arrs);
    B = arrs[0];C = arrs[1], D = arrs[2];
    char* E = subtractionSets(A, B, C, D); //subtraction of sets

    //output result array
    std::cout << "Result set: ";
    for(int i=0; i<strlen(E);i++){
        std::cout << E[i]<< ' ';
    }
    std::cout <<'\n';
    //deleting allocated memory
    delete[] B;
    delete[] C;
    delete[] D;
    delete[] E;
}

void listSet(){
    std::cout << "          _____LIST SET_____\n\n";
    List<char> setA(A, strlen(A));
    char* B, *C, *D;
    char* arrs[3] = {B, C, D};
    inputCharArrays(arrs);
    List<char> setB(arrs[0], strlen(arrs[0])), setC(arrs[1], strlen(arrs[1])), setD(arrs[2], strlen(arrs[2]));
    List<char>* setRes;

    setRes = setA.substractLists(setB, setC, setD);
    std::cout << "Result set: ";
    setRes->print();
}

void inputCharArrays(char** arrays, int numArr){
    int arrSize;
    for(int i=0;i<numArr;i++){
        std::cout << "___________Set " << static_cast<char>('B'+i) << "___________" <<'\n';
        std::cout << "Enter size of set " << static_cast<char>('B'+i) << ": ";
        std::cin >> arrSize; 
        arrays[i] = new char[arrSize+1];
        std::cout << "Enter set: ";
        std::cin >> arrays[i];
        arrays[i][arrSize] = '\0';
    }
}