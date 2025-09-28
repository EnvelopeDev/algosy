#include <iostream>
#include "array_set.hpp"
using namespace std;

int main()
{
    ArraySet set1, set2("AABCCDEFGHIM"), set3("ABCDEFGHIN");
    set2.print();
    std::cout << set2.getSize() << '\n';
    set3.print();
    std::cout  << set3.getSize() << '\n';
    ArraySet set4(set2);
    set4.print();
    std::cout  << set4.getSize() << '\n';
    for(int i=0;i<26;i++){
        set1.insert('A'+i);
    }
    set1.print(); cout << set1.getSize() << '\n';
    for(int i=0;i<26;i++){
        set1.insert('A'+i);
    }
    set1.print(); cout << set1.getSize() << '\n';
    set1 = ~set3;
    set1.print(); cout << set1.getSize() << '\n';
    set1 &= set2;
    set1.print(); cout << set1.getSize() << '\n';
    bool bl = set2==set3;
    if(bl){
        cout << "ok\n";
    }
    return 0;
}
