#include <iostream>
#include <fstream>

using namespace std;

// Array untuk mengonversi indeks ke karakter
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

    int mod_inverse[94];

    for (int i = 0; i < 94; i++) {
        mod_inverse[i] = -1;
        for (int j = 0; j < 94; j++) {
            if ((i * j) % 94 == 1) {
                mod_inverse[i] = j;
                break;
            }
        }
    }

    for (size_t i = 0; i < len; i += n) {
        const char* block = encrypted_text + i;

        int result[2] = {0};

        for (int j = 0; j < n; j = j + 1) {
            for (int k = 0; k < n; ++k) {
                result[j] += mod_inverse[key[j][k]] * static_cast<int>(block[k]); 
            }
            result[j] %= 94; 
        }

        for (int j = 0; j < n; j = j + 1) {
            decrypted_text[i + j] = mod[result[j]];
        }
    }
    decrypted_text[len] = '\0'; // Menambahkan null terminator pada string hasil dekripsi
}

// Fungsi untuk menyimpan hasil dekripsi ke file
void saveToFile(const char* encryption_file.txt, const char* original, const char* decrypted) {
    ofstream file(encryption_file.txt);
    if (file.is_open()) {
        file << "Encrypted Text: " << original << '\n';
        file << "Decrypted Text: " << decrypted << '\n';
        cout << "Data has been saved to " << encryption_file.txt << std::endl;
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

    const int max_text_length = 1000; // Tentukan panjang maksimum string
    char encrypted_text[max_text_length];

    cout << "Enter the encrypted message to decrypt: ";
    cin.getline(encrypted_text, max_text_length);

    char decrypted_text[max_text_length];
    hill_cipher_decrypt(encrypted_text, static_key, decrypted_text);

    const char* filename = "decryption_file.txt";
    saveToFile(filename, encrypted_text, decrypted_text);

    return 0;
}
