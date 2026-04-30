#include "HashTable.hpp"

HashTable::HashTable():numBuckets(43){

}

unsigned HashTable::hash(const BitMaskSet& set){
    return set.getMask()%numBuckets;
}