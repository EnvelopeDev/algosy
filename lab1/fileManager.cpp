#include "fileManager.hpp"

//Function compares two files
int compareFiles(const string& filename1, const string& filename2) {
    ifstream file1(filename1);
    ifstream file2(filename2);

    string line1, line2;
    bool f1;
    bool f2;
    int diffCount = 0;

    do{
        f1 = static_cast<bool>(getline(file1, line1));
        f2 = static_cast<bool>(getline(file2, line2));

        if(f1 && f2) if (line1 != line2) diffCount++;
    }while(f1 && f2);

    file1.close();
    file2.close();

    return diffCount;
}

void writeToCSV(const vector<vector<char>>& arrays){
    ofstream csvFile("input.csv");

    if(!csvFile.is_open()){
        cout << "Error opening file input.csv" << endl;
        return;
    }

    for(int i = 0; i < arrays.size(); i += 3){

        if(i < arrays.size()){

            csvFile << arrays[i].size() << ";";
            for(int j = 0; j < arrays[i].size(); j++){
                csvFile << arrays[i][j];
                if(j < arrays[i].size() - 1) csvFile << ",";
            }
        }

        if(i + 1 < arrays.size()){
            csvFile << ";" << arrays[i + 1].size() << ";";
            for(int j = 0; j < arrays[i + 1].size(); j++){
                csvFile << arrays[i + 1][j];
                if(j < arrays[i + 1].size() - 1) csvFile << ",";
            }
        }

        if(i + 2 < arrays.size()){
            csvFile << ";" << arrays[i + 2].size() << ";";
            for(int j = 0; j < arrays[i + 2].size(); j++){
                csvFile << arrays[i + 2][j];
                if(j < arrays[i + 2].size() - 1) csvFile << ",";
            }
        }

        csvFile << "\n";
    }

    csvFile.close();
}

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
