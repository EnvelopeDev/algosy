#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>

#include "array_set.hpp"
#include "list.hpp"
#include "barray_set.hpp"
#include "bmask_set.hpp"
#include "generator.hpp"

long long* testSets(std::vector<char**> sets);
std::vector<char*> arraySet(std::vector<char**> sets);
std::vector<char*> listSet(std::vector<List<char>*> sets);
std::vector<char*> bitArraySet(std::vector<BitArraySet*> sets);
std::vector<char*> bitMaskSet(std::vector<BitMask*> sets);
char** parseCSVLine(const std::string& line);
char** inputCharArrays();


int main(){
    bool inpFromFile = true;
    std::ofstream fout("output.txt");
    std::ifstream fin("input.txt");
    char userOpt;
    long long* time;
    std::vector<char**> sets;
    std::vector<char*> setsRes;
    std::string line;
    char** setGroup;

    std::cout << "Input sets from input.csv?(y/n): ";
    std::cin >> userOpt;
    if(userOpt=='n'){
        inpFromFile=false;
    }

    if(inpFromFile){
        generatorInterface();
        while(getline(fin, line)){
            setGroup = parseCSVLine(line);
            sets.push_back(setGroup);
        }
    }
    else{
        sets.push_back(inputCharArrays());
    }
    time = testSets(sets);
    return 0;
}

long long* testSets(std::vector<char**> sets){
    long long* times = new long long[4];
    auto start = std::chrono::high_resolution_clock::now();
    arraySet(sets);
    auto end = std::chrono::high_resolution_clock::now();
    times[0] = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    listSet(sets);
    end = std::chrono::high_resolution_clock::now();
    times[1] = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    bitArraySet(sets);
    end = std::chrono::high_resolution_clock::now();
    times[2] = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    bitMaskSet(sets);
    end = std::chrono::high_resolution_clock::now();
    times[3] = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    return times;
}

std::vector<char*> arraySet(std::vector<char**> sets){
    std::cout << "          _____ARRAY SET_____\n\n";
    std::vector<char*> setsRes;
    char* E;
    for(int i=0; i<sets.size();i++){
        E = subtractionSets(sets[i][0], sets[i][1], sets[i][2], sets[i][3]);
        setsRes.push_back(E);
    }
    //deleting allocated memory
    delete[] E;
    return setsRes;
}

std::vector<char*> listSet(std::vector<List<char>*> sets){
    std::cout << "          _____LIST SET_____\n\n";
    std::vector<char*> setsRes;
    List<char> setA, setB, setC, setD, *setE;

    for(int i=0; i<sets.size();i++){
        setE = setA.substractLists(setB, setC, setD);
        setsRes.push_back(setE->toDynChar());
    }
    return setsRes;
}

std::vector<char*> bitArraySet(std::vector<BitArraySet*> sets){
    std::cout << "          _____BIT ARRAY SET_____\n\n";
    std::vector<char*> setsRes;

    for(int i=0; i<sets.size();i++){

    }
    BitArraySet setA(sets[0]), setB(sets[1]), setC(sets[2]), setD(sets[3]);
    BitArraySet setRes = setA.subtractSets(setB, setC, setD);
    std::cout << "Result set: ";
    setRes.print();
    std::cout << '\n';
    for(int i=0;i<4;i++){
        delete[] sets[i];
    }
}

std::vector<char*> bitMaskSet(std::vector<BitMask*> sets){
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

char** inputCharArrays(){
    int arrSize;
    bool doFullAlphabet=false;
    char userChoice;
    char** arrays = new char*[4];
    for(int i=0;i<4;i++){
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
    return arrays;
}


char** parseCSVLine(const std::string& line){
    std::stringstream ss(line);
    std::string token;
    char** sets = new char*[4];
    int currSet=0;

    while(getline(ss, token, ';')){
        if (token.empty()) continue;
        if(token.find(',') != std::string::npos){
            std::stringstream setSS(token);
            std::string element;
            std::vector<char> tempSet;

            while(getline(setSS, element, ',')){
                if(!element.empty()){
                    tempSet.push_back(element[0]);
                }
            }

            char* arr = new char[tempSet.size()+1];
            for(int i=0; i<tempSet.size(); i++){
                arr[i] = tempSet[i];
            }
            arr[tempSet.size()] = '\0';
            sets[currSet] = arr;
            currSet++;
        }
    }
    return sets;
}

