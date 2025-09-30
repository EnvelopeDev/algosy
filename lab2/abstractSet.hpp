#include <string>

class Set{
public:
    virtual ~Set() = default;
    virtual char* subtractSets(const Set& B, const Set& C, const Set& D)=0;
    virtual void print()=0;
    virtual char* toChar()=0;
    virtual bool contains(char ch)=0;
    virtual std::string toString();
    virtual void insert(char ch);
    virtual void remove(char ch);
    virtual void clear();
    virtual Set operator|(const Set& other);
    virtual Set operator&(const Set& other);
    virtual Set& operator=(const Set& other);
    virtual Set& operator|=(const Set& other);
    virtual Set& operator&=(const Set& other);
    virtual Set operator~();
};