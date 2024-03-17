#ifndef HILL_CIPHER_H
#define HILL_CIPHER_H

#include <string>

using namespace std;

void hill_cipher_encrypt(const char* text, const int key[2][2], char* encrypted_text);
void tampilkanDataPasienByNIK(std::string& nik);

#endif