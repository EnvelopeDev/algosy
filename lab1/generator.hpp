#include <iostream>
#include <fstream>
#include <cstring>
#include <random>
#define MAX_SET_SIZE 26
#define NUM_SETS 4

void generateArraysToCSV(int numArrays, size_t minSizeA, size_t maxSizeA);
void generateSet(char* set, size_t minSize, size_t maxSize, bool fillWithAllLetters);
int randomInt(int min, int max); //generates num in [min, max] (including min and max)
void generatorInterface();