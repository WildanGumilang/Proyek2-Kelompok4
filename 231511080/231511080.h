#include <iostream>
#include <fstream> //untuk memproses file
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
    ofstream outfile("daftarperiksa.txt", ios::app); //membuka file untuk menambahkan data baru
    if (!outfile) {
        cerr << "Gagal membuka file!" << endl;
        return;
    }

    //menulis data pemeriksaan ke file
    outfile << "NIK: " << input.nik << endl;
    outfile << "Nama Lengkap: " << input.namalengkap << endl;
    outfile << "Tanggal Lahir: " << input.tanggallahir << endl;
    outfile << "Tanggal Periksa: " << input.tanggalperiksa << endl;
    outfile << "Pilihan Dokter: " << input.pilihandokter << endl;
    outfile << "Cara Bayar: " << input.carabayar << endl;
    outfile << "---------------------------------------" << endl;

    outfile.close(); //menutup file
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

    infile.close(); // Menutup file
}

int main() {
    UserInput input;

    // Mengisi data input
    input.nik = "1234567890";
    input.namalengkap = "John Doe";
    input.tanggallahir = "01-01-1990";
    cout << "Masukkan tanggal periksa: ";
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

 