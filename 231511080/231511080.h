#include "231511080.cpp"

extern int nomorPendaftaran; //variabel statis untuk nomor pendaftaran

string generateNomorPendaftaran(); //fungsi untuk menghasilkan nomor pendaftaran acak
void pendaftaranPeriksa(const string& nik, const string& namalengkap, const string& tanggallahir); //fungsi untuk mengisi pendaftaran pemeriksaan
void tampilkanDataPeriksa(); //menampilkan data pendaftaran periksa