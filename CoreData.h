#ifndef COREDATA_H
#define COREDATA_H
#include "Models.h"
#include <string>
using namespace std;

void initHashTable(HashTable &ht);
Node* createNode(ThiSinh ts);

int hashFunction(string hoTen);
void clearHashTable(HashTable &ht);

#endif 
