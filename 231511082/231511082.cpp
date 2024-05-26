#include "231511082.h"

using namespace std;

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

string hill_cipher_decrypt(string cipherteks, tAddr awalT, kAddr awalKinv) {

    pAddr awalP = nullptr;
    bool genap;
    cipherteks = chekAndDelLastBool(cipherteks, genap);
    // cout << "pLAINTEKS setelah dihapus 0 atau 1 = " << cipherteks << endl;  
    awalP = konversiPlainteksKeAngka(cipherteks, awalT);
    // cout << "pLAINTEKS setelah dijadikan angka dan dijadikan linked list = ";
    awalP = perkalianMatriksLL(awalP, awalKinv);
    // cout << "aNGKA setelah dikalikan matriks linked list = " << endl;
    // tampilkanLinkedList(awalP);
    cipherteks = konversiAngkaKePlainteks(awalP, awalT);
    // cout << "pLAINTEKS setelah dijadikan string = " << cipherteks << endl;
    cipherteks = deleteLastBool(cipherteks, genap);
    // cout << "pLAINTEKS setelah dicek 0 1 = " << cipherteks << endl;
    // cout << "pLAINTEKS setelah dikonversi didalam function = " << cipherteks << endl;

    if(hapusLinkedList(awalP)) {
        return cipherteks;
    }
}

string dekripsi(const string& encrypted_text) {
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

void tampilkanSeluruhDataPasien(tAddr awalT, kAddr awalKinv) {

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

            user.nik = hill_cipher_decrypt(user.nik, awalT, awalKinv);
            user.namalengkap = hill_cipher_decrypt(user.namalengkap, awalT, awalKinv);
            user.tanggallahir = hill_cipher_decrypt(user.tanggallahir, awalT, awalKinv);
            user.alamat = hill_cipher_decrypt(user.alamat, awalT, awalKinv);

            // Tambahkan data pengguna ke vektor userData
            userData.push_back(user);
        }
        inFile.close();

        cout << "=============================================================" << endl;
        cout << "                         DATA PASIEN                         " << endl;
        cout << "=============================================================" << endl;

        // Menampilkan data pasien
        for (const auto& user : userData) {
            cout << "Nama Lengkap  : " << user.namalengkap << endl;
            cout << "NIK           : " << user.nik << endl;
            cout << "Tanggal Lahir : " << user.tanggallahir << endl;
            cout << "Alamat        : " << user.alamat << endl;
            cout << "-------------------------------------------------------------" << endl;
        }
        cout << "=============================================================" << endl;

    } else {
        cout << "Gagal mengakses penyimpanan data.\n";
    }
}

// Fungsi untuk membaca isi file tabel konversi
tAddr bacaTabelKonversi() {
    tAddr awal = nullptr;
    tAddr akhir = nullptr;

    ifstream inFile("file/tabel_konversi.txt");
    if (inFile.is_open()) {
        char karakter;
        while (inFile.get(karakter)) {
            if (karakter != '|' && karakter != '\n') {
                tAddr newNode = new NodeT;
                newNode->info = karakter;
                newNode->next = nullptr;

                if (awal == nullptr) {
                    awal = akhir = newNode;
                } else {
                    akhir->next = newNode;
                    akhir = newNode;
                }
            }
        }
        inFile.close();
    } else {
        cout << "Gagal membaca file tabel konversi." << endl;
    }

    return awal;
}
// fungsi untuk mengecek karakter dalam string genap atau ganjil, jika ganjil maka akan ditambah X, dan genap bernilai false
string chekNumChar(string str, bool& genap) {
    int panjang = str.length();
    if (panjang % 2 == 0) {
        genap = true;
    } else {
        genap = false;
        str += 'X';
    }
    return str;
}
// fungsi untuk menambahkan karakter 1 (jika genap bernilai true) atau 0 (jika genap bernilai false) padasaat sebelum dimasukkan ke file
string addAngka(string str, bool genap) {
    if (genap) {
        str += "1";
    } else {
        str += "0";
    }
    return str;
}

bool insertTengahUserDaftar(const userDaftar& data, dfAddr& awal, dfAddr& akhir) {
    dfAddr newNode = new userDaftar;
    if (newNode != nullptr) {
        *newNode = data;
        newNode->next = nullptr;

        if (awal == nullptr) {  // Linked list kosong
            awal = akhir = newNode;
        } else if (awal->namalengkap > newNode->namalengkap) {  // Sisipkan di awal
            newNode->next = awal;
            awal = newNode;
        } else {  // Sisipkan di tengah atau akhir
            dfAddr prev = nullptr;
            dfAddr current = awal;
            while (current != nullptr && current->namalengkap <= newNode->namalengkap) {
                prev = current;
                current = current->next;
            }
            if (current == nullptr) {  // Sisipkan di akhir
                akhir->next = newNode;
                akhir = newNode;
            } else {  // Sisipkan di tengah
                prev->next = newNode;
                newNode->next = current;
            }
        }
        return true;
    } else {
        cout << "Alokasi memori gagal. Tidak dapat menyisipkan node baru." << endl;
        return false;
    }
}