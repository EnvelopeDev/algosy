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

    // Записываем по 3 массива в строку в формате: длина;массив;длина;массив;длина;массив
    for (size_t i = 0; i < arrays.size(); i += 3) {
        // Проверяем, что есть хотя бы один массив для записи
        if (i < arrays.size()) {
            // Первый массив
            csvFile << arrays[i].size() << ";";
            for (size_t j = 0; j < arrays[i].size(); j++) {
                csvFile << arrays[i][j];
                if (j < arrays[i].size() - 1) csvFile << ",";
            }
        }
        
        // Второй массив (если есть)
        if (i + 1 < arrays.size()) {
            csvFile << ";" << arrays[i + 1].size() << ";";
            for (size_t j = 0; j < arrays[i + 1].size(); j++) {
                csvFile << arrays[i + 1][j];
                if (j < arrays[i + 1].size() - 1) csvFile << ",";
            }
        }
        
        // Третий массив (если есть)
        if (i + 2 < arrays.size()) {
            csvFile << ";" << arrays[i + 2].size() << ";";
            for (size_t j = 0; j < arrays[i + 2].size(); j++) {
                csvFile << arrays[i + 2][j];
                if (j < arrays[i + 2].size() - 1) csvFile << ",";
            }
        }
        
        csvFile << "\n";
    }
    
    csvFile.close();
}

int main() {
    cout << "=== Array Generator ===\n\n";
    
    int arraySize;
    vector<vector<char>> arrays;

    cout << "Enter array size: ";
    cin >> arraySize;
    
    cout << "\nGenerating arrays...\n";
    arrays = generateArrays(300, arraySize);

    writeToCSV(arrays);
    
    cout << "\n=== Program Completed ===\n";
    cout << "Arrays created: " << arrays.size() << endl;
    cout << "Size of each array: " << (arrays.empty() ? 0 : arrays[0].size()) << " elements\n";
    cout << "File saved as input.csv" << endl;
    
    return 0;
}