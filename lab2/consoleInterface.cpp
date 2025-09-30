#include "consoleInterface.hpp"

void ConsoleInterface::show(){
    bool inpFromFile = true; //flag to check if we need to do the input from the file
    bool needGenNewTests=true; //flag to check if we need to generate new tests in input.csv
    char userOpt; //user option
    Generator testGenerator;

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
            testGenerator.generatorInterface(); //calling generator.cpp to generate new tests
        }
    }
    else{
        //inputting sets from the console
        inputFromConsole();
    }
}

void ConsoleInterface::inputFromConsole(){
    size_t arrSize; //size of the array
    int numOfTests;
    std::vector<std::string> groupSet; //group of 4 sets (A, B, C, D)
    std::ofstream fout("data/input.csv");

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

std::vector<std::string> ConsoleInterface::inputGroupSet(){
    //input the sets
    bool doFullAlphabet=false; //flag to check if it`s need to fill the set with all latin letters
    char userChoice;
    std::string inpSet;
    std::vector<std::string> groupSet(4);
    for(int i=0;i<4;i++){
        std::cout << "Set " << static_cast<char>('A'+i) << '\n';
        if(i==0){
            std::cout << "Fill the set A with all the latin letters? (y/n): ";
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
            std::cout << "Set A filled with all the latin letters\n";
        }else{
            //inputting sets from the keyboard
            std::cout << "Enter set: ";
            std::cin >> inpSet;
            if(!isValidSet(inpSet)){
                throw std::invalid_argument("Error: Set must contain only latin uppercase letters!");
            }
        }
        std::cout << "---------------------------\n";
        groupSet[i] = inpSet;
    }
    return groupSet;
}

bool ConsoleInterface::isValidSet(std::string str){
    for(int i=0; i<str.length();i++){
        if(!(str[i]>='A' && str[i]<='Z')){
            return false;
        }
    }
    return true;
}
