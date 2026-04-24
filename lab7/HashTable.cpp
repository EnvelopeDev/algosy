#include "HashTable.hpp"

HashTable::HashTable():numBuckets(43){

}

unsigned HashTable::hash(unsigned long num){
    return (43*num+7)%numBuckets;
}