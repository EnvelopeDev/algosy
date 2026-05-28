#pragma once
#include <iostream>
#include <random>
#define MAX_SET_SIZE 32

class Generator{
private:
    std::mt19937 rng;
    int randomInt(int min, int max); //generates num in [min, max] (including min and max)
public:
    Generator();
    ~Generator();
    unsigned long generateSet(size_t minSize, size_t maxSize);
};