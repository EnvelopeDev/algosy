#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm> //for find()
#include <random>

using namespace std;

class FileManager{
    int compareFiles(const string& filename1, const string& filename2); //Function that compares two filse, using set to compare strings
    vector<set<char>> parseCSVLine(const string& line); //function converts a CSV format string into a vector of character sets
    set<string> stringToSet(const string& line); //function to convert string to set (ingores order and duplicates)
};