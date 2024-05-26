#include "231511081.h"
#include "../231511067/231511067.h"
#include "../231511082/231511082.h"

// Fungsi untuk menyisipkan node baru di akhir linked list plainteks/cipherteks
bool insertAkhir(int nilai, pAddr& awal, pAddr& akhir) {
    pAddr p = new NodeP;
    if (p != nullptr) {
        p->info = nilai;
        p->next = nullptr;
        if (awal == nullptr && akhir == nullptr) {
            awal = p;
        } else {
            akhir->next = p;
        }
        akhir = p;
        return true; 
    } else {
        cout << "Alokasi memori gagal. Tidak dapat menyisipkan node baru." << endl;
        return false;
    }
}

// Fungsi untuk mencari indeks karakter pada tabel konversi
int cariIndeks(tAddr head, char karakter) {
    int indeks = 0;
    tAddr current = head;
    while (current != nullptr) {
        if (current->info == karakter) {
            return indeks;
        }
        current = current->next;
        indeks++;
    }
    return -1; // Karakter tidak ditemukan dalam tabel konversi
}
// Fungsi untuk mengkonversi plainteks menjadi linked list angka sesuai urutan pada tabel konversi
pAddr konversiPlainteksKeAngka(const string& plainteks, tAddr awal) {
    pAddr angkaAwal = nullptr;
    pAddr angkaAkhir = nullptr;

    for (char karakter : plainteks) {
        int indeks = cariIndeks(awal, karakter);
        if (indeks != -1) {
            insertAkhir(indeks, angkaAwal, angkaAkhir);
        } else {
            cout << "Karakter '" << karakter << "' tidak ada di dalam tabel konversi." << endl;
        }
    }

    return angkaAwal;
}

bool buatSuratHasilPemeriksaan(tAddr awalT,kAddr awalK)
{
    string nomorPendaftaran, nik, namalengkap, tanggallahir, tanggalperiksa, pilihandokter;
    cout << "Masukkan Nomor Pendaftaran Pasien : ";
    cin >> nomorPendaftaran;
    while(nomorPendaftaran.find('|') != string::npos) {
        system("cls");
        cout << "Pastikan tidak menggunakan simbol '|'. Silahkan masukkan lagi.\n";
        cout << "Masukkan nomor pendaftaran : ";
        cin >> nomorPendaftaran;
    }
    nomorPendaftaran = hill_cipher_encrypt(nomorPendaftaran, awalT, awalK);
    
    ifstream inFile("file/daftarperiksa.txt");
    if (inFile.is_open()) {
        userDaftar pendaftaran;
        bool pendaftaranDitemukan = false;
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            getline(ss, pendaftaran.nomorPendaftaran, '|');
            getline(ss, pendaftaran.nik, '|');
            getline(ss, pendaftaran.namalengkap, '|');
            getline(ss, pendaftaran.tanggallahir, '|');
            getline(ss, pendaftaran.tanggalperiksa, '|');
            getline(ss, pendaftaran.pilihandokter, '|');

            if (pendaftaran.nomorPendaftaran == nomorPendaftaran)
            {
                pendaftaranDitemukan = true;
                nik = pendaftaran.nik;
                namalengkap = pendaftaran.namalengkap;
                tanggallahir = pendaftaran.tanggallahir;
                tanggalperiksa = pendaftaran.tanggalperiksa;
                pilihandokter = pendaftaran.pilihandokter;
                break;
            }
        }
        inFile.close();

        if (pendaftaranDitemukan) 
        {
            string hasilPemeriksaan;
            cout << "Masukkan hasil pemeriksaan: ";
            cin.ignore();
            getline(cin, hasilPemeriksaan);
            while(hasilPemeriksaan.find('|') != string::npos) {
                system("cls");
                cout << "Pastikan tidak menggunakan simbol '|'. Silahkan masukkan lagi.\n";
                cout << "Masukkan Hasil pemeriksaan : ";
                getline(cin, hasilPemeriksaan);
            }
            hasilPemeriksaan = hill_cipher_encrypt(hasilPemeriksaan, awalT, awalK);

            // Mengisi resep obat
            string resepObat;
            cout << "Masukkan resep obat: ";
            getline(cin, resepObat);
            while(resepObat.find('|') != string::npos) {
                system("cls");
                cout << "Pastikan tidak menggunakan simbol '|'. Silahkan masukkan lagi.\n";
                cout << "Masukkan Resep obat : ";
                getline(cin, resepObat);
            }
            resepObat = hill_cipher_encrypt(resepObat, awalT, awalK);
            ofstream outFile("file/hasilperiksa.txt", ios::app);
            if (outFile.is_open()) 
            {
                outFile << pendaftaran.nomorPendaftaran << "|" << pendaftaran.nik << "|" << pendaftaran.namalengkap << "|"
                        << pendaftaran.tanggallahir << "|" << pendaftaran.tanggalperiksa << "|" << pendaftaran.pilihandokter << "|"
                        << hasilPemeriksaan << "|" << resepObat << endl;
                outFile.close();
                cout << "Surat hasil pemeriksaan berhasil dibuat.\n";
                return true;
            } else {
                cout << "Gagal menyimpan surat hasil pemeriksaan.\n";
                return false;
            }
        } else {
            cout << "Nomor pendaftaran tidak ditemukan.\n";
            return false;
        }
    } else {
        cout << "Gagal membuka file daftarperiksa.txt.\n";
        return false;
    }
}

