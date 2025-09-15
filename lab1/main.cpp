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
#include "fileManager.hpp"

long long* testSets(std::vector<char**> sets);
std::vector<char*> arraySet(std::vector<char**> sets);
std::vector<char*> listSet(std::vector<List<char>*> sets);
std::vector<char*> bitArraySet(std::vector<BitArraySet*> sets);
std::vector<char*> bitMaskSet(std::vector<BitMask*> sets);
char** parseFileLine(const std::string& line);
char** inputCharArrays();

int main(){
    bool inpFromFile = true; //flag to check if we need to do the input from the file
    bool needGenNewTests=true; //flag to check if we need to generate new tests in input.csv
    std::ifstream fin("input.csv");
    char userOpt; //user option
    long long* time; //array of runtimes (array, list, bit array, bitmask)
    std::vector<char**> sets; //sets from input.csv
    std::vector<char*> setsRes; //results of the program, we need to output to output.txt
    std::string line; //line in input.csv to read
    char** setGroup; //group of 4 sets (A, B, C, D)

    std::cout << "Input sets from input.csv?(y/n): ";
    std::cin >> userOpt;
    if(userOpt=='n'){
        inpFromFile=false;
    }

    if(inpFromFile){
        std::cout << "Generate new tests?(y/n): ";
        std::cin >> userOpt;
        if(userOpt=='n'){
            needGenNewTests=false;
        }
        if(needGenNewTests){
            generatorInterface(); //calling generator.cpp to generate new tests
        }
        //reading input.csv
        while(getline(fin, line)){
            setGroup = parseFileLine(line);
            sets.push_back(setGroup);
        }
    }
    else{
        //adding sets inputed from the console
        sets.push_back(inputCharArrays());
    }
    time = testSets(sets); //doing tests
    //outputing runtimes
    std::cout << "=====RUNTIMES====\n";
    std::cout << "Array: " << time[0] << '\n';
    std::cout << "List: " << time[1] << '\n';
    std::cout << "Bit Array: " << time[2] << '\n';
    std::cout << "Bit Mask: " << time[3] << '\n';
    std::cout << '\n';
    return 0;
}

long long* testSets(std::vector<char**> sets){
    long long* times = new long long[4]; //allocating memory for array of runtimes
    std::vector<List<char>*> listSets; //
    std::vector<BitArraySet*> baset;
    std::vector<BitMask*> bmset;
    std::ofstream fout("output.txt");
    std::vector<char*> results;

    std::cout << "\n\n=====ARRAY SET=====\n";
    auto start = std::chrono::high_resolution_clock::now();
    results = arraySet(sets);
    auto end = std::chrono::high_resolution_clock::now();
    times[0] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Array set completed successfully!\n";
    std::cout <<"RUNTIME: " << times[0] << '\n';

    for(int i=0;i<results.size();i++){
        for(int j=0;j<strlen(results[i]);j++){
            fout << results[i][j];
            if(j!=strlen(results[i])-1){
                fout << ',';
            }
        }
        fout << '\n';
    }
    fout << "=\n";
    std::cout << "Results was saved to output.txt\n\n";

    for(int i=0;i<sets.size();i++){
        List<char>* lists = new List<char>[4]{List<char>(sets[i][0], strlen(sets[i][0])), List<char>(sets[i][1], strlen(sets[i][1])),\
             List<char>(sets[i][2], strlen(sets[i][2])), List<char>(sets[i][3], strlen(sets[i][3]))};
        listSets.push_back(lists);

        BitArraySet* basets = new BitArraySet[4]{BitArraySet(sets[i][0]), BitArraySet(sets[i][1]), BitArraySet(sets[i][2]), BitArraySet(sets[i][3])};
        baset.push_back(basets);

        BitMask* bmsets = new BitMask[4]{BitMask(sets[i][0]), BitMask(sets[i][1]), BitMask(sets[i][2]), BitMask(sets[i][3])};
        bmset.push_back(bmsets);
    }

    std::cout << "=====LIST SET=====\n";
    start = std::chrono::high_resolution_clock::now();
    results = listSet(listSets);
    end = std::chrono::high_resolution_clock::now();
    times[1] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "List set completed successfully!\n";
    std::cout <<"RUNTIME: " << times[1] << '\n';

    for(int i=0;i<results.size();i++){
        for(int j=0;j<strlen(results[i]);j++){
            fout << results[i][j];
            if(j!=strlen(results[i])-1){
                fout << ',';
            }
        }
        fout << '\n';
    }
    fout << "=\n";
    std::cout << "Results was saved to output.txt\n\n";

    std::cout << "=====BIT ARRAY SET=====\n";
    start = std::chrono::high_resolution_clock::now();
    results = bitArraySet(baset);
    end = std::chrono::high_resolution_clock::now();
    times[2] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Bit array set completed successfully!\n";
    std::cout <<"RUNTIME: " << times[2] << '\n';

    for(int i=0;i<results.size();i++){
        for(int j=0;j<strlen(results[i]);j++){
            fout << results[i][j];
            if(j!=strlen(results[i])-1){
                fout << ',';
            }
        }
        fout << '\n';
    }
    fout << "=\n";
    std::cout << "Results was saved to output.txt\n\n";

    std::cout << "=====BIT MASK SET=====\n";
    start = std::chrono::high_resolution_clock::now();
    results = bitMaskSet(bmset);
    end = std::chrono::high_resolution_clock::now();
    times[3] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Bit mask set completed successfully!\n";
    std::cout <<"RUNTIME: " << times[3] << '\n';

    for(int i=0;i<results.size();i++){
        for(int j=0;j<strlen(results[i]);j++){
            fout << results[i][j];
            if(j!=strlen(results[i])-1){
                fout << ',';
            }
        }
        fout << '\n';
    }
    fout << "=\n";
    std::cout << "Results was saved to output.txt\n\n";

    return times;
}

std::vector<char*> arraySet(std::vector<char**> sets){
    std::vector<char*> setsRes;
    char* E;

    for(int i=0; i<sets.size();i++){
        E = subtractionSets(sets[i][0], sets[i][1], sets[i][2], sets[i][3]);
        setsRes.push_back(E);
    }
    return setsRes;
}

std::vector<char*> listSet(std::vector<List<char>*> sets){
    std::vector<char*> setsRes;
    List<char> *setE;

    for(int i=0; i<sets.size();i++){
        setE = sets[i][0].substractLists(sets[i][1], sets[i][2], sets[i][3]);
        setsRes.push_back(setE->toDynChar());
    }
    return setsRes;
}

std::vector<char*> bitArraySet(std::vector<BitArraySet*> sets){
    std::vector<char*> setsRes;
    BitArraySet setE("");

    for(int i=0; i<sets.size();i++){
        setE = sets[i][0].subtractSets(sets[i][1], sets[i][2], sets[i][3]);
        setsRes.push_back(setE.toDynChar());
    }
    return setsRes;
}

std::vector<char*> bitMaskSet(std::vector<BitMask*> sets){
    std::vector<char*> setsRes;
    BitMask setE("");

    for(int i=0; i<sets.size();i++){
        setE = sets[i][0].subtractSets(sets[i][1], sets[i][2], sets[i][3]);
        setsRes.push_back(setE.toDynChar());
    }
    return setsRes;
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


char** parseFileLine(const std::string& line){
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