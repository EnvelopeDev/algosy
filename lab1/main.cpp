#include <iostream> //input/output
#include <vector> //for easier work with arrays and memory
#include <string> //for easier work with chars
#include <sstream> //for easier reading of strings
#include <chrono> //for work with time

#include "array_set.hpp" //realization of set with using an array
#include "list.hpp" //realization of set with using a list
#include "barray_set.hpp" //realization of set with using a bit array
#include "bmask_set.hpp" //realization of set with using a bit mask
#include "generator.hpp" //generation of test cases (groups of 4 sets - A, B, C, D)
#include "fileManager.hpp" //for working with files (reading, writing, compare)
#include "idol_test.hpp" //to create expected results (stl set)

long long* testSets(std::vector<char**> sets); //function does tests from vector sets, returning runtimes in microseconds
std::vector<char*> arraySet(std::vector<char**> sets); //function doing tests of array set version
std::vector<char*> listSet(std::vector<List<char>*> sets); //function doing tests of list set version
std::vector<char*> bitArraySet(std::vector<BitArraySet*> sets); //function doing tests of bit array set version
std::vector<char*> bitMaskSet(std::vector<BitMask*> sets); //function doing tests of bit mask set version
char** parseFileLine(const std::string& line); //reads the line of .csv file, returns a group of 4 sets
void inputFromConsole(); //does the input from the console to input.csv
std::vector<std::string> inputGroupSet(); //does the input from console to the set group (A, B, C, D)
int* compareWithSTLset(); //function compares results of 4 set realizations with results of stl set

int main(){
    bool inpFromFile = true; //flag to check if we need to do the input from the file
    bool needGenNewTests=true; //flag to check if we need to generate new tests in input.csv
    std::ifstream fin("input.csv"); //file with generated tests
    char userOpt; //user option
    int* errors; //array of number of errors
    long long* time; //array of runtimes (array, list, bit array, bitmask)
    std::vector<char**> sets; //sets from input.csv
    std::string line; //line in input.csv to read
    char** setGroup; //group of 4 sets (A, B, C, D)

    std::cout << "Use the test generator?(y/n): ";
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
    }
    else{
        //inputting sets from the console
        inputFromConsole();
    }
    //reading input.csv
    while(getline(fin, line)){
        setGroup = parseFileLine(line);
        sets.push_back(setGroup);
    }

    time = testSets(sets); //doing tests

    //outputing runtimes
    std::cout << "=================[RUNTIMES]=================\n";
    std::cout << "Array: " << time[0] << " ms" <<'\n';
    std::cout << "List: " << time[1] << " ms" <<'\n';
    std::cout << "Bit Array: " << time[2] << " ms" <<'\n';
    std::cout << "Bit Mask: " << time[3] << " ms" <<'\n';
    std::cout << "============================================\n\n";

    testIdolSet(); //doing expected results with stl set
    errors = compareWithSTLset(); //comparing the expected result with actual result

    //outputing numbers of errors
    std::cout << "=============[NUMBER OF ERRORS]=============\n";
    std::cout << "Array: " << errors[0] << '\n';
    std::cout << "List: " << errors[1] << '\n';
    std::cout << "Bit Array: " << errors[2] << '\n';
    std::cout << "Bit Mask: " << errors[3] << '\n';
    std::cout << "============================================\n\n";

    std::ifstream finA("outputAr.txt"); //file with results of array set
    std::ifstream finL("outputLi.txt"); //file with results of list set
    std::ifstream finBa("outputBa.txt"); //file with results of Bit array set
    std::ifstream finBm("outputBm.txt"); //file with results of Bit mask set
    std::string out;

    //if the amount of sets is less than 16, it is outputting to the console
    if(sets.size() < 16){
        std::cout << "=============[OUTPUT]=============\n";
        for(int i=0;i<sets.size();i++){
            getline(finA, out);
            setGroup = sets[i];
            std::cout << i+1 << " test\n";
            for(int j=0;j<4;j++){
                std::cout << static_cast<char>('A'+j) << ": ";
                for(int l=0; l<strlen(setGroup[j]);l++){
                    std::cout << setGroup[j][l];
                    if(l!=strlen(setGroup[j])-1){
                        std::cout << ", ";
                    }
                }
                std::cout << '\n';
            }
            std::cout <<"E: "<< out << '\n';
            std::cout << "---------------------------\n";
        }
        std::cout << "==================================\n";
    }
    return 0;
}

