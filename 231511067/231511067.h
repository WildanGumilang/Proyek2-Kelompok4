#ifndef HILL_CIPHER_H
#define HILL_CIPHER_H

#include <string>

using namespace std;

typedef struct NodeT *tAddr;
typedef struct NodeP *pAddr;
typedef struct NodeK *kAddr;
// Struct Node untuk linked list tabel konversi
struct NodeT {
    char info;
    tAddr next;
};

// Struct Node untuk linked list angka hasil konversi
struct NodeP {
    int info;
    pAddr next;
};

struct NodeK {
    int info;
    kAddr nextrow;
    kAddr nextcol;
};

string hill_cipher_encrypt(const string& plaintext);
void tampilkanDataPasienByNIK(std::string& nik);
bool deleteAwal(pAddr& awal, pAddr& akhir);
char cariKarakter(const tAddr awal, int indeks);
string konversiAngkaKePlainteks(const pAddr awal, const tAddr tabelKonversi);

#endif