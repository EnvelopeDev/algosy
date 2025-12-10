#pragma once

#include "Graph.hpp"
#include <string>
#include <cstdlib>  
#include <sstream>

class UI
{
private:
    Graph graph;
    int userChoice;
    void RandomGeneration();
    void CustomGeneration();
    
public:
    UI();
    ~UI();
    void show();
};