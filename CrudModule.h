#ifndef CRUDMODULE_H
#define CRUDMODULE_H
#include "Models.h"
#include <string>
using namespace std;

bool kiemTraTrungMa(const HashTable &ht, string ma);

int soSanhThiSinhTheoTen(const ThiSinh &a, const ThiSinh &b);

void themThiSinh(HashTable &ht, ThiSinh ts);

void nhapThiSinhTuBanPhim(HashTable &ht);

bool xoaThiSinhTheoMa(HashTable &ht, string ma);

void suaThiSinhTheoMa(HashTable &ht, string ma);

#endif 
