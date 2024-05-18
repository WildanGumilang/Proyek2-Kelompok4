#ifndef LOGINREGISTER_H
#define LOGINREGISTER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "../program.h"
#include "../231511067/231511067.h"
#include "../231511082/231511082.h"

using namespace std;

bool simpanDataPasien(const UserData& userData);
bool lupaPassword();
bool registrasi();
bool login(string& nik, string& namalengkap, string& tanggallahir, string& alamat, string& password);
bool loginAdmin(string& namaAdmin);
int countDeterminan(kAddr awal);
kAddr inversKey(kAddr awal, int determinan);
pAddr perkalianMatriksLL(pAddr pAwal, kAddr kAwal);

#endif