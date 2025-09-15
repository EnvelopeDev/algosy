#include "fileManager.hpp"

using namespace std;

//Operation: E = A xor (B ∪ C ∪ D)
set<char> subtractSets(const vector<set<char>>& sets){
    set<char> result; // Set for results
    
    const set<char>& A = sets[0];
    const set<char>& B = sets[1];
    const set<char>& C = sets[2];
    const set<char>& D = sets[3];
    
    for (char elem : A){
        // Check that the element is not contained in B, C and D
        if(!(B.find(elem) != B.end() ||
             C.find(elem) != C.end() ||  
             D.find(elem) != D.end())){  
            result.insert(elem); // Add to result
        }
    }
    
    return result;
}

//Function creates perfect csv file processing in txt
void testIdolSet(){
    ifstream inputFile("input.csv");
    ofstream outputFile("idol_output.txt");

    string line;
    
    while(getline(inputFile, line)){
        vector<set<char>> sets = parseCSVLine(line); //Converts a csv string into a vector of sets

        set<char> result = subtractSets(sets); //Performs the operation of subtracting sets

        //Write result sets to a txt file with using a comma
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
