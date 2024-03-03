#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Definisi struct UserInfo
struct UserInfo {
    string nik;
    string namalengkap;
    string tanggallahir;
    string tanggalperiksa;
    int pilihandokter;
    int carabayar;
};

// Fungsi untuk mengambil informasi pasien dari file daftarperiksa.txt
void ambilInformasiPasien(const string& nik, UserInfo& user) {
    ifstream inFile("daftarperiksa.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            string currentNik = line.substr(0, line.find(','));
            if (currentNik == nik) {
                // Jika NIK pasien cocok, mengisi informasi pasien dari file
                user.nik = currentNik;
                user.namalengkap = line.substr(line.find(',') + 1);
                getline(inFile, user.tanggallahir);
                getline(inFile, user.tanggalperiksa);
                inFile >> user.pilihandokter;
                inFile >> user.carabayar;
                break;
            }
        }
        inFile.close();
    } else {
        cout << "Gagal membuka file daftarperiksa.txt." << endl;
    }
}

// Fungsi untuk mengirim hasil pemeriksaan dari dokter ke pasien
void kirimHasilPemeriksaan(const UserInfo& user, const string& hasilPemeriksaan, const string& resepObat) {
    // Membuka file daftarperiksa.txt untuk menambahkan hasil pemeriksaan
    ofstream outFile("daftarperiksa.txt", ios::app);
    if (outFile.is_open()) {
        // Menambahkan hasil pemeriksaan ke file
        outFile << user.nik << "," << user.tanggalperiksa << "," << hasilPemeriksaan << "," << resepObat << endl;
        outFile.close();
        cout << "Hasil pemeriksaan berhasil dikirim ke pasien." << endl;
    } else {
        cout << "Gagal membuka file daftarperiksa.txt." << endl;
    }
}

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