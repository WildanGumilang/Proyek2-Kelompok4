#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


struct userDaftar {
    string nomorPendaftaran;
    string nik;
    string namalengkap;
    string tanggallahir;
    string tanggalperiksa;
    string pilihandokter;
    string carabayar;
};


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


void tampilkanSuratHasilPemeriksaan(string& targetNik);


void buatSuratHasilPemeriksaan();