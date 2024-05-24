#include "231511087.h"

bool lupaPassword(tAddr awalT, kAddr awalK) {
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
    nik = hill_cipher_encrypt(nik, awalT, awalK);

    cout << "Masukkan Jawaban Clue Keamanan : ";
    getline(cin, jawaban);
    jawaban = hill_cipher_encrypt(jawaban, awalT, awalK);

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
                userData.password = hill_cipher_encrypt(userData.password, awalT, awalK);
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

bool registrasi(tAddr awalT, kAddr awalK, kAddr awalKinv) {
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
    userData.nik = hill_cipher_encrypt(userData.nik, awalT, awalK);

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
    // userData.namalengkap = hill_cipher_encrypt(userData.namalengkap, awalT, awalK);

    cout << "Tanggal Lahir (dd/mm/yyyy) : ";
    getline(cin, userData.tanggallahir);
    while(userData.tanggallahir.find('|') != string::npos) {
        system("cls");
        cout << "Pastikan tidak menggunakan simbol '|'. Silahkan masukkan lagi.\n";
        cout << "Masukkan Tanggal Lahir : ";
        getline(cin, userData.tanggallahir);
    }
    userData.tanggallahir = hill_cipher_encrypt(userData.tanggallahir, awalT, awalK);

    cout << "Alamat Rumah : ";
    getline(cin, userData.alamat);
    while(userData.alamat.find('|') != string::npos) {
        system("cls");
        cout << "Pastikan tidak menggunakan simbol '|'. Silahkan masukkan lagi.\n";
        cout << "Masukkan Alamat Rumah : ";

        getline(cin, userData.alamat);
    }
    userData.alamat = hill_cipher_encrypt(userData.alamat, awalT, awalK);

    cout << "Masukkan Password : ";
    getline(cin, userData.password);
    while(userData.password.find('|') != string::npos || userData.password.find(' ') != string::npos) {
        system("cls");
        cout << "Password tidak valid. Pastikan tidak menggunakan spasi atau simbol '|'. Silahkan masukkan lagi.\n";
        cout << "Masukkan Password : ";
        getline(cin, userData.password);
    }
    userData.password = hill_cipher_encrypt(userData.password, awalT, awalK);

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
    userData.clueKeamanan = hill_cipher_encrypt(userData.clueKeamanan, awalT, awalK);
    
    // Untuk sorting dalam file
    dtAddr awalD = nullptr;
    dtAddr akhirD = nullptr;
    ifstream myFile("file/akun_pengguna.txt");
    if (myFile.is_open()) {
        string line;
        while (getline(myFile, line)) {
            stringstream ss(line);
            UserData data;
            getline(ss, data.nik, '|');
            getline(ss, data.password, '|');
            getline(ss, data.namalengkap, '|');
            getline(ss, data.tanggallahir, '|');
            getline(ss, data.alamat, '|');
            getline(ss, data.clueKeamanan, '|');
            data.next = nullptr;

            data.namalengkap = hill_cipher_decrypt(data.namalengkap, awalT, awalKinv);

            insertUserData(data, awalD, akhirD);
        }
        myFile.close();
    } else {
        cout << "Gagal membuka file untuk dijadikan LL" << endl;
    }

    cout << "LL insert akhir :" << endl;
    cetakListUserData(awalD);
    system("pause");

    insertTengahUserData(userData, awalD, akhirD);

    cout << "LL insert tengah :" << endl;
    cetakListUserData(awalD);
    system("pause");

    // Tulis ulang data ke file
    ofstream outFile("file/akun_pengguna.txt", ios::trunc);
    if (outFile.is_open()) {
        dtAddr current = awalD;
        while (current != nullptr) {
            current->namalengkap = hill_cipher_encrypt(current->namalengkap, awalT, awalK);
            outFile << current->nik << "|" << current->password << "|" << current->namalengkap << "|" << current->tanggallahir << "|" << current->alamat << "|" << current->clueKeamanan << endl;
            current = current->next;
        }
        outFile.close();
        system("cls");
        cout << "Data Berhasil Disimpan.\n\n";
        hapusLinkedListUserData(awalD);
        return true;
    } else {
        system("cls");
        cout << "Gagal menyimpan data.\n";
        hapusLinkedListUserData(awalD);
        return false;
    }
}



bool login(string& nik, string& namalengkap, string& tanggallahir, string& alamat, string& password, tAddr awalT, kAddr awalK, kAddr awalKinv) {

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
    nik = hill_cipher_encrypt(nik, awalT, awalK);

    cout << "Masukkan Password : ";
    cin >> password;
    password = hill_cipher_encrypt(password, awalT, awalK);

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
                
                nik = hill_cipher_decrypt(nik, awalT, awalKinv);
                password = hill_cipher_decrypt(password, awalT, awalKinv);
                namalengkap = hill_cipher_decrypt(namalengkap, awalT, awalKinv);
                tanggallahir = hill_cipher_decrypt(tanggallahir, awalT, awalKinv);
                alamat = hill_cipher_decrypt(alamat, awalT, awalKinv);
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
bool loginAdmin(string& namaAdmin, tAddr awalT, kAddr awalK, kAddr awalKinv) {
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
    
    nomorAdmin = hill_cipher_encrypt(nomorAdmin, awalT, awalK);

    cout << "Masukkan Password : ";
    cin >> password;
    password = hill_cipher_encrypt(password, awalT, awalK);

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

                namaAdmin = hill_cipher_decrypt(namaAdmin, awalT, awalKinv);
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