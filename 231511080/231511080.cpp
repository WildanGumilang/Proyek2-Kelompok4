#include "231511080.h"
#include "../231511067/231511067.h"
#include "../231511082/231511082.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Definisikan struct untuk data pendaftaran
struct userDaftar {
    string nomorPendaftaran;
    string nik;
    string namalengkap;
    string tanggallahir;
    string tanggalperiksa;
    string pilihandokter;
    string carabayar;
};

// Variabel statis untuk nomor pendaftaran
static int nomorPendaftaran = 1;

// Fungsi untuk menghasilkan nomor pendaftaran acak
string generateNomorPendaftaran() {
    srand(time(0)); // Inisialisasi generator nomor acak dengan waktu saat ini
    int randomNumber = rand() % 900000 + 100000; // Menghasilkan nomor acak antara 100000 dan 999999
    return to_string(randomNumber); // Mengonversi nomor acak ke dalam string
}

// Fungsi untuk mengisi pendaftaran pemeriksaan
void pendaftaranPeriksa(const string& nik, const string& namalengkap, const string& tanggallahir) {
    userDaftar pendaftaran;
    int key[2][2] = {
        {31, 59},
        {17, 92}
    };
    char decrypted_text[100];
    char encrypted_text[100];

    // Isi data pendaftaran
    pendaftaran.nomorPendaftaran = generateNomorPendaftaran();
    hill_cipher_encrypt(pendaftaran.nomorPendaftaran.c_str(), key, encrypted_text);
    pendaftaran.nomorPendaftaran = encrypted_text;
    pendaftaran.nik = nik;
    hill_cipher_encrypt(pendaftaran.nik.c_str(), key, encrypted_text);
    pendaftaran.nik = encrypted_text;
    pendaftaran.namalengkap = namalengkap;
    hill_cipher_encrypt(pendaftaran.namalengkap.c_str(), key, encrypted_text);
    pendaftaran.namalengkap = encrypted_text;
    pendaftaran.tanggallahir = tanggallahir;
    hill_cipher_encrypt(pendaftaran.tanggallahir.c_str(), key, encrypted_text);
    pendaftaran.tanggallahir = encrypted_text;

    // Input data tambahan
    cout << "Masukkan Tanggal Periksa: ";
    cin >> pendaftaran.tanggalperiksa;

    // Pilihan dokter
    cout << "Pilih dokter yang Anda inginkan:\n";
    cout << "1. Dr. Wildan Gumilang (Dokter Umum)\n";
    cout << "2. Dr. Daffa Tridya (Spesialis Jantung)\n";
    cout << "3. Dr. Agra Anisa (Spesialis Anak)\n";
    int dokter;
    cout << "Pilihan Anda: ";
    cin >> dokter;
    switch (dokter) {
        case 1:
            pendaftaran.pilihandokter = "Dr. Wildan Gumilang (Dokter Umum)";
            break;
        case 2:
            pendaftaran.pilihandokter = "Dr. Daffa Tridya (Spesialis Jantung)";
            break;
        case 3:
            pendaftaran.pilihandokter = "Dr. Agra Anisa (Spesialis Anak)";
            break;
        default:
            cout << "Pilihan dokter tidak valid. Memilih secara default Dokter Umum.\n";
            pendaftaran.pilihandokter = "Dr. Wildan Gumilang (Dokter Umum)";
            break;
    }

    // Pilihan cara pembayaran
    cout << "\nPilih cara pembayaran:\n";
    cout << "1. BPJS Kesehatan\n";
    cout << "2. Pembayaran Reguler\n";
    int bayar;
    cout << "Pilihan Anda: ";
    cin >> bayar;
    switch (bayar) {
        case 1:
            pendaftaran.carabayar = "BPJS Kesehatan";
            hill_cipher_encrypt(pendaftaran.carabayar.c_str(), key, encrypted_text);
            pendaftaran.carabayar = encrypted_text;
            break;
        case 2:
            pendaftaran.carabayar = "Pembayaran Reguler";
            hill_cipher_encrypt(pendaftaran.carabayar.c_str(), key, encrypted_text);
            pendaftaran.carabayar = encrypted_text;
            break;
        default:
            cout << "Pilihan cara pembayaran tidak valid. Memilih secara default Pembayaran Reguler.\n";
            pendaftaran.carabayar = "Pembayaran Reguler";
            hill_cipher_encrypt(pendaftaran.carabayar.c_str(), key, encrypted_text);
            pendaftaran.carabayar = encrypted_text;
            break;
    }

    // Simpan data ke dalam file
    ofstream outFile("file/daftarperiksa.txt", ios::app); // Mode append agar tidak menghapus data yang sudah ada
    if (outFile.is_open()) {
        outFile << pendaftaran.nomorPendaftaran << "|" << pendaftaran.nik << "|" << pendaftaran.namalengkap << "|" << pendaftaran.tanggallahir << "|"
                << pendaftaran.tanggalperiksa << "|" << pendaftaran.pilihandokter << "|" << pendaftaran.carabayar << endl;
        outFile.close();
        cout << "Pendaftaran berhasil disimpan.\n";
    } else {
        cout << "Gagal menyimpan data pendaftaran.\n";
    }
}

// Menampilkan data pendaftaran periksa
void tampilkanDataPeriksa() {
    userDaftar pendaftaran;
    int key[2][2] = {
        {31, 59},
        {17, 92}
    };
    char decrypted_text[100];
    char encrypted_text[100];
    ifstream inFile("file/daftarperiksa.txt");
    if (inFile.is_open()) {
        cout << "===================================================================================================" << endl;
        cout << "                                SELURUH DATA PENDAFTARAN PERIKSA                                     " << endl;
        cout << "===================================================================================================" << endl;
        cout << "No. Pendaftaran\tNIK\tNama Lengkap\tTanggal Lahir\tTanggal Periksa\tPilihan Dokter\tCara Bayar" << endl;
        cout << "---------------------------------------------------------------------------------------------------" << endl;

        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string nomorPendaftaran, nik, namalengkap, tanggallahir, tanggalperiksa, pilihandokter, carabayar;
            getline(ss, nomorPendaftaran, '|');
            getline(ss, nik, '|');
            getline(ss, namalengkap, '|');
            getline(ss, tanggallahir, '|');
            getline(ss, tanggalperiksa, '|');
            getline(ss, pilihandokter, '|');
            getline(ss, carabayar);

            hill_cipher_decrypt(nomorPendaftaran.c_str(), key, decrypted_text);
            nomorPendaftaran = decrypted_text;
            hill_cipher_decrypt(nik.c_str(), key, decrypted_text);
            nik = decrypted_text;
            hill_cipher_decrypt(namalengkap.c_str(), key, decrypted_text);
            namalengkap = decrypted_text;
            hill_cipher_decrypt(tanggallahir.c_str(), key, decrypted_text);
            tanggallahir = decrypted_text;
            hill_cipher_decrypt(carabayar.c_str(), key, decrypted_text);
            carabayar = decrypted_text;            

            cout << nomorPendaftaran << "\t" << nik << "\t" << namalengkap << "\t" << tanggallahir << "\t" << tanggalperiksa << "\t" << pilihandokter << "\t" << carabayar << endl;

        }
        cout << "===================================================================================================" << endl;
        inFile.close();
        
    } else {
        cout << "Gagal membuka file daftarperiksa.txt.\n";
    }
}