long long* testSets(std::vector<char**> sets){
    long long* times = new long long[4]; //allocating memory for array of runtimes
    std::vector<List<char>*> listSets; //vector with tests for listSet() with the lists of a groups of the sets
    std::vector<BitArraySet*> baset; //vector with tests fot bitArraySet() with sets in BitArray Form
    std::vector<BitMask*> bmset; //vector with tests fot bitMaskSet() with sets in BitMask Form
    std::ofstream foutA("outputAr.txt"); //file with results of array set
    std::ofstream foutL("outputLi.txt"); //file with results of list set
    std::ofstream foutBa("outputBa.txt"); //file with results of Bit array set
    std::ofstream foutBm("outputBm.txt"); //file with results of Bit mask set
    std::vector<char*> results; //vector with results

    auto start = std::chrono::high_resolution_clock::now(); //timer starts
    results = arraySet(sets);
    auto end = std::chrono::high_resolution_clock::now(); //timer stops
    times[0] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); //counting runtime in microseconds

    //writing results to the file with array set results
    for(int i=0;i<results.size();i++){
        for(int j=0;j<strlen(results[i]);j++){
            foutA << results[i][j];
            if(j!=strlen(results[i])-1){
                foutA << ',';
            }
        }
        foutA << '\n';
    }

    //converting vector with char** to List, BitArraySet, Bitmask vectors
    for(int i=0;i<sets.size();i++){
        List<char>* lists = new List<char>[4]{List<char>(sets[i][0], strlen(sets[i][0])), List<char>(sets[i][1], strlen(sets[i][1])),\
             List<char>(sets[i][2], strlen(sets[i][2])), List<char>(sets[i][3], strlen(sets[i][3]))};
        listSets.push_back(lists);

        BitArraySet* basets = new BitArraySet[4]{BitArraySet(sets[i][0]), BitArraySet(sets[i][1]), BitArraySet(sets[i][2]), BitArraySet(sets[i][3])};
        baset.push_back(basets);

        BitMask* bmsets = new BitMask[4]{BitMask(sets[i][0]), BitMask(sets[i][1]), BitMask(sets[i][2]), BitMask(sets[i][3])};
        bmset.push_back(bmsets);
    }

    start = std::chrono::high_resolution_clock::now(); //timer starts
    results = listSet(listSets);
    end = std::chrono::high_resolution_clock::now(); //timer stops
    times[1] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); //counting runtime in microseconds

    //writing results to the file with list set results
    for(int i=0;i<results.size();i++){
        for(int j=0;j<strlen(results[i]);j++){
            foutL << results[i][j];
            if(j!=strlen(results[i])-1){
                foutL << ',';
            }
        }
        foutL << '\n';
    }

    start = std::chrono::high_resolution_clock::now(); //timer starts
    results = bitArraySet(baset);
    end = std::chrono::high_resolution_clock::now(); //timer stops
    times[2] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); //counting runtime in microseconds

    //writing results to the file with bit array set results
    for(int i=0;i<results.size();i++){
        for(int j=0;j<strlen(results[i]);j++){
            foutBa << results[i][j];
            if(j!=strlen(results[i])-1){
                foutBa << ',';
            }
        }
        foutBa << '\n';
    }

    start = std::chrono::high_resolution_clock::now(); //timer starts
    results = bitMaskSet(bmset);
    end = std::chrono::high_resolution_clock::now(); //timer stops
    times[3] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); //counting runtime in microseconds

    //writing results to the file with bit mask set results
    for(int i=0;i<results.size();i++){
        for(int j=0;j<strlen(results[i]);j++){
            foutBm << results[i][j];
            if(j!=strlen(results[i])-1){
                foutBm << ',';
            }
        }
        foutBm << '\n';
    }

    return times;
}

std::vector<char*> arraySet(std::vector<char**> sets){
    std::vector<char*> setsRes; //resulting array with sets E
    char* E;
    for(int i=0; i<sets.size();i++){
        E = subtractionSets(sets[i][0], sets[i][1], sets[i][2], sets[i][3]);
        setsRes.push_back(E);
    }
    return setsRes;
}

std::vector<char*> listSet(std::vector<List<char>*> sets){
    std::vector<char*> setsRes; //resulting array with sets E
    List<char> *setE;

    for(int i=0; i<sets.size();i++){
        setE = sets[i][0].substractLists(sets[i][1], sets[i][2], sets[i][3]);
        setsRes.push_back(setE->toDynChar());
    }
    return setsRes;
}

