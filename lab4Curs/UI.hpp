#pragma once

#include "Graph.hpp"
#include <iostream>
#include <string>
#include <cstdlib>  
#include <sstream>

class UI
{
private:
    Graph graph;
    
    void GraphCreator();
    void RandomGeneration();
    void CustomGeneration();

public:
    UI();
    ~UI();


};