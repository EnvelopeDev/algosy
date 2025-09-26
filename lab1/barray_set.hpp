#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <stdexcept>
const int POWER_OF_ALPHABET = 26;

bool* convStrToBitSet(const char* set);
bool* subtractSets(const bool* A, const bool* B, const bool* C, const bool* D); //E = A AND NOT(B OR C OR D)
char* convBitSetToStr(const bool* set);