std::vector<char*> bitArraySet(std::vector<BitArraySet*> sets){
    std::vector<char*> setsRes; //resulting array with sets E
    BitArraySet setE("");

    for(int i=0; i<sets.size();i++){
        setE = sets[i][0].subtractSets(sets[i][1], sets[i][2], sets[i][3]);
        setsRes.push_back(setE.toDynChar());
    }
    return setsRes;
}

std::vector<char*> bitMaskSet(std::vector<BitMask*> sets){
    std::vector<char*> setsRes; //resulting array with sets E
    BitMask setE("");

    for(int i=0; i<sets.size();i++){
        setE = sets[i][0].subtractSets(sets[i][1], sets[i][2], sets[i][3]);
        setsRes.push_back(setE.toDynChar());
    }
    return setsRes;
}

void inputFromConsole(){
    size_t arrSize; //size of the array
    int numOfTests;
    std::vector<std::string> groupSet; //group of 4 sets (A, B, C, D)
    ofstream fout("input.csv");

    std::cout << "Enter number of tests: ";
    std::cin >> numOfTests;

    //outputting sets to input.csv
    for(int i=0;i<numOfTests;i++){
        std::cout << "\n=========TEST " << i+1 << "=========\n";
        groupSet = inputGroupSet();
        for(int j=0;j<4;j++){
            fout << groupSet[j].length() << ';';
            for(int l=0;l<groupSet[j].length();l++){
                fout << groupSet[j][l];
                if(l!=groupSet[j].length()-1){
                    fout << ',';
                }
            }
            fout << ';';
        }
        fout << '\n';
    }
}

std::vector<std::string> inputGroupSet(){
    //input the sets
    bool doFullAlphabet=false; //flag to check if it`s need to fill the set with all latin letters
    char userChoice;
    std::string inpSet;
    std::vector<std::string> groupSet(4);
    for(int i=0;i<4;i++){
        std::cout << "Set " << static_cast<char>('A'+i) << '\n';
        if(i==0){
            std::cout << "Fill set A with all latin letters? (y/n): ";
            std::cin >> userChoice;
            if(userChoice=='y'){
                doFullAlphabet = true;
            }
        }
        if(doFullAlphabet && i==0){
            //filling the set with all the latin letters
            inpSet.resize(26);
            for(int j=0;j<26;j++){
                inpSet[j] = 'A'+j;
            }
            std::cout << "Set A filled with all latin letters\n";
        }else{
            //inputting sets from the keyboard
            std::cout << "Enter set: ";
            std::cin >> inpSet;
        }
        std::cout << "---------------------------\n";
        groupSet[i] = inpSet;
    }
    return groupSet;
}

char** parseFileLine(const std::string& line){
    std::stringstream ss(line); //stream with the line (string)
    std::string token;
    char** sets = new char*[4]; //allocating memory for the group of the sets(A, B, C ,D)
    int currSet=0; //counter for a number of the set

    //split the line with ';'
    while(getline(ss, token, ';')){
        if (token.empty()) continue;
        //if string contains commas - it is set
        if(token.find(',') != std::string::npos){
            std::stringstream setSS(token); //creating stream in token
            std::string element; //element of set
            std::vector<char> tempSet; //temporary container for elements of the set

            while(getline(setSS, element, ',')){
                if(!element.empty()){
                    tempSet.push_back(element[0]);
                }
            }

            //convert vector to char array
            char* arr = new char[tempSet.size()+1]; //allocating memory for array with the set
            for(int i=0; i<tempSet.size(); i++){
                arr[i] = tempSet[i];
            }
            arr[tempSet.size()] = '\0';
            sets[currSet] = arr; //adding set to the group of the sets
            currSet++;
        }
    }
    return sets;
}

int* compareWithSTLset(){
    int* errors = new int[4]; //allocating memory for array with the number of errors
    errors[0] = compareFiles("idol_output.txt", "outputAr.txt"); //comparing with array results
    errors[1] = compareFiles("idol_output.txt", "outputLi.txt"); //comparing with list results
    errors[2] = compareFiles("idol_output.txt", "outputBa.txt"); //comparing with bit array results
    errors[3] = compareFiles("idol_output.txt", "outputBm.txt"); //comparing with bit mask results
    return errors;
}
