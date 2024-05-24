#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <stdlib.h>

using namespace std;

typedef struct NodeT *tAddr;
typedef struct NodeP *pAddr;
typedef struct NodeK *kAddr;
typedef struct UserData *dtAddr;
typedef struct userDaftar *dfAddr;
typedef struct UserHasil *hsAddr;

struct UserData {
    string nik;
    string password;
    string namalengkap;
    string tanggallahir;
    string alamat;
    string clueKeamanan;
    dtAddr next;
};

struct AdminData {
    string namaAdmin;
    string password;
    string nomorAdmin;
};

// Definisikan struct untuk data pendaftaran
struct userDaftar {
    string nomorPendaftaran;
    string nik;
    string namalengkap;
    string tanggallahir;
    string tanggalperiksa;
    string pilihandokter;
    string carabayar;
    dfAddr next;
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
    hsAddr next;
};

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

#endif