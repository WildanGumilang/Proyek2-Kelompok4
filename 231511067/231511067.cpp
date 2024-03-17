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


void hill_cipher_encrypt(const char* plaintext, const int key[2][2], char* encrypted_text) {
    int len = strlen(plaintext);

    if (len % 2 != 0) {
        len++;
    }

    char padded_plaintext[len + 1];
    strcpy(padded_plaintext, plaintext);
    if (len > strlen(plaintext)) {
        padded_plaintext[len - 1] = 'X';
        padded_plaintext[len] = '\0';
    }

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
            return;
        }

        int y1 = (key[0][0] * x1 + key[0][1] * x2) % 94;
        int y2 = (key[1][0] * x1 + key[1][1] * x2) % 94;

        encrypted_text[i] = mod[y1];
        encrypted_text[i + 1] = mod[y2];
    }
    encrypted_text[len] = '\0';
}

void tampilkanDataPasienByNIK(string& nik) {
    int key[2][2] = {
        {31, 59},
        {17, 92}
    };
    char decrypted_text[100];
    char encrypted_text[100];

    hill_cipher_encrypt(nik.c_str(), key, encrypted_text);
    nik = encrypted_text;
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

                hill_cipher_decrypt(userData.nik.c_str(), key, decrypted_text);
                userData.nik = decrypted_text;
                hill_cipher_decrypt(userData.password.c_str(), key, decrypted_text);
                userData.password = decrypted_text;
                hill_cipher_decrypt(userData.namalengkap.c_str(), key, decrypted_text);
                userData.namalengkap = decrypted_text;
                hill_cipher_decrypt(userData.tanggallahir.c_str(), key, decrypted_text);
                userData.tanggallahir = decrypted_text;
                hill_cipher_decrypt(userData.alamat.c_str(), key, decrypted_text);
                userData.alamat = decrypted_text;
                hill_cipher_decrypt(userData.clueKeamanan.c_str(), key, decrypted_text);
                userData.clueKeamanan = decrypted_text;

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


                hill_cipher_encrypt(userData.nik.c_str(), key, encrypted_text);
                userData.nik = encrypted_text;
                hill_cipher_encrypt(userData.password.c_str(), key, encrypted_text);
                userData.password = encrypted_text;
                hill_cipher_encrypt(userData.namalengkap.c_str(), key, encrypted_text);
                userData.namalengkap = encrypted_text;
                hill_cipher_encrypt(userData.tanggallahir.c_str(), key, encrypted_text);
                userData.tanggallahir = encrypted_text;
                hill_cipher_encrypt(userData.alamat.c_str(), key, encrypted_text);
                userData.alamat = encrypted_text;
                hill_cipher_encrypt(userData.clueKeamanan.c_str(), key, encrypted_text);
                userData.clueKeamanan = encrypted_text;
                break; // Keluar dari loop setelah menemukan data yang dicari
            }
        }
        inFile.close();

        hill_cipher_decrypt(nik.c_str(), key, decrypted_text);
        nik = decrypted_text;
        
        if (!found) {
            cout << "Data pasien dengan NIK " << nik << " tidak ditemukan." << endl;
        }
    } else {
        cout << "Gagal mengakses penyimpanan data.\n";
    }
}