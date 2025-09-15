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

int main(){
    ifstream inputFile("input.csv");
    ofstream outputFile("idol_output.txt");

    string line;
    int lineCount = 0;
    
    while(getline(inputFile, line)){
        lineCount++;
        vector<set<char>> sets = parseCSVLine(line);

        set<char> result = subtractSets(sets);
        
        for(auto it = result.begin(); it != result.end();){
            outputFile << *it;
            if(++it != result.end()){
                outputFile << ",";
            }
        }
        outputFile << endl;
        
    }
    
    inputFile.close();
    outputFile.close();
    
    return 0;
}
