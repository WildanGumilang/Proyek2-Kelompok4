#include "231511087/231511087.h"

using namespace std;

int main() {
    int pilihan;
    string nik, password, namalengkap, tanggallahir, alamat;

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
                main();
            case 2:
                system("cls");
                login(nik, namalengkap, tanggallahir, alamat, password);
                break;
            case 3:
                system("cls");
                lupaPassword();
                main();
            case 4:
                system("cls");
                // Saat keluar dari program, simpan data pengguna ke file
                simpanDataPasien();
                cout << "\t\t\t TerimaKasih Telah Memakai Aplikasi Ini! \n\n";
                return 0;
            default:
                system("cls");
                cout << "Mohon pilih salah satu pilihan diatas!\n\n";
        }

    system("cls");
    cout << "   ================================ Halo, " << namalengkap << "  ====================================== \n";
    
    }
    return 0;
}
