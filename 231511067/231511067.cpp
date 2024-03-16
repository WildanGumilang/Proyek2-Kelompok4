#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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

// ini adalah ungsi untuk melakukan enkripsi Hill Cipher
void hill_cipher_encrypt(const char* text, const int key[2][2], char* encrypted_text) {
    int n = 2; // ini untuk menentukan ukuran matriks kunci
    size_t len = 0; // ini untuk menghitung panjang teks yang akan di enkripsi
    while (text[len] != '\0') { // ini adalah looping while jika character sama dengan null atau (\0) maka looping keluar
        len = len +1 ;
    }

    for (size_t i = 0; i < len; i += n) { // ini adalah looping for untuk menentukan panjang matriks kunci dengan dengan len sebagai batas
        const char* block = text + i; // variabel block ini untuk menyimpan blok text sepanjang n

        int result[2] = {0}; // ini untuk menyimpan hasil enkripsi

        for (int j = 0; j < n; j = j + 1) { // ini adalah looping for baris matriks kunci
            for (int k = 0; k < n; ++k) { // ini adalah looping for hasil enkripsi yang dihitung dengan mengalikan elemen matriks kunci (key[j][k]) dengan elemen blok teks (block[k])
                result[j] += key[j][k] * static_cast<int>(block[k]); 
            }
            result[j] %= 94; // ini adalah hasil enkripsi
        }

        for (int j = 0; j < n; j = j + 1) { // ini adalah looping for baris matriks kunci
            encrypted_text[i + j] = mod[result[j]]; // karakter hasil enkripsi diambil dari array mod lalu disimpan di dalam encrypted_text
        }
    }
    encrypted_text[len] = '\0'; // ini untuk untuk menandakan akhir dari string hasil enkripsi
}

void saveToFile(const char* filename, const char* original, const char* encrypted) { // ini adalah fungsi yang berisi tiga parameter yaitu, filename, original, dan terenkripsi
    ofstream file(filename); // ini untuk menulis ke file dengan nama yang diberikan (filename)
    if (file.is_open()) { // membuka file
        file << original << "|" << encrypted << '\n'; // ini untuk menuliskan plaintext dan hasil terenkripsi ke dalam file 
        cout << "Data has been saved to " << filename << endl; // untuk menampilkan pada layar bahwa data tersimpan
        file.close(); // menutup file
    } else {
        cerr << "Error: Unable to open the file." << endl; // untuk menampilkan pada layar bahwa file tidak dapat terbuka
    }
}

int main() {
    int static_key[2][2] = { // ini adalah matriks statis 2x2
        {2, 1}, {3, 4} // ini adalah kunci matriks 
    };

    const int max_text_length = 1000; // ini untuk menentukan maksimal panjang string
    char plaintext[max_text_length]; // ini adalah array untuk menyimpan teks asli

    cout << "Enter the message to encrypt: "; // ini untuk menginput text untuk di encryption
    cin.getline(plaintext, max_text_length); // ini untuk membaca text yang di input

    char encrypted_text[max_text_length]; // ini adalah array untuk menyimpan teks terenkripsi
    hill_cipher_encrypt(plaintext, static_key, encrypted_text); // untuk melakukan enkripsi menggunakan kunci statis

    // cout << "Encrypted text: " << encrypted_text << endl;

    const char* filename = "encryption_file.txt"; // untuk menyimpan kedalam file bernama encryption_file.txt
    saveToFile(filename, plaintext, encrypted_text); // data yang disimpan meliputi plaintext dan encrypted text 

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
