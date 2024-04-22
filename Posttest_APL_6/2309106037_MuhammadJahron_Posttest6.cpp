#include <iostream>
#include <cstdlib> // ini menggunakan sistem 'cls'
#include <vector>
#include <map>
#include <algorithm> // untuk sorting
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

// Function prototypes
void registerUser();
pair<bool, string> authenticate(string username, string password);
void login();
void adminMenu(string username);
void userMenu(string username);
void viewTickets();
void buyTicket(string username);
void addTicket();
void deleteTicket();
void updateTicket(Ticket* ticket);
void sortTicketsAscendingAlphabetically();
void sortTicketsDescendingByPrice();
void sortTicketsByAirline();
int binarySearch(string destination);
int reverseBinarySearch(string destination);
void userSortingMenu();
void userSearchingMenu();

// Main function
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

// Function definitions

// Sort tickets dari destinasi  (ascending)
void sortTicketsAscendingAlphabetically() {
    sort(tickets.begin(), tickets.end(), [](const Ticket &a, const Ticket &b) {
        return a.destination < b.destination;
    });
    cout << "Tiket berhasil diurutkan berdasarkan destinasi secara ascending." << endl;
}

// Sort tickets dari harga secara descending
void sortTicketsDescendingByPrice() {
    sort(tickets.begin(), tickets.end(), [](const Ticket &a, const Ticket &b) {
        return a.price > b.price;
    });
    cout << "Tiket berhasil diurutkan berdasarkan harga secara descending." << endl;
}

// Sorting tiket dari maskapai alphabet
void sortTicketsByAirline() {
    sort(tickets.begin(), tickets.end(), [](const Ticket &a, const Ticket &b) {
        return a.airline < b.airline;
    });
    cout << "Tiket berhasil diurutkan berdasarkan maskapai." << endl;
}

// Binary Search untuk mencari tiket berdasarkan destinasi
int binarySearch(string destination) {
    int left = 0;
    int right = tickets.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (tickets[mid].destination == destination) {
            return mid; // Found
        } else if (tickets[mid].destination < destination) {
            left = mid + 1; // Mencari di sisi kanan
        } else {
            right = mid - 1; // Mencari di sisi kiri
        }
    }
    return -1; // Tidak ketemu
}

// Binary Search untuk descending sorting tiket
int reverseBinarySearch(string destination) {
    int left = 0;
    int right = tickets.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (tickets[mid].destination == destination) {
            return mid; // Found
        } else if (tickets[mid].destination > destination) {
            left = mid + 1; // Mencari di sisi kanan
        } else {
            right = mid - 1; // Mencari di sisi kiri
        }
    }
    return -1; // TIdak ketemu
}

// Prosedur untuk mendaftarkan pengguna baru
void registerUser() {
    system("cls");
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
    auto [authenticated, role] = authenticate(username, password); // Panggil fungsi authenticate

    if (authenticated) {
        if (role == "user") {
            userMenu(username); // Panggil menu pengguna jika berhasil login sebagai pengguna
        } else if (role == "admin") {
            adminMenu(username); // Panggil menu admin jika berhasil login sebagai admin
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
            int beli;
            cout << "Masukkan nomor tiket yang akan diubah: ";
            cin >> beli;
            if (beli >= 1 && beli <= tickets.size()) {
                updateTicket(&tickets[beli - 1]); // Perbarui informasi tiket
            } else {
                cout << "Nomor tiket tidak valid." << endl;
            }
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
        cout << "3. Sorting Tiket" << endl;
        cout << "4. Searching Tiket" << endl;
        cout << "5. Logout" << endl;

        string pilih;
        cout << "Dipilih: ";
        cin >> pilih;

        if (pilih == "1") {
            viewTickets(); // tampilkan daftar tiket
        } else if (pilih == "2") {
            buyTicket(username); // beli tiket
        } else if (pilih == "3") {
            userSortingMenu(); // Panggil menu sorting
        } else if (pilih == "4") {
            userSearchingMenu(); // Panggil menu searching
        } else if (pilih == "5") {
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

// Prosedur untuk memperbarui informasi tiket dengan menggunakan pointer
void updateTicket(Ticket* ticket) {
    system("cls");
    cout << "---- Update Tiket ----" << endl;
    cout << "Destinasi saat ini: " << ticket->destination << endl;
    cout << "Maskapai saat ini  : " << ticket->airline << endl;
    cout << "Harga saat ini    : Rp " << ticket->price << endl;

    string rute, maskapai, price;

    cout << "Masukkan destinasi baru atau biarkan kosong : ";
    cin.ignore();
    getline(cin, rute);
    if (rute.empty()) {
        rute = ticket->destination;
    }

    cout << "Masukkan maskapai baru atau biarkan kosong : ";
    getline(cin, maskapai);
    if (maskapai.empty()) {
        maskapai = ticket->airline;
    }

    cout << "Masukkan harga baru atau biarkan kosong : ";
    getline(cin, price);
    if (price.empty()) {
        price = to_string(ticket->price);
    }

    // Perbaikan: Mengupdate tiket yang ada menggunakan pointer
    ticket->destination = rute;
    ticket->airline = maskapai;
    ticket->price = stoi(price);

    cout << "Tiket berhasil diperbarui." << endl;
    system("pause"); // Menahan layar sebelum kembali ke menu utama
}

// Prosedur untuk menampilkan menu sorting pada pengguna
void userSortingMenu() {
    system("cls");
    cout << "--SORTING TIKET--" << endl;
    cout << "1. Berdasarkan Destinasi (Ascending)" << endl;
    cout << "2. Berdasarkan Harga (Descending)" << endl;
    cout << "3. Berdasarkan Maskapai" << endl;

    string sortingOption;
    cout << "Pilihan: ";
    cin >> sortingOption;

    if (sortingOption == "1") {
        sortTicketsAscendingAlphabetically();
    } else if (sortingOption == "2") {
        sortTicketsDescendingByPrice();
    } else if (sortingOption == "3") {
        sortTicketsByAirline();
    } else {
        cout << "Pilihan tidak valid." << endl;
    }
    system("pause");
}

// Prosedur untuk menampilkan menu searching pada pengguna
void userSearchingMenu() {
    system("cls");
    cout << "--SEARCHING TIKET--" << endl;
    cout << "1. Cari Berdasarkan Destinasi (Ascending)" << endl;
    cout << "2. Cari Berdasarkan Destinasi (Descending)" << endl;

    string searchingOption;
    cout << "Pilihan: ";
    cin >> searchingOption;

    if (searchingOption == "1") {
        // Searching Destinasi (Ascending)
        string destination;
        cout << "Masukkan destinasi yang ingin dicari: ";
        cin >> destination;
        int index = binarySearch(destination);
        if (index != -1) {
            cout << "Tiket ditemukan pada indeks " << index << endl;
        } else {
            cout << "Tiket tidak ditemukan." << endl;
        }
    } else if (searchingOption == "2") {
        // Searching Destinasi (Descending)
        string destination;
        cout << "Masukkan destinasi yang ingin dicari: ";
        cin >> destination;
        int index = reverseBinarySearch(destination);
        if (index != -1) {
            cout << "Tiket ditemukan pada indeks " << index << endl;
        } else {
            cout << "Tiket tidak ditemukan." << endl;
        }
    } else {
        cout << "Pilihan tidak valid." << endl;
    }
    system("pause");
}
