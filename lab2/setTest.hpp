#include <chrono>
#include <vector>
#include "array_set.hpp" //realization of set with using an array
#include "listSet.hpp" //realization of set with using a list
#include "barray_set.hpp" //realization of set with using a bit array
#include "bmask_set.hpp" //realization of set with using a bit mask
#include "fileManager.hpp"

class SetTest
{
private:
    std::vector<ArraySet*> arraySets;
    std::vector<ListSet*> listSets;
    std::vector<BitArraySet*> bitArraySets;
    std::vector<BitMaskSet*> bitMaskSets;
    FileManager fm;
    long long* runtimes;
    int* errors;
    int numTests;
    std::vector<char*> arraySet(); //function doing tests of array set version
    std::vector<char*> listSet(); //function doing tests of list set version
    std::vector<char*> bitArraySet(); //function doing tests of bit array set version
    std::vector<char*> bitMaskSet(); //function doing tests of bit mask set version
    set<char> subtractSets(const vector<set<char>>& sets); //function that does a subtraction of sets B, C, D from set A
    void testIdolSet(); //does the expected results with using the stl set
    void compareWithSTLset();
    
public:
    SetTest(std::vector<char**> sets);
    ~SetTest();
    void doSetTests(); //function does tests from vector sets, returning runtimes in microseconds
    long long* getRuntimes();
    int* getErrors();
    void printTestInfo();
    int getNumTests();
};