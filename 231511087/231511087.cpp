#include "231511087.h"

bool simpanDataPasien(const UserData& userData) {
    ofstream outFile("file/akun_pengguna.txt", ios::app);
    if (outFile.is_open()) {
        outFile << userData.nik << "|" << userData.password << "|" << userData.namalengkap << "|" << userData.tanggallahir << "|" << userData.alamat << "|" << userData.clueKeamanan << endl;
        outFile.close();
        system("cls");
        return true;
    } else {
        system("cls");
        return false;
    }
}

bool lupaPassword() {
    string nik, jawaban;
    bool ditemukan = false;

    cout << " ====================================== Halaman Lupa Password ========================================== \n";
    cout << " ------------------------------- Masukkan NIK dan Jawaban Clue Keamanan -------------------------------- \n\n";
    cout << "Masukkan NIK : ";
    cin >> nik;
    cin.ignore();
    while(nik.length() != 16) {
        system("cls");
        cout << "NIK yang anda masukkan tidak valid. Silakan masukkan lagi.\n";
        cout << "Masukkan NIK : ";
        cin >> nik;
        cin.ignore();
    }
    nik = hill_cipher_encrypt(nik);

    cout << "Masukkan Jawaban Clue Keamanan : ";
    getline(cin, jawaban);
    jawaban = hill_cipher_encrypt(jawaban);

    ifstream inFile("file/akun_pengguna.txt");
    if (inFile.is_open()) {
        vector<UserData> updatedUsersData; 
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            UserData userData;

            getline(ss, userData.nik, '|');
            getline(ss, userData.password, '|');
            getline(ss, userData.namalengkap, '|');
            getline(ss, userData.tanggallahir, '|');
            getline(ss, userData.alamat, '|');
            getline(ss, userData.clueKeamanan);

            if (userData.nik == nik && jawaban == userData.clueKeamanan) {
                cout << "Masukkan Password Baru : ";
                getline(cin, userData.password);
                while(userData.password.find('|') != string::npos || userData.password.find(' ') != string::npos) {
                    system("cls");
                    cout << "Password tidak valid. Pastikan tidak menggunakan spasi atau simbol '|'. Silahkan masukkan lagi.\n";
                    cout << "Masukkan Password Baru: ";
                    getline(cin, userData.password);
                }
                userData.password = hill_cipher_encrypt(userData.password);
                ditemukan = true;
            }
            updatedUsersData.push_back(userData);
        }
        inFile.close();

        if (!ditemukan) {
            cout << "NIK atau clue keamanan yang anda masukkan tidak cocok.\n\n";
            return false;  
        }

        ofstream outFile("file/akun_pengguna.txt");
        if (outFile.is_open()) {
            for (const auto& userData : updatedUsersData) {
                outFile << userData.nik << "|" << userData.password << "|" << userData.namalengkap << "|" << userData.tanggallahir << "|" << userData.alamat << "|" << userData.clueKeamanan << endl;
            }
            outFile.close();
            system("cls");
            return true;
        } else {
            system("cls");
            return false; 
        }
    } else {
        system("cls");
        cout << "Gagal mengakses penyimpanan data.\n";
        return false;  
    }
}

