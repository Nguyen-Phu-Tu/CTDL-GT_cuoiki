#include "RoomDivisionModule.h"
#include "CoreData.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
using namespace std;

void phanChiaPhongThi(const HashTable &ht, int soPhong) {

    if (ht.soLuong == 0) {
        cout << "  [Loi] Bang bam rong, khong co thi sinh de chia phong!" << endl;
        return;
    }
    if (soPhong <= 0 || soPhong > ht.soLuong) {
        cout << "  [Loi] So phong khong hop le! Yeu cau: 0 < soPhong <= "
             << ht.soLuong << endl;
        return;
    }


    Node** phongThi = new Node*[soPhong];
    for (int j = 0; j < soPhong; j++) {
        phongThi[j] = nullptr;
    }

    int* siSoPhong = new int[soPhong];
    for (int j = 0; j < soPhong; j++) {
        siSoPhong[j] = 0;
    }


    int currentRoom = 0; 

    for (int i = 0; i < 26; i++) {
        Node* current = ht.buckets[i];
        while (current != nullptr) {
            Node* copyNode = createNode(current->data);
            copyNode->next = phongThi[currentRoom];
            phongThi[currentRoom] = copyNode;
            siSoPhong[currentRoom]++;

            currentRoom = (currentRoom + 1) % soPhong;

            current = current->next;
        }
    }



    cout << "\n============================================================" << endl;
    cout << "  PHAN CHIA " << ht.soLuong << " THI SINH VAO " << soPhong
         << " PHONG THI" << endl;
    cout << "  Thuat toan: Round-Robin theo tung Bucket (A -> Z)" << endl;
    cout << "============================================================" << endl;

    for (int j = 0; j < soPhong; j++) {
        cout << "\n  --- PHONG THI " << (j + 1) << " (Si so: "
             << siSoPhong[j] << " thi sinh) ---" << endl;

        if (phongThi[j] == nullptr) {
            cout << "    (Phong trong)" << endl;
            continue;
        }

        inTieuDeBang();
        int stt = 0;
        Node* cur = phongThi[j];
        while (cur != nullptr) {
            stt++;
            inDongThiSinh(cur->data, stt);
            cur = cur->next;
        }
        inDuongKe();
    }



    cout << "\n============================================================" << endl;
    cout << "  BANG THONG KE DANH GIA THUAT TOAN CHIA PHONG" << endl;
    cout << "============================================================" << endl;


    cout << "+--------+--------+-----------------------------------"
         << "+----------+------------+" << endl;
    cout << "| Phong  | Si so  | Phan bo chu cai dau (Ten)         "
         << "| Max trung| Xac suat P |" << endl;
    cout << "+--------+--------+-----------------------------------"
         << "+----------+------------+" << endl;

    for (int j = 0; j < soPhong; j++) {
        int M = siSoPhong[j]; 

  
        int charCount[26];
        for (int c = 0; c < 26; c++) {
            charCount[c] = 0;
        }

        Node* cur = phongThi[j];
        while (cur != nullptr) {
            string ten = tachTen(cur->data.hoTen);
            if (!ten.empty()) {
                char ch = toupper((unsigned char)ten[0]);
                if (ch >= 'A' && ch <= 'Z') {
                    charCount[ch - 'A']++;
                }
            }
            cur = cur->next;
        }


        int maxDup = 0;
        string phanBo = "";
        for (int c = 0; c < 26; c++) {
            if (charCount[c] > 0) {
                if (!phanBo.empty()) {
                    phanBo += ", ";
                }
                phanBo += (char)('A' + c);
                phanBo += ":";
                int val = charCount[c];
                string numStr = "";
                if (val == 0) {
                    numStr = "0";
                } else {
                    while (val > 0) {
                        numStr = (char)('0' + val % 10) + numStr;
                        val /= 10;
                    }
                }
                phanBo += numStr;

                if (charCount[c] > maxDup) {
                    maxDup = charCount[c];
                }
            }
        }

        double P = 0.0;
        if (M >= 2) {
            int sumC2 = 0;
            for (int c = 0; c < 26; c++) {
                int k = charCount[c];
                sumC2 += k * (k - 1); 
            }
            P = (double)sumC2 / ((double)M * (double)(M - 1));
        }

        cout << "| " << left << setw(7) << (j + 1)
             << "| " << left << setw(7) << M
             << "| " << left << setw(34) << phanBo
             << "| " << left << setw(9) << maxDup
             << "| " << right << setw(8) << fixed << setprecision(2)
             << (P * 100.0) << " %" << " |" << endl;
    }

    cout << "+--------+--------+-----------------------------------"
         << "+----------+------------+" << endl;

    cout << "\n  Giai thich cong thuc:" << endl;
    cout << "  P = sum(C(k_i, 2)) / C(M, 2)" << endl;
    cout << "    = sum(k_i * (k_i - 1)) / (M * (M - 1))" << endl;
    cout << "  Voi k_i = so nguoi co Ten bat dau bang chu cai i," << endl;
    cout << "       M  = si so phong." << endl;
    cout << "  P cang nho => cac thi sinh trong phong cang it trung chu cai dau" << endl;
    cout << "             => thuat toan chia phong cang tot." << endl;


    for (int j = 0; j < soPhong; j++) {
        Node* cur = phongThi[j];
        while (cur != nullptr) {
            Node* temp = cur;
            cur = cur->next;
            delete temp; 
        }
        phongThi[j] = nullptr;
    }

    delete[] phongThi; 
    delete[] siSoPhong; 

    cout << "\n  >> Da giai phong toan bo bo nho dong cua phongThi." << endl;
}
