#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm> //for find()

using namespace std;

class FileManager{
public:
    int compareFiles(const string& filename1, const string& filename2); //Function that compares two filse, using set to compare strings
    vector<set<char>> parseCSVLine(const string& line); //function converts a CSV format string into a vector of character sets
    set<string> stringToSet(const string& line); //function to convert string to set (ingores order and duplicates)
    void outputToCSV(std::vector<char*> results, const char* filename);
    void outputFromCSVtoConsole(const char* filename, std::vector<char**> sets);
    std::vector<char**> inputFromCSV(const char* filename);
    char** parseFileLine(const std::string& line); //reads the line of .csv file, returns a group of 4 sets
};