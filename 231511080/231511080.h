#include <string>
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

string generateNomorPendaftaran(); //fungsi untuk menghasilkan nomor pendaftaran acak
void pendaftaranPeriksa(const string& nik, const string& namalengkap, const string& tanggallahir); //fungsi untuk mengisi pendaftaran pemeriksaan
void tampilkanDataPeriksa(); //menampilkan data pendaftaran periksa