#include "idol_test.hpp"

set<char> subtractSets(const vector<set<char>>& sets){
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

void testIdolSet(){
    ifstream inputFile("data/input.csv");
    ofstream outputFile("data/idol_output.txt");
    string line;
    
    while(getline(inputFile, line)){
        vector<set<char>> sets = parseCSVLine(line); //converts a csv string into a vector of sets
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
