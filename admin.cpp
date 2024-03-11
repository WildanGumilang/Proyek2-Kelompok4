#include "231511087/231511087.h"

using namespace std;

int main() {
    int pilihan;
    string namaAdmin, passwordAdmin, nomorAdmin;
    bool loginBerhasil = false;

    //HALAMAN AWAL

    while (true) {
        if (!loginBerhasil) {     
            cout << "|| ====================================== RUMAH SAKIT JTK ============================================ ||\n";
            cout << "||                                                                                                     ||\n";
            cout << "||                     --- Jl. Komputer, Kampus Politeknik Negeri Bandung ---                          ||\n";
            cout << "||                        --- Ciwaruga, Parongpong, Kab. Bandung Barat ---                             ||\n";
            cout << "||                                                                                                     ||\n";
            cout << "|| ============================================ MENU ================================================= ||\n";
            cout << "||                                                                                                     ||\n";
            cout << "||     1. Login                                                                                        ||\n";
            cout << "||     2. KELUAR                                                                                       ||\n";
            cout << "||                                                                                                     ||\n";
            cout << "|| =================================================================================================== ||\n\n";
            cout << "Pilihan anda : ";
            cin >> pilihan;
            cout << endl;

            switch (pilihan) 
            {
                case 1:
                    // HALAMAN LOGIN
                    system("cls");
                    loginBerhasil = loginAdmin(namaAdmin, passwordAdmin, nomorAdmin);
                    break;
                case 2:
                    // KELUAR
                    system("cls");
                    cout << "\t\t\t TerimaKasih Telah Memakai Aplikasi Ini! \n\n";
                    return 0;
                default:
                    system("cls");
                    cout << "Mohon pilih salah satu pilihan diatas!\n\n";
            }
        } else {

        // HALAMAN UTAMA
            cout << "|| ====================================== RUMAH SAKIT JTK ============================================ ||\n";
            cout << "                                                                                                         \n";
            cout << "                              Halo, " << namaAdmin << "                                                \n";
            cout << "                                                                                                         \n";
            cout << "|| ============================================ MENU ================================================= ||\n";
            cout << "||                                                                                                     ||\n";
            cout << "||     1. Melihat Data Pasien                                                                          ||\n";
            cout << "||     2. Melihat Data Pendaftaran Pemeriksaan                                                         ||\n";
            cout << "||     3. Ganti Password Akun                                                                          ||\n";
            cout << "||     4. KELUAR                                                                                       ||\n";
            cout << "||                                                                                                     ||\n";
            cout << "|| =================================================================================================== ||\n\n";
            cout << "Pilihan anda : ";
            cin >> pilihan;
            switch (pilihan) {
                case 1:
                    system("cls");
                    // HALAMAN MENAMPILKAN DATA PASIEN
                    // dataPasien();
                    break;
                case 2:
                    system("cls");
                    // HALAMAN MENAMPILKAN DATA PENDAFTARAN PASIEN
                    // melihatDataPendaftaran();
                    break;
                case 3:
                    system("cls");
                    //HALAMAN GANTI PASSWORD
                    gantiPasswordAdmin();
                    break;
                case 4:
                    // KELUAR
                    cout << "Terima kasih telah menggunakan layanan kami.\n";
                    return 0;
                default:
                    cout << "Pilihan tidak valid. Silakan masukkan pilihan antara 1-4.\n";
            }
        }
    }
    return 0;
}
