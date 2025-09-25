#pragma once
#include <iostream>
#include <fstream> //for work with files (i/o)
#include <cstring> //for work with char*
#include <random> //for generating random numbers
#define MAX_SET_SIZE 26
#define NUM_SETS 4

void generateArraysToCSV(int numArrays, size_t minSizeA, size_t maxSizeA); //generates sets, writes it to input.csv
void generateSet(char* set, size_t minSize, size_t maxSize, bool fillWithAllLetters); //generates set with size from minSize to maxSize
int randomInt(int min, int max); //generates num in [min, max] (including min and max)
void generatorInterface(); //interface of generator