bool registrasi() {
    UserData userData;

    cout << " ==================================== Halaman Registrasi ============================================ \n\n";
    cout << " ---------------------------------- Lengkapi Data Diri Anda ----------------------------------------- \n\n";
    cout << "NIK : ";
    cin >> userData.nik; 
    cin.ignore();
    while(userData.nik.length() != 16 || userData.nik.find('|') != string::npos) {
        system("cls");
        cout << "NIK yang anda masukkan tidak valid. Silakan masukkan lagi.\n";
        cout << "NIK : ";
        cin >> userData.nik;
        cin.ignore();
    }
    userData.nik = hill_cipher_encrypt(userData.nik);

    ifstream inFile("file/akun_pengguna.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string nik;
            getline(ss, nik, '|');
            if (nik == userData.nik) {
                system("cls");
                cout << "NIK yang anda masukkan sudah terdaftar. Registrasi tidak dapat dilakukan lagi.\n SIlahkan lakukan Login.\n\n";
                inFile.close();
                return false; 
            }
        }
        inFile.close();
    }

    cout << "Nama Lengkap : ";
    getline(cin, userData.namalengkap);
    while(userData.namalengkap.find('|') != string::npos) {
        system("cls");
        cout << "Pastikan tidak menggunakan simbol '|'. Silahkan masukkan lagi.\n";
        cout << "Masukkan Nama Lengkap : ";

        getline(cin, userData.namalengkap);
    }
    userData.namalengkap = hill_cipher_encrypt(userData.namalengkap);

    cout << "Tanggal Lahir (dd/mm/yyyy) : ";
    getline(cin, userData.tanggallahir);
    while(userData.tanggallahir.find('|') != string::npos) {
        system("cls");
        cout << "Pastikan tidak menggunakan simbol '|'. Silahkan masukkan lagi.\n";
        cout << "Masukkan Tanggal Lahir : ";
        getline(cin, userData.tanggallahir);
    }
    userData.tanggallahir = hill_cipher_encrypt(userData.tanggallahir);

    cout << "Alamat Rumah : ";
    getline(cin, userData.alamat);
    while(userData.alamat.find('|') != string::npos) {
        system("cls");
        cout << "Pastikan tidak menggunakan simbol '|'. Silahkan masukkan lagi.\n";
        cout << "Masukkan Alamat Rumah : ";

        getline(cin, userData.alamat);
    }
    userData.alamat = hill_cipher_encrypt(userData.alamat);

    cout << "Masukkan Password : ";
    getline(cin, userData.password);
    while(userData.password.find('|') != string::npos || userData.password.find(' ') != string::npos) {
        system("cls");
        cout << "Password tidak valid. Pastikan tidak menggunakan spasi atau simbol '|'. Silahkan masukkan lagi.\n";
        cout << "Masukkan Password : ";
        getline(cin, userData.password);
    }
    userData.password = hill_cipher_encrypt(userData.password);

    cout << "Membuat Clue Keamanan\n";
    cout << "Note : Clue keamanan ini akan digunakan jika anda lupa password pada suatu saat. Isi dengan yang mudah diingat oleh anda!\n\n";
    cout << "Masukkan Clue Keamanan Anda : ";
    getline(cin, userData.clueKeamanan);
    while(userData.clueKeamanan.find('|') != string::npos) {
        system("cls");
        cout << "Pastikan tidak menggunakan simbol '|'. Silahkan masukkan lagi.\n";
        cout << "Masukkan Clue Keamanan : ";
        getline(cin, userData.clueKeamanan);
    }
    userData.clueKeamanan = hill_cipher_encrypt(userData.clueKeamanan);
    
    if (simpanDataPasien(userData)) {
        cout << "Data Berhasil Disimpan.\n\n";
        return true;
    } else {
        cout << "Gagal menyimpan data.\n";
        return false;
    }
}



bool login(string& nik, string& namalengkap, string& tanggallahir, string& alamat, string& password) {

    bool cek = false;

    cout << " ======================================= Halaman Login ============================================== \n";
    cout << " ------------------------------- Masukkan NIK dan Password Anda ------------------------------------- \n\n";

    cout << "Masukkan NIK : ";
    cin >> nik;
    while(nik.length() != 16) {
        system("cls");
        cout << "NIK yang anda masukkan tidak valid. Silakan masukkan lagi.\n";
        cout << "NIK : ";
        cin >> nik;

    }
    nik = hill_cipher_encrypt(nik);

    cout << "Masukkan Password : ";
    cin >> password;
    password = hill_cipher_encrypt(password);

    ifstream input("file/akun_pengguna.txt");
    if (input.is_open()) {
        string line;
        while (getline(input, line)) {
            stringstream ss(line);
            UserData userData;

            getline(ss, userData.nik, '|');
            getline(ss, userData.password, '|');
            getline(ss, userData.namalengkap, '|');
            getline(ss, userData.tanggallahir, '|');
            getline(ss, userData.alamat, '|');
            getline(ss, userData.clueKeamanan);
            
            if (nik == userData.nik && password == userData.password) {
                cek = true;
                namalengkap = userData.namalengkap;
                tanggallahir = userData.tanggallahir;
                alamat = userData.alamat;
                
                nik = hill_cipher_decrypt(nik);
                password = hill_cipher_decrypt(password);
                namalengkap = hill_cipher_decrypt(namalengkap);
                tanggallahir = hill_cipher_decrypt(tanggallahir);
                alamat = hill_cipher_decrypt(alamat);
                break;
            }
        }
        input.close();

        if (cek) {
            system("cls");
            cout << "|| -------------------------------------- Login Berhasil! -------------------------------------------- ||\n\n";
            return true;
        } else {
            system("cls");
            cout << "Login gagal, cek kembali NIK dan password Anda.\n\n";
            return false;
        }
    } else {
        system("cls");
        cout << "Gagal mengakses penyimpanan data.\n";
        return false;
    }
}


