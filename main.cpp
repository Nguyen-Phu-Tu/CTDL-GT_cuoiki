#include "Models.h"
#include "CoreData.h"
#include "Utils.h"
#include "CrudModule.h"
#include "SearchSortModule.h"
#include "RoomDivisionModule.h"
#include "FileModule.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


static void inMenu() {
    cout << "\n+======================================================+" << endl;
    cout << "|     CHUONG TRINH QUAN LY DANH SACH THI SINH          |" << endl;
    cout << "|     Bang bam (Hash Table) & Danh sach lien ket (DSLK)|" << endl;
    cout << "+======================================================+" << endl;
    cout << "|  --- THEM / XOA / SUA ---                            |" << endl;
    cout << "|   1. Them thi sinh moi (nhap tu ban phim)            |" << endl;
    cout << "|   2. Xoa thi sinh theo Ma Du Thi                     |" << endl;
    cout << "|   3. Sua thong tin thi sinh theo Ma Du Thi           |" << endl;
    cout << "|  --- TRA CUU ---                                     |" << endl;
    cout << "|   4. Tra cuu theo Ten                                |" << endl;
    cout << "|   5. Tra cuu theo Ma Du Thi                          |" << endl;
    cout << "|  --- HIEN THI & SAP XEP ---                          |" << endl;
    cout << "|   6. Hien thi cau truc Bang bam (Hash Table)         |" << endl;
    cout << "|   7. Hien thi danh sach theo Ten tang dan            |" << endl;
    cout << "|   8. Sap xep theo Ma Du Thi (Merge Sort DSLK)        |" << endl;
    cout << "|  --- CHIA PHONG THI ---                              |" << endl;
    cout << "|   9. Phan chia thi sinh vao N phong thi              |" << endl;
    cout << "|  --- DOC / GHI FILE ---                              |" << endl;
    cout << "|  10. Doc du lieu tu file TXT                         |" << endl;
    cout << "|  11. Ghi du lieu ra file TXT                         |" << endl;
    cout << "|                                                      |" << endl;
    cout << "|   0. Thoat chuong trinh                              |" << endl;
    cout << "+======================================================+" << endl;
}


int main() {
    HashTable ht;
    initHashTable(ht);

    ifstream checkFile("thisinh.txt");
    if (checkFile.is_open()) {
        checkFile.close();
        cout << "============================================" << endl;
        cout << "  Phat hien file 'thisinh.txt'. Tu dong nap du lieu..." << endl;
        cout << "============================================" << endl;
        docFileTXT(ht, "thisinh.txt");
    } else {
        cout << "============================================" << endl;
        cout << "  Khong tim thay file 'thisinh.txt'." << endl;
        cout << "  Chuong trinh khoi dong voi bang bam rong." << endl;
        cout << "============================================" << endl;
    }

    int luaChon;
    string input;

    do {
        inMenu();
        cout << "\n  Nhap lua chon cua ban (0-11): ";
        cin >> luaChon;

        if (cin.fail()) {
            cin.clear();             
            cin.ignore(1000, '\n');  
            cout << "\n  [Loi] Vui long nhap mot so tu 0 den 11!" << endl;
            continue;
        }

        cin.ignore(1000, '\n'); 

        switch (luaChon) {


            case 1: {
                nhapThiSinhTuBanPhim(ht);
                break;
            }

            case 2: {
                cout << "\n=== XOA THI SINH ===" << endl;
                cout << "  Nhap ma du thi can xoa: ";
                getline(cin, input);
                xoaThiSinhTheoMa(ht, input);
                break;
            }

            case 3: {
                cout << "\n=== SUA THONG TIN THI SINH ===" << endl;
                cout << "  Nhap ma du thi can sua: ";
                getline(cin, input);
                suaThiSinhTheoMa(ht, input);
                break;
            }


            case 4: {
                cout << "\n=== TRA CUU THEO TEN ===" << endl;
                cout << "  Nhap ten can tim: ";
                getline(cin, input);
                traCuuTheoTen(ht, input);
                break;
            }

            case 5: {
                cout << "\n=== TRA CUU THEO MA DU THI ===" << endl;
                cout << "  Nhap ma du thi can tim: ";
                getline(cin, input);
                traCuuTheoMa(ht, input);
                break;
            }

            case 6: {
                hienThiTheoBangBam(ht);
                break;
            }

            case 7: {
                hienThiTenTangDan(ht);
                break;
            }

            case 8: {
                sapXepTheoMa_MergeSort(ht);
                break;
            }


            case 9: {
                cout << "\n=== PHAN CHIA PHONG THI ===" << endl;
                cout << "  Tong so thi sinh hien tai: " << ht.soLuong << endl;

                if (ht.soLuong == 0) {
                    cout << "  [Loi] Bang bam rong, khong co thi sinh de chia phong!" << endl;
                    break;
                }

                int soPhong;
                cout << "  Nhap so phong thi (1 - " << ht.soLuong << "): ";
                cin >> soPhong;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "  [Loi] Vui long nhap mot so nguyen!" << endl;
                    break;
                }
                cin.ignore(1000, '\n');

                phanChiaPhongThi(ht, soPhong);
                break;
            }


            case 10: {
                cout << "\n=== DOC DU LIEU TU FILE ===" << endl;
                cout << "  Nhap ten file (VD: thisinh.txt): ";
                getline(cin, input);
                docFileTXT(ht, input);
                break;
            }

            case 11: {
                cout << "\n=== GHI DU LIEU RA FILE ===" << endl;
                cout << "  Nhap ten file xuat (VD: output.txt): ";
                getline(cin, input);
                ghiFileTXT(ht, input);
                break;
            }


            case 0: {
                cout << "\n============================================" << endl;
                cout << "  Dang giai phong bo nho..." << endl;
                clearHashTable(ht);
                cout << "  Da giai phong toan bo bo nho." << endl;
                cout << "  Cam on ban da su dung chuong trinh!" << endl;
                cout << "============================================" << endl;
                break;
            }

            default: {
                cout << "\n  [Loi] Lua chon khong hop le! Vui long chon 0-11." << endl;
                break;
            }
        }

    } while (luaChon != 0);

    return 0;
}
