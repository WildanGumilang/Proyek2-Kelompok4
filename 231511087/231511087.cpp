#include "231511087.h"
#include "../231511067/231511067.h"
#include "../231511082/231511082.h"

void simpanDataPasien(const UserData& userData) {
    ofstream outFile("file/akun_pengguna.txt", ios::app);
    if (outFile.is_open()) {
        outFile << userData.nik << "|" << userData.password << "|" << userData.namalengkap << "|" << userData.tanggallahir << "|" << userData.alamat << "|" << userData.clueKeamanan << endl;
        outFile.close();
        system("cls");
        cout << "Data Berhasil Disimpan.\n\n";
    } else {
        system("cls");
        cout << "Gagal menyimpan data.\n";
    }
}

void lupaPassword() {

    string nik, jawaban;
    bool ditemukan = false;

    cout << " ====================================== Halaman Lupa Password ========================================== \n";
    cout << " ------------------------------- Masukkan NIK dan Jawaban Clue Keamanan -------------------------------- \n\n";
    cout << "Masukkan NIK : ";
    cin >> nik;
    nik = hill_cipher_encrypt(nik);
    cout << "Masukkan Jawaban Clue Keamanan : ";
    cin.ignore();
    getline(cin, jawaban);
    jawaban = hill_cipher_encrypt(jawaban);


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
                userData.password = hill_cipher_encrypt(userData.password);
                ditemukan = true;
            }

            updatedUsersData.push_back(userData);
        }
        inFile.close();

        if (!ditemukan) {
            cout << "NIK atau clue keamanan yang anda masukkan tidak cocok.\n\n";
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

    cout << " ==================================== Halaman Registrasi ============================================ \n\n";
    cout << " ---------------------------------- Lengkapi Data Diri Anda ----------------------------------------- \n\n";
    cout << "NIK : ";
    cin >> userData.nik; 

    while(userData.nik.length() != 16) {
        system("cls");
        cout << "NIK yang anda masukkan tidak valid. Silakan masukkan lagi.\n";
        cout << "NIK : ";
        cin >> userData.nik;
    }

    userData.nik = hill_cipher_encrypt(userData.nik);

    ifstream inFile("file/akun_pengguna.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string nik;
            getline(ss, nik, '|');
            if (nik == userData.nik) {
                system("cls");
                cout << "NIK yang anda masukkan sudah terdaftar. Registrasi tidak dapat dilakukan lagi.\n SIlahkan lakukan Login.\n\n";
                inFile.close();
                return; 
            }
        }
        inFile.close();
    }

    cout << "Nama Lengkap : ";
    cin.ignore();
    getline(cin, userData.namalengkap);
    userData.namalengkap = hill_cipher_encrypt(userData.namalengkap);
    cout << "Tanggal Lahir (dd/mm/yyyy) : ";
    cin >> userData.tanggallahir;
    userData.tanggallahir = hill_cipher_encrypt(userData.tanggallahir);
    cout << "Alamat Rumah : ";
    cin.ignore();
    getline(cin, userData.alamat);
    userData.alamat = hill_cipher_encrypt(userData.alamat);
    cout << "Masukkan Password : ";
    getline(cin, userData.password);
    userData.password = hill_cipher_encrypt(userData.password);

    cout << "Membuat Clue Keamanan\n";
    cout << "Note : Clue keamanan ini akan digunakan jika anda lupa password pada suatu saat. Isi dengan yang mudah diingat oleh anda!\n\n";
    cout << "Masukkan Clue Keamanan Anda : ";
    cin.ignore();
    getline(cin, userData.clueKeamanan);
    userData.clueKeamanan = hill_cipher_encrypt(userData.clueKeamanan);
    
    // Simpan data pengguna yang telah dienkripsi ke dalam file
    simpanDataPasien(userData);
}



bool login(string& nik, string& namalengkap, string& tanggallahir, string& alamat, string& password) {

    bool cek = false;

    cout << " ======================================= Halaman Login ============================================== \n";
    cout << " ------------------------------- Masukkan NIK dan Password Anda ------------------------------------- \n\n";

    cout << "Masukkan NIK : ";
    cin >> nik;
    while(nik.length() != 16) {
        system("cls");
        cout << "NIK yang anda masukkan tidak valid. Silakan masukkan lagi.\n";
        cout << "NIK : ";
        cin >> nik;

    }
    nik = hill_cipher_encrypt(nik);

    cout << "Masukkan Password : ";
    cin >> password;
    password = hill_cipher_encrypt(password);

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
                
                nik = hill_cipher_decrypt(nik);
                password = hill_cipher_decrypt(password);
                namalengkap = hill_cipher_decrypt(namalengkap);
                tanggallahir = hill_cipher_decrypt(tanggallahir);
                alamat = hill_cipher_decrypt(alamat);
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


//Fungsi Login Admin

bool loginAdmin(string& namaAdmin) {
    string nomorAdmin, password; 
    bool cek = false;
    int key[2][2] = {
        {31, 59},
        {17, 92}
    };
    char decrypted_text[100];
    char encrypted_text[100];

    cout << " ======================================= Halaman Login Admin ======================================== \n";
    cout << " ----------------------------------- Masukkan Nomor Admin dan Password -------------------------------- \n\n";

    cout << "Masukkan Nomor Admin : ";
    cin >> nomorAdmin;
    while(nomorAdmin.length() != 6) {
        system("cls");
        cout << "NIK yang anda masukkan tidak valid. Silakan masukkan lagi.\n";
        cout << "Nomor Admin : ";
        cin >> nomorAdmin;
    }
    
    nomorAdmin = hill_cipher_encrypt(nomorAdmin);

    cout << "Masukkan Password : ";
    cin >> password;
    password = hill_cipher_encrypt(password);

    ifstream input("file/akun_admin.txt");
    if (input.is_open()) {
        string line;
        while (getline(input, line)) {
            stringstream ss(line);
            AdminData adminData;

            getline(ss, adminData.nomorAdmin, '|');
            getline(ss, adminData.namaAdmin, '|');
            getline(ss, adminData.password);
            if (nomorAdmin == adminData.nomorAdmin && password == adminData.password) {
                cek = true;
                namaAdmin = adminData.namaAdmin;

                namaAdmin = hill_cipher_decrypt(namaAdmin);
                break;
            }
        }
        input.close();

        if (cek) {
            system("cls");
            cout << "|| ----------------------------------------- Login Berhasil! --------------------------------------- ||\n\n";
            return true;
        } else {
            system("cls");
            cout << "Login Admin gagal, cek kembali Nomor Admin dan password Anda.\n\n";
            return false;
        }
    } else {
        system("cls");
        cout << "Gagal mengakses penyimpanan data.\n";
        return false;
    }
}