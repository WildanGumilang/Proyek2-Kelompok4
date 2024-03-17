#include "231511081.h"
#include "../231511067/231511067.h"
#include "../231511082/231511082.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
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

// Definisikan struct untuk data hasil pemeriksaan
struct UserHasil {
    string nomorpendaftaran;
    string nik;
    string namalengkap;
    string tanggallahir;
    string tanggalperiksa;
    string pilihandokter;
    string hasilPemeriksaan;
    string resepObat;
};

// Fungsi untuk membuat surat hasil pemeriksaan
void buatSuratHasilPemeriksaan(const string& nomorPendaftaran) {
    userDaftar pendaftaran;
    int key[2][2] = {
        {31, 59},
        {17, 92}
    };
    char decrypted_text[100];
    char encrypted_text[100];


    // Baca data dari file daftarperiksa.txt
    ifstream inFile("file/daftarperiksa.txt");
    if (inFile.is_open()) {
        userDaftar pendaftaran;
        bool pendaftaranDitemukan = false;
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            getline(ss, pendaftaran.nomorPendaftaran, '|');
            getline(ss, pendaftaran.nik, '|');
            getline(ss, pendaftaran.namalengkap, '|');
            getline(ss, pendaftaran.tanggallahir, '|');
            getline(ss, pendaftaran.tanggalperiksa, '|');
            getline(ss, pendaftaran.pilihandokter,'|');
            getline(ss, pendaftaran.carabayar,'|');

            hill_cipher_decrypt(pendaftaran.nomorPendaftaran.c_str(), key, decrypted_text);
            pendaftaran.nomorPendaftaran = decrypted_text;
            hill_cipher_decrypt(pendaftaran.nik.c_str(), key, decrypted_text);
            pendaftaran.nik = decrypted_text;
            hill_cipher_decrypt(pendaftaran.namalengkap.c_str(), key, decrypted_text);
            pendaftaran.namalengkap = decrypted_text;
            hill_cipher_decrypt(pendaftaran.tanggallahir.c_str(), key, decrypted_text);
            pendaftaran.tanggallahir = decrypted_text;
            hill_cipher_decrypt(pendaftaran.pilihandokter.c_str(), key, decrypted_text);
            pendaftaran.pilihandokter = decrypted_text;
            hill_cipher_decrypt(pendaftaran.carabayar.c_str(), key, decrypted_text);
            pendaftaran.carabayar = decrypted_text;

            // Jika nomor pendaftaran ditemukan, ambil data pendaftaran
            if (pendaftaran.nomorPendaftaran == nomorPendaftaran) {
                pendaftaranDitemukan = true;
                break;
            }
        }
        inFile.close();

        if (pendaftaranDitemukan) {
            // Mengisi hasil pemeriksaan
            string hasilPemeriksaan;
            cout << "Masukkan hasil pemeriksaan: ";
            cin.ignore();
            getline(cin, hasilPemeriksaan);

            // Mengisi resep obat
            string resepObat;
            cout << "Masukkan resep obat: ";
            getline(cin, resepObat);

            // Simpan data hasil pemeriksaan ke dalam file
            ofstream outFile("file/hasilpemeriksaan.txt", ios::app); // Mode append agar tidak menghapus data yang sudah ada
            if (outFile.is_open()) {
                outFile << pendaftaran.nomorPendaftaran << "|" << pendaftaran.nik << "|" << pendaftaran.namalengkap << "|"
                        << pendaftaran.tanggallahir << "|" << pendaftaran.tanggalperiksa << "|" << pendaftaran.pilihandokter << "|"
                        << hasilPemeriksaan << "|" << resepObat << endl;
                outFile.close();
                cout << "Surat hasil pemeriksaan berhasil dibuat.\n";
            } else {
                cout << "Gagal menyimpan surat hasil pemeriksaan.\n";
            }
        } else {
            cout << "Nomor pendaftaran tidak ditemukan.\n";
        }
    } else {
        cout << "Gagal membuka file daftarperiksa.txt.\n";
    }
}



// Fungsi untuk menampilkan surat hasil pemeriksaan berdasarkan nik
void tampilkanSuratHasilPemeriksaan(const string& targetNik) {
    ifstream inFile("file/hasilperiksa.txt");
    if (inFile.is_open()) {
        cout << "==================================================================================================================" << endl;
        cout << "                                    SURAT HASIL PEMERIKSAAN PASIEN                                                   " << endl;
        cout << "==================================================================================================================" << endl;
        cout << "Nomor Pendaftaran\tNIK\tNama Lengkap\tTanggal Lahir\tTanggal Periksa\tPilihan Dokter\tHasil Pemeriksaan\tResep Obat" << endl;
        cout << "------------------------------------------------------------------------------------------------------------------" << endl;

        string line;
        bool found = false;
        while (getline(inFile, line)) {
            stringstream ss(line);
            UserHasil data;
            getline(ss, data.nomorpendaftaran, '|');
            getline(ss, data.nik, '|');
            getline(ss, data.namalengkap, '|');
            getline(ss, data.tanggallahir, '|');
            getline(ss, data.tanggalperiksa, '|');
            getline(ss, data.pilihandokter, '|');
            getline(ss, data.hasilPemeriksaan, '|');
            getline(ss, data.resepObat);
            
            if (data.nik == targetNik) {
                found = true;
                cout << data.nomorpendaftaran << "\t\t" << data.nik << "\t" << data.namalengkap << "\t" << data.tanggallahir << "\t" << data.tanggalperiksa << "\t" 
                     << data.pilihandokter << "\t" << data.hasilPemeriksaan << "\t" << data.resepObat << endl;
            }
        }

        if (!found) {
            cout << "Tidak ditemukan surat hasil pemeriksaan untuk NIK " << targetNik << endl;
        }
        
        cout << "==================================================================================================================" << endl;
        inFile.close();
    } else {
        cout << "Gagal membuka file hasilpemeriksaan.txt.\n";
    }
}