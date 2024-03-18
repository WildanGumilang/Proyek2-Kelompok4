#include "231511067.h"
#include "../231511082/231511082.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

// Deklarasi struktur UserData
struct UserData {
    string nik;
    string password;
    string namalengkap;
    string tanggallahir;
    string alamat;
    string clueKeamanan;
};

// ini array untuk mengonversi indeks ke karakter
char mod[94] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '-', '+', '=', '{', '}', 
    '[', ']', '<', '>', '.', ',', ';', '"', '\'', '`', '\\', '/', '?', ':', '~', ' '
};


string hill_cipher_encrypt(const string& plaintext) {
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
    int len = plaintext.length();

    if (len % 2 != 0) {
        len++;
    }

    string padded_plaintext = plaintext;
    if (len > plaintext.length()) {
        padded_plaintext += 'X';
    }

    string encrypted_text = "";

    for (int i = 0; i < len; i += 2) {
        int x1 = -1, x2 = -1;
        for (int j = 0; j < 94; ++j) {
            if (mod[j] == padded_plaintext[i]) {
                x1 = j;
            }
            if (mod[j] == padded_plaintext[i + 1]) {
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