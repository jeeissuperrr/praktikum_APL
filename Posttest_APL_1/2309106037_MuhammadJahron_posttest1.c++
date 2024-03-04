#include <iostream>
#include <string>
#include <map>

using namespace std;

// Definisikan nilai tukar mata uang
map<string, double> nilaiTukar = {
    {"Rupiah", 1.0},
    {"Dollar", 15702.0},
    {"Euro", 17038.0},
    {"Yen", 105.00}
};

int main() {
    string namaPengguna;
    string nim;
    int percobaanLogin = 0;
    
    // Login Pengguna
    while (percobaanLogin < 3) {
        cout << "Masukkan nama pengguna: ";
        cin >> namaPengguna;
        cout << "Masukkan NIM Anda: ";
        cin >> nim;
        
        if (namaPengguna == "jahron" && nim == "037") {
            break; // Validasi berhasil
        } else {
            cout << "Nama pengguna atau NIM tidak valid, coba yang betul." << endl;
            percobaanLogin++;
        }
    }
    
    if (percobaanLogin == 3) {
        cout << "Terlalu banyak cobaan hidup, coba lagi." << endl;
        return 0;
    }
    
    // Menu Konversi Mata Uang
    while (true) {
        cout << "1. Konversi Rupiah ke (Dollar, Euro, Yen)\n";
        cout << "2. Konversi Dollar ke (Rupiah, Euro, Yen)\n";
        cout << "3. Konversi Euro ke (Rupiah, Dollar, Yen)\n";
        cout << "4. Konversi Yen ke (Rupiah, Dollar, Euro)\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        
        int pilihan;
        cin >> pilihan;
        
        if (pilihan == 1) {
            double jumlah;
            cout << "Masukkan jumlah Rupiah: ";
            cin >> jumlah;
            
            cout << "Hasil konversi ke Dollar: " << jumlah / nilaiTukar["Dollar"] << endl;
            cout << "Hasil konversi ke Euro: " << jumlah / nilaiTukar["Euro"] << endl;
            cout << "Hasil konversi ke Yen: " << jumlah / nilaiTukar["Yen"] << endl;
        } else if (pilihan == 2) {
            double jumlah;
            cout << "Masukkan jumlah Dollar: ";
            cin >> jumlah;
            
            cout << "Hasil konversi ke Rupiah: " << jumlah * nilaiTukar["Dollar"] << endl;
            cout << "Hasil konversi ke Euro: " << jumlah * nilaiTukar["Dollar"] / nilaiTukar["Euro"] << endl;
            cout << "Hasil konversi ke Yen: " << jumlah * nilaiTukar["Dollar"] / nilaiTukar["Yen"] << endl;
        } else if (pilihan == 3) {
            double jumlah;
            cout << "Masukkan jumlah Euro: ";
            cin >> jumlah;
            
            cout << "Hasil konversi ke Rupiah: " << jumlah * nilaiTukar["Euro"] << endl;
            cout << "Hasil konversi ke Dollar: " << jumlah * nilaiTukar["Euro"] / nilaiTukar["Dollar"] << endl;
            cout << "Hasil konversi ke Yen: " << jumlah * nilaiTukar["Euro"] / nilaiTukar["Yen"] << endl;
        } else if (pilihan == 4) {
            double jumlah;
            cout << "Masukkan jumlah Yen: ";
            cin >> jumlah;
            
            cout << "Hasil konversi ke Rupiah: " << jumlah * nilaiTukar["Yen"] << endl;
            cout << "Hasil konversi ke Dollar: " << jumlah * nilaiTukar["Yen"] / nilaiTukar["Dollar"] << endl;
            cout << "Hasil konversi ke Euro: " << jumlah * nilaiTukar["Yen"] / nilaiTukar["Euro"] << endl;
        } else if (pilihan == 5) {
            break; // Keluar dari loop
        } else {
            cout << "Pilihan anda tidak sesuai, yang betul we!" << endl;
        }
    }
    
    return 0;
}

