#ifndef LOGINREGISTER_H
#define LOGINREGISTER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct UserData {
    string nik;
    string password;
    string namalengkap;
    string tanggallahir;
    string alamat;
    string clueKeamanan;
};

struct AdminData {
    string namaAdmin;
    string password;
    string nomorAdmin;
};

// Deklarasi fungsi-fungsi modul
void simpanDataPasien(const UserData& userData);
void lupaPassword();
void registrasi();
bool login(string& nik, string& namalengkap, string& tanggallahir, string& alamat, string& password);
bool loginAdmin(string& namaAdmin);

#endif