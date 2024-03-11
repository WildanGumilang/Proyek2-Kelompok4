#include "231511081.cpp"
using namespace std;

// Fungsi untuk mengambil informasi pasien dari file daftarperiksa.txt
void ambilInformasiPasien(const string& nik, UserInfo& user);

// Fungsi untuk mengirim hasil pemeriksaan dari dokter ke pasien
void kirimHasilPemeriksaan(const UserInfo& user, const string& hasilPemeriksaan, const string& resepObat);

int main() {
    // Contoh penggunaan untuk dokter
    string nik, hasilPemeriksaan, resepObat;
    UserInfo pasien;
    
    // Input NIK pasien yang akan diperiksa
    cout << "Masukkan NIK pasien: ";
    getline(cin, nik);

    // Mengambil informasi pasien dari file
    ambilInformasiPasien(nik, pasien);
    
    // Input hasil pemeriksaan dan resep obat oleh dokter
    cout << "Masukkan hasil pemeriksaan: ";
    getline(cin, hasilPemeriksaan);
    cout << "Masukkan resep obat: ";
    getline(cin, resepObat);
    
    // Mengirim hasil pemeriksaan ke pasien oleh dokter
    kirimHasilPemeriksaan(pasien, hasilPemeriksaan, resepObat);

    return 0;
}
