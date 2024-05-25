#ifndef HILL_CIPHER_H
#define HILL_CIPHER_H

#include <string>
#include "../program.h"
#include "../231511082/231511082.h"
#include "../231511087/231511087.h"
#include "../231511080/231511080.h"
#include "../231511081/231511081.h"

using namespace std;

string hill_cipher_encrypt(string plainteks, tAddr awalT, kAddr awalK);
bool hapusLinkedList(pAddr& awalP);
char cariKarakter(const tAddr awal, int indeks);
string konversiAngkaKePlainteks(const pAddr awal, const tAddr tabelKonversi);
string enkripsi(const string& plaintext);
void tampilkanDataPasienByNIK(std::string& nik, tAddr awalT, kAddr awalK, kAddr awalKinv);
void hapusLinkedListUserDaftar(dfAddr &awalD);

#endif