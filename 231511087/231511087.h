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

int countDeterminan(kAddr awal);
kAddr inversKey(kAddr awal, int determinan);
pAddr perkalianMatriksLL(pAddr pAwal, kAddr kAwal);
bool simpanDataPasien(const UserData& userData);
bool lupaPassword(tAddr awalT, kAddr awalK);
bool registrasi(tAddr awalT, kAddr awalK, kAddr awalKinv);
bool login(string& nik, string& namalengkap, string& tanggallahir, string& alamat, string& password, tAddr awalT, kAddr awalK, kAddr awalKinv);
bool loginAdmin(string& namaAdmin, tAddr awalT, kAddr awalK, kAddr awalKinv);

#endif