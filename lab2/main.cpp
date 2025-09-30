#include "setTest.hpp"
#include "consoleInterface.hpp"

int main(){
    ConsoleInterface consoleInterface;
    consoleInterface.show();
    std::vector<char**> sets; //sets from input.csv
    FileManager fm;

    //reading input.csv
    sets = fm.inputFromCSV("data/input.csv");

    SetTest setTests(sets);
    setTests.doSetTests();
    setTests.printTestInfo();

    //if the amount of sets is less than 16, it is outputting to the console
    if(setTests.getNumTests() < 16){
        fm.outputFromCSVtoConsole("data/outputAr.txt", sets);
    }
    return 0;
}