//Fungsi Login Admin
bool loginAdmin(string& namaAdmin) {
    string nomorAdmin, password; 
    bool cek = false;

    cout << " ======================================= Halaman Login Admin ======================================== \n";
    cout << " ----------------------------------- Masukkan Nomor Admin dan Password -------------------------------- \n\n";

    cout << "Masukkan Nomor Admin : ";
    cin >> nomorAdmin;
    while(nomorAdmin.length() != 6) {
        system("cls");
        cout << "NIK yang anda masukkan tidak valid. Silakan masukkan lagi.\n";
        cout << "Nomor Admin : ";
        cin >> nomorAdmin;
    }
    
    nomorAdmin = hill_cipher_encrypt(nomorAdmin);

    cout << "Masukkan Password : ";
    cin >> password;
    password = hill_cipher_encrypt(password);

    ifstream input("file/akun_admin.txt");
    if (input.is_open()) {
        string line;
        while (getline(input, line)) {
            stringstream ss(line);
            AdminData adminData;

            getline(ss, adminData.nomorAdmin, '|');
            getline(ss, adminData.namaAdmin, '|');
            getline(ss, adminData.password);
            if (nomorAdmin == adminData.nomorAdmin && password == adminData.password) {
                cek = true;
                namaAdmin = adminData.namaAdmin;

                namaAdmin = hill_cipher_decrypt(namaAdmin);
                break;
            }
        }
        input.close();

        if (cek) {
            system("cls");
            cout << "|| ----------------------------------------- Login Berhasil! --------------------------------------- ||\n\n";
            return true;
        } else {
            system("cls");
            cout << "Login Admin gagal, cek kembali Nomor Admin dan password Anda.\n\n";
            return false;
        }
    } else {
        system("cls");
        cout << "Gagal mengakses penyimpanan data.\n";
        return false;
    }
}

// Fungsi untuk menghitung determinan matriks 2x2 dari linked list
int countDeterminan(kAddr awal) {
    if (awal == nullptr || awal->nextrow == nullptr || awal->nextcol == nullptr || awal->nextrow->nextcol == nullptr) {
        cout << "Error: Linked list tidak lengkap." << endl;
        return 0;
    }
    int det = (awal->info * awal->nextrow->nextcol->info) - (awal->nextrow->info * awal->nextcol->info);
    return det;
}

kAddr inversKey(kAddr awal, int determinan) {
    if (determinan == 0) {
        cout << "Error: Determinan nol, tidak dapat menghitung invers determinan." << endl;
        return nullptr;
    }

    // Cari invers determinan
    int inverseDeterminan = 0;
    for (int i = 1; i < 94; ++i) {
        if ((determinan * i) % 94 == 1) {
            inverseDeterminan = i;
            break;
        }
    }

    int a = awal->info;
    int b = awal->nextrow->info;
    int c = awal->nextcol->info;
    int d = awal->nextrow->nextcol->info;

    awal->info = d;
    awal->nextrow->info = -b;
    awal->nextcol->info = -c;
    awal->nextrow->nextcol->info = a;

    kAddr current = awal;
    while (current != nullptr) {
        current->info = ((current->info * inverseDeterminan) % 94); //Dalam operasi modulus, jika hasil perkalian adalah negatif, maka hasil modulus juga akan negatif.
        if (current->info < 0) {
            current->info += 94; // memastikan hasil modulus selalu positif
        }
        current = current->nextrow;
    }
    current = awal->nextcol;
    while (current != nullptr) {
        current->info = ((current->info * inverseDeterminan) % 94); //Dalam operasi modulus, jika hasil perkalian adalah negatif, maka hasil modulus juga akan negatif.
        if (current->info < 0) {
            current->info += 94; // memastikan hasil modulus selalu positif
        }
        current = current->nextrow;
    }
    return awal;
}

// fungsi untuk perkalian matriksLL kunci dengan matriksLL plainteks/cipherteks 
pAddr perkalianMatriksLL(pAddr pAwal, kAddr kAwal) { 
    pAddr currentP = pAwal;

    while (currentP != nullptr && currentP->next != nullptr) {
        kAddr currentK = kAwal;

        int node1 = currentP->info;
        int node2 = currentP->next->info;


        int hasil1 = (((node1 * currentK->info) + (node2 * currentK->nextrow->info)) % 94);

        currentK = currentK->nextcol;
        int hasil2 = (((node1 * currentK->info) + (node2 * currentK->nextrow->info)) % 94);


        currentP->info = hasil1;
        currentP->next->info = hasil2;

        currentP = currentP->next->next;
    }
    return pAwal;
}