#include "fileManager.hpp"

// Функция для преобразования строки в set (игнорирует порядок и дубликаты)
set<string> stringToSet(const string& line) {
    set<string> result;
    stringstream ss(line);
    string item;
    
    while (getline(ss, item, ',')) {
        result.insert(item);
    }
    
    return result;
}

// Функция сравнивает два файла, используя set для сравнения строк
int compareFiles(const string& filename1, const string& filename2) {
    ifstream file1(filename1);
    ifstream file2(filename2);

    if (!file1.is_open() || !file2.is_open()) {
        cerr << "Ошибка открытия файлов!" << endl;
        return -1;
    }

    string line1, line2;
    int diffCount = 0;
    int lineNumber = 0;

    while (getline(file1, line1) && getline(file2, line2)) {
        lineNumber++;
        
        // Преобразуем строки в sets
        set<string> set1 = stringToSet(line1);
        set<string> set2 = stringToSet(line2);
        
        // Сравниваем sets
        if (set1 != set2) {
            diffCount++;
        }
    }

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
