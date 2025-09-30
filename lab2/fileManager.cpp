#include "fileManager.hpp"

set<string> FileManager::stringToSet(const string& line) {
    set<string> result;
    stringstream ss(line); //openning stream in line
    string item;
    
    //split line by commas
    while (getline(ss, item, ',')) {
        result.insert(item);
    }
    
    return result;
}

int FileManager::compareFiles(const string& filename1, const string& filename2) {
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

vector<set<char>> FileManager::parseCSVLine(const string& line){
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

void FileManager::outputToCSV(std::vector<char*> results, const char* filename){
    std::ofstream fout(filename);
    for(int i=0;i<results.size();i++){
        for(int j=0;j<strlen(results[i]);j++){
            fout << results[i][j];
            if(j!=strlen(results[i])-1){
                fout << ',';
            }
        }
        fout << '\n';
    }
}

std::vector<char**> FileManager::inputFromCSV(const char* filename){
    std::vector<char**> res;
    std::ifstream fin(filename); //file with generated tests
    std::string line; //line in input.csv to read
    char** setGroup; //group of 4 sets (A, B, C, D)

    while(getline(fin, line)){
        setGroup = parseFileLine(line);
        res.push_back(setGroup);
    }
    return res;
}

void FileManager::outputFromCSVtoConsole(const char* filename, std::vector<char**> sets){
    char** setGroup;
    std::ifstream fin(filename);
    std::string out;
    std::cout << "==================[OUTPUT]==================\n";
    for(int i=0;i<sets.size();i++){
        getline(fin, out);
        setGroup = sets[i];
        std::cout << i+1 << " test\n";
        for(int j=0;j<4;j++){
            std::cout << static_cast<char>('A'+j) << ": ";
            for(int l=0; l<strlen(setGroup[j]);l++){
                std::cout << setGroup[j][l];
                if(l!=strlen(setGroup[j])-1){
                    std::cout << ", ";
                }
            }
            std::cout << '\n';
        }
        std::cout <<"E: "<< out << '\n';
        std::cout << "--------------------------------------------\n";
    }
    std::cout << "============================================\n";
}

char** FileManager::parseFileLine(const std::string& line){
    std::stringstream ss(line); //stream with the line (string)
    std::string token;
    char** sets = new char*[4]; //allocating memory for the group of the sets(A, B, C ,D)
    int currSet=0; //counter for a number of the set

    //split the line with ';'
    while(getline(ss, token, ';')){
        if (token.empty()) continue;
        //if string contains commas - it is set
        if(token.find(',') != std::string::npos){
            std::stringstream setSS(token); //creating stream in token
            std::string element; //element of set
            std::vector<char> tempSet; //temporary container for elements of the set

            while(getline(setSS, element, ',')){
                if(!element.empty()){
                    tempSet.push_back(element[0]);
                }
            }

            //convert vector to char array
            char* arr = new char[tempSet.size()+1]; //allocating memory for array with the set
            for(int i=0; i<tempSet.size(); i++){
                arr[i] = tempSet[i];
            }
            arr[tempSet.size()] = '\0';
            sets[currSet] = arr; //adding set to the group of the sets
            currSet++;
        }
    }
    return sets;
}