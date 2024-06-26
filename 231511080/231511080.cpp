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
bool pendaftaranPeriksa(const string& nik, const string& namalengkap, const string& tanggallahir, tAddr awalT, kAddr awalK, kAddr awalKinv) {
    userDaftar pendaftaran;

    // Isi data pendaftaran
    pendaftaran.nomorPendaftaran = generateNomorPendaftaran();
    pendaftaran.nomorPendaftaran = hill_cipher_encrypt(pendaftaran.nomorPendaftaran, awalT, awalK);
    pendaftaran.nik = nik;
    pendaftaran.nik = hill_cipher_encrypt(pendaftaran.nik, awalT, awalK);
    pendaftaran.namalengkap = namalengkap;
    // pendaftaran.namalengkap = hill_cipher_encrypt(pendaftaran.namalengkap, awalT, awalK);
    pendaftaran.tanggallahir = tanggallahir;
    pendaftaran.tanggallahir = hill_cipher_encrypt(pendaftaran.tanggallahir, awalT, awalK);

    // Input data tambahan
    cout << "Masukkan Tanggal Periksa (dd/mm/yyyy): ";
    cin >> pendaftaran.tanggalperiksa;
    while (pendaftaran.tanggalperiksa.find('|') != string::npos) {
        cout << "Pastikan tidak menggunakan simbol '|'. Silahkan masukkan lagi.\n";
        cout << "Masukkan Tanggal Periksa (dd/mm/yyyy): ";
        cin >> pendaftaran.tanggalperiksa;
    }
    
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
            pendaftaran.pilihandokter = "Dr. Daffa Tridya (Spesialis Jantung)";
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
            pendaftaran.carabayar = hill_cipher_encrypt(pendaftaran.carabayar, awalT, awalK);
            break;
        case 2:
            pendaftaran.carabayar = "Pembayaran Reguler";
            pendaftaran.carabayar = hill_cipher_encrypt(pendaftaran.carabayar, awalT, awalK);
            break;
        default:
            cout << "Pilihan cara pembayaran tidak valid. Memilih secara default Pembayaran Reguler.\n";
            pendaftaran.carabayar = "Pembayaran Reguler";
            pendaftaran.carabayar = hill_cipher_encrypt(pendaftaran.carabayar, awalT, awalK);
            break;
    }

    // Untuk sorting dalam file, dengan membaca isi file dan menjadikan linked list
    dfAddr awalD = nullptr;
    dfAddr akhirD = nullptr;
    ifstream myFile("file/daftarperiksa.txt");
    if (myFile.is_open()) {
        string line;
        while (getline(myFile, line)) {
            stringstream ss(line);
            userDaftar data;
            getline(ss, data.nomorPendaftaran, '|');
            getline(ss, data.nik, '|');
            getline(ss, data.namalengkap, '|');
            getline(ss, data.tanggallahir, '|');
            getline(ss, data.tanggalperiksa, '|');
            getline(ss, data.pilihandokter, '|');
            getline(ss, data.carabayar);
            data.next = nullptr;

            data.namalengkap = hill_cipher_decrypt(data.namalengkap, awalT, awalKinv);

            insertUserDaftar(data, awalD, akhirD);
        }
        myFile.close();
    } else {
        cout << "Gagal membuka file untuk dijadikan LL" << endl;
    }

    // cout << "LL insert akhir :" << endl;
    // cetakListUserDaftar(awalD);
    // system("pause");

    insertTengahUserDaftar(pendaftaran, awalD, akhirD);

    // cout << "LL insert tengah :" << endl;
    // cetakListUserDaftar(awalD);
    // system("pause");

    // Tulis ulang data ke file
    ofstream outFile("file/daftarperiksa.txt", ios::trunc);
    if (outFile.is_open()) {
        dfAddr current = awalD;
        while (current != nullptr) {
            current->namalengkap = hill_cipher_encrypt(current->namalengkap, awalT, awalK);
            outFile << current->nomorPendaftaran << "|" << current->nik << "|" << current->namalengkap << "|" << current->tanggallahir << "|" << current->tanggalperiksa << "|" << current->pilihandokter << "|" << current->carabayar << endl;
            current = current->next;
        }
        outFile.close();
        system("cls");
        cout << "Pendaftaran berhasil disimpan.\n\n";
        hapusLinkedListUserDaftar(awalD);
        return true;
    } else {
        system("cls");
        cout << "Gagal menyimpan data pendaftaran.\n";
        hapusLinkedListUserDaftar(awalD);
        return false;
    }
}

// Menampilkan data pendaftaran periksa
void tampilkanDataPeriksa(tAddr awalT, kAddr awalKinv) {
    userDaftar pendaftaran;

    ifstream inFile("file/daftarperiksa.txt");
    if (inFile.is_open()) {
        cout << "==================================================================================================================" << endl;
        cout << "                                SELURUH DATA PENDAFTARAN PERIKSA                                     " << endl;
        cout << "==================================================================================================================" << endl;
        cout << "No.Pendaftaran\tNama Lengkap\tNIK\tTanggal Lahir\tTanggal Periksa\tPilihan Dokter\tCara Bayar" << endl;
        cout << "------------------------------------------------------------------------------------------------------------------" << endl;

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

            nomorPendaftaran = hill_cipher_decrypt(nomorPendaftaran, awalT, awalKinv);
            nik = hill_cipher_decrypt(nik, awalT, awalKinv);
            namalengkap = hill_cipher_decrypt(namalengkap, awalT, awalKinv);
            tanggallahir = hill_cipher_decrypt(tanggallahir, awalT, awalKinv);
            carabayar = hill_cipher_decrypt(carabayar, awalT, awalKinv);            

            cout << nomorPendaftaran << "\t" << namalengkap << "\t" << nik << "\t" << tanggallahir << "\t" << tanggalperiksa << "\t" << pilihandokter << "\t" << carabayar << endl;
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

// fungsi untuk menghapus karakter 1 (berarti karakter string genap) atau 0 (berarti karakter string ganjil) diakhir string padasaat membaca dari file, chekjumlah true jika string genap, dan sebaliknya
string chekAndDelLastBool(string str, bool& chekJumlah) {
    int panjang = str.length();
    if (panjang > 0) {
        char akhir = str[panjang - 1];
        if (akhir == '1') {
            str.pop_back(); // Hapus karakter '1' dari akhir string
            chekJumlah = true;
        } else if (akhir == '0') {
            str.pop_back(); // Hapus karakter '0' dari akhir string
            chekJumlah = false;
        }
    }
    return str; // Jika tidak ada '1' atau '0' di akhir string
}

// fungsi untuk menghapus karakter akhir pada string jika chekjumlah tadi bernilai false
string deleteLastBool(string str, bool chekJumlah) {
    if (!chekJumlah && !str.empty()) {
        str.pop_back(); // Hapus karakter terakhir dari string
    }
    return str;
}

bool insertUserDaftar(const userDaftar& data, dfAddr& awal, dfAddr& akhir) {
    dfAddr newNode = new userDaftar;
    if (newNode != nullptr) {
        *newNode = data;
        newNode->next = nullptr;
        if (awal == nullptr) {
            awal = newNode;
        } else {
            akhir->next = newNode;
        }
        akhir = newNode;
        return true;
    } else {
        cout << "Alokasi memori gagal. Tidak dapat menyisipkan node baru." << endl;
        return false;
    }
}