#include <iostream>
#include "array_set.hpp"
using namespace std;

int main()
{
    ArraySet set1, set2("AABCCDEFGHI"), set3("ABCDEF");
    set2.print();
    std::cout << '\n';
    set3.print();
    std::cout << '\n';
    ArraySet set4(set2);
    set4.print();
    std::cout << '\n';
    
    return 0;
}
