#include <vector>
#include <string>
#include <iostream>
#include "generator.hpp"

class ConsoleInterface
{
private:
    std::vector<std::string> inputGroupSet(); //does the input from console to the set group (A, B, C, D)
    bool isValidSet(std::string str); //for checking correctness of the entered set
public:
    void show();
    void inputFromConsole(); //does the input from the console to input.csv
};