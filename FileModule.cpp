#include "FileModule.h"
#include "CoreData.h"
#include "Utils.h"
#include "CrudModule.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void docFileTXT(HashTable &ht, string tenFile) {
    ifstream fin(tenFile.c_str());

    if (!fin.is_open()) {
        cout << "  [Loi] Khong the mo file: " << tenFile << endl;
        return;
    }

    cout << "\n=== DOC DU LIEU TU FILE: " << tenFile << " ===" << endl;

    string line;
    int dongDoc = 0;       
    int dongThanhCong = 0;  
    int dongLoi = 0;        

    string danhSachLoi[100];
    int soLoi = 0;

    while (getline(fin, line)) {
        dongDoc++;

        bool isEmpty = true;
        for (int i = 0; i < (int)line.length(); i++) {
            if (line[i] != ' ' && line[i] != '\t' && line[i] != '\r' && line[i] != '\n') {
                isEmpty = false;
                break;
            }
        }
        if (isEmpty) {
            continue; 
        }

       
        if (!line.empty() && line[line.length() - 1] == '\r') {
            line.erase(line.length() - 1);
        }


        stringstream ss(line);
        string fields[5];
        int fieldCount = 0;

        for (int f = 0; f < 5; f++) {
            if (getline(ss, fields[f], '|')) {
                fieldCount++;
            }
        }

    
        if (fieldCount < 5) {
            dongLoi++;
            if (soLoi < 100) {
                string msg = "  Dong ";
                int d = dongDoc;
                string numStr = "";
                if (d == 0) {
                    numStr = "0";
                } else {
                    while (d > 0) {
                        numStr = (char)('0' + d % 10) + numStr;
                        d /= 10;
                    }
                }
                msg += numStr + ": Thieu truong du lieu (can 5 truong, chi co ";
                d = fieldCount;
                numStr = "";
                if (d == 0) {
                    numStr = "0";
                } else {
                    while (d > 0) {
                        numStr = (char)('0' + d % 10) + numStr;
                        d /= 10;
                    }
                }
                msg += numStr + ")";
                danhSachLoi[soLoi] = msg;
                soLoi++;
            }
            continue;
        }

        ThiSinh ts;

        string ma = fields[0];
        int s = 0, e = (int)ma.length() - 1;
        while (s <= e && ma[s] == ' ') s++;
        while (e >= s && ma[e] == ' ') e--;
        ma = (s <= e) ? ma.substr(s, e - s + 1) : "";
        ts.maDuThi = toUpperStr(ma);

   
        ts.hoTen = chuanHoaChuoi(fields[1]);


        string gt = chuanHoaChuoi(fields[2]);

  
        string ns = fields[3];
        s = 0;
        e = (int)ns.length() - 1;
        while (s <= e && ns[s] == ' ') s++;
        while (e >= s && ns[e] == ' ') e--;
        ts.ngaySinh = (s <= e) ? ns.substr(s, e - s + 1) : "";


        ts.queQuan = chuanHoaChuoi(fields[4]);


        string dongStr = "";
        int tmpDong = dongDoc;
        if (tmpDong == 0) {
            dongStr = "0";
        } else {
            while (tmpDong > 0) {
                dongStr = (char)('0' + tmpDong % 10) + dongStr;
                tmpDong /= 10;
            }
        }

        if (ts.maDuThi.empty()) {
            dongLoi++;
            if (soLoi < 100) {
                danhSachLoi[soLoi] = "  Dong " + dongStr + ": Ma du thi rong";
                soLoi++;
            }
            continue;
        }

        if (ts.hoTen.empty()) {
            dongLoi++;
            if (soLoi < 100) {
                danhSachLoi[soLoi] = "  Dong " + dongStr + ": Ho ten rong";
                soLoi++;
            }
            continue;
        }

        if (!kiemTraGioiTinh(gt)) {
            dongLoi++;
            if (soLoi < 100) {
                danhSachLoi[soLoi] = "  Dong " + dongStr + ": Gioi tinh khong hop le ('" + fields[2] + "')";
                soLoi++;
            }
            continue;
        }
        ts.gioiTinh = gt;

        if (!kiemTraNgaySinh(ts.ngaySinh)) {
            dongLoi++;
            if (soLoi < 100) {
                danhSachLoi[soLoi] = "  Dong " + dongStr + ": Ngay sinh khong hop le ('" + ts.ngaySinh + "')";
                soLoi++;
            }
            continue;
        }

        if (ts.queQuan.empty()) {
            dongLoi++;
            if (soLoi < 100) {
                danhSachLoi[soLoi] = "  Dong " + dongStr + ": Que quan rong";
                soLoi++;
            }
            continue;
        }

     
        if (kiemTraTrungMa(ht, ts.maDuThi)) {
            dongLoi++;
            if (soLoi < 100) {
                danhSachLoi[soLoi] = "  Dong " + dongStr + ": Ma du thi '" + ts.maDuThi + "' da ton tai (trung ma)";
                soLoi++;
            }
            continue;
        }

        themThiSinh(ht, ts);
        dongThanhCong++;
    }

    fin.close();

    cout << "\n  --- BAO CAO DOC FILE ---" << endl;
    cout << "  Tong so dong doc: " << dongDoc << endl;
    cout << "  Dong nap thanh cong: " << dongThanhCong << endl;
    cout << "  Dong bi bo qua (loi): " << dongLoi << endl;

    if (soLoi > 0) {
        cout << "\n  Chi tiet cac dong loi:" << endl;
        for (int i = 0; i < soLoi; i++) {
            cout << danhSachLoi[i] << endl;
        }
    }

    cout << "\n  >> Tong so thi sinh trong bang bam: " << ht.soLuong << endl;
}

void ghiFileTXT(const HashTable &ht, string tenFile) {
    ofstream fout(tenFile.c_str());

    if (!fout.is_open()) {
        cout << "  [Loi] Khong the tao/ghi file: " << tenFile << endl;
        return;
    }

    int count = 0;

    for (int i = 0; i < 26; i++) {
        Node* current = ht.buckets[i];
        while (current != nullptr) {
            fout << current->data.maDuThi << "|"
                 << current->data.hoTen << "|"
                 << current->data.gioiTinh << "|"
                 << current->data.ngaySinh << "|"
                 << current->data.queQuan << endl;

            count++;
            current = current->next;
        }
    }

    fout.close();

    cout << "  >> Da ghi " << count << " thi sinh ra file: " << tenFile << endl;
}
