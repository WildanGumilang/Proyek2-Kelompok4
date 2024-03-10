#include <iostream>
#include "231511087.h"

using namespace std;

int main() {
    int pilihan;

    bacaDataPasien();

    while (true) {

        cout << "|| ====================================== RUMAH SAKIT JTK ============================================ ||\n";
        cout << "||                                                                                                     ||\n";
        cout << "||                     --- Jl. Komputer, Kampus Politeknik Negeri Bandung ---                          ||\n";
        cout << "||                        --- Ciwaruga, Parongpong, Kab. Bandung Barat ---                             ||\n";
        cout << "||                                                                                                     ||\n";
        cout << "|| ============================================ MENU ================================================= ||\n";
        cout << "||                                                                                                     ||\n";
        cout << "||     1. Registrasi                                                                                   ||\n";
        cout << "||     2. Login                                                                                        ||\n";
        cout << "||     3. Lupa Password Akun                                                                           ||\n";
        cout << "||     4. KELUAR                                                                                       ||\n";
        cout << "||                                                                                                     ||\n";
        cout << "|| =================================================================================================== ||\n\n";
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
                lupaPassword();
                break;
            case 4:
                system("cls");
                cout << "\t\t\t TerimaKasih Telah Memakai Aplikasi Ini! \n\n";
                // Saat keluar dari program, simpan data pengguna ke file
                simpanDataPasien();
                return 0;
            default:
                system("cls");
                cout << "Mohon pilih salah satu pilihan diatas!\n\n";
        }
    }

    return 0;
}