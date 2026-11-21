#include "CrudModule.h"
#include "CoreData.h"
#include "Utils.h"
#include <iostream>
#include <string>
using namespace std;


bool kiemTraTrungMa(const HashTable &ht, string ma) {
    string maUpper = toUpperStr(ma);

    for (int i = 0; i < 26; i++) {
        Node* current = ht.buckets[i];
        while (current != nullptr) {
            if (toUpperStr(current->data.maDuThi) == maUpper) {
                return true; // Da ton tai
            }
            current = current->next;
        }
    }

    return false; // Khong trung
}

int soSanhThiSinhTheoTen(const ThiSinh &a, const ThiSinh &b) {
    // Cap 1: So sanh Ten (tu cuoi cung), khong phan biet hoa thuong
    string tenA = toLowerStr(tachTen(a.hoTen));
    string tenB = toLowerStr(tachTen(b.hoTen));

    if (tenA < tenB) return -1;
    if (tenA > tenB) return 1;

    // Cap 2: Ten trung -> So sanh Ho Dem
    string hoDemA = toLowerStr(tachHoDem(a.hoTen));
    string hoDemB = toLowerStr(tachHoDem(b.hoTen));

    if (hoDemA < hoDemB) return -1;
    if (hoDemA > hoDemB) return 1;

    // Cap 3: Ho Dem cung trung -> So sanh Ma Du Thi
    if (a.maDuThi < b.maDuThi) return -1;
    if (a.maDuThi > b.maDuThi) return 1;

    return 0; // Hoan toan giong nhau
}

void themThiSinh(HashTable &ht, ThiSinh ts) {
    int index = hashFunction(ts.hoTen);
    Node* newNode = createNode(ts);

    if (ht.buckets[index] == nullptr ||
        soSanhThiSinhTheoTen(ts, ht.buckets[index]->data) <= 0) {

        newNode->next = ht.buckets[index]; 
        ht.buckets[index] = newNode;       

    } else {
        Node* current = ht.buckets[index];

        while (current->next != nullptr &&
               soSanhThiSinhTheoTen(ts, current->next->data) > 0) {
            current = current->next;
        }


        newNode->next = current->next;
        current->next = newNode;
    }

    ht.soLuong++; 
}


void nhapThiSinhTuBanPhim(HashTable &ht) {
    ThiSinh ts;
    string input;

    cout << "\n=== NHAP THONG TIN THI SINH MOI ===" << endl;

    // --- Buoc 1: Nhap Ma Du Thi ---
    while (true) {
        cout << "  Nhap ma du thi: ";
        getline(cin, input);

        int s = 0, e = (int)input.length() - 1;
        while (s <= e && input[s] == ' ') s++;
        while (e >= s && input[e] == ' ') e--;
        input = (s <= e) ? input.substr(s, e - s + 1) : "";

        input = toUpperStr(input);

        if (input.empty()) {
            cout << "  [Loi] Ma du thi khong duoc de trong! Nhap lai." << endl;
            continue;
        }
        if (kiemTraTrungMa(ht, input)) {
            cout << "  [Loi] Ma du thi '" << input << "' da ton tai! Nhap ma khac." << endl;
            continue;
        }
        ts.maDuThi = input;
        break;
    }


    while (true) {
        cout << "  Nhap ho ten: ";
        getline(cin, input);
        input = chuanHoaChuoi(input);
        if (input.empty()) {
            cout << "  [Loi] Ho ten khong duoc de trong! Nhap lai." << endl;
            continue;
        }
        ts.hoTen = input;
        break;
    }


    while (true) {
        cout << "  Nhap gioi tinh (Nam/Nu): ";
        getline(cin, input);
        if (kiemTraGioiTinh(input)) {
            ts.gioiTinh = input;
            break;
        }
        cout << "  [Loi] Gioi tinh khong hop le! Chi chap nhan 'Nam' hoac 'Nu'." << endl;
    }

    while (true) {
        cout << "  Nhap ngay sinh (DD/MM/YYYY): ";
        getline(cin, input);
        if (kiemTraNgaySinh(input)) {
            ts.ngaySinh = input;
            break;
        }
        cout << "  [Loi] Ngay sinh khong hop le! Nhap dung dinh dang DD/MM/YYYY." << endl;
    }

    while (true) {
        cout << "  Nhap que quan: ";
        getline(cin, input);
        input = chuanHoaChuoi(input);
        if (input.empty()) {
            cout << "  [Loi] Que quan khong duoc de trong! Nhap lai." << endl;
            continue;
        }
        ts.queQuan = input;
        break;
    }

    themThiSinh(ht, ts);
    cout << "\n  >> Them thanh cong thi sinh: " << ts.hoTen
         << " (Ma: " << ts.maDuThi << ")" << endl;
}

