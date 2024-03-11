#include "231511087/231511087.h"

using namespace std;

int main() {
    int pilihan;
    string nik, password, namalengkap, tanggallahir, alamat;
    bool loginBerhasil = false;

    //HALAMAN AWAL

    bacaDataPasien();

    while (true) {
        if (!loginBerhasil) {     
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
                    // HALAMAN REGISTRASI
                    system("cls");
                    registrasi();
                    break;
                case 2:
                    // HALAMAN LOGIN
                    system("cls");
                    loginBerhasil = login(nik, namalengkap, tanggallahir, alamat, password);
                    break;
                case 3:
                    system("cls");
                    // HALAMAN LUPAPASSWORD
                    lupaPassword();
                    break;
                case 4:
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
            cout << "                              Halo, " << namalengkap << "                                                \n";
            cout << "                                                                                                         \n";
            cout << "|| ============================================ MENU ================================================= ||\n";
            cout << "||                                                                                                     ||\n";
            cout << "||     1. Mendaftar Untuk Pemeriksaan                                                                  ||\n";
            cout << "||     2. Melihat Riwayat Hasil Pemeriksaan                                                            ||\n";
            cout << "||     3. Ganti Password Akun                                                                          ||\n";
            cout << "||     4. KELUAR                                                                                       ||\n";
            cout << "||                                                                                                     ||\n";
            cout << "|| =================================================================================================== ||\n\n";
            cout << "Pilihan anda : ";
            cin >> pilihan;
            switch (pilihan) {
                case 1:
                    system("cls");
                    // HALAMAN PENDAFTARAN
                    // mendaftarPemeriksaan();
                    break;
                case 2:
                    system("cls");
                    // HALAMAN PENDAFTARAN
                    // melihatRiwayatPemeriksaan();
                    break;
                case 3:
                    system("cls");
                    //HALAMAN GANTI PASSWORD
                    gantipassword();
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
