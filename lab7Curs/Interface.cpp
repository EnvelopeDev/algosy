// Consolidated Interface.cpp - Combined output of both interfaces
#include "Interface.hpp"
#include <iostream>
#include <string>

Interface::Interface() {}
Interface::~Interface() {}

static void printSet(const std::string& name, const BitMaskSet& s) {
    std::cout << name << " = ";
    s.print();
    std::cout << "\n";
}

void Interface::show() {
    std::cout << "============================================================\n";
    std::cout << "  Variant 36 | Power: 32 | (A ⊕ B ∩ C) \\ D ∩ E\n";
    std::cout << "  Priority: ∩ > ⊕ > \\ > ∪\n";
    std::cout << "  Formula expands as: ((A ⊕ (B ∩ C)) \\ D) ∩ E\n";
    std::cout << "============================================================\n\n";

    Generator gen;

    std::cout << "=== Example 1: Manual Sets ===\n";
    {
        BitMaskSet A("ABCDEFabcdef"); 
        BitMaskSet B("BCDEFGabcd");   
        BitMaskSet C("CDEFGHbcde");   
        BitMaskSet D("DEFGHIcdef");   
        BitMaskSet E("EFGHIJdef");     

        printSet("A", A);
        printSet("B", B);
        printSet("C", C);
        printSet("D", D);
        printSet("E", E);
        std::cout << "\n";

        BitMaskSet step1 = B & C;
        printSet("B ∩ C", step1);

        BitMaskSet step2 = A ^ step1;
        printSet("A ⊕ (B ∩ C)", step2);

        BitMaskSet step3 = step2 - D;
        printSet("(A ⊕ (B ∩ C)) \\ D", step3);

        BitMaskSet result = step3 & E;
        printSet("((A ⊕ (B ∩ C)) \\ D) ∩ E", result);
    }

    std::cout << "\n=== Example 2: Random Sets ===\n";
    {
        BitMaskSet A(gen.generateSet(5, 20));
        BitMaskSet B(gen.generateSet(5, 20));
        BitMaskSet C(gen.generateSet(5, 20));
        BitMaskSet D(gen.generateSet(5, 20));
        BitMaskSet E(gen.generateSet(5, 20));

        printSet("A", A);
        printSet("B", B);
        printSet("C", C);
        printSet("D", D);
        printSet("E", E);
        std::cout << "\n";

        BitMaskSet step1 = B & C;
        printSet("B ∩ C", step1);

        BitMaskSet step2 = A ^ step1;
        printSet("A ⊕ (B ∩ C)", step2);

        BitMaskSet step3 = step2 - D;
        printSet("(A ⊕ (B ∩ C)) \\ D", step3);

        BitMaskSet result = step3 & E;
        printSet("((A ⊕ (B ∩ C)) \\ D) ∩ E", result);
    }

    std::cout << "\n=== Example 3: Intermediate Results in HashTable ===\n";
    {
        BitMaskSet A("ABCDEFGHIJ");
        BitMaskSet B("CDEFGHIJKL");
        BitMaskSet C("EFGHIJKLMN");
        BitMaskSet D("GHIJKLMNOP");
        BitMaskSet E("IJKLMNOPQR");

        HashTable<std::string, BitMaskSet> steps;
        steps.insert("A", A);
        steps.insert("B", B);
        steps.insert("C", C);
        steps.insert("D", D);
        steps.insert("E", E);
        steps.insert("B∩C", steps.getElem("B") & steps.getElem("C"));
        steps.insert("A⊕(B∩C)", steps.getElem("A") ^ steps.getElem("B∩C"));
        steps.insert("(A⊕B∩C)\\D", steps.getElem("A⊕(B∩C)") - steps.getElem("D"));
        steps.insert("result", steps.getElem("(A⊕B∩C)\\D") & steps.getElem("E"));

        for (const std::string& key : {"A", "B", "C", "D", "E","B∩C", "A⊕(B∩C)", "(A⊕B∩C)\\D", "result"}) {
            std::cout << key << " = ";
            steps.getElem(key).print();
            std::cout << "\n";
        }
    }

    std::cout << "\n\n========================================\n";
    std::cout << "         SEQUENCE OPERATIONS\n";
    std::cout << "========================================\n\n";

    std::cout << "================ CONCAT ================\n";
    {
        Sequence<char> A = {'a', 'b', 'c', 'd'};
        Sequence<char> B = {'e', 'f'};
        std::cout << "A           = "; A.print(); std::cout << "\n";
        std::cout << "B           = "; B.print(); std::cout << "\n";
        std::cout << "A.concat(B) = "; A.concat(B).print(); std::cout << "\n";
    }
    {
        Sequence<int> A = {10, 20, 30};
        Sequence<int> B = {40, 50};
        std::cout << "A           = "; A.print(); std::cout << "\n";
        std::cout << "B           = "; B.print(); std::cout << "\n";
        std::cout << "A.concat(B) = "; A.concat(B).print(); std::cout << "\n";
    }
    std::cout << "\n";

    std::cout << "================= ERASE ================\n";
    {
        Sequence<char> A = {'a', 'b', 'c', 'd', 'e', 'f'};
        std::cout << "A                   = "; A.print(); std::cout << "\n";

        std::cout << "A.erase(p1=2, p2=4) = "; A.erase(2, 4).print(); std::cout << "\n";
        std::cout << "A.erase(p1=1, p2=1) = "; A.erase(1, 1).print(); std::cout << "\n";
        std::cout << "A.erase(p1=1, p2=6) = "; A.erase(1, 6).print(); std::cout << "\n";

        try {
            A.erase(4, 2);
        } catch (const std::out_of_range& e) {
            std::cout << "A.erase(4,2): incorrect input\n";
        }
    }
    std::cout << "\n";

    std::cout << "================== EXCL ================\n";
    {
        Sequence<char> A = {'a', 'b', 'c', 'd', 'e', 'f'};
        std::cout << "A                = "; A.print(); std::cout << "\n";

        Sequence<char> sub1 = {'b', 'c', 'd'};
        std::cout << "A.excl([b,c,d])  = "; A.excl(sub1).print(); std::cout << "\n";

        Sequence<char> sub2 = {'x', 'y'};
        std::cout << "A.excl([x,y])    = "; A.excl(sub2).print(); std::cout << "\n";

        Sequence<char> sub3 = {'a', 'b', 'c', 'd', 'e', 'f'};
        std::cout << "A.excl(A)        = "; A.excl(sub3).print(); std::cout << "\n";

        Sequence<char> A2 = {'a', 'b', 'c', 'a', 'b', 'c', 'd'};
        Sequence<char> sub4 = {'a', 'b', 'c'};
        std::cout << "A2               = "; A2.print(); std::cout << "\n";
        std::cout << "A2.excl([a,b,c]) = "; A2.excl(sub4).print(); std::cout << "\n";
    }
    std::cout << "\n";

    std::cout << "========================================\n";
    std::cout << "    HASHTABLE WITH SEQUENCE TEST\n";
    std::cout << "========================================\n\n";
    {
        HashTable<std::string, Sequence<char>> ht;
        ht["s1"] = Sequence<char>({'H', 'e', 'l', 'l', 'o'});
        ht["s2"] = Sequence<char>({'W', 'o', 'r', 'l', 'd'});
        std::cout << "ht[s1]                = "; ht.getElem("s1").print(); std::cout << "\n";
        std::cout << "ht[s2]                = "; ht.getElem("s2").print(); std::cout << "\n";

        Sequence<char> merged = ht.getElem("s1").concat(ht.getElem("s2"));
        std::cout << "ht[s1].concat(ht[s2]) = "; merged.print(); std::cout << "\n";

        Sequence<char> trimmed = ht.getElem("s1").erase(2, 3);
        std::cout << "ht[s1].erase(2,3)     = "; trimmed.print(); std::cout << "\n";

        Sequence<char> sub = {'l', 'l'};
        std::cout << "ht[s1].excl([l,l])    = "; ht.getElem("s1").excl(sub).print(); std::cout << "\n";
    }
}