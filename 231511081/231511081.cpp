#include "231511081.h"
#include "../231511067/231511067.h"
#include "../231511082/231511082.h"



void buatSuratHasilPemeriksaan() {

    string nomorPendaftaran, nik, namalengkap, tanggallahir, tanggalperiksa, pilihandokter;
    cout << "Masukkan Nomor Pendaftaran Pasien : ";
    cin >> nomorPendaftaran;
    nomorPendaftaran = hill_cipher_encrypt(nomorPendaftaran);
    
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

           
            if (pendaftaran.nomorPendaftaran == nomorPendaftaran) {
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

        if (pendaftaranDitemukan) {
            
            string hasilPemeriksaan;
            cout << "Masukkan hasil pemeriksaan: ";
            cin.ignore();
            getline(cin, hasilPemeriksaan);
            hasilPemeriksaan = hill_cipher_encrypt(hasilPemeriksaan);

            // Mengisi resep obat
            string resepObat;
            cout << "Masukkan resep obat: ";
            getline(cin, resepObat);
            resepObat = hill_cipher_encrypt(resepObat);

            
            ofstream outFile("file/hasilperiksa.txt", ios::app); 
            if (outFile.is_open()) {
                outFile << pendaftaran.nomorPendaftaran << "|" << pendaftaran.nik << "|" << pendaftaran.namalengkap << "|"
                        << pendaftaran.tanggallahir << "|" << pendaftaran.tanggalperiksa << "|" << pendaftaran.pilihandokter << "|"
                        << hasilPemeriksaan << "|" << resepObat << endl;
                outFile.close();
                cout << "Surat hasil pemeriksaan berhasil dibuat.\n";
            } else {
                cout << "Gagal menyimpan surat hasil pemeriksaan.\n";
            }
        } else {
            cout << "Nomor pendaftaran tidak ditemukan.\n";
        }
    } else {
        cout << "Gagal membuka file daftarperiksa.txt.\n";
    }
}




void tampilkanSuratHasilPemeriksaan(string& targetNik) {

    targetNik = hill_cipher_encrypt(targetNik);
    ifstream inFile("file/hasilperiksa.txt");
    if (inFile.is_open()) {
        cout << "==================================================================================================================" << endl;
        cout << "                                    SURAT HASIL PEMERIKSAAN PASIEN                                                   " << endl;
        cout << "==================================================================================================================" << endl;
        cout << "Nomor Pendaftaran\tNIK\tNama Lengkap\tTanggal Lahir\tTanggal Periksa\tPilihan Dokter\tHasil Pemeriksaan\tResep Obat" << endl;
        cout << "------------------------------------------------------------------------------------------------------------------" << endl;

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

                data.nomorpendaftaran = hill_cipher_decrypt(data.nomorpendaftaran);
                data.nik = hill_cipher_decrypt(data.nik);
                data.namalengkap = hill_cipher_decrypt(data.namalengkap);
                data.tanggallahir = hill_cipher_decrypt(data.tanggallahir);
                data.hasilPemeriksaan = hill_cipher_decrypt(data.hasilPemeriksaan);
                data.resepObat = hill_cipher_decrypt(data.resepObat);

                cout << data.nomorpendaftaran << "\t\t" << data.nik << "\t" << data.namalengkap << "\t" << data.tanggallahir << "\t" << data.tanggalperiksa << "\t" 
                     << data.pilihandokter << "\t" << data.hasilPemeriksaan << "\t" << data.resepObat << endl;
            }
        }
        targetNik = hill_cipher_decrypt(targetNik);
        if (!found) {
            cout << "Tidak ditemukan surat hasil pemeriksaan untuk NIK " << targetNik << endl;
        }
        
        cout << "==================================================================================================================" << endl;
        inFile.close();
    } else {
        cout << "Gagal membuka file hasilpemeriksaan.txt.\n";
    }
}