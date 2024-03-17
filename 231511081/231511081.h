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

// Fungsi untuk mengambil hasil pasiaen
void tampilkanSuratHasilPemeriksaan(string& targetNik);

// Fungsi untuk mengirim hasil pemeriksaan dari dokter ke pasien
void buatSuratHasilPemeriksaan();