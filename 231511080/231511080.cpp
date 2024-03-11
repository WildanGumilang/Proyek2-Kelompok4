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
    string nomorbpjs;
};

void tampilkanPilihanDokter() {
    cout << "\n\n|| ============================= Pilihan Dokter ================================= ||\n\n";
    cout << "Pilih dokter yang Anda inginkan:\n";
    cout << "1. Dr. Wildan Gumilang (Dokter Umum)\n";
    cout << "2. Dr. Daffa Tridya (Spesialis Jantung)\n";
    cout << "3. Dr. Agra Anisa (Spesialis Anak)\n\n";
}

void tampilkanPilihanCaraBayar() {
    cout << "\n\n|| ============================= Pilihan Cara Bayar ============================= ||\n\n";
    cout << "Pilih cara pembayaran:\n";
    cout << "1. BPJS Kesehatan\n";
    cout << "2. Pembayaran Reguler\n\n";
}

void ambilInformasiPasien(const string& nik, UserInput& user) {
    ifstream inFile("akun_pengguna.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            string currentNik = line.substr(0, line.find('|'));
            if (currentNik == nik) {
                // Jika NIK pasien cocok, mengisi informasi pasien dari file
                user.nik = currentNik;
                size_t pos = line.find('|', currentNik.length() + 1);
                user.namalengkap = line.substr(currentNik.length() + 1, pos - currentNik.length() - 1);
                pos = line.find('|', pos + 1);
                user.tanggallahir = line.substr(pos + 1);
                break;
            }
        }
        inFile.close();
    } else {
        cout << "Gagal membuka file akun_pengguna.txt." << endl;
    }
}

void kirimDaftarPeriksa(const UserInput& input) {
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
    outfile << "Nomor BPJS: " << input.nomorbpjs << endl;
    outfile << "---------------------------------------" << endl;

    outfile.close();
}


void ambilDataAkunPengguna(UserInput& input) {

    cout << "|| ===================================== DAFTAR PERIKSA RUMAH SAKIT JTK ==================================== ||\n\n";
    cout << "-------------------------------------------------------------------------------------------------------------\n";
    cout << "-------------------------------------------------------------------------------------------------------------\n\n";



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

