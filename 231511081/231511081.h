#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../program.h"


bool insertAkhir(int nilai, pAddr& awal, pAddr& akhir);
void tampilkanSuratHasilPemeriksaan(string& targetNik, tAddr awalT, kAddr awalK, kAddr awalKinv);
bool buatSuratHasilPemeriksaan(tAddr awalT, kAddr awalK);
pAddr konversiPlainteksKeAngka(const string& plainteks, tAddr awal);
int cariIndeks(tAddr head, char karakter);
bool insertTengahUserData(const UserData& data, dtAddr& awal, dtAddr& akhir);
void hapusLinkedListUserData(dtAddr &awalD);