void tampilkanSuratHasilPemeriksaan(string& targetNik, tAddr awalT, kAddr awalK, kAddr awalKinv) {

    targetNik = hill_cipher_encrypt(targetNik, awalT, awalK);
    ifstream inFile("file/hasilperiksa.txt");
    if (inFile.is_open()) {
        cout << "================================================================================================================================" << endl;
        cout << "                                    SURAT HASIL PEMERIKSAAN PASIEN                                                   " << endl;
        cout << "================================================================================================================================" << endl;
        cout << "No.Pendaftaran\t\tNIK\t\tNama Lengkap\t\tTanggal Lahir\tTanggal Periksa\t\tPilihan Dokter\t\tHasil Pemeriksaan\tResep Obat" << endl;
        cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;

        string line;
        bool found = false;
        while (getline(inFile, line)) {
            stringstream ss(line);
            UserHasil data;
            getline(ss, data.nomorpendaftaran, '|');
            getline(ss, data.nik, '|');
            getline(ss, data.namalengkap, '|');
            getline(ss, data.tanggallahir, '|');
            getline(ss, data.tanggalperiksa, '|');
            getline(ss, data.pilihandokter, '|');
            getline(ss, data.hasilPemeriksaan, '|');
            getline(ss, data.resepObat);
            
            if (data.nik == targetNik) {
                found = true;

                data.nomorpendaftaran = hill_cipher_decrypt(data.nomorpendaftaran, awalT, awalKinv);
                data.nik = hill_cipher_decrypt(data.nik, awalT, awalKinv);
                data.namalengkap = hill_cipher_decrypt(data.namalengkap, awalT, awalKinv);
                data.tanggallahir = hill_cipher_decrypt(data.tanggallahir, awalT, awalKinv);
                data.hasilPemeriksaan = hill_cipher_decrypt(data.hasilPemeriksaan, awalT, awalKinv);
                data.resepObat = hill_cipher_decrypt(data.resepObat, awalT, awalKinv);

                cout << data.nomorpendaftaran << "\t\t" << data.nik << "\t" << data.namalengkap << "\t" << data.tanggallahir << "\t" << data.tanggalperiksa << "\t" 
                     << data.pilihandokter << "\t" << data.hasilPemeriksaan << "\t" << data.resepObat << endl;
            }
        }
        targetNik = hill_cipher_decrypt(targetNik, awalT, awalKinv);
        if (!found) {
            cout << "Tidak ditemukan surat hasil pemeriksaan untuk NIK " << targetNik << endl;
        }
        
        cout << "===============================================================================================================================" << endl;
        inFile.close();
    } else {
        cout << "Gagal membuka file hasilpemeriksaan.txt.\n";
    }
}


bool insertTengahUserData(const UserData& data, dtAddr& awal, dtAddr& akhir) {
    dtAddr newNode = new UserData;
    if (newNode != nullptr) {
        *newNode = data;
        newNode->next = nullptr;

        if (awal == nullptr) {  // Linked list kosong
            awal = akhir = newNode;
        } else if (awal->namalengkap > newNode->namalengkap) {  // Sisipkan di awal
            newNode->next = awal;
            awal = newNode;
        } else {  // Sisipkan di tengah atau akhir
            dtAddr prev = nullptr;
            dtAddr current = awal;
            while (current != nullptr && current->namalengkap <= newNode->namalengkap) {
                prev = current;
                current = current->next;
            }
            if (current == nullptr) {  // Sisipkan di akhir
                akhir->next = newNode;
                akhir = newNode;
            } else {  // Sisipkan di tengah
                prev->next = newNode;
                newNode->next = current;
            }
        }
        return true;
    } else {
        cout << "Alokasi memori gagal. Tidak dapat menyisipkan node baru." << endl;
        return false;
    }
}

void hapusLinkedListUserData(dtAddr &awalD) {
    dtAddr current = awalD;
    while (current != nullptr) {
        dtAddr nextNode = current->next;
        delete current;
        current = nextNode;
    }
    awalD = nullptr;
}