#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <sstream>

using namespace std;

//Function converts a CSV format string into a vector of character sets 
vector<set<char>> parseCSVLine(const string& line){
    vector<set<char>> sets; // Container for results
    stringstream ss(line); // Stream for parsing the string
    string token; // Temporary storage for tokens

    // Split the string by ';' delimiter
    while(getline(ss, token, ';')){
        if(token.empty()) continue;
        
        // Look for tokens containing commas (these are our sets)
        if(token.find(',') != string::npos){
            set<char> currentSet;
            stringstream setSS(token);
            string element;
            
            // Split the token by commas
            while(getline(setSS, element, ',')){
                if(!element.empty()){
                    currentSet.insert(element[0]);
                }
            }
            sets.push_back(currentSet); // Save the set
        }
    }
    return sets; // Return all found sets
}

//Main operation: E = A xor (B ∪ C ∪ D)
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