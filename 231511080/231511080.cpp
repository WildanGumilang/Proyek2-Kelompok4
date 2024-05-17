#include "231511080.h"
#include "../231511067/231511067.h"
#include "../231511082/231511082.h"

// Variabel statis untuk nomor pendaftaran
static int nomorPendaftaran = 1;

// Fungsi untuk menghasilkan nomor pendaftaran acak
string generateNomorPendaftaran() {
    srand(time(0)); // Inisialisasi generator nomor acak dengan waktu saat ini
    int randomNumber = rand() % 900000 + 100000; // Menghasilkan nomor acak antara 100000 dan 999999
    return to_string(randomNumber); // Mengonversi nomor acak ke dalam string
}

// Fungsi untuk mengisi pendaftaran pemeriksaan
void pendaftaranPeriksa(const string& nik, const string& namalengkap, const string& tanggallahir) {
    userDaftar pendaftaran;

    // Isi data pendaftaran
    pendaftaran.nomorPendaftaran = generateNomorPendaftaran();
    pendaftaran.nomorPendaftaran = hill_cipher_encrypt(pendaftaran.nomorPendaftaran);
    pendaftaran.nik = nik;
    pendaftaran.nik = hill_cipher_encrypt(pendaftaran.nik);
    pendaftaran.namalengkap = namalengkap;
    pendaftaran.namalengkap = hill_cipher_encrypt(pendaftaran.namalengkap);
    pendaftaran.tanggallahir = tanggallahir;
    pendaftaran.tanggallahir = hill_cipher_encrypt(pendaftaran.tanggallahir);

    // Input data tambahan
    cout << "Masukkan Tanggal Periksa (dd/mm/yyyy): ";
    cin >> pendaftaran.tanggalperiksa;

    // Pilihan dokter
    cout << "Pilih dokter yang Anda inginkan:\n";
    cout << "1. Dr. Wildan Gumilang (Dokter Umum)\n";
    cout << "2. Dr. Daffa Tridya (Spesialis Jantung)\n";
    cout << "3. Dr. Agra Anisa (Spesialis Anak)\n";
    int dokter;
    cout << "Pilihan Anda: ";
    cin >> dokter;
    switch (dokter) {
        case 1:
            pendaftaran.pilihandokter = "Dr. Wildan Gumilang (Dokter Umum)";
            break;
        case 2:
            pendaftaran.pilihandokter = "Dr. Daffa Tridya (Spesialis Melahirkan)";
            break;
        case 3:
            pendaftaran.pilihandokter = "Dr. Agra Anisa (Spesialis Anak)";
            break;
        default:
            cout << "Pilihan dokter tidak valid. Memilih secara default Dokter Umum.\n";
            pendaftaran.pilihandokter = "Dr. Wildan Gumilang (Dokter Umum)";
            break;
    }

    // Pilihan cara pembayaran
    cout << "\nPilih cara pembayaran:\n";
    cout << "1. BPJS Kesehatan\n";
    cout << "2. Pembayaran Reguler\n";
    int bayar;
    cout << "Pilihan Anda: ";
    cin >> bayar;
    switch (bayar) {
        case 1:
            pendaftaran.carabayar = "BPJS Kesehatan";
            pendaftaran.carabayar = hill_cipher_encrypt(pendaftaran.carabayar);
            break;
        case 2:
            pendaftaran.carabayar = "Pembayaran Reguler";
            pendaftaran.carabayar = hill_cipher_encrypt(pendaftaran.carabayar);
            break;
        default:
            cout << "Pilihan cara pembayaran tidak valid. Memilih secara default Pembayaran Reguler.\n";
            pendaftaran.carabayar = "Pembayaran Reguler";
            pendaftaran.carabayar = hill_cipher_encrypt(pendaftaran.carabayar);
            break;
    }

    // Simpan data ke dalam file
    ofstream outFile("file/daftarperiksa.txt", ios::app); // Mode append agar tidak menghapus data yang sudah ada
    if (outFile.is_open()) {
        outFile << pendaftaran.nomorPendaftaran << "|" << pendaftaran.nik << "|" << pendaftaran.namalengkap << "|" << pendaftaran.tanggallahir << "|"
                << pendaftaran.tanggalperiksa << "|" << pendaftaran.pilihandokter << "|" << pendaftaran.carabayar << endl;
        outFile.close();
        cout << "Pendaftaran berhasil disimpan.\n";
    } else {
        cout << "Gagal menyimpan data pendaftaran.\n";
    }
}

// Menampilkan data pendaftaran periksa
void tampilkanDataPeriksa() {
    userDaftar pendaftaran;

    ifstream inFile("file/daftarperiksa.txt");
    if (inFile.is_open()) {
        cout << "===================================================================================================" << endl;
        cout << "                                SELURUH DATA PENDAFTARAN PERIKSA                                     " << endl;
        cout << "===================================================================================================" << endl;
        cout << "No. Pendaftaran\tNIK\tNama Lengkap\tTanggal Lahir\tTanggal Periksa\tPilihan Dokter\tCara Bayar" << endl;
        cout << "---------------------------------------------------------------------------------------------------" << endl;

        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string nomorPendaftaran, nik, namalengkap, tanggallahir, tanggalperiksa, pilihandokter, carabayar;
            getline(ss, nomorPendaftaran, '|');
            getline(ss, nik, '|');
            getline(ss, namalengkap, '|');
            getline(ss, tanggallahir, '|');
            getline(ss, tanggalperiksa, '|');
            getline(ss, pilihandokter, '|');
            getline(ss, carabayar);

            nomorPendaftaran = hill_cipher_decrypt(nomorPendaftaran);
            nik = hill_cipher_decrypt(nik);
            namalengkap = hill_cipher_decrypt(namalengkap);
            tanggallahir = hill_cipher_decrypt(tanggallahir);
            carabayar = hill_cipher_decrypt(carabayar);            

            cout << nomorPendaftaran << "\t" << nik << "\t" << namalengkap << "\t" << tanggallahir << "\t" << tanggalperiksa << "\t" << pilihandokter << "\t" << carabayar << endl;

        }
        cout << "===================================================================================================" << endl;
        inFile.close();
        
    } else {
        cout << "Gagal membuka file daftarperiksa.txt.\n";
    }
}

// fungsi untuk membuat node untuk linked list key
kAddr createNodeKey(int nilai) {
    kAddr newNode = new NodeK;
    if (newNode != nullptr) {
        newNode->info = nilai;
        newNode->nextrow = nullptr;
        newNode->nextcol = nullptr;
    } else {
        cout << "Alokasi memori gagal. Tidak dapat membuat node baru." << endl;
    }
    return newNode;
}

// fungsi untuk membuat linked list menjadi seperti matriks 2x2
kAddr buatLinkedListKey(int Key11, int Key12, int Key21, int Key22) {

    //membuat linked list yang merepresentasikan array 2 dimensi Key[2][2]
    kAddr key11 = createNodeKey(Key11);
    kAddr key12 = createNodeKey(Key12);
    kAddr key21 = createNodeKey(Key21);
    kAddr key22 = createNodeKey(Key22);

    //menghubungkan node secara horizontal
    key11->nextrow = key12;
    key21->nextrow = key22;

    //menghubungkan node secara vertikal
    key11->nextcol = key21;
    key12->nextcol = key22;

    return key11;
}