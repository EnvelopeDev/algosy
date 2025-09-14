#include "fileManager.hpp"

using namespace std;

vector<vector<char>> generateArrays(int arrayCount, int arraySize) {
    vector<vector<char>> arrays(arrayCount);
 
    random_device rd;
    mt19937 rng(rd());
    
    for (int i = 0; i < arrayCount; i++) {
        arrays[i].resize(arraySize);
        for (int j = 0; j < arraySize; j++) {
            arrays[i][j] = static_cast<char>('A' + (rng() % 26));
        }
    }
    
    return arrays;
}
/*
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
    */