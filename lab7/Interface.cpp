#include "Interface.hpp"

Interface::Interface() {}
Interface::~Interface() {}

void Interface::show()
{
    std::cout << "========================================\n";
    std::cout << "   Демонстрация операций над Sequence<T>\n";
    std::cout << "========================================\n\n";

    // ── CONCAT ───────────────────────────────────────────────────────────
    std::cout << "=== CONCAT ===\n";
    {
        Sequence<char> A = {'a','b','c','d'};
        Sequence<char> B = {'e','f'};
        std::cout << "A = "; A.print(); std::cout << "\n";
        std::cout << "B = "; B.print(); std::cout << "\n";
        std::cout << "A.concat(B) = "; A.concat(B).print(); std::cout << "\n";
        // -> [a, b, c, d, e, f]
    }
    {
        Sequence<int> A = {10, 20, 30};
        Sequence<int> B = {40, 50};
        std::cout << "A = "; A.print(); std::cout << "\n";
        std::cout << "B = "; B.print(); std::cout << "\n";
        std::cout << "A.concat(B) = "; A.concat(B).print(); std::cout << "\n";
        // -> [10, 20, 30, 40, 50]
    }
    std::cout << "\n";

    // ── ERASE ────────────────────────────────────────────────────────────
    std::cout << "=== ERASE ===\n";
    {
        Sequence<char> A = {'a','b','c','d','e','f'};
        std::cout << "A = "; A.print(); std::cout << "\n";

        std::cout << "A.erase(p1=2, p2=4) = "; A.erase(2,4).print(); std::cout << "\n";
        // -> [a, e, f]

        std::cout << "A.erase(p1=1, p2=1) = "; A.erase(1,1).print(); std::cout << "\n";
        // -> [b, c, d, e, f]

        std::cout << "A.erase(p1=1, p2=6) = "; A.erase(1,6).print(); std::cout << "\n";
        // -> []

        try {
            A.erase(4, 2);
        } catch (const std::out_of_range& e) {
            std::cout << "A.erase(4,2) -> исключение: " << e.what() << "\n";
        }
    }
    std::cout << "\n";

    // ── EXCL ─────────────────────────────────────────────────────────────
    std::cout << "=== EXCL ===\n";
    {
        Sequence<char> A = {'a','b','c','d','e','f'};
        std::cout << "A = "; A.print(); std::cout << "\n";

        Sequence<char> sub1 = {'b','c','d'};
        std::cout << "A.excl([b,c,d]) = "; A.excl(sub1).print(); std::cout << "\n";
        // -> [a, e, f]

        Sequence<char> sub2 = {'x','y'};
        std::cout << "A.excl([x,y])   = "; A.excl(sub2).print(); std::cout << "\n";
        // -> [a, b, c, d, e, f]  (не найдена)

        Sequence<char> sub3 = {'a','b','c','d','e','f'};
        std::cout << "A.excl(A)       = "; A.excl(sub3).print(); std::cout << "\n";
        // -> []

        // Повторяющееся вхождение — удаляется первое
        Sequence<char> A2 = {'a','b','c','a','b','c','d'};
        Sequence<char> sub4 = {'a','b','c'};
        std::cout << "A2 = "; A2.print(); std::cout << "\n";
        std::cout << "A2.excl([a,b,c]) = "; A2.excl(sub4).print(); std::cout << "\n";
        // -> [a, b, c, d]
    }
    std::cout << "\n";

    // ── Sequence<int> — те же операции, другой тип ────────────────────────
    std::cout << "=== Sequence<int>: ERASE и EXCL ===\n";
    {
        Sequence<int> A = {10, 20, 30, 40, 50};
        std::cout << "A = "; A.print(); std::cout << "\n";

        std::cout << "A.erase(2,3) = "; A.erase(2,3).print(); std::cout << "\n";
        // -> [10, 40, 50]

        Sequence<int> sub = {20, 30};
        std::cout << "A.excl([20,30]) = "; A.excl(sub).print(); std::cout << "\n";
        // -> [10, 40, 50]
    }
    std::cout << "\n";

    // ── HashTable<string, Sequence<char>> ────────────────────────────────
    std::cout << "=== HashTable<string, Sequence<char>> ===\n";
    {
        HashTable<std::string, Sequence<char>> ht;
        ht["s1"] = Sequence<char>({'H','e','l','l','o'});
        ht["s2"] = Sequence<char>({'W','o','r','l','d'});
        std::cout << "ht[s1] = "; ht.getElem("s1").print(); std::cout << "\n";
        std::cout << "ht[s2] = "; ht.getElem("s2").print(); std::cout << "\n";

        Sequence<char> merged = ht.getElem("s1").concat(ht.getElem("s2"));
        std::cout << "ht[s1].concat(ht[s2]) = "; merged.print(); std::cout << "\n";
        // -> [H, e, l, l, o, W, o, r, l, d]

        Sequence<char> trimmed = ht.getElem("s1").erase(2, 3);
        std::cout << "ht[s1].erase(2,3)     = "; trimmed.print(); std::cout << "\n";
        // "Hello" без 'e','l' -> [H, l, o]

        Sequence<char> sub = {'l','l'};
        std::cout << "ht[s1].excl([l,l])    = "; ht.getElem("s1").excl(sub).print(); std::cout << "\n";
        // "Hello": excl('l','l') -> [H, e, o]
    }
}
