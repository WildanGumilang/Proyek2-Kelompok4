#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

std::unordered_map<int, char> reverse_char_map = {
      {0, 'A'}, {1, 'B'}, {2, 'C'}, {3, 'D'}, {4, 'E'}, {5, 'F'}, {6, 'G'}, {7, 'H'}, {8, 'I'}, {9, 'J'}, {10, 'K'}, {11, 'L'}, {12, 'M'}, {13, 'N'}, {14, 'O'}, {15, 'P'}, {16, 'Q'}, {17, 'R'}, {18, 'S'}, {19, 'T'}, {20, 'U'}, {21, 'V'}, {22, 'W'}, {23, 'X'}, {24, 'Y'}, {25, 'Z'},
    {26, 'a'}, {27, 'b'}, {28, 'c'}, {29, 'd'}, {30, 'e'}, {31, 'f'}, {32, 'g'}, {33, 'h'}, {34, 'i'}, {35, 'j'}, {36, 'k'}, {37, 'l'}, {38, 'm'}, {39, 'n'}, {40, 'o'}, {41, 'p'}, {42, 'q'}, {43, 'r'}, {44, 's'}, {45, 't'}, {46, 'u'}, {47, 'v'}, {48, 'w'}, {49, 'x'}, {50, 'y'}, {51, 'z'},
    {52, '0'}, {53, '1'}, {54, '2'}, {55, '3'}, {56, '4'}, {57, '5'}, {58, '6'}, {59, '7'}, {60, '8'}, {61, '9'}, {62, '!'}, {63, '@'}, {64, '#'}, {65, '$'}, {66, '%'}, {67, '^'}, {68, '&'}, {69, '*'}, {70, '('}, {71, ')'}, {72, '_'}, {73, '-'}, {74, '+'}, {75, '='}, {76, '{'}, {77, '}'}, {78, '['}, {79, ']'}, {80, '<'}, {81, '>'}, {82, '.'}, {83, ','}, {84, ';'}, {85, '"'}, {86, '\''}, {87, '`'}, {88, '\\'}, {89, '/'}, {90, '?'}, {91, ':'}, {92, '~'}, {93, ' '}
};

int mod_inverse(int a, int m) {
    a = (a % m + m) % m;
    for (int i = 1; i < m; ++i) {
        if ((a * i) % m == 1) {
            return i;
        }
    }
    return -1;  // Inverse does not exist
}

std::vector<std::vector<int>> get_inverse_key(const std::vector<std::vector<int>>& key) {
    int n = key.size();
    std::vector<std::vector<int>> inverse_key(n, std::vector<int>(n, 0));

    // Menghitung determinan matriks kunci
    int det = key[0][0] * (key[1][1] * key[2][2] - key[1][2] * key[2][1]) -
              key[0][1] * (key[1][0] * key[2][2] - key[1][2] * key[2][0]) +
              key[0][2] * (key[1][0] * key[2][1] - key[1][1] * key[2][0]);

    int det_inv = mod_inverse(det, 94);

    // Menghitung matriks adjoint
    inverse_key[0][0] = (key[1][1] * key[2][2] - key[1][2] * key[2][1]) * det_inv % 94;
    inverse_key[0][1] = (key[0][2] * key[2][1] - key[0][1] * key[2][2]) * det_inv % 94;
    inverse_key[0][2] = (key[0][1] * key[1][2] - key[0][2] * key[1][1]) * det_inv % 94;
    inverse_key[1][0] = (key[1][2] * key[2][0] - key[1][0] * key[2][2]) * det_inv % 94;
    inverse_key[1][1] = (key[0][0] * key[2][2] - key[0][2] * key[2][0]) * det_inv % 94;
    inverse_key[1][2] = (key[0][2] * key[1][0] - key[0][0] * key[1][2]) * det_inv % 94;
    inverse_key[2][0] = (key[1][0] * key[2][1] - key[1][1] * key[2][0]) * det_inv % 94;
    inverse_key[2][1] = (key[0][1] * key[2][0] - key[0][0] * key[2][1]) * det_inv % 94;
    inverse_key[2][2] = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) * det_inv % 94;

    return inverse_key;
}

std::string hill_cipher_decrypt(const std::string& text, const std::vector<std::vector<int>>& key) {
    std::string decrypted_text = "";
    int n = key.size();

    // Periksa apakah matriks kunci dapat diinvers
    int det = key[0][0] * (key[1][1] * key[2][2] - key[1][2] * key[2][1]) -
              key[0][1] * (key[1][0] * key[2][2] - key[1][2] * key[2][0]) +
              key[0][2] * (key[1][0] * key[2][1] - key[1][1] * key[2][0]);
    if (mod_inverse(det, 94) == -1) {
        std::cerr << "Error: Matriks kunci tidak dapat diinvers." << std::endl;
        return "";
    }

    std::vector<std::vector<int>> inverse_key = get_inverse_key(key);

    for (size_t i = 0; i < text.size(); i += n) {
        std::string block = text.substr(i, n);

        std::vector<int> result(n, 0);
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                result[j] += inverse_key[j][k] * (int)(block[k]);
            }
            result[j] = (result[j] % 94 + 94) % 94;  // Handle nilai negatif
        }

        for (int j = 0; j < n; ++j) {
            decrypted_text += reverse_char_map[result[j]];
        }
    }

    return decrypted_text;
}

int main() {
    int n;
    std::cout << "Enter the size of the key matrix encry: ";
    std::cin >> n;

    std::vector<std::vector<int>> key(n, std::vector<int>(n));

    std::cout << "Enter the key matrix encry:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << "Enter element " << i + 1 << "," << j + 1 << ": ";
            std::cin >> key[i][j];
        }
    }

    std::string plaintext;
    std::cin.ignore(); 
    std::cout << "Enter the message to decrypt: ";
    std::getline(std::cin, plaintext); 

    std::string decrypted_text = hill_cipher_decrypt(plaintext, key);
    std::cout << "Dekripsi teks: " << decrypted_text << std::endl;

    return 0;
}
