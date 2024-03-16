#include "231511067.cpp"
#ifndef HILL_CIPHER_H
#define HILL_CIPHER_H

#include <string>

using namespace std;

void hill_cipher_encrypt(const char* text, const int key[2][2], char* encrypted_text);
void saveToFile(const char* filename, const char* original, const char* encrypted);
void tampilkanDataPasienByNIK(const std::string& nik);

#endif 
