#include <iostream>
#include <cstdlib> // ini menggunakan sistem 'cls'
#include <vector>
#include <map>
using namespace std;

// struktur data untuk menyimpan informasi tiket pesawat
struct Ticket {
    string destination;
    string airline;
    int price;
};

// struktur data untuk menyimpan informasi pengguna
struct User {
    string password;
    string role;
};

// array of struct untuk menyimpan tiket pesawat
vector<Ticket> tickets = {
    {"JPN", "GARUDA", 100},
    {"MLY", "EMIRATES", 300},
    {"SGP", "AIRASIA", 200}
};

// map of struct untuk menyimpan informasi pengguna
map<string, User> users;

// fungsi dan prosedur lainnya tetap sama seperti sebelumnya
void registerUser();
pair<bool, string> authenticate(string username, string password);
void login();
void adminMenu(string username);
void userMenu(string username);
void viewTickets();
void buyTicket(string username);
void addTicket();
void deleteTicket();
void updateTicket();

int main() {
    while (true) {
        system("cls"); // membersihkan layar konsol sebelum menampilkan menu
        cout << "Selamat datang! Silakan login atau daftar." << endl;
        cout << "1. Login" << endl;
        cout << "2. Daftar" << endl;
        cout << "3. Keluar" << endl;

        string option;
        cout << "Pilihan: ";
        cin >> option;

        if (option == "1") {
            login();
        } else if (option == "2") {
            registerUser();
        } else if (option == "3") {
            cout << "TERIMAKASIH TELAH MEMBELI TIKET DISINI, SEE U!" << endl;
            break;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }
    return 0;
}

// Prosedur untuk mendaftarkan pengguna baru
void registerUser() {
    system ("cls");
    string username, password, role;
    cout << "Masukkan username: ";
    cin >> username;
    if (users.find(username) != users.end()) {
        cout << "Username sudah ada. Coba lagi!" << endl; // Cek apakah username sudah ada
        return;
    }

    cout << "Masukkan password: ";
    cin >> password;
    cout << "Apakah anda ingin menjadi admin [a]/pengguna biasa [u]? ";
    cin >> role;

    if (role == "a") {
        users[username] = {password, "admin"}; // Tambahkan pengguna baru dengan peran admin
    } else {
        users[username] = {password, "user"}; // Tambahkan pengguna baru dengan peran pengguna biasa
    }
    cout << "SELAMAT " << username << ", REGISTRASI BERHASIL!" << endl;
}

// Fungsi untuk melakukan autentikasi pengguna
pair<bool, string> authenticate(string username, string password) {
    if (users.find(username) != users.end() && users[username].password == password) {
        return {true, users[username].role}; // Jika autentikasi berhasil, kembalikan true dan peran pengguna
    } else {
        return {false, ""}; // Jika autentikasi gagal, kembalikan false
    }
}

// Prosedur untuk melakukan login
void login() {
    system("cls");
    string username, password;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;
    auto [authenticated, role] = authenticate(username, password);// Panggil fungsi authenticate

    if (authenticated) {
        if (role == "user") {
            userMenu(username);// Panggil menu pengguna jika berhasil login sebagai pengguna
        } else if (role == "admin") {
            adminMenu(username);// Panggil menu admin jika berhasil login sebagai admin
        }
    } else {
        char retry;
        cout << "Login gagal. Apakah Anda ingin mencoba lagi? (y/n): ";
        cin >> retry;
        if (retry == 'y' || retry == 'Y') {
            login(); // Rekursi untuk mencoba login lagi
        } else {
            cout << "Kembali ke menu utama..." << endl;
        }
    }
}


// Prosedur untuk menampilkan menu admin dan mengelola operasi-admin
void adminMenu(string username) {
    while (true) {
        cout << "---SELAMAT DATANG DI MENU ADMIN---" << endl;
        cout << "1. Lihat daftar tiket" << endl;
        cout << "2. Tambah tiket" << endl;
        cout << "3. Ubah tiket" << endl;
        cout << "4. Hapus tiket" << endl;
        cout << "5. Logout" << endl;
        cout << "----------------------------------" << endl;

        string pilih;
        cout << "Dipilih: ";
        cin >> pilih;

        if (pilih == "1") {
            viewTickets(); // Tampilkan daftar tiket
        } else if (pilih == "2") {
            addTicket(); // Tambahkan tiket baru
        } else if (pilih == "3") {
            updateTicket(); // Perbarui informasi tiket
        } else if (pilih == "4") {
            deleteTicket(); // Hapus tiket
        } else if (pilih == "5") {
            break; // Logout
        } else {
            cout << "Pilihan anda tidak valid" << endl; // Tampilkan pesan jika pilihan tidak valid
        }
    }
}

// Prosedur untuk menampilkan menu pengguna dan mengelola operasi-pengguna
void userMenu(string username) {
    while (true) {
        cout << "--SELAMAT DATANG " << username << " DI LIST PEMESANAN TIKET PESAWAT--" << endl;
        cout << "1. Lihat daftar tiket" << endl;
        cout << "2. Beli tiket" << endl;
        cout << "3. Logout" << endl;

        string pilih;
        cout << "Dipilih: ";
        cin >> pilih;

        if (pilih == "1") {
            viewTickets(); // tampilkan daftar tiket
        } else if (pilih == "2") {
            buyTicket(username); // beli tiket
        } else if (pilih == "3") {
            break;
        } else {
            cout << "Pilihan anda tidak valid" << endl; // jika pilihan tidak sesuai akan menampilkan output ini
        }
    }
}

// Prosedur untuk menampilkan daftar tiket pesawat
void viewTickets() {
    system("cls");
    cout << "-----Daftar Tiket Pesawat-----" << endl;
    cout << "No. | Rute | Maskapai | Harga" << endl;
    int i = 1;
    for (auto ticket : tickets) {
        cout << i << ". " << ticket.destination << " | " << ticket.airline << " | Rp " << ticket.price << endl;
        i++;
    }
}

// Prosedur untuk membeli tiket
void buyTicket(string username) {
    system("cls");
    viewTickets();
    int beli;
    cout << "Pilihan tiket (masukkan nomor): ";
    cin >> beli;
    if (beli >= 1 && beli <= tickets.size()) {
        int jumlah;
        cout << "Masukkan jumlah tiket yang akan dibeli: ";
        cin >> jumlah;
        int totalHarga = jumlah * tickets[beli - 1].price;
        if (jumlah <= tickets[beli - 1].price) {
            cout << "Selamat datang, " << username << "! Anda telah membeli " << jumlah << " tiket seharga Rp " << totalHarga << "." << endl;
        } else {
            cout << "Stok tiket tidak mencukupi." << endl;
        }
    } else {
        cout << "Nomor tiket tidak valid." << endl;
    }
}

// Prosedur untuk menambahkan tiket baru
void addTicket() {
    system("cls");
    string destination, airline;
    int price;
    cout << "Masukkan destinasi baru: ";
    cin >> destination;
    cout << "Masukkan nama maskapai: ";
    cin >> airline;
    cout << "Masukkan harga tiket: ";
    cin >> price;
    tickets.push_back({destination, airline, price}); // Menambahkan tiket baru
    cout << "Tiket berhasil ditambahkan." << endl;
}

// Prosedur untuk menghapus tiket
void deleteTicket() {
    system("cls");
    viewTickets();
    int beli;
    cout << "Masukkan nomor tiket yang akan dihapus: ";
    cin >> beli;
    if (beli >= 1 && beli <= tickets.size()) {
        tickets.erase(tickets.begin() + beli - 1); // hapus tiket 
        cout << "Tiket berhasil dihapus." << endl;
    } else {
        cout << "Nomor tiket tidak valid." << endl;
    }
}

// Prosedur untuk memperbarui informasi tiket
void updateTicket() {
    system("cls");
    viewTickets();
    int beli;
    cout << "Masukkan nomor tiket yang akan diubah: ";
    cin >> beli;
    if (beli >= 1 && beli <= tickets.size()) {
        string rute, maskapai, price;
        
        cout << "Masukkan destinasi tiket baru: ";
        cin.ignore();//membersihkan buffer input
        getline(cin, rute); 

        cout << "Masukkan maskapai tiket baru : ";
        getline(cin, maskapai ); // menggunakan getline untuk mengambil input sbgai string
        if (maskapai.empty()){
            maskapai = tickets[beli - 1].airline;
        }
        cout << "Masukkan harga tiket baru  (biarkan kosong untuk tetap menggunakan harga yang lama) : ";
        getline(cin, price);
        if (price.empty()){
            price = to_string(tickets[beli - 1].price);
        }

        // Perbaikan: Mengupdate tiket yang ada
        tickets[beli - 1] = {rute, maskapai, stoi(price)};
        cout << "Tiket berhasil diubah." << endl;
    } else {
        cout << "Nomor tiket tidak valid." << endl;
    }
}