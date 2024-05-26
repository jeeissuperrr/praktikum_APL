#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

struct User {
    string username;
    string password;
    string role;
};

struct Produk {
    string nama;
    int harga;
    int jumlah;
};

struct Transaksi {
    string namaProduk;
    int jumlah;
    string username; 
};

vector<Produk> produk;
vector<User> users;
vector<Transaksi> transaksiAktif;

void loadData() {
    ifstream file("data.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string type;
            ss >> type;

            if (type == "#USER") {
                User user;
                ss >> user.username >> user.password >> user.role;
                users.push_back(user);
            } else if (type == "#PRODUCT") {
                Produk prod;
                string temp;
                getline(ss, temp, '"');
                getline(ss, prod.nama, '"'); 
                ss >> prod.harga >> prod.jumlah;
                produk.push_back(prod);
            }
        }
        file.close();
    }
}

void saveData() {
    ofstream file("data.txt");
    if (file.is_open()) {
        for (const auto &user : users) {
            file << "#USER " << user.username << " " << user.password << " " << user.role << endl;
        }
        for (const auto &prod : produk) {
            file << "#PRODUCT \"" << prod.nama << "\" " << prod.harga << " " << prod.jumlah << endl;
        }
        file.close();
    } else {
        cout << "Tidak dapat membuka file data" << endl;
    }
}

void initializeDefaultData() {
    users.push_back({"admin", "admin123", "admin"});
    produk.push_back({"oreo", 10000, 50});
    produk.push_back({"chitato", 12000, 30});
    produk.push_back({"aqua", 3000, 100});
    produk.push_back({"indomie", 2500, 200});
    produk.push_back({"lays", 15000, 20});
    saveData();
}

bool onlySpaces(const string& str) {
    for (char c : str) {
        if (c != ' ') {
            return false;
        }
    }
    return true;
}

bool registerUser() {
    User newUser;
    cin.ignore();
    
    // Meminta nama pengguna
    do {
        cout << "Masukkan nama pengguna baru: ";
        getline(cin, newUser.username);
        if (onlySpaces(newUser.username)) {
            cout << "Nama pengguna tidak boleh hanya berisi spasi.\n";
        }
    } while (onlySpaces(newUser.username));
    
    // Meminta kata sandi
    do {
        cout << "Masukkan kata sandi baru: ";
        getline(cin, newUser.password);
        if (onlySpaces(newUser.password)) {
            cout << "Kata sandi tidak boleh hanya berisi spasi.\n";
        }
    } while (onlySpaces(newUser.password));

    newUser.role = "user";

    for (const auto &user : users) {
        if (user.username == newUser.username) {
            cout << "Nama pengguna sudah ada. Silakan coba lagi.\n";
            return false;
        }
    }

    users.push_back(newUser);
    saveData();
    cout << "Registrasi berhasil!\n";
    return true;
}


bool loginUser(User &loggedUser) {
    string username, password;
    cin.ignore();
    
    // Meminta username
    bool onlySpaces = false;
    do {
        cout << "Masukkan username: ";
        getline(cin, username);
        onlySpaces = true;
        for (char c : username) {
            if (c != ' ') {
                onlySpaces = false;
                break;
            }
        }
        if (onlySpaces) {
            cout << "Username tidak boleh hanya berisi spasi.\n";
        }
    } while (onlySpaces);
    
    // Meminta password
    do {
        cout << "Masukkan password: ";
        getline(cin, password);
        onlySpaces = true;
        for (char c : password) {
            if (c != ' ') {
                onlySpaces = false;
                break;
            }
        }
        if (onlySpaces) {
            cout << "Password tidak boleh hanya berisi spasi.\n";
        }
    } while (onlySpaces);

    for (const auto &user : users) {
        if (user.username == username && user.password == password) {
            loggedUser = user;
            return true;
        }
    }

    cout << "Username atau password salah. Silakan coba lagi.\n";
    return false;
}

