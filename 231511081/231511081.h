#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

bool insertAkhir(int nilai, pAddr& awal, pAddr& akhir);
void tampilkanSuratHasilPemeriksaan(string& targetNik);
bool buatSuratHasilPemeriksaan();
pAddr konversiPlainteksKeAngka(const string& plainteks, tAddr awal);
int cariIndeks(tAddr head, char karakter);