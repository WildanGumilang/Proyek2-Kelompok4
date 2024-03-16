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

// Deklarasi prototipe fungsi
void tampilkanDataPasienByNIK(const string& nik);

// ini array untuk mengonversi indeks ke karakter
char mod[94] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '-', '+', '=', '{', '}', 
    '[', ']', '<', '>', '.', ',', ';', '"', '\'', '`', '\\', '/', '?', ':', '~', ' '
};

int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // Modular inverse does not exist
}

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

int main() {
    int static_key[2][2] = { // ini adalah matriks statis 2x2
        {31, 59},
        {17, 92} // ini adalah kunci matriks 
    };

    const int max_text_length = 1000; // ini untuk menentukan maksimal panjang string
    char plaintext[max_text_length]; // ini adalah array untuk menyimpan teks asli

    cout << "Enter the message to encrypt: "; // ini untuk menginput text untuk di encryption
    cin.getline(plaintext, max_text_length); // ini untuk membaca text yang di input

    char encrypted_text[max_text_length]; // ini adalah array untuk menyimpan teks terenkripsi
    hill_cipher_encrypt(plaintext, static_key, encrypted_text); // untuk melakukan enkripsi menggunakan kunci statis

    cout << "Encrypted text: " << encrypted_text << endl;

    return 0;
}

void tampilkanDataPasienByNIK(const string& nik) {
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
                cout << "NIK: " << userData.nik << endl;
                cout << "Password: " << userData.password << endl;
                cout << "Nama Lengkap: " << userData.namalengkap << endl;
                cout << "Tanggal Lahir: " << userData.tanggallahir << endl;
                cout << "Alamat: " << userData.alamat << endl;
                cout << "Clue Keamanan: " << userData.clueKeamanan << endl;
                found = true;
                break; // Keluar dari loop setelah menemukan data yang dicari
            }
        }
        inFile.close();
        
        if (!found) {
            cout << "Data pasien dengan NIK " << nik << " tidak ditemukan." << endl;
        }
    } else {
        cout << "Gagal mengakses penyimpanan data.\n";
    }
}