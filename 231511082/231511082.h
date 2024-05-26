#include <iostream>
#include <cstring>
#include <cmath>
#include <sstream>
#include <fstream>
#include <vector>
#include "../program.h"
#include "../231511087/231511087.h"
#include "../231511080/231511080.h"
#include "../231511081/231511081.h"
#include "../231511067/231511067.h"

using namespace std;

string hill_cipher_decrypt(string cipherteks);
string addAngka(string str, bool genap);
string chekNumChar(string str, bool& genap);
tAddr bacaTabelKonversi();
string dekripsi(const string& encrypted_text);
void tampilkanSeluruhDataPasien();
bool insertTengahUserDaftar(const userDaftar& data, dfAddr& awal, dfAddr& akhir);
