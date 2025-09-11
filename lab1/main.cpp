#include <iostream>
#include <vector>
#include "array_set.hpp"
#include "list.hpp"
//#include "barray_set.hpp"
//#include "bmask_set.hpp"
//#include "test.hpp"

int main() {
    std::cout << "_____ARRAY SET_____\n";
    //set of all latin letters
    const char A[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','\0'};
    int bsize, csize, dsize;

    //input size of sets
    std::cout << "Enter size of set B: ";
    std::cin >> bsize;
    std::cout << "Enter size of set C: ";
    std::cin >> csize;
    std::cout << "Enter size of set D: ";
    std::cin >> dsize;

    //memory allocation for subsets
    char* B = new char[bsize+1];
    char* C = new char[csize+1];
    char* D = new char[dsize+1];

    //input sets
    std::cin >> B;
    B[bsize+1]='\0';
    std::cin >> C;
    C[csize+1]='\0';
    std::cin >> D;
    D[dsize+1]='\0';

    char* E = subtractionSets(A, B, C, D); //subtraction of sets

    //output result array
    for(int i=0; i<strlen(E);i++){
        std::cout << E[i]<< ' ';
    }
    std::cout <<'\n';


    std::cout << "_____LIST SET_____\n";
    List<char> setA;
    List<char>* setB = new List<char>("DP", 2);
    List<char>* setC = new List<char>("AF", 2);
    List<char>* setD = new List<char>("GU", 2);
    List<char>* setRes;
    for(int i='A';i<'K';i++){
        setA.push_back(i);
    }
    List<char>* lists[3] = {setB, setC, setD};
    setRes = setA.substractLists(lists, 3);
    setRes->print();
    return 0;
}