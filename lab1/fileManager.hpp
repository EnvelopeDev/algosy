/*This file is required for generator.cpp and idol_test.cpp programs to work with files*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm>
#include <random>

using namespace std;

int compareFiles(const string& filename1, const string& filename2);
void writeToCSV(const vector<vector<char>>& arrays);
vector<set<char>> parseCSVLine(const string& line);
set<string> stringToSet(const string& line);