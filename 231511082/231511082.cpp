#include <iostream>
#include <fstream>

using namespace std;

char mod[94] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '-', '+', '=', '{', '}', 
    '[', ']', '<', '>', '.', ',', ';', '"', '\'', '`', '\\', '/', '?', ':', '~', ' '
};
// Fungsi untuk melakukan dekripsi Hill Cipher
void hill_cipher_decrypt(const char* encrypted_text, const int key[2][2], char* decrypted_text) {
    int n = 2; // Ukuran matriks kunci

    size_t len = 0;
    while (encrypted_text[len] != '\0') {
        len++;
    }

    for (size_t i = 0; i < len; i += n) {
        const char* block = encrypted_text + i;

        int result[2] = {0};

        for (int j = 0; j < n; j = j + 1) {
            for (int k = 0; k < n; ++k) {
                result[j] += key[j][k] * static_cast<int>(block[k] - ' '); 
            }
            result[j] = (result[j] % 94 + 94) % 94; // Menangani hasil modulus yang negatif
        }

        for (int j = 0; j < n; j = j + 1) {
            decrypted_text[i + j] = mod[result[j]];
        }
    }
    decrypted_text[len] = '\0'; // Menambahkan null terminator pada string hasil dekripsi
}

// Fungsi untuk membaca file dan melakukan dekripsi Hill Cipher
void decryptFromFile(const char* filename, int key[2][2]) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        getline(file, line); // Baca plaintext dari file
        const char* plaintext = line.c_str();

        getline(file, line); // Baca encrypted text dari file
        const char* encrypted_text = line.c_str();

        char decrypted_text[1000];
        hill_cipher_decrypt(encrypted_text, key, decrypted_text);

        const char* decrypted_filename = "decryption_file.txt";
        ofstream decrypted_file(decrypted_filename);
        if (decrypted_file.is_open()) {
            decrypted_file << "Plaintext: " << plaintext << '\n';
            decrypted_file << "Decrypted Text: " << decrypted_text << '\n';
            cout << "Decrypted data has been saved to " << decrypted_filename << std::endl;
            decrypted_file.close();
        } else {
            cerr << "Error: Unable to open the decrypted file." << std::endl;
        }

        file.close();
    } else {
        cerr << "Error: Unable to open the file." << std::endl;
    }
}

int main() {
    // Gunakan matriks kunci statis
    int static_key[2][2] = {
        {2, 1}, {3, 4}
    };

    const char* filename = "encryption_file.txt";
    decryptFromFile(filename, static_key);

    return 0;
}
