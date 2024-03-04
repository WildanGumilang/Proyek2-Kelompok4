//modul untuk registrasi dan login

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct UserData {
    string nik;
    string password;
    string namalengkap;
    string tanggallahir;
    string alamat;

};
void registrasi();
void login();


int main() {
    int pilihan;

    cout << "\t\t\t|| ====================================== RUMAH SAKIT JTK ============================================ ||\n";
    cout << "\t\t\t||                                                                                                     ||\n";
    cout << "\t\t\t||                     --- Jl. Komputer, Kampus Politeknik Negeri Bandung ---                          ||\n";
    cout << "\t\t\t||                        --- Ciwaruga, Parongpong, Kab. Bandung Barat ---                             ||\n";
    cout << "\t\t\t||                                                                                                     ||\n";
    cout << "\t\t\t|| ============================================ MENU ================================================= ||\n";
    cout << "\t\t\t||                                                                                                     ||\n";
    cout << "\t\t\t||     1. Registrasi                                                                                   ||\n";
    cout << "\t\t\t||     2. Login                                                                                        ||\n";
    cout << "\t\t\t||     3. KELUAR                                                                                       ||\n";
    cout << "\t\t\t||                                                                                                     ||\n";    
    cout << "\t\t\t|| =================================================================================================== ||\n\n";
    cout << "Note : Jika anda belum memiliki akun, silahkan lakukan REGISTRASI terlebih dahulu.\n\n";
    cout << "Pilihan anda : ";
    cin >> pilihan;
    cout << endl;

    switch (pilihan) 
    {
        case 1:
            system("cls");
            registrasi();
            break;
        case 2:
            system("cls");
            login();
            break;
        case 3:
            system("cls");
            cout << "\t\t\t TerimaKasih Telah Memakai Aplikasi Ini! \n\n";
            break;
        default:
            system("cls");
            cout << "Mohon pilih salah satu pilihan diatas!\n\n";
            main();
    }
    return 0;
}


void registrasi() {
    UserData userData;

    cout << "\t\t\t|| ==================================== Halaman Registrasi ============================================ ||\n";
    cout << "\t\t\t|| ---------------------------------- Lengkapi Data Diri Anda ----------------------------------------- ||\n\n";
    cout << "NIK : ";
    cin >> userData.nik; 
    while(userData.nik.length() != 16) {
        cout << "NIK yang anda masukkan tidak valid. Silakan masukkan lagi: \n";
        cin >> userData.nik;
    }
    cout << "Nama Lengkap : ";
    cin >> userData.namalengkap;
    cout << "Tanggal Lahir (dd/mm/yyyy) : ";
    cin >> userData.tanggallahir;
    cout << "Alamat Rumah : ";
    cin >> userData.alamat;

    cout << "Masukkan Password : ";
    cin >> userData.password;

    //mengenkripsi

    // Menyimpan data pengguna ke dalam file
    ofstream outFile("akun_pengguna.txt", ios::app);
    if (outFile.is_open()) {
        outFile << userData.nik << " " << userData.password << " " << userData.namalengkap << " " << userData.tanggallahir << " " << userData.alamat << endl;
        outFile.close();
        system("cls");
    cout << "\t\t\t|| ----------------------------------- Registrasi Berhasil! ------------------------------------------ ||\n\n";
        main();
    } else {
        cout << "Gagal membuka file untuk menyimpan data.\n";
    }

    // Mengirim data ke admin (dapat ditambahkan fungsi lain sesuai kebutuhan)
}


void login() {
    string nik, password, storedNik, storedPassword, storedNamalengkap, storedTanggallahir, storedAlamat;
    bool cek = false;

    cout << "\t\t\t|| ======================================= Halaman Login ============================================== ||\n";
    cout << "\t\t\t|| ------------------------------- Masukkan NIK dan Password Anda ------------------------------------- ||\n\n";

    cout << "Masukkan NIK : ";
    cin >> nik;
    cout << "Masukkan Password : ";
    cin >> password;

    ifstream input("akun_pengguna.txt");
    if (input.is_open()) {
        while (input >> storedNik >> storedPassword >> storedNamalengkap >> storedTanggallahir >> storedAlamat) {
            if (nik == storedNik && password == storedPassword) {
                cek = true;
                break;
            }
        }
        input.close();

        if (cek) {
            system("cls");
    cout << "\t\t\t|| -------------------------------------- Login Berhasil! -------------------------------------------- ||\n\n";
            // MASUK KE HALAMAN UTAMA
        } else {
            cout << "\t\t\tLogin Anda gagal, cek kembali NIK dan password Anda.\n\n";
            login();
        }
    } else {
        cout << "Gagal membuka file akun_pengguna.txt.\n";
    }
}