#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

std::unordered_map<int, char> reverse_char_map = {
    {0, 'A'}, {1, 'B'}, {2, 'C'}, {3, 'D'}, {4, 'E'}, {5, 'F'}, {6, 'G'}, {7, 'H'}, {8, 'I'}, {9, 'J'}, {10, 'K'}, {11, 'L'}, {12, 'M'}, {13, 'N'}, {14, 'O'}, {15, 'P'}, {16, 'Q'}, {17, 'R'}, {18, 'S'}, {19, 'T'}, {20, 'U'}, {21, 'V'}, {22, 'W'}, {23, 'X'}, {24, 'Y'}, {25, 'Z'},
    {26, 'a'}, {27, 'b'}, {28, 'c'}, {29, 'd'}, {30, 'e'}, {31, 'f'}, {32, 'g'}, {33, 'h'}, {34, 'i'}, {35, 'j'}, {36, 'k'}, {37, 'l'}, {38, 'm'}, {39, 'n'}, {40, 'o'}, {41, 'p'}, {42, 'q'}, {43, 'r'}, {44, 's'}, {45, 't'}, {46, 'u'}, {47, 'v'}, {48, 'w'}, {49, 'x'}, {50, 'y'}, {51, 'z'},
    {52, '0'}, {53, '1'}, {54, '2'}, {55, '3'}, {56, '4'}, {57, '5'}, {58, '6'}, {59, '7'}, {60, '8'}, {61, '9'}, {62, '!'}, {63, '@'}, {64, '#'}, {65, '$'}, {66, '%'}, {67, '^'}, {68, '&'}, {69, '*'}, {70, '('}, {71, ')'}, {72, '_'}, {73, '-'}, {74, '+'}, {75, '='}, {76, '{'}, {77, '}'}, {78, '['}, {79, ']'}, {80, '<'}, {81, '>'}, {82, '.'}, {83, ','}, {84, ';'}, {85, '"'}, {86, '\''}, {87, '`'}, {88, '\\'}, {89, '/'}, {90, '?'}, {91, ':'}, {92, '~'}, {93, ' '}
};

std::string hill_cipher_encrypt(const std::string& text, const std::vector<std::vector<int>>& key) {
    std::string encrypted_text = "";

    int n = key.size();

    for (size_t i = 0; i < text.size(); i += n) {
        std::string block = text.substr(i, n);

        std::vector<int> result(n, 0);
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                result[j] += key[j][k] * (int)(block[k]);
            }
            result[j] %= 94;
        }

        for (int j = 0; j < n; ++j) {
            encrypted_text += reverse_char_map[result[j]];
        }
    }

    return encrypted_text;
}

std::string hill_cipher_decrypt(const std::string& text, const std::vector<std::vector<int>>& key) {
    std::string decrypted_text = "";

    int n = key.size();
    int mod_inverse = 0;

    // Temukan modulus inverse dari determinan matriks kunci
    for (int i = 0; i < 94; ++i) {
        if ((key[0][0] * key[1][1] - key[0][1] * key[1][0]) * i % 94 == 1) {
            mod_inverse = i;
            break;
        }
    }

    for (size_t i = 0; i < text.size(); i += n) {
        std::string block = text.substr(i, n);

        std::vector<int> result(n, 0);
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                result[j] += key[j][k] * ((int)(block[k]) - 32);
            }
            result[j] *= mod_inverse;
            result[j] %= 94;

            if (result[j] < 0) {
                result[j] += 94;
            }
        }

        for (int j = 0; j < n; ++j) {
            decrypted_text += reverse_char_map[result[j]];
        }
    }

    return decrypted_text;
}

void saveToFile(const std::string& filename, const std::string& original, const std::string& encrypted) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Original Text: " << original << '\n';
        file << "Encrypted Text: " << encrypted << '\n';
        std::cout << "Data has been saved to " << filename << std::endl;
        file.close();
    } else {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }
}

int main() {
    // Gunakan matriks kunci statis
    int static_key[2][2] = {
        {2, 1}, {3, 4}
    };

    std::vector<std::vector<int>> key(2, std::vector<int>(2));

    // Salin matriks kunci statis ke vektor
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            key[i][j] = static_key[i][j];
        }
    }

    std::string plaintext;
    std::cout << "Enter the message to encrypt: ";
    std::getline(std::cin, plaintext);

    std::string encrypted_text = hill_cipher_encrypt(plaintext, key);
    std::cout << "Encrypted text: " << encrypted_text << std::endl;

    std::string filename = "encryption_file.txt";
    saveToFile(filename, plaintext, encrypted_text);

    std::string decrypted_text = hill_cipher_decrypt(encrypted_text, key);
    std::cout << "Decrypted text: " << decrypted_text << std::endl;

    return 0;
}
