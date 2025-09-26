#pragma once
#include <iostream>
#include <string>
#include <cstring>
const int ALPHABET_SIZE = 26;

unsigned long long convStrToBitMask(const char* set);
unsigned long long subtractBitMaskSets(const unsigned long long A, const unsigned long long B, const unsigned long long C, const unsigned long long D); //E = A AND NOT(B OR C OR D)
char* convBitMaskToStr(const unsigned long long set);