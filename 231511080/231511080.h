#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct UserInput {
    string nik;
    string namalengkap;
    string tanggallahir;
    string tanggalperiksa;
    string pilihandokter;
    string carabayar;
    string nomorbpjs;
};

void tampilkanPilihanDokter() {
    cout << "|| ============================= Pilihan Dokter ================================= ||\n\n";
    cout << "Pilih dokter yang Anda inginkan:\n";
    cout << "1. Dr. Wildan Gumilang (Dokter Umum)\n";
    cout << "2. Dr. Daffa Tridya (Spesialis Jantung)\n";
    cout << "3. Dr. Agra Anisa (Spesialis Anak)\n\n\n";
}

void tampilkanPilihanCaraBayar() {
    cout << "\n\n|| ============================= Pilihan Cara Bayar ============================= ||\n\n";
    cout << "Pilih cara pembayaran:\n";
    cout << "1. BPJS Kesehatan\n";
    cout << "2. Pembayaran Reguler\n\n\n";
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
