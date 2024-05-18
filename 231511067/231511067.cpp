#include "231511067.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

// ini array untuk mengonversi indeks ke karakter
char mod[94] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '-', '+', '=', '{', '}', 
    '[', ']', '<', '>', '.', ',', ';', '"', '\'', '`', '\\', '/', '?', ':', '~', ' '
};

string hill_cipher_encrypt(string plainteks) {

    tAddr awalT = bacaTabelKonversi();
    kAddr awalK = buatLinkedListKey(2, 1, 3, 4);
    pAddr awalP = nullptr;
    bool genap;
    plainteks = chekNumChar(plainteks, genap);
    // cout << "pLAINTEKS setelah dicek genap/ ganjil = " << plainteks << endl;
    awalP = konversiPlainteksKeAngka(plainteks, awalT);
    // cout << "pLAINTEKS setelah dijadikan angka dan dijadikan linked list = ";
    // tampilkanLinkedList(awalP);
    awalP = perkalianMatriksLL(awalP, awalK);
    // cout << "aNGKA setelah dikalikan matriks linked list = " << endl;
    // tampilkanLinkedList(awalP);
    plainteks = konversiAngkaKePlainteks(awalP, awalT);
    plainteks = addAngka(plainteks, genap);
    // cout << "pLAINTEKS setelah dikonversi didalam function = " << plainteks << endl;

    if(hapusLinkedList(awalP) && hapusLinkedListKey(awalK) && hapusLinkedListTabel(awalT)) {
        return plainteks;
    }
}

string enkripsi(const string& plaintext) {
    char mod[94] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '-', '+', '=', '{', '}', 
        '[', ']', '<', '>', '.', ',', ';', '"', '\'', '`', '\\', '/', '?', ':', '~', ' '
    };
    
    int key[2][2] = {
        {2, 1},
        {3, 4}
    };

    // Menghitung panjang plaintext
    int len = plaintext.length();

    // Jika panjang plaintext ganjil, tambahkan satu karakter 'X'
    if (len % 2 != 0) {
        plaintext += 'X';
        len++;
    }

    string encrypted_text = "";

    for (int i = 0; i < len; i += 2) {
        int x1 = -1, x2 = -1;
        for (int j = 0; j < 94; ++j) {
            if (mod[j] == plaintext[i]) {
                x1 = j;
            }
            if (mod[j] == plaintext[i + 1]) {
                x2 = j;
            }
        }

        if (x1 == -1 || x2 == -1) {
            cerr << "Invalid character in plaintext." << endl;
            return "";
        }

        int y1 = (key[0][0] * x1 + key[0][1] * x2) % 94;
        int y2 = (key[1][0] * x1 + key[1][1] * x2) % 94;

        encrypted_text += mod[y1];
        encrypted_text += mod[y2];
    }
    return encrypted_text;
}


void tampilkanDataPasienByNIK(string& nik) {

    nik = hill_cipher_encrypt(nik);

    ifstream inFile("file/akun_pengguna.txt");
    if (inFile.is_open()) {
        string line;
        bool found = false;
        while (getline(inFile, line)) {
            stringstream ss(line);
            UserData userData;

            getline(ss, userData.nik, '|');
            getline(ss, userData.password, '|');
            getline(ss, userData.namalengkap, '|');
            getline(ss, userData.tanggallahir, '|');
            getline(ss, userData.alamat, '|');
            getline(ss, userData.clueKeamanan);

            if (userData.nik == nik) {

                userData.nik = hill_cipher_decrypt(userData.nik);
                userData.password = hill_cipher_decrypt(userData.password);
                userData.namalengkap = hill_cipher_decrypt(userData.namalengkap);
                userData.tanggallahir = hill_cipher_decrypt(userData.tanggallahir);
                userData.alamat = hill_cipher_decrypt(userData.alamat);
                userData.clueKeamanan = hill_cipher_decrypt(userData.clueKeamanan);

                cout << "+---------------------------------------------+\n";
                cout << "|            Informasi Pengguna              |\n";
                cout << "+---------------------------------------------+\n";
                cout << "| NIK:           " << userData.nik << "\n";
                cout << "|---------------------------------------------|\n";
                cout << "| Password:      " << userData.password << "\n";
                cout << "|---------------------------------------------|\n";
                cout << "| Nama Lengkap:  " << userData.namalengkap << "\n";
                cout << "|---------------------------------------------|\n";
                cout << "| Tanggal Lahir: " << userData.tanggallahir << "\n";
                cout << "|---------------------------------------------|\n";
                cout << "| Alamat:        " << userData.alamat << "\n";
                cout << "|---------------------------------------------|\n";
                cout << "| Clue Keamanan: " << userData.clueKeamanan << "\n";
                cout << "+---------------------------------------------+\n";
                found = true;

                break; // Keluar dari loop setelah menemukan data yang dicari
            }
        }
        inFile.close();

        nik = hill_cipher_decrypt(nik);
        if (!found) {
            cout << "Data pasien dengan NIK " << nik << " tidak ditemukan." << endl;
        }
    } else {
        cout << "Gagal mengakses penyimpanan data.\n";
    }
}

// Fungsi untuk menghapus semua node dalam linked list
bool hapusLinkedListTabel(tAddr& awalT) {
    while (awalT != nullptr) {
        tAddr temp = awalT;
        awalT = awalT->next;
        delete temp;
    }
    return awalT == nullptr;
}
/// Fungsi untuk menghapus semua node dalam linked list
bool hapusLinkedList(pAddr& awalP) {
    while (awalP != nullptr) {
        pAddr temp = awalP;
        awalP = awalP->next;
        delete temp;
    }
    return awalP == nullptr;
}

bool hapusLinkedListKey(kAddr& awalK) {
    while (awalK != nullptr) {
        kAddr tempRow = awalK;
        while (tempRow != nullptr) {
            kAddr temp = tempRow;
            tempRow = tempRow->nextcol;
            delete temp;
        }
        awalK = awalK->nextrow;
    }
    return awalK == nullptr;
}

// Fungsi untuk mencari karakter pada tabel konversi berdasarkan indeks
char cariKarakter(const tAddr awal, int indeks) {
    tAddr current = awal;
    int currentIdx = 0; // Indeks dimulai dari 1

    while (current != nullptr && currentIdx != indeks) {
        current = current->next;
        currentIdx++;
    }

    if (currentIdx == indeks && current != nullptr) {
        return current->info;
    } else {
        return '\0'; // Indeks di luar jangkauan tabel konversi
    }
}
// Fungsi untuk mengkonversi angka pada setiap info node menjadi karakter
string konversiAngkaKePlainteks(const pAddr awal, const tAddr tabelKonversi) {
    pAddr current = awal;
    string hasilkonversi = "";
    while (current != nullptr) {
        int indeks = current->info;
        char karakter = cariKarakter(tabelKonversi, indeks);
        if (karakter != '\0') {
            hasilkonversi += karakter;
        } else {
            cout << "Indeks " << indeks << " tidak ada di dalam tabel konversi." << endl;
            cout << "'" << current->info << "'" << endl;
        }
        current = current->next;
    }
    return hasilkonversi;
}

