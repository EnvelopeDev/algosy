#include <iostream>
#include "array_set.hpp"
#include "listSet.hpp"
using namespace std;

int main()
{
    ListSet set1, set2("AABCCDEFGHI"), set3("ABCDEFGHI");
    set2.print();
    std::cout << set2.getSize() << '\n';
    set3.print();
    std::cout  << set3.getSize() << '\n';
    ListSet set4(set2);
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
    set2.remove('A');
    set2.print(); cout << ' ' << set2.getSize() << '\n';
    set2.remove('D');
    set2.print(); cout << ' ' << set2.getSize() << '\n';
    set2.remove(3);
    set2.print(); cout << ' ' << set2.getSize() << '\n';
    set2.clear();
    set2.print(); cout << ' ' << set2.getSize() << '\n';
    set2.insert('A');
    
    set2.print(); cout << ' ' << set2.getSize() << '\n';
    return 0;
}