bool xoaThiSinhTheoMa(HashTable &ht, string ma) {
    string maUpper = toUpperStr(ma);

  
    for (int i = 0; i < 26; i++) {
        Node* current = ht.buckets[i];
        Node* prev = nullptr;

     
        while (current != nullptr) {
            if (toUpperStr(current->data.maDuThi) == maUpper) {
            
           
                string tenXoa = current->data.hoTen;
                string maXoa = current->data.maDuThi;

                if (prev == nullptr) {
         
                    ht.buckets[i] = current->next;
                } else {
           
                    prev->next = current->next;
                }
                delete current;   
                ht.soLuong--;    

                cout << "  >> Da xoa thi sinh: " << tenXoa
                     << " (Ma: " << maXoa << ")" << endl;
                return true;
            }

            prev = current;
            current = current->next;
        }
    }
    cout << "  >> Khong tim thay thi sinh co ma: " << ma << endl;
    return false;
}


void suaThiSinhTheoMa(HashTable &ht, string ma) {
    string maUpper = toUpperStr(ma);

  
    Node* found = nullptr;    
    Node* prev = nullptr;    
    int foundBucket = -1;     

    for (int i = 0; i < 26; i++) {
        Node* current = ht.buckets[i];
        Node* p = nullptr;
        while (current != nullptr) {
            if (toUpperStr(current->data.maDuThi) == maUpper) {
                found = current;
                prev = p;
                foundBucket = i;
                break;
            }
            p = current;
            current = current->next;
        }
        if (found != nullptr) break;
    }

    if (found == nullptr) {
        cout << "  >> Khong tim thay thi sinh co ma: " << ma << endl;
        return;
    }


    cout << "\n--- Thong tin hien tai cua thi sinh ---" << endl;
    inTieuDeBang();
    inDongThiSinh(found->data, 1);
    inDuongKe();


    ThiSinh tsNew = found->data;
    bool hoTenChanged = false; 
    int choice;
    string input;

    do {
        cout << "\n  Chon truong can sua:" << endl;
        cout << "    1. Ho Ten" << endl;
        cout << "    2. Gioi Tinh" << endl;
        cout << "    3. Ngay Sinh" << endl;
        cout << "    4. Que Quan" << endl;
        cout << "    0. Hoan tat chinh sua" << endl;
        cout << "  Lua chon cua ban: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                while (true) {
                    cout << "  Nhap Ho Ten moi: ";
                    getline(cin, input);
                    input = chuanHoaChuoi(input);
                    if (!input.empty()) {
                        tsNew.hoTen = input;
                        hoTenChanged = true;
                        cout << "  >> Da ghi nhan Ho Ten moi: " << input << endl;
                        break;
                    }
                    cout << "  [Loi] Ho ten khong duoc de trong! Nhap lai." << endl;
                }
                break;
            }
            case 2: {
                while (true) {
                    cout << "  Nhap Gioi Tinh moi (Nam/Nu): ";
                    getline(cin, input);
                    if (kiemTraGioiTinh(input)) {
                        tsNew.gioiTinh = input;
                        cout << "  >> Da ghi nhan Gioi Tinh moi: " << input << endl;
                        break;
                    }
                    cout << "  [Loi] Chi chap nhan 'Nam' hoac 'Nu'! Nhap lai." << endl;
                }
                break;
            }
            case 3: {
                while (true) {
                    cout << "  Nhap Ngay Sinh moi (DD/MM/YYYY): ";
                    getline(cin, input);
                    if (kiemTraNgaySinh(input)) {
                        tsNew.ngaySinh = input;
                        cout << "  >> Da ghi nhan Ngay Sinh moi: " << input << endl;
                        break;
                    }
                    cout << "  [Loi] Ngay sinh khong hop le! Nhap dung DD/MM/YYYY." << endl;
                }
                break;
            }
            case 4: {
                while (true) {
                    cout << "  Nhap Que Quan moi: ";
                    getline(cin, input);
                    input = chuanHoaChuoi(input);
                    if (!input.empty()) {
                        tsNew.queQuan = input;
                        cout << "  >> Da ghi nhan Que Quan moi: " << input << endl;
                        break;
                    }
                    cout << "  [Loi] Que quan khong duoc de trong! Nhap lai." << endl;
                }
                break;
            }
            case 0:
                break;
            default:
                cout << "  [Loi] Lua chon khong hop le! Vui long chon 0-4." << endl;
        }
    } while (choice != 0);


    if (hoTenChanged) {

        if (prev == nullptr) {
     
            ht.buckets[foundBucket] = found->next;
        } else {

            prev->next = found->next;
        }

        delete found;
        ht.soLuong--;

        themThiSinh(ht, tsNew);

        cout << "\n  >> Da cap nhat va sap xep lai thi sinh trong bang bam." << endl;

    } else {

        found->data = tsNew;

        cout << "\n  >> Da cap nhat thong tin thi sinh." << endl;
    }

    cout << "\n--- Thong tin sau khi sua ---" << endl;
    inTieuDeBang();
    inDongThiSinh(tsNew, 1);
    inDuongKe();
}
