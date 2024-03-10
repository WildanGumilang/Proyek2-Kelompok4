#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct UserData {
    string nik;
    string password;
    string namalengkap;
    string tanggallahir;
    string alamat;
    string clueKeamanan;
};

vector<UserData> usersData;

void simpanDataPasien() {
    ofstream outFile("file/akun_pengguna.txt");
    if (outFile.is_open()) {
        for (const auto& userData : usersData) {
            outFile << userData.nik << "|" << userData.password << "|" << userData.namalengkap << "|" << userData.tanggallahir << "|" << userData.alamat << "|" << userData.clueKeamanan << endl;
        }
        outFile.close();
        system("cls");
        cout << " ---------------------------------------------------------------------------------------------------- \n\n";
    } else {
        system("cls");
        cout << "Gagal menyimpan data.\n";
    }
}

void bacaDataPasien() {
    ifstream inFile("file/akun_pengguna.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            UserData userData;

            getline(ss, userData.nik, '|');
            getline(ss, userData.password, '|');
            getline(ss, userData.namalengkap, '|');
            getline(ss, userData.tanggallahir, '|');
            getline(ss, userData.alamat, '|');
            getline(ss, userData.clueKeamanan);

            // tambahin data pengguna ke vektor usersData
            usersData.push_back(userData);
        }
        inFile.close();
    } else {
        cout << "Gagal mengakses penyimpanan data.\n";
    }
}


void gantipassword() {
    string nik, password, newPassword;
    bool ditemukan = false;

    cout << " =================================== Halaman Ganti Password ======================================== \n";
    cout << " ------------------------------- Masukkan NIK dan Password Baru ------------------------------------ \n\n";

    cout << "Masukkan NIK : ";
    cin >> nik;
    cout << "Masukkan Password Lama : ";
    cin >> password;


    ifstream inFile("file/akun_pengguna.txt");
    if (inFile.is_open()) {
        vector<UserData> updatedUsersData; // Vektor untuk menyimpan data pengguna yang baru diperbarui
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            UserData userData;


            getline(ss, userData.nik, '|');
            getline(ss, userData.password, '|');
            getline(ss, userData.namalengkap, '|');
            getline(ss, userData.tanggallahir, '|');
            getline(ss, userData.alamat, '|');
            getline(ss, userData.clueKeamanan);


            if (userData.nik == nik && password == userData.password) {
                ditemukan = true;
                cout << "Masukkan Password Baru : ";
                cin >> newPassword;
                userData.password = newPassword; 
            }

            updatedUsersData.push_back(userData);
        }
        inFile.close();

        if (!ditemukan) {
            system("cls");
            cout << "Password tidak berhasil diganti. Pastikan NIK dan password lama Anda benar!\n\n";
            gantipassword();

        }

        ofstream outFile("file/akun_pengguna.txt");
        if (outFile.is_open()) {
            for (const auto& userData : updatedUsersData) {
                outFile << userData.nik << "|" << userData.password << "|" << userData.namalengkap << "|" << userData.tanggallahir << "|" << userData.alamat << "|" << userData.clueKeamanan << endl;
            }
            outFile.close();
            system("cls");
            cout << " ------------------------------ Password Berhasil Diganti! ----------------------------------------- \n\n";
        } else {
            system("cls");
            cout << "Gagal mengganti password.\n";
        }

    } else {
        system("cls");
        cout << "Gagal mengakses penyimpanan data.\n";
    }
}

