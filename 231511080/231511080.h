#include "231511080.cpp"

using namespace std;

//fungsi-fungsi modul
void tampilkanPilihanDokter();
void tampilkanPilihanCaraBayar();
void ambilInformasiPasien(const string& nik, UserInput& user);
void kirimDaftarPeriksa(const UserInput& input);
void ambilDataAkunPengguna(UserInput& input);

int main() {
    UserInput input;


    //mengambil data akun pengguna
    ambilDataAkunPengguna(input);

    cout << "Masukkan tanggal periksa (dd/mm/yyyy): ";
    getline(cin, input.tanggalperiksa);

    //menampilkan dokter dan metode bayar
    tampilkanPilihanDokter();
    cout << "Masukkan pilihan dokter (1/2/3): ";
    cin >> input.pilihandokter;

    tampilkanPilihanCaraBayar();
    cout << "Masukkan cara bayar (1 untuk BPJS, 2 untuk reguler): ";
    cin >> input.carabayar;
    cout << "Masukkan nomor BPJS (jika ada): ";
    cin >> input.nomorbpjs;

    //mengirim daftar periksa pasien
    kirimDaftarPeriksa(input);

   
    return 0;
}
