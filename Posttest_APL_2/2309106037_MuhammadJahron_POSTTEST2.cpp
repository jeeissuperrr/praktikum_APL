#include <iostream>
#include <vector>
#include <map>
using namespace std;

vector<vector<string>> tickets = {
    {"JPN", "GARUDA", "100"},
    {"MLY", "EMIRATES", "300"},
    {"SGP", "AIRASIA", "200"}
};

map<string, map<string, string>> users;

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

void registerUser() {
    string username, password, role;
    cout << "Masukkan username: ";
    cin >> username;
    if (users.find(username) != users.end()) {
        cout << "Username sudah ada. Coba lagi!" << endl;
        return;
    }

    cout << "Masukkan password: ";
    cin >> password;
    cout << "Apakah anda ingin menjadi admin [a]/pengguna biasa [u]? ";
    cin >> role;

    if (role == "a") {
        users[username] = {{"password", password}, {"role", "admin"}};
    } else {
        users[username] = {{"password", password}, {"role", "user"}};
    }
    cout << "SELAMAT " << username << ", REGISTRASI BERHASIL!" << endl;
}

pair<bool, string> authenticate(string username, string password) {
    if (users.find(username) != users.end() && users[username]["password"] == password) {
        return {true, users[username]["role"]};
    } else {
        return {false, ""};
    }
}

void login() {
    string username, password;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;
    auto [authenticated, role] = authenticate(username, password);

    if (authenticated) {
        if (role == "user") {
            userMenu(username);
        } else if (role == "admin") {
            adminMenu(username);
        }
    } else {
        cout << "Authentikasi gagal, coba lagi deh" << endl;
    }
}

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
            viewTickets();
        } else if (pilih == "2") {
            addTicket();
        } else if (pilih == "3") {
            updateTicket();
        } else if (pilih == "4") {
            deleteTicket();
        } else if (pilih == "5") {
            break;
        } else {
            cout << "Pilihan anda tidak valid" << endl;
        }
    }
}

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
            viewTickets();
        } else if (pilih == "2") {
            buyTicket(username);
        } else if (pilih == "3") {
            break;
        } else {
            cout << "Pilihan anda tidak valid" << endl;
        }
    }
}

void viewTickets() {
    cout << "-----Daftar Tiket Pesawat-----" << endl;
    cout << "No. | Rute | Maskapai | Harga" << endl;
    int i = 1;
    for (auto ticket : tickets) {
        cout << i << ". " << ticket[0] << " | " << ticket[1] << " | Rp " << ticket[2] << endl;
        i++;
    }
}

void buyTicket(string username) {
    viewTickets();
    int beli;
    cout << "Pilihan tiket (masukkan nomor): ";
    cin >> beli;
    if (beli >= 1 && beli <= tickets.size()) {
        int jumlah;
        cout << "Masukkan jumlah tiket yang akan dibeli: ";
        cin >> jumlah;
        int totalHarga = jumlah * stoi(tickets[beli - 1][2]);
        if (jumlah <= stoi(tickets[beli - 1][2])) {
            cout << "Selamat datang, " << username << "! Anda telah membeli " << jumlah << " tiket seharga Rp " << totalHarga << "." << endl;
        } else {
            cout << "Stok tiket tidak mencukupi." << endl;
        }
    } else {
        cout << "Nomor tiket tidak valid." << endl;
    }
}

void addTicket() {
    string route, maskapai, price;
    cout << "Masukkan rute baru: ";
    cin >> route;
    cout << "Masukkan nama maskapai: ";
    cin >> maskapai;
    cout << "Masukkan harga tiket: ";
    cin >> price;
    tickets.push_back({route, maskapai, price});
    cout << "Tiket berhasil ditambahkan." << endl;
}

void deleteTicket() {
    viewTickets();
    int beli;
    cout << "Masukkan nomor tiket yang akan dihapus: ";
    cin >> beli;
    if (beli >= 1 && beli <= tickets.size()) {
        tickets.erase(tickets.begin() + beli - 1);
        cout << "Tiket berhasil dihapus." << endl;
    } else {
        cout << "Nomor tiket tidak valid." << endl;
    }
}

void updateTicket() {
    viewTickets();
    int beli;
    cout << "Masukkan nomor tiket yang akan diubah: ";
    cin >> beli;
    if (beli >= 1 && beli <= tickets.size()) {
        string rute, maskapai, price;
        cout << "Masukkan rute tiket baru: ";
        cin >> rute;
        cout << "Masukkan maskapai tiket baru: ";
        cin >> maskapai;
        cout << "Masukkan harga tiket baru: ";
        cin >> price;
        tickets[beli - 1] = {rute, maskapai, price};
        cout << "Tiket berhasil diubah." << endl;
    } else {
        cout << "Nomor tiket tidak valid." << endl;
    }
}

