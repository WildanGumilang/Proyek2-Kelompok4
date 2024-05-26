#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <string>
#include "../program.h"

using namespace std;

string generateNomorPendaftaran(); //fungsi untuk menghasilkan nomor pendaftaran acak
bool pendaftaranPeriksa(const string& nik, const string& namalengkap, const string& tanggallahir); //fungsi untuk mengisi pendaftaran pemeriksaan
void tampilkanDataPeriksa(tAddr awalT, kAddr awalKinv); //menampilkan data pendaftaran periksa
kAddr createNodeKey(int nilai);
kAddr buatLinkedListKey(int Key11, int Key12, int Key21, int Key22); 
string chekAndDelLastBool(string str, bool& chekJumlah);
string deleteLastBool(string str, bool chekJumlah);
bool insertUserDaftar(const userDaftar& data, dfAddr& awal, dfAddr& akhir);
