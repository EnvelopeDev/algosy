#include "setTest.hpp"
#include "consoleInterface.hpp"

int main(){
    ConsoleInterface consoleInterface;
    long long totalRuntime;
    std::vector<char**> sets; //sets to do tests
    FileManager fm; //filemanager for work with a files (input/output)

    consoleInterface.show();
    auto start = std::chrono::high_resolution_clock::now(); //timer starts
    //reading input.csv
    sets = fm.inputFromCSV("data/input.csv");

    SetTest setTests(sets); //init the class to do the tests with the sets from input.csv
    setTests.doSetTests(); //doing tests
    setTests.printTestInfo(); //printing results of tests (time, amount of errors)

    //if the amount of sets is less than 16, it is outputting to the console
    std::cout << "\nArray set results was saved to data/outputAr.txt\n";
    std::cout << "List set results was saved to data/outputLi.txt\n";
    std::cout << "Bit array set results was saved to data/outputBa.txt\n";
    std::cout << "Bitmask set results was saved to data/outputBm.txt\n\n";
    if(setTests.getNumTests() < 16){
        //priting input sets and result sets from .txt files
        fm.outputFromCSVtoConsole("data/outputAr.txt", sets);
        std::cout << "\n\n";
        fm.outputFromCSVtoConsole("data/outputLi.txt", sets);
        std::cout << "\n\n";
        fm.outputFromCSVtoConsole("data/outputBa.txt", sets);
        std::cout << "\n\n";
        fm.outputFromCSVtoConsole("data/outputBm.txt", sets);
        std::cout << "\n\n";
    }
    auto end = std::chrono::high_resolution_clock::now(); //timer stops
    totalRuntime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); //counting runtime in microseconds
    std::cout << "TOTAL PROGRAM RUNTIME: " << totalRuntime << " microseconds" << '\n';
    return 0;
}