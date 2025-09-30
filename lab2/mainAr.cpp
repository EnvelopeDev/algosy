#include <iostream>
#include "array_set.hpp"
#include "listSet.hpp"
#include "barray_set.hpp"
#include "bmask_set.hpp"
using namespace std;

int main()
{
    BitMaskSet set1, set2("AABCCDEFGHI"), set3("ABCDEFGHI");
    set2.print(); std::cout << '\n';
    //std::cout << set2.getSize() << '\n';
    set3.print();std::cout << '\n';
    //std::cout  << set3.getSize() << '\n';
    BitMaskSet set4(set2);
    set4.print();std::cout << '\n';
    //std::cout  << set4.getSize() << '\n';
    for(int i=0;i<26;i++){
        set1.insert('A'+i);
    }
    set1.print();std::cout << '\n'; //cout << set1.getSize() << '\n';
    for(int i=0;i<26;i++){
        set1.insert('A'+i);
    }
    set1.print(); std::cout << '\n';//cout << set1.getSize() << '\n';
    set1 = ~set3;
    set1.print();std::cout << '\n'; //cout << set1.getSize() << '\n';
    set1 &= set2;
    set1.print(); std::cout << '\n';//cout << set1.getSize() << '\n';
    bool bl = set2==set3;
    if(bl){
        cout << "ok\n";
    }
    set2.remove('A');
    set2.print();std::cout << '\n'; //cout << ' ' << set2.getSize() << '\n';
    set2.remove('D');
    set2.print();std::cout << '\n'; //cout << ' ' << set2.getSize() << '\n';
    set2.print(); std::cout << '\n';//cout << ' ' << set2.getSize() << '\n';
    set2.clear();
    set2.print(); std::cout << '\n';//cout << ' ' << set2.getSize() << '\n';
    set2.insert('A');
    
    set2.print();std::cout << '\n'; //cout << ' ' << set2.getSize() << '\n';
    return 0;
}
