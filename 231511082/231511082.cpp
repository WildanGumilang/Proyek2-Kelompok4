#include "231511082.h"

using namespace std;

struct UserData {
    string nik;
    string password;
    string namalengkap;
    string tanggallahir;
    string alamat;
    string clueKeamanan;
};

const char mod[94] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '-', '+', '=', '{', '}', 
    '[', ']', '<', '>', '.', ',', ';', '"', '\'', '`', '\\', '/', '?', ':', '~', ' '
};

int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // Modular inverse does not exist
}

string hill_cipher_decrypt(const string& encrypted_text) {
    char mod[94] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '-', '+', '=', '{', '}', 
        '[', ']', '<', '>', '.', ',', ';', '"', '\'', '`', '\\', '/', '?', ':', '~', ' '
    };
    int key[2][2] = {
        {2, 1},
        {3, 4}
    };
    int len = encrypted_text.length();
    char* decrypted_temp = new char[len + 1];

    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 94;
    int det_inv = mod_inverse(det, 94);
    if (det_inv == -1) {
        cerr << "Modular inverse does not exist." << endl;
        return "";
    }

    int key_inv[2][2];
    key_inv[0][0] = key[1][1];
    key_inv[0][1] = -key[0][1];
    key_inv[1][0] = -key[1][0];
    key_inv[1][1] = key[0][0];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            key_inv[i][j] = (key_inv[i][j] * det_inv) % 94;
            if (key_inv[i][j] < 0) {
                key_inv[i][j] += 94;
            }
        }
    }

    for (int i = 0; i < len; i += 2) {
        int y1 = -1, y2 = -1;
        for (int j = 0; j < 94; ++j) {
            if (mod[j] == encrypted_text[i]) {
                y1 = j;
            }
            if (mod[j] == encrypted_text[i + 1]) {
                y2 = j;
            }
        }

        if (y1 == -1 || y2 == -1) {
            cerr << "Invalid character in encrypted text." << endl;
            return "";
        }

        int x1 = (key_inv[0][0] * y1 + key_inv[0][1] * y2) % 94;
        int x2 = (key_inv[1][0] * y1 + key_inv[1][1] * y2) % 94;

        decrypted_temp[i] = mod[x1];
        decrypted_temp[i + 1] = mod[x2];
    }
    decrypted_temp[len] = '\0';

    for (int i = 0; i < len; i++) {
        if (decrypted_temp[i] == 'X') {
            decrypted_temp[i] = '\0';
            break;
        }
    }

    string decrypted_text = decrypted_temp;
    delete[] decrypted_temp;
    return decrypted_text;
}

void tampilkanSeluruhDataPasien() {

    ifstream inFile("file/akun_pengguna.txt");
    if (inFile.is_open()) {
        string line;
        vector<UserData> userData; // Vektor untuk menyimpan data pengguna

        while (getline(inFile, line)) {
            stringstream ss(line);
            UserData user;

            getline(ss, user.nik, '|');
            getline(ss, user.password, '|');
            getline(ss, user.namalengkap, '|');
            getline(ss, user.tanggallahir, '|');
            getline(ss, user.alamat, '|');
            getline(ss, user.clueKeamanan);

            user.nik = hill_cipher_decrypt(user.nik);
            user.namalengkap = hill_cipher_decrypt(user.namalengkap);
            user.tanggallahir = hill_cipher_decrypt(user.tanggallahir);
            user.alamat = hill_cipher_decrypt(user.alamat);

            // Tambahkan data pengguna ke vektor userData
            userData.push_back(user);
        }
        inFile.close();

        // Menampilkan semua data pasien
        cout << "Data Pasien:" << endl;
        for (const auto& user : userData) {
            cout << "NIK: " << user.nik << endl;
            cout << "Nama Lengkap: " << user.namalengkap << endl;
            cout << "Tanggal Lahir: " << user.tanggallahir << endl;
            cout << "Alamat: " << user.alamat << endl;
            cout << "-------------------------------------------" << endl;
        }
    } else {
        cout << "Gagal mengakses penyimpanan data.\n";
    }
}