#include "setTest.hpp"

SetTest::SetTest(std::vector<char**> sets){
    runtimes = new long long[4];
    errors = new int[4];
    for(int i=0;i<4;i++){
        runtimes[i]=-1;
        errors[i]=-1;
    }

    //converting vector with char** to List, BitArraySet, Bitmask vectors
    for(int i=0;i<sets.size();i++){
        ArraySet* arrays = new ArraySet[4]{ArraySet(sets[i][0]), ArraySet(sets[i][1]), ArraySet(sets[i][2]), ArraySet(sets[i][3])};
        arraySets.push_back(arrays);

        ListSet* lists = new ListSet[4]{ListSet(sets[i][0]), ListSet(sets[i][1]), ListSet(sets[i][2]), ListSet(sets[i][3])};
        listSets.push_back(lists);

        BitArraySet* basets = new BitArraySet[4]{BitArraySet(sets[i][0]), BitArraySet(sets[i][1]), BitArraySet(sets[i][2]), BitArraySet(sets[i][3])};
        bitArraySets.push_back(basets);

        BitMaskSet* bmsets = new BitMaskSet[4]{BitMaskSet(sets[i][0]), BitMaskSet(sets[i][1]), BitMaskSet(sets[i][2]), BitMaskSet(sets[i][3])};
        bitMaskSets.push_back(bmsets);
    }
    numTests=sets.size();
}

SetTest::~SetTest(){
    delete[] runtimes;
}

void SetTest::doSetTests(){
    std::vector<ArraySet*> arraySets;
    std::vector<ListSet*> listSets; //vector with tests for listSet() with the lists of a groups of the sets
    std::vector<BitArraySet*> baset; //vector with tests fot bitArraySet() with sets in BitArray Form
    std::vector<BitMaskSet*> bmset; //vector with tests fot bitMaskSet() with sets in BitMask Form
    std::vector<char*> results; //vector with results

    auto start = std::chrono::high_resolution_clock::now(); //timer starts
    results = arraySet();
    auto end = std::chrono::high_resolution_clock::now(); //timer stops
    runtimes[0] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); //counting runtime in microseconds

    //writing results to the file with array set results
    fm.outputToCSV(results, "data/outputAr.txt");

    start = std::chrono::high_resolution_clock::now(); //timer starts
    results = listSet();
    end = std::chrono::high_resolution_clock::now(); //timer stops
    runtimes[1] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); //counting runtime in microseconds

    //writing results to the file with list set results
    fm.outputToCSV(results, "data/outputLi.txt");

    start = std::chrono::high_resolution_clock::now(); //timer starts
    results = bitArraySet();
    end = std::chrono::high_resolution_clock::now(); //timer stops
    runtimes[2] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); //counting runtime in microseconds

    //writing results to the file with bit array set results
    fm.outputToCSV(results, "data/outputBa.txt");

    start = std::chrono::high_resolution_clock::now(); //timer starts
    results = bitMaskSet();
    end = std::chrono::high_resolution_clock::now(); //timer stops
    runtimes[3] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); //counting runtime in microseconds

    //writing results to the file with bit mask set results
    fm.outputToCSV(results, "data/outputBm.txt");
    testIdolSet();
    compareWithSTLset();
}

std::vector<char*> SetTest::arraySet(){
    std::vector<char*> setsRes; //resulting array with sets E
    ArraySet E;
    for(int i=0; i<arraySets.size();i++){
        E = arraySets[i][0].subtractSets(arraySets[i][1], arraySets[i][2], arraySets[i][3]);
        setsRes.push_back(E.toChar());
    }
    return setsRes;
}

std::vector<char*> SetTest::listSet(){
    std::vector<char*> setsRes; //resulting array with sets E
    ListSet setE;

    for(int i=0; i<listSets.size();i++){
        setE = listSets[i][0].subtractSets(listSets[i][1], listSets[i][2], listSets[i][3]);
        setsRes.push_back(setE.toChar());
    }
    return setsRes;
}

std::vector<char*> SetTest::bitArraySet(){
    std::vector<char*> setsRes; //resulting array with sets E
    BitArraySet setE("");

    for(int i=0; i<bitArraySets.size();i++){
        setE = bitArraySets[i][0].subtractSets(bitArraySets[i][1], bitArraySets[i][2], bitArraySets[i][3]);
        setsRes.push_back(setE.toChar());
    }
    return setsRes;
}

std::vector<char*> SetTest::bitMaskSet(){
    std::vector<char*> setsRes; //resulting array with sets E
    BitMaskSet setE("");

    for(int i=0; i<bitMaskSets.size();i++){
        setE = bitMaskSets[i][0].subtractSets(bitMaskSets[i][1], bitMaskSets[i][2], bitMaskSets[i][3]);
        setsRes.push_back(setE.toChar());
    }
    return setsRes;
}

set<char> SetTest::subtractSets(const vector<set<char>>& sets){
    set<char> result; //set for results
    const set<char>& A = sets[0];
    const set<char>& B = sets[1];
    const set<char>& C = sets[2];
    const set<char>& D = sets[3];
    
    for (char elem : A){
        //check that the element is not contained in B, C and D
        if(!(B.find(elem) != B.end() ||
             C.find(elem) != C.end() ||  
             D.find(elem) != D.end())){  
            result.insert(elem); //add to result
        }
    }
    
    return result;
}

void SetTest::testIdolSet(){
    ifstream inputFile("data/input.csv");
    ofstream outputFile("data/idol_output.txt");
    string line;

    while(getline(inputFile, line)){
        vector<set<char>> sets = fm.parseCSVLine(line); //converts a csv string into a vector of sets
        set<char> result = subtractSets(sets); //performs the operation of subtracting sets
        //write result sets to a txt file with using a comma
        bool first = true;
        for(const char& element : result){
            if(!first) outputFile << ","; //comma for all lines
            outputFile << element;
            first = false;
        }
        outputFile << '\n';
        
    }
    
    inputFile.close();
    outputFile.close();
}

void SetTest::compareWithSTLset(){
    errors[0] = fm.compareFiles("data/idol_output.txt", "data/outputAr.txt"); //comparing with array results
    errors[1] = fm.compareFiles("data/idol_output.txt", "data/outputLi.txt"); //comparing with list results
    errors[2] = fm.compareFiles("data/idol_output.txt", "data/outputBa.txt"); //comparing with bit array results
    errors[3] = fm.compareFiles("data/idol_output.txt", "data/outputBm.txt"); //comparing with bit mask results
}

long long* SetTest::getRuntimes(){
    return runtimes;
}

int* SetTest::getErrors(){
    return errors;
}

int SetTest::getNumTests(){
    return numTests;
}

void SetTest::printTestInfo(){
    //outputing runtimes
    std::cout << "=================[RUNTIMES]=================\n";
    std::cout << "Array: " << runtimes[0] << " microsecs" <<'\n';
    std::cout << "List: " << runtimes[1] << " microsecs" <<'\n';
    std::cout << "Bit Array: " << runtimes[2] << " microsecs" <<'\n';
    std::cout << "Bit Mask: " << runtimes[3] << " microsecs" <<'\n';
    std::cout << "============================================\n\n";
    //outputing numbers of errors
    std::cout << "=============[NUMBER OF ERRORS]=============\n";
    std::cout << "Array: " << errors[0] << '\n';
    std::cout << "List: " << errors[1] << '\n';
    std::cout << "Bit Array: " << errors[2] << '\n';
    std::cout << "Bit Mask: " << errors[3] << '\n';
    std::cout << "============================================\n\n";
}