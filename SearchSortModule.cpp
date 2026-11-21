#include "SearchSortModule.h"
#include "CoreData.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
using namespace std;

void traCuuTheoTen(const HashTable &ht, string tenCanTim) {
    tenCanTim = chuanHoaChuoi(tenCanTim);
    if (tenCanTim.empty()) {
        cout << "  [Loi] Ten tim kiem khong duoc de trong!" << endl;
        return;
    }
    string tenSearch = tachTen(tenCanTim);
    string tenSearchLower = toLowerStr(tenSearch);

    int index = hashFunction(tenCanTim);

    cout << "\n=== KET QUA TRA CUU THEO TEN: \"" << tenSearch << "\" ===" << endl;
    cout << "  (Tim trong Bucket " << index << " - '"
         << (char)('A' + index) << "')" << endl;

    Node* current = ht.buckets[index];
    int count = 0;
    bool headerPrinted = false;

    while (current != nullptr) {
        string tenCurrent = toLowerStr(tachTen(current->data.hoTen));

        if (tenCurrent == tenSearchLower) {
            if (!headerPrinted) {
                inTieuDeBang();
                headerPrinted = true;
            }
            count++;
            inDongThiSinh(current->data, count);
        }
        current = current->next;
    }

    if (count > 0) {
        inDuongKe();
        cout << "  >> Tim thay " << count << " thi sinh co ten \"" << tenSearch << "\"." << endl;
    } else {
        // Buoc 5: Khong tim thay
        cout << "  >> Khong tim thay thi sinh nao co ten \"" << tenSearch << "\"." << endl;
    }
}


void traCuuTheoMa(const HashTable &ht, string maCanTim) {
    string maUpper = toUpperStr(maCanTim);

    if (maUpper.empty()) {
        cout << "  [Loi] Ma du thi tim kiem khong duoc de trong!" << endl;
        return;
    }

    cout << "\n=== KET QUA TRA CUU THEO MA: \"" << maUpper << "\" ===" << endl;

    for (int i = 0; i < 26; i++) {
        Node* current = ht.buckets[i];
        while (current != nullptr) {
            if (toUpperStr(current->data.maDuThi) == maUpper) {
         
                cout << "  Tim thay tai Bucket " << i << " ('"
                     << (char)('A' + i) << "'):" << endl;
                inTieuDeBang();
                inDongThiSinh(current->data, 1);
                inDuongKe();
                return;
            }
            current = current->next;
        }
    }

    cout << "  >> Khong tim thay thi sinh co ma \"" << maUpper << "\"." << endl;
}


void hienThiTheoBangBam(const HashTable &ht) {
    cout << "\n========================================" << endl;
    cout << "  CAU TRUC BANG BAM (HASH TABLE)" << endl;
    cout << "  Tong so thi sinh: " << ht.soLuong << endl;
    cout << "  So bucket: 26 (A-Z)" << endl;
    cout << "========================================" << endl;

    if (ht.soLuong == 0) {
        cout << "  (Bang bam rong, chua co thi sinh nao)" << endl;
        return;
    }

    int bucketCoData = 0;

    for (int i = 0; i < 26; i++) {
        if (ht.buckets[i] == nullptr) {
            continue; 
        }

        bucketCoData++;

        int countInBucket = 0;
        Node* temp = ht.buckets[i];
        while (temp != nullptr) {
            countInBucket++;
            temp = temp->next;
        }

        cout << "\n  Bucket " << setw(2) << i << " ('"
             << (char)('A' + i) << "'): " << countInBucket
             << " phan tu" << endl;
        cout << "  ";

        Node* current = ht.buckets[i];
        while (current != nullptr) {
            cout << "[" << current->data.maDuThi << " - "
                 << current->data.hoTen << "]";
            if (current->next != nullptr) {
                cout << " -> ";
            }
            current = current->next;
        }
        cout << " -> NULL" << endl;
    }

    cout << "\n----------------------------------------" << endl;
    cout << "  Tong ket: " << bucketCoData << "/26 bucket co du lieu, "
         << (26 - bucketCoData) << " bucket rong." << endl;
    cout << "========================================" << endl;
}

void hienThiTenTangDan(const HashTable &ht) {
    cout << "\n=== DANH SACH THI SINH THEO TEN TANG DAN ===" << endl;
    cout << "  (Duyet tuan tu Bucket A -> Z, tan dung DSLK da sap xep)" << endl;

    if (ht.soLuong == 0) {
        cout << "  (Bang bam rong, chua co thi sinh nao)" << endl;
        return;
    }

    inTieuDeBang();

    int stt = 0;
    for (int i = 0; i < 26; i++) {
        Node* current = ht.buckets[i];
        while (current != nullptr) {
            stt++;
            inDongThiSinh(current->data, stt);
            current = current->next;
        }
    }

    inDuongKe();
    cout << "  >> Tong cong: " << stt << " thi sinh." << endl;
}

static void splitList(Node* source, Node** firstHalf, Node** secondHalf) {
    if (source == nullptr || source->next == nullptr) {
        // Danh sach co 0 hoac 1 phan tu -> khong can chia
        *firstHalf = source;
        *secondHalf = nullptr;
        return;
    }

    Node* slow = source;
    Node* fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *firstHalf = source;
    *secondHalf = slow->next;
    slow->next = nullptr; 
}

static Node* mergeSortedLists(Node* listA, Node* listB) {
    Node dummy;
    dummy.next = nullptr;
    Node* tail = &dummy;

    while (listA != nullptr && listB != nullptr) {
        if (toUpperStr(listA->data.maDuThi) <= toUpperStr(listB->data.maDuThi)) {
            tail->next = listA;
            listA = listA->next;
        } else {
            tail->next = listB;
            listB = listB->next;
        }
        tail = tail->next;
    }

    if (listA != nullptr) {
        tail->next = listA;
    } else {
        tail->next = listB;
    }

    return dummy.next;
}


static Node* mergeSort(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    Node* firstHalf = nullptr;
    Node* secondHalf = nullptr;
    splitList(head, &firstHalf, &secondHalf);

    firstHalf = mergeSort(firstHalf);
    secondHalf = mergeSort(secondHalf);

    return mergeSortedLists(firstHalf, secondHalf);
}

void sapXepTheoMa_MergeSort(const HashTable &ht) {
    cout << "\n=== SAP XEP THEO MA DU THI (MERGE SORT TREN DSLK) ===" << endl;
    if (ht.soLuong == 0) {
        cout << "  (Bang bam rong, khong co du lieu de sap xep)" << endl;
        return;
    }


    Node* tempList = nullptr; 
    Node* tempTail = nullptr; 

    for (int i = 0; i < 26; i++) {
        Node* current = ht.buckets[i];
        while (current != nullptr) {
     
            Node* copyNode = createNode(current->data);

    
            if (tempList == nullptr) {
                tempList = copyNode;
                tempTail = copyNode;
            } else {
                tempTail->next = copyNode;
                tempTail = copyNode;
            }

            current = current->next;
        }
    }

  
    tempList = mergeSort(tempList);


    cout << "  (Da sap xep " << ht.soLuong << " thi sinh theo Ma Du Thi tang dan)" << endl;
    inTieuDeBang();

    int stt = 0;
    Node* printer = tempList;
    while (printer != nullptr) {
        stt++;
        inDongThiSinh(printer->data, stt);
        printer = printer->next;
    }
    inDuongKe();


    Node* toDelete = tempList;
    while (toDelete != nullptr) {
        Node* temp = toDelete;
        toDelete = toDelete->next;
        delete temp;
    }

    cout << "  >> Da giai phong bo nho DSLK tam." << endl;
}
