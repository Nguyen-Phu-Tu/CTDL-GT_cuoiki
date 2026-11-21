#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;


string chuanHoaChuoi(string s) {
    int len = (int)s.length();
    if (len == 0) {
        return "";
    }

    int start = 0;
    while (start < len && s[start] == ' ') {
        start++;
    }

    int end = len - 1;
    while (end >= start && s[end] == ' ') {
        end--;
    }

    if (start > end) {
        return "";
    }

    string result = "";
    bool prevSpace = false;
    for (int i = start; i <= end; i++) {
        if (s[i] == ' ') {
            if (!prevSpace) {
                result += ' ';
                prevSpace = true;
            }
        } else {
            result += s[i];
            prevSpace = false;
        }
    }

    bool newWord = true;
    for (int i = 0; i < (int)result.length(); i++) {
        if (result[i] == ' ') {
            newWord = true;
        } else {
            if (newWord) {
                result[i] = toupper((unsigned char)result[i]);
                newWord = false;
            } else {
                result[i] = tolower((unsigned char)result[i]);
            }
        }
    }

    return result;
}


string tachTen(string hoTen) {
    if (hoTen.empty()) {
        return "";
    }

    int lastSpace = -1;
    for (int i = (int)hoTen.length() - 1; i >= 0; i--) {
        if (hoTen[i] == ' ') {
            lastSpace = i;
            break;
        }
    }

    if (lastSpace == -1) {

        return hoTen;
    }

 
    return hoTen.substr(lastSpace + 1);
}


string tachHoDem(string hoTen) {
    if (hoTen.empty()) {
        return "";
    }


    int lastSpace = -1;
    for (int i = (int)hoTen.length() - 1; i >= 0; i--) {
        if (hoTen[i] == ' ') {
            lastSpace = i;
            break;
        }
    }

    if (lastSpace == -1) {
        return "";
    }
    return hoTen.substr(0, lastSpace);
}

string toUpperStr(string s) {
    for (int i = 0; i < (int)s.length(); i++) {
        s[i] = toupper((unsigned char)s[i]);
    }
    return s;
}

string toLowerStr(string s) {
    for (int i = 0; i < (int)s.length(); i++) {
        s[i] = tolower((unsigned char)s[i]);
    }
    return s;
}


bool kiemTraNgaySinh(string ns) {
    // Buoc 1: Kiem tra do dai
    if ((int)ns.length() != 10) {
        return false;
    }

    if (ns[2] != '/' || ns[5] != '/') {
        return false;
    }

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) {
            continue; 
        }
        if (!isdigit((unsigned char)ns[i])) {
            return false;
        }
    }

    int day   = (ns[0] - '0') * 10 + (ns[1] - '0');
    int month = (ns[3] - '0') * 10 + (ns[4] - '0');
    int year  = (ns[6] - '0') * 1000 + (ns[7] - '0') * 100
              + (ns[8] - '0') * 10   + (ns[9] - '0');

    if (year < 1900 || year > 2026) {
        return false;
    }
    if (month < 1 || month > 12) {
        return false;
    }
    if (day < 1) {
        return false;
    }

    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (isLeapYear) {
        daysInMonth[2] = 29;
    }


    if (day > daysInMonth[month]) {
        return false;
    }

    return true;
}


bool kiemTraGioiTinh(string &gt) {
    string lower = toLowerStr(gt);

    if (lower == "nam") {
        gt = "Nam";
        return true;
    }

    if (lower == "nu") {
        gt = "Nu";
        return true;
    }

    return false;
}


void inDuongKe() {
    cout << "+-----+------------+-------------------------+"
         << "----------+------------+--------------------+"
         << endl;
}


void inTieuDeBang() {
    inDuongKe();
    cout << "|" << right << setw(4) << "STT" << " "
         << "| " << left << setw(11) << "Ma Du Thi"
         << "| " << left << setw(24) << "Ho Ten"
         << "| " << left << setw(9)  << "Gioi Tinh"
         << "| " << left << setw(11) << "Ngay Sinh"
         << "| " << left << setw(19) << "Que Quan"
         << "|" << endl;
    inDuongKe();
}


void inDongThiSinh(ThiSinh ts, int stt) {
    cout << "|" << right << setw(4) << stt << " "
         << "| " << left << setw(11) << ts.maDuThi
         << "| " << left << setw(24) << ts.hoTen
         << "| " << left << setw(9)  << ts.gioiTinh
         << "| " << left << setw(11) << ts.ngaySinh
         << "| " << left << setw(19) << ts.queQuan
         << "|" << endl;
}
