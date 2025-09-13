#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <cctype>

using namespace std;


vector<vector<char>> generateArrays(int arrayCount, int arraySize) {
    vector<vector<char>> arrays(arrayCount);
    string uppercaseLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    random_device rd;
    mt19937 rng(rd());
    
    for (int i = 0; i < arrayCount; i++) {
        arrays[i].resize(arraySize);
        for (int j = 0; j < arraySize; j++) {
            arrays[i][j] = uppercaseLetters[rng() % 26];
        }
    }
    
    return arrays;
}

void writeToCSV(const vector<vector<char>>& arrays) {
    ofstream csvFile("input.csv");
    
    if (!csvFile.is_open()) {
        cout << "Error opening file input.csv" << endl;
        return;
    }

    for (size_t i = 0; i < arrays.size(); i++) {
        for (size_t j = 0; j < arrays[i].size(); j++) {
            csvFile << arrays[i][j];
            if (j < arrays[i].size() - 1) csvFile << ";";
        }
        csvFile << "\n";
    }
    
    csvFile.close();
}

int main() {
    cout << "=== Array Generator ===\n\n";
    
    int arrayCount, arraySize;
    vector<vector<char>> arrays;

    cout << "Enter array size: ";
    cin >> arraySize;
    
    cout << "\nGenerating arrays...\n";
    arrays = generateArrays(100, arraySize);

    writeToCSV(arrays);
    
    cout << "\n=== Program Completed ===\n";
    cout << "Arrays created: " << arrays.size() << endl;
    cout << "Size of each array: " << (arrays.empty() ? 0 : arrays[0].size()) << " elements\n";
    cout << "File saved as input.csv" << endl;
    return 0;
}