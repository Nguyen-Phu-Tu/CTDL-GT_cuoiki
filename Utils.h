#ifndef UTILS_H
#define UTILS_H


#include "Models.h"
#include <string>
using namespace std;


string chuanHoaChuoi(string s);


string tachTen(string hoTen);


string tachHoDem(string hoTen);


string toUpperStr(string s);


string toLowerStr(string s);

bool kiemTraNgaySinh(string ns);

bool kiemTraGioiTinh(string &gt);

void inDuongKe();

void inTieuDeBang();

void inDongThiSinh(ThiSinh ts, int stt);

#endif 
