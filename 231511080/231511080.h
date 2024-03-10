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

void tampilkanPilihanDokter() {
    cout << "|| ============================= Pilihan Dokter ================================= ||\n\n";
    cout << "Pilih dokter yang Anda inginkan:\n";
    cout << "1. Dr. Wildan Gumilang (Dokter Umum)\n";
    cout << "2. Dr. Daffa Tridya (Spesialis Jantung)\n";
    cout << "3. Dr. Agra Anisa (Spesialis Anak)\n";
}

void tampilkanPilihanCaraBayar() {
    cout << "\n\n|| ============================= Pilihan Cara Bayar ============================= ||\n\n";
    cout << "Pilih cara pembayaran:\n";
    cout << "1. BPJS Kesehatan\n";
    cout << "2. Pembayaran Reguler\n";
}

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

    cout << "|| ================================== DAFTAR PEMERIKSAAN RUMAH SAKIT JTK ================================= ||\n\n";
    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------" << endl;



    ifstream infile("akun_pengguna.txt");
    if (!infile) {
        cerr << "Gagal membuka file!" << endl;
        return;
    }

    getline(infile, input.nik, '|');
    getline(infile, input.namalengkap, '|');
    getline(infile, input.tanggallahir);

    infile.close();
}

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

    kirimDaftarPemeriksaan(input);

    cout << "\nDaftar Pemeriksaan:" << endl;
    menerimaDaftarPemeriksaan();

    return 0;
}
