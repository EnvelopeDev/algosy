#pragma once
#include "fileManager.hpp" //for working with files (reading, writing, compare)
using namespace std;
class ExpectedResultCalculator{
public:
    set<char> subtractSets(const vector<set<char>>& sets); //function that does a subtraction of sets B, C, D from set A
    void testIdolSet(); //does the expected results with using the stl set
};