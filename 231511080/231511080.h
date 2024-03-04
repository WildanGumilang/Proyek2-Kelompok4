#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct UserInput {
    string nik;
    string namalengkap;
    string tanggallahir;
    string tanggalperiksa;
    int pilihandokter;
    int carabayar;
};

void kirimDaftarPemeriksaan(const UserInput& input) {
    ofstream outfile("daftarperiksa.txt", ios::app);
    if (!outfile) {
        cerr << "Gagal membuka file!" << endl;
        return;
    }

    outfile << "NIK: " << input.nik << endl;
    outfile << "Nama Lengkap: " << input.namalengkap << endl;
    outfile << "Tanggal Lahir: " << input.tanggallahir << endl;
    outfile << "Tanggal Periksa: " << input.tanggalperiksa << endl;
    outfile << "Pilihan Dokter: " << input.pilihandokter << endl;
    outfile << "Cara Bayar: " << input.carabayar << endl;
    outfile << "---------------------------------------" << endl;

    outfile.close();
}

void menerimaDaftarPemeriksaan() {
    ifstream infile("daftarperiksa.txt");
    if (!infile) {
        cerr << "Gagal membuka file!" << endl;
        return;
    }

    string line;
    while (getline(infile, line)) {
        cout << line << endl;
    }

    infile.close();
}

void ambilDataAkunPengguna(UserInput& input) {
    ifstream infile("akun_pengguna.txt");
    if (!infile) {
        cerr << "Gagal membuka file!" << endl;
        return;
    }

    getline(infile, input.nik);
    getline(infile, input.namalengkap);
    getline(infile, input.tanggallahir);

    infile.close();
}

int main() {
    UserInput input;

    // Mengambil data akun pengguna dari file
    ambilDataAkunPengguna(input);

    cout << "Masukkan tanggal periksa (dd/mm/yyyy): ";
    getline(cin, input.tanggalperiksa);
    cout << "Masukkan pilihan dokter (1/2/3): ";
    cin >> input.pilihandokter;
    cout << "Masukkan cara bayar (1 untuk BPJS, 2 untuk reguler): ";
    cin >> input.carabayar;

    // Kirim data pemeriksaan
    kirimDaftarPemeriksaan(input);

    // Menerima dan menampilkan daftar pemeriksaan
    cout << "\nDaftar Pemeriksaan:" << endl;
    menerimaDaftarPemeriksaan();

    return 0;
}
