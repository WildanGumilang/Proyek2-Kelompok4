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

    if (n != key[0].size()) {
        std::cerr << "Error: Key matrix must be square." << std::endl;
        return "";
    }

    if (text.size() % n != 0) {
        std::cerr << "Error: Plaintext length must be a multiple of the key matrix size." << std::endl;
        return "";
    }

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

int main() 
{
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
    std::cout << "Enter the message to encrypt: ";
    std::getline(std::cin, plaintext); 

    std::string encrypted_text = hill_cipher_encrypt(plaintext, key);
    std::cout << "Encrypted text: " << encrypted_text << std::endl;

    std::string filename = "encryption_file.txt";
    saveToFile(filename, plaintext, encrypted_text);

    return 0;
}