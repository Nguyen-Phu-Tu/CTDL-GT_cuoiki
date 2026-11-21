#ifndef MODELS_H
#define MODELS_H
#include <string>
using namespace std;


struct ThiSinh {
    string maDuThi;   
    string hoTen;   
    string gioiTinh;  
    string ngaySinh;  
    string queQuan;   
};


struct Node {
    ThiSinh data;     
    Node* next;       
};


struct HashTable {
    Node* buckets[26]; 
    int soLuong;      
};

#endif 