void lupaPassword() {
    string nik, jawaban;
    bool ditemukan = false;

    cout << " ====================================== Halaman Lupa Password ========================================== \n";
    cout << " ------------------------------- Masukkan NIK dan Jawaban Clue Keamanan -------------------------------- \n\n";
    cout << "Masukkan NIK : ";
    cin >> nik;
    cout << "Masukkan Jawaban Clue Keamanan : ";
    cin.ignore();
    getline(cin, jawaban);


    ifstream inFile("file/akun_pengguna.txt");
    if (inFile.is_open()) {
        vector<UserData> updatedUsersData; 
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            UserData userData;

            getline(ss, userData.nik, '|');
            getline(ss, userData.password, '|');
            getline(ss, userData.namalengkap, '|');
            getline(ss, userData.tanggallahir, '|');
            getline(ss, userData.alamat, '|');
            getline(ss, userData.clueKeamanan);

            if (userData.nik == nik && jawaban == userData.clueKeamanan) {
                cout << "Masukkan Password Baru : ";
                cin >> userData.password;
                ditemukan = true;
            }

            updatedUsersData.push_back(userData);
        }
        inFile.close();

        if (!ditemukan) {
            cout << "NIK atau jawaban clue keamanan yang anda masukkan tidak cocok.\n\n";
            lupaPassword();
        }

        ofstream outFile("file/akun_pengguna.txt");
        if (outFile.is_open()) {
            for (const auto& userData : updatedUsersData) {
                outFile << userData.nik << "|" << userData.password << "|" << userData.namalengkap << "|" << userData.tanggallahir << "|" << userData.alamat << "|" << userData.clueKeamanan << endl;
            }
            outFile.close();
            system("cls");
            cout << " ------------------------------ Password Berhasil Diganti! ----------------------------------------- \n\n";
        } else {
            system("cls");
            cout << "Gagal mengganti password.\n";
        }
    } else {
        system("cls");
        cout << "Gagal mengakses penyimpanan data.\n";
    }
}

void registrasi() {
    UserData userData;

    cout << " ==================================== Halaman Registrasi ============================================ \n";
    cout << " ---------------------------------- Lengkapi Data Diri Anda ----------------------------------------- \n\n";
    cout << "NIK : ";
    cin >> userData.nik; 
    while(userData.nik.length() != 16) {
        system("cls");
        cout << "NIK yang anda masukkan tidak valid. Silakan masukkan lagi.\n";
        cout << "NIK : ";
        cin >> userData.nik;
    }

    for (const auto& user : usersData) {
        if (user.nik == userData.nik) {
            system("cls");
            cout << "NIK yang anda masukkan sudah terdaftar. Registrasi tidak dapat dilakukan lagi.\n SIlahkan lakukan Login.\n\n";
            return; 
        }
    }

    cout << "Nama Lengkap : ";
    cin.ignore();
    getline(cin, userData.namalengkap);
    cout << "Tanggal Lahir (dd/mm/yyyy) : ";
    cin >> userData.tanggallahir;
    cout << "Alamat Rumah : ";
    cin.ignore();
    getline(cin, userData.alamat);
    cout << "Masukkan Password : ";
    cin >> userData.password;

    cout << "Membuat Clue Keamanan\n";
    cout << "Note : Clue keamanan ini akan digunakan jika anda lupa password pada suatu saat. Isi dengan yang mudah diingat oleh anda!\n\n";
    cout << "Masukkan Clue Keamanan Anda : ";
    cin.ignore();
    getline(cin, userData.clueKeamanan);

    usersData.push_back(userData);

    simpanDataPasien();
}

bool login(string& nik, string& namalengkap, string& tanggallahir, string& alamat, string& password) {
    bool cek = false;

    cout << " ======================================= Halaman Login ============================================== \n";
    cout << " ------------------------------- Masukkan NIK dan Password Anda ------------------------------------- \n\n";

    cout << "Masukkan NIK : ";
    cin >> nik;
    cout << "Masukkan Password : ";
    cin >> password;

    ifstream input("file/akun_pengguna.txt");
    if (input.is_open()) {
        string line;
        while (getline(input, line)) {
            stringstream ss(line);
            UserData userData;

            getline(ss, userData.nik, '|');
            getline(ss, userData.password, '|');
            getline(ss, userData.namalengkap, '|');
            getline(ss, userData.tanggallahir, '|');
            getline(ss, userData.alamat, '|');
            getline(ss, userData.clueKeamanan);

            if (nik == userData.nik && password == userData.password) {
                cek = true;
                namalengkap = userData.namalengkap;
                tanggallahir = userData.tanggallahir;
                alamat = userData.alamat;
                break;
            }
        }
        input.close();

        if (cek) {
            system("cls");
            cout << "|| -------------------------------------- Login Berhasil! -------------------------------------------- ||\n\n";
            return true;
        } else {
            system("cls");
            cout << "Login gagal, cek kembali NIK dan password Anda.\n\n";
            return false;
        }
    } else {
        system("cls");
        cout << "Gagal mengakses penyimpanan data.\n";
        return false;
    }
}


