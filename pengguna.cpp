#include "231511087/231511087.h"
#include "231511067/231511067.h"
#include "231511080/231511080.h"
#include "231511081/231511081.h"
#include "231511082/231511082.h"
using namespace std;

int main() {
    int pilihan;
    string nik, password, namalengkap, tanggallahir, alamat;
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
            cout << "||     1. Registrasi                                                                                   ||\n";
            cout << "||     2. Login                                                                                        ||\n";
            cout << "||     3. Lupa Password                                                                                ||\n";
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
                    // HALAMAN LOGIN
                    system("cls");
                    lupaPassword();
                    break;
                case 4:
                    system("cls");
                    cout << "\t\t\t TerimaKasih Telah Memakai Aplikasi Ini! \n\n";
                    return 0;
                    break;
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
            cout << "||     1. Melihat Data Pribadi Anda                                                                    ||\n";            
            cout << "||     2. Mendaftar Untuk Pemeriksaan                                                                  ||\n";
            cout << "||     3. Melihat Riwayat Hasil Pemeriksaan                                                            ||\n";
            cout << "||     4. KELUAR                                                                                       ||\n";
            cout << "||                                                                                                     ||\n";
            cout << "|| =================================================================================================== ||\n\n";
            cout << "Pilihan anda : ";
            cin >> pilihan;
            switch (pilihan) {
                case 1:
                    system("cls");
                    // HALAMAN DATAPASIEN
                    tampilkanDataPasienByNIK(nik);
                    break;
                case 2:
                    system("cls");
                    // HALAMAN PENDAFTARAN
                    pendaftaranPeriksa(nik, namalengkap, tanggallahir);
                    break;
                case 3:
                    system("cls");
                    // HALAMAN HASIL PERIKSA
                    tampilkanSuratHasilPemeriksaan(nik);
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
