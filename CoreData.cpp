#include "CoreData.h"
#include <cctype>
using namespace std;

void initHashTable(HashTable &ht) {
    for (int i = 0; i < 26; i++) {
        ht.buckets[i] = nullptr;
    }
    ht.soLuong = 0;
}

Node* createNode(ThiSinh ts) {
    Node* newNode = new Node;
    newNode->data = ts;
    newNode->next = nullptr;
    return newNode;
}

int hashFunction(string hoTen) {
    if (hoTen.empty()) {
        return 0;
    }

    int lastSpace = -1;
    for (int i = (int)hoTen.length() - 1; i >= 0; i--) {
        if (hoTen[i] == ' ') {
            lastSpace = i;
            break;
        }
    }

    char firstCharOfTen;
    if (lastSpace == -1) {
        firstCharOfTen = hoTen[0];
    } else {
        firstCharOfTen = hoTen[lastSpace + 1];
    }

    firstCharOfTen = toupper((unsigned char)firstCharOfTen);


    if (firstCharOfTen >= 'A' && firstCharOfTen <= 'Z') {
        return firstCharOfTen - 'A';
    }

    return 0;
}

void clearHashTable(HashTable &ht) {
    for (int i = 0; i < 26; i++) {
        Node* current = ht.buckets[i];
        while (current != nullptr) {
            Node* temp = current;     
            current = current->next;  
            delete temp;               
        }
        ht.buckets[i] = nullptr;         
    }
    ht.soLuong = 0;
}