string toLowerCase(const string &str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

void sortProdukByName() {
    sort(produk.begin(), produk.end(), [](const Produk &a, const Produk &b) {
        return a.nama < b.nama;
    });
}

void Tampilkan() {
    sortProdukByName();
    system("CLS");
    cout << "Daftar Produk" << endl;
    cout << "====================" << endl;

    if (produk.empty()) {
        cout << "Tidak ada produk yang tersedia." << endl;
    } else {
        cout << "No. - Nama - Harga - Jumlah" << endl;
        for (size_t i = 0; i < produk.size(); ++i) {
            cout << i + 1 << ". " << produk[i].nama << " - Rp" << produk[i].harga << " - " << produk[i].jumlah << " pcs" << endl;
        }
    }
}

void CariProduk() {
    sortProdukByName();
    system("CLS");
    
    // Tampilkan daftar produk
    cout << "\nDaftar Produk" << endl;
    cout << "====================" << endl;
    Tampilkan();
    
    string namaProduk;
    cout << "\nMasukkan nama produk untuk mencari (atau tekan Enter untuk kembali): ";
    cin.ignore();
    getline(cin, namaProduk);

    if (!namaProduk.empty()) {
        string lowerNamaProduk = toLowerCase(namaProduk);
        bool found = false;
        for (const auto &prod : produk) {
            if (toLowerCase(prod.nama).find(lowerNamaProduk) != string::npos) {
                cout << "Produk ditemukan: " << prod.nama << " - Rp" << prod.harga << " - " << prod.jumlah << " pcs" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Produk tidak ditemukan." << endl;
        }
    }
    return;
}

void Tambah() {
    system("CLS");
    Produk prod;
    bool productExists = false;
    cin.ignore();

    do {
        cout << "Nama Produk: ";
        getline(cin, prod.nama);
        
        // Memeriksa apakah nama produk kosong
        if (prod.nama.empty()) {
            cout << "Nama produk tidak boleh kosong.\n";
        } else {
            // Memeriksa apakah nama produk sudah ada
            productExists = false;
            for (const auto &existingProd : produk) {
                if (toLowerCase(existingProd.nama) == toLowerCase(prod.nama)) {
                    productExists = true;
                    cout << "Produk sudah ada. Silakan masukkan nama produk yang belum ada.\n";
                    break;
                }
            }
        }
    } while (prod.nama.empty() || productExists);

    string hargaStr;
    int harga;
    bool validInput = false;
    do {
        cout << "Harga: ";
        getline(cin, hargaStr);
        validInput = true;
        for (char c : hargaStr) {
            if (!isdigit(c)) {
                validInput = false;
                break;
            }
        }
        if (!validInput) {
            cout << "Harga harus berupa bilangan bulat positif.\n";
        }
    } while (!validInput);
    // Konversi harga dari string menjadi integer
    harga = stoi(hargaStr);
    prod.harga = harga;

    cout << "Jumlah: ";
    cin >> prod.jumlah;
    produk.push_back(prod);
    saveData();
    cout << "Produk berhasil ditambahkan!" << endl;
}


void Pembelian(User &loggedUser) {
    vector<tuple<string, int, int>> sesiPembelian;
    while (true) {
        system("CLS");
        Tampilkan();
        string namaProduk;
        int jumlah;

        cin.ignore();
        cout << "Masukkan nama produk (atau tekan Enter untuk kembali): ";
        getline(cin, namaProduk);

        if (namaProduk.empty()) {
            break;
        }

        bool found = false;
        for (auto &prod : produk) {
            if (toLowerCase(prod.nama) == toLowerCase(namaProduk)) {
                found = true;
                cout << "Masukkan jumlah: ";
                cin >> jumlah;

                if (prod.jumlah >= jumlah) {
                    prod.jumlah -= jumlah;
                    sesiPembelian.push_back({prod.nama, jumlah, prod.harga});
                    cout << "Produk " << prod.nama << " berhasil dibeli. Total: Rp" << prod.harga * jumlah << endl;
                } else {
                    cout << "Stok tidak mencukupi." << endl;
                }
                break;
            }
        }
        
        if (!found) {
            cout << "Produk tidak ditemukan." << endl;
        }

        while (true) {
            cout << "\nApakah Anda ingin melanjutkan pembelian? (y/n): ";
            string lanjut;
            cin >> lanjut;
            if (tolower(lanjut[0]) == 'y') {
                break;
            } else if (tolower(lanjut[0]) == 'n') {
                if (!sesiPembelian.empty()) {
                    int totalHarga = 0;
                    ofstream receipt("receipt.txt", ios::app);
                    if (receipt.is_open()) {
                        receipt << "Pembelian oleh " << loggedUser.username << ":\n";
                        receipt << "====================\n";
                        cout << "\nStruk Pembelian:\n";
                        for (const auto &item : sesiPembelian) {
                            string nama;
                            int jumlah, harga;
                            tie(nama, jumlah, harga) = item;
                            int total = jumlah * harga;
                            totalHarga += total;
                            receipt << "Produk: " << nama << endl;
                            receipt << "Harga: Rp" << harga << endl;
                            receipt << "Jumlah: " << jumlah << endl;
                            receipt << "Total: Rp" << total << endl;
                            receipt << "--------------------\n";
                            cout << "Produk: " << nama << endl;
                            cout << "Harga: Rp" << harga << endl;
                            cout << "Jumlah: " << jumlah << endl;
                            cout << "Total: Rp" << total << endl;
                            cout << "--------------------\n";
                        }
                        receipt << "Total Harga: Rp" << totalHarga << endl;
                        receipt << "====================\n";
                        receipt.close();
                        cout << "Total Harga: Rp" << totalHarga << endl;
                        cout << "====================\n";
                        for (const auto &item : sesiPembelian) {
                            string nama;
                            int jumlah;
                            tie(nama, jumlah, ignore) = item;
                            transaksiAktif.push_back({nama, jumlah, loggedUser.username});
                        }
                    }
                    saveData();
                }
                return;
            } else {
                cout << "Masukkan hanya 'y' atau 'n'." << endl;
            }
        }
    }
}


void BatalkanPembelian() {
    system("CLS");
    if (!transaksiAktif.empty()) {
        Transaksi transaksiTerakhir = transaksiAktif.back();
        for (auto &prod : produk) { 
            if (prod.nama == transaksiTerakhir.namaProduk) {
                cout << "Anda telah membeli produk berikut:\n";
                cout << "Nama Produk: " << prod.nama << endl;
                cout << "Jumlah: " << transaksiTerakhir.jumlah << endl;
                cout << "Harga Total: Rp" << prod.harga * transaksiTerakhir.jumlah << endl;
                while (true) {
                    cout << "Apakah Anda yakin ingin membatalkan pesanan? (y/n): ";
                    string jawaban;
                    cin >> jawaban;
                    if (tolower(jawaban[0]) == 'y') { 
                        prod.jumlah += transaksiTerakhir.jumlah;
                        cout << "Transaksi pembelian produk " << transaksiTerakhir.namaProduk << " berhasil dibatalkan." << endl;
                        transaksiAktif.pop_back();
                        saveData();
                        return;
                    } else if (tolower(jawaban[0]) == 'n') {
                        cout << "Batal pembatalan pesanan." << endl;
                        return;
                    } else {
                        cout << "Masukkan hanya 'y' atau 'n'." << endl;
                    }
                }
            }
        }
    } else {
        cout << "Tidak ada transaksi yang bisa dibatalkan." << endl;
    }
}

void Ubah() {
    system("CLS");
    Tampilkan();
    string namaProduk;
    cin.ignore();
    cout << "Masukkan nama produk yang ingin diubah: ";
    getline(cin, namaProduk);

    for (auto &prod : produk) {
        if (toLowerCase(prod.nama) == toLowerCase(namaProduk)) {
            cout << "Masukkan nama baru: ";
            getline(cin, prod.nama);
            
            string hargaStr;
            int harga;
            bool validInput = false;
            do {
                cout << "Masukkan harga baru: ";
                getline(cin, hargaStr);
                validInput = true;
                for (char c : hargaStr) {
                    if (!isdigit(c)) {
                        validInput = false;
                        break;
                    }
                }
                if (!validInput) {
                    cout << "Harga harus berupa bilangan bulat positif.\n";
                }
            } while (!validInput);
            harga = stoi(hargaStr);
            prod.harga = harga;

            cout << "Masukkan Jumlah Stock Produk Baru: ";
            cin >> prod.jumlah;
            cout << "Produk berhasil diubah." << endl;
            saveData();
            return;
        }
    }
    cout << "Produk tidak ditemukan." << endl;
}


void Hapus() {
    system("CLS");
    Tampilkan();
    string namaProduk;
    cin.ignore();
    cout << "Masukkan nama produk yang ingin dihapus: ";
    getline(cin, namaProduk);

    for (size_t i = 0; i < produk.size(); ++i) {
        if (toLowerCase(produk[i].nama) == toLowerCase(namaProduk)) {
            produk.erase(produk.begin() + i);
            cout << "Produk berhasil dihapus." << endl;
            saveData();
            return;
        }
    }
    cout << "Produk tidak ditemukan." << endl;
}

void TampilkanHistoriPembelian() {
    system("CLS");
    ifstream file("receipt.txt");
    if (file.is_open()) {
        string line;
        cout << "\nHistori Pembelian:\n";
        cout << "====================\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Tidak ada histori pembelian" << endl;
    }
}

void userMenu(User &loggedUser) {
    system("CLS");
    int opsi;
    do {
        cout << "\nMenu Pelanggan" << endl;
        cout << "1. Beli" << endl;
        cout << "2. Batalkan Pembelian" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilih: ";
        cin >> opsi;

        switch (opsi) {
            case 1: Pembelian(loggedUser);
                break;
            case 2: BatalkanPembelian();
                break;
            case 3: cout << "Keluar" << endl;
                return;
            default: cout << "Pilihan tidak valid. Coba lagi." << endl;
        }
    } while (opsi != 3);
}

void adminMenu() {
    system("CLS");
    int opsi;
    do {
        cout << "\nSelamat datang Admin tamvan" << endl;
        cout << "1. Tambah Produk" << endl;
        cout << "2. Tampilkan Produk" << endl;
        cout << "3. Ubah Produk" << endl;
        cout << "4. Hapus Produk" << endl;
        cout << "5. Lihat Histori Pembelian Pelanggan" << endl;
        cout << "6. Cari Produk" << endl;
        cout << "7. Keluar" << endl;
        cout << "Pilih: ";
        cin >> opsi;

        switch (opsi) {
            case 1: Tambah();
                break;
            case 2: Tampilkan();
                break;
            case 3: Ubah();
                break;
            case 4: Hapus();
                break;
            case 5: TampilkanHistoriPembelian();
                break;
            case 6: CariProduk();
                break;
            case 7: cout << "Logout berhasil." << endl;
                return;
            default: cout << "Pilihan tidak valid. Coba lagi." << endl;
        }
    } while (opsi != 7);
}

int main() {
    system("CLS");
    loadData();
    if (users.empty() && produk.empty()) {
        initializeDefaultData();
    }
    int pilihan;
    User loggedUser;

    while (true) {
        cout << "\nSelamat Datang di Program Mesin Kasir" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser(loggedUser)) {
                    if (loggedUser.role == "admin") {
                        adminMenu();
                    } else {
                        userMenu(loggedUser);
                    }
                }
                break;
            case 3:
                cout << "Keluar dari program!\n";
                return 0;
            default:
                cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    }

    return 0;
}