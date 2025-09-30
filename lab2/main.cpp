#include "setTest.hpp"
#include "generator.hpp" //generation of test cases (groups of 4 sets - A, B, C, D)
#include "consoleInterface.hpp"

void inputFromConsole(); //does the input from the console to input.csv
std::vector<std::string> inputGroupSet(); //does the input from console to the set group (A, B, C, D)
bool isValidSet(std::string str); //for checking correctness of the entered set

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