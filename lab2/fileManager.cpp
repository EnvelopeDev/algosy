#include "fileManager.hpp"

set<string> stringToSet(const string& line) {
    set<string> result;
    stringstream ss(line); //openning stream in line
    string item;
    
    //split line by commas
    while (getline(ss, item, ',')) {
        result.insert(item);
    }
    
    return result;
}

int compareFiles(const string& filename1, const string& filename2) {
    ifstream file1(filename1);
    ifstream file2(filename2);

    if(!file1.is_open() || !file2.is_open()){
        cerr << "Ошибка открытия файлов!" << endl;
        return -1;
    }

    string line1, line2; //lines of two files
    int diffCount = 0; //number of the differents of the files
    int lineNumber = 0;

    //reading file line by line, comparing lines
    while(getline(file1, line1) && getline(file2, line2)){
        lineNumber++;
        
        //Converting strings to sets
        set<string> set1 = stringToSet(line1);
        set<string> set2 = stringToSet(line2);
        
        //Comparing sets
        if(set1 != set2){
            diffCount++;
        }
    }

    file1.close();
    file2.close();

    return diffCount;
}

vector<set<char>> parseCSVLine(const string& line){
    vector<set<char>> sets; //container for results
    stringstream ss(line); //stream for parsing the string
    string token; //temporary storage for tokens

    //split the string by ';' delimiter
    while(getline(ss, token, ';')){
        if(token.empty()) continue;

        //look for tokens containing commas (these are our sets)
        if(token.find(',') != string::npos){
            set<char> currentSet;
            stringstream setSS(token);
            string element;

            //split the token by commas
            while(getline(setSS, element, ',')){
                if(!element.empty()){
                    currentSet.insert(element[0]);
                }
            }
            sets.push_back(currentSet); //save the set
        }
    }
    return sets;
}
