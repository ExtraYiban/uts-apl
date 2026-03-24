#include <iostream>
#include <string>
using namespace std;

struct Obat {
    string kode;
    string nama;
    int harga;
    int stok;
};

struct NodeTree {
    Obat data;
    NodeTree *kiri;
    NodeTree *kanan;
};

int minInt(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

void tukarObat(Obat &a, Obat &b) {
    Obat temp = a;
    a = b;
    b = temp;
}

void bersihkanInput() {
    cin.clear();
    char c;
    while (cin.get(c)) {
        if (c == '\n') {
            break;
        }
    }
}

int bacaIntDenganBatas(string pesan, int minValue, int maxValue) {
    int nilai;
    while (true) {
        cout << pesan;
        if (cin >> nilai && nilai >= minValue && nilai <= maxValue) {
            bersihkanInput();
            return nilai;
        }
        cout << "Input harus angka antara " << minValue << " sampai " << maxValue << "!\n";
        bersihkanInput();
    }
}

void salinData(Obat *asal, Obat *tujuan, int n) {
    for (int i = 0; i < n; i++) {
        tujuan[i] = asal[i];
    }
}

void tampilData(Obat *data, int n) {
    if (n == 0) {
        cout << "Data obat masih kosong.\n";
        return;
    }

    cout << "\n=== DATA OBAT ===\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". Kode: " << data[i].kode
             << " | Nama: " << data[i].nama
             << " | Harga: " << data[i].harga
             << " | Stok: " << data[i].stok << '\n';
    }
}

void inputData(Obat *data, int &n) {
    n = bacaIntDenganBatas("Jumlah data obat: ", 0, 100);

    for (int i = 0; i < n; i++) {
        cout << "\nData obat ke-" << i + 1 << '\n';
        cout << "Kode obat: ";
        getline(cin, (data + i)->kode);

        cout << "Nama obat: ";
        getline(cin, (data + i)->nama);

        (data + i)->harga = bacaIntDenganBatas("Harga: ", 0, 1000000000);
        (data + i)->stok = bacaIntDenganBatas("Stok: ", 0, 1000000000);
    }

    cout << "\nInput data selesai.\n";
}

int totalStok(Obat *data, int n) {
    int total = 0;
    Obat *ptr = data;

    for (int i = 0; i < n; i++) {
        total += ptr->stok;
        ptr++;
    }
    return total;
}

void inputPenjualanCabang(int (*penjualan)[12], int jumlahCabang) {
    cout << "\nInput data penjualan (array 2D: cabang x bulan)\n";
    for (int i = 0; i < jumlahCabang; i++) {
        cout << "Cabang " << i + 1 << '\n';
        for (int j = 0; j < 12; j++) {
            penjualan[i][j] = bacaIntDenganBatas("  Bulan " + to_string(j + 1) + ": ", 0, 1000000000);
        }
    }
}

int totalPenjualanSatuCabang(int *barisCabang) {
    int total = 0;
    for (int i = 0; i < 12; i++) {
        total += *(barisCabang + i);
    }
    return total;
}

void tampilRekapPenjualan(int (*penjualan)[12], int jumlahCabang) {
    cout << "\n=== REKAP PENJUALAN CABANG ===\n";
    for (int i = 0; i < jumlahCabang; i++) {
        int total = totalPenjualanSatuCabang(penjualan[i]);
        double rataRata = static_cast<double>(total) / 12;
        cout << "Cabang " << i + 1
             << " | Total: " << total
             << " | Rata-rata/bulan: " << rataRata << '\n';
    }
}

// Exchange Sort berdasarkan nama
void exchangeSortNama(Obat *data, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (data[i].nama > data[j].nama) {
                tukarObat(data[i], data[j]);
            }
        }
    }
}

// Bubble Sort berdasarkan stok (naik) agar mudah melihat obat dengan stok menipis
void bubbleSortStokNaik(Obat *data, int n) {
    for (int i = 0; i < n - 1; i++) {
        bool adaTukar = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (data[j].stok > data[j + 1].stok) {
                tukarObat(data[j], data[j + 1]);
                adaTukar = true;
            }
        }

        if (!adaTukar) {
            break;
        }
    }
}

// Insertion Sort berdasarkan nama
void insertionSortNama(Obat *data, int n) {
    for (int i = 1; i < n; i++) {
        Obat key = data[i];
        int j = i - 1;

        while (j >= 0 && data[j].nama > key.nama) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
}

// Shell Sort berdasarkan nama
void shellSortNama(Obat *data, int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Obat temp = data[i];
            int j;
            for (j = i; j >= gap && data[j - gap].nama > temp.nama; j -= gap) {
                data[j] = data[j - gap];
            }
            data[j] = temp;
        }
    }
}

void mergeNama(Obat *data, int kiri, int tengah, int kanan, Obat *buffer) {
    int i = kiri;
    int j = tengah + 1;
    int k = kiri;

    while (i <= tengah && j <= kanan) {
        if (data[i].nama <= data[j].nama) {
            buffer[k++] = data[i++];
        } else {
            buffer[k++] = data[j++];
        }
    }

    while (i <= tengah) {
        buffer[k++] = data[i++];
    }
    while (j <= kanan) {
        buffer[k++] = data[j++];
    }

    for (int idx = kiri; idx <= kanan; idx++) {
        data[idx] = buffer[idx];
    }
}

void mergeSortNamaRekursif(Obat *data, int kiri, int kanan, Obat *buffer) {
    if (kiri >= kanan) {
        return;
    }

    int tengah = kiri + (kanan - kiri) / 2;
    mergeSortNamaRekursif(data, kiri, tengah, buffer);
    mergeSortNamaRekursif(data, tengah + 1, kanan, buffer);
    mergeNama(data, kiri, tengah, kanan, buffer);
}

void mergeSortNama(Obat *data, int n) {
    Obat buffer[100];
    mergeSortNamaRekursif(data, 0, n - 1, buffer);
}

int partitionNama(Obat *data, int low, int high) {
    string pivot = data[high].nama;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (data[j].nama <= pivot) {
            i++;
            tukarObat(data[i], data[j]);
        }
    }
    tukarObat(data[i + 1], data[high]);
    return i + 1;
}

void quickSortNama(Obat *data, int low, int high) {
    if (low < high) {
        int pi = partitionNama(data, low, high);
        quickSortNama(data, low, pi - 1);
        quickSortNama(data, pi + 1, high);
    }
}

void heapifyNama(Obat *data, int n, int i) {
    int terbesar = i;
    int kiri = 2 * i + 1;
    int kanan = 2 * i + 2;

    if (kiri < n && data[kiri].nama > data[terbesar].nama) {
        terbesar = kiri;
    }
    if (kanan < n && data[kanan].nama > data[terbesar].nama) {
        terbesar = kanan;
    }

    if (terbesar != i) {
        tukarObat(data[i], data[terbesar]);
        heapifyNama(data, n, terbesar);
    }
}

void heapSortNama(Obat *data, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyNama(data, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        tukarObat(data[0], data[i]);
        heapifyNama(data, i, 0);
    }
}

NodeTree *buatNode(Obat item) {
    NodeTree *nodeBaru = new NodeTree;
    nodeBaru->data = item;
    nodeBaru->kiri = nullptr;
    nodeBaru->kanan = nullptr;
    return nodeBaru;
}

NodeTree *insertNodeTree(NodeTree *root, Obat item) {
    if (root == nullptr) {
        return buatNode(item);
    }

    if (item.nama < root->data.nama) {
        root->kiri = insertNodeTree(root->kiri, item);
    } else {
        root->kanan = insertNodeTree(root->kanan, item);
    }
    return root;
}

void inorderTreeKeArray(NodeTree *root, Obat *hasil, int &idx) {
    if (root == nullptr) {
        return;
    }

    inorderTreeKeArray(root->kiri, hasil, idx);
    hasil[idx++] = root->data;
    inorderTreeKeArray(root->kanan, hasil, idx);
}

void hapusTree(NodeTree *root) {
    if (root == nullptr) {
        return;
    }
    hapusTree(root->kiri);
    hapusTree(root->kanan);
    delete root;
}

void treeSortNama(Obat *data, int n) {
    NodeTree *root = nullptr;
    for (int i = 0; i < n; i++) {
        root = insertNodeTree(root, data[i]);
    }

    int idx = 0;
    inorderTreeKeArray(root, data, idx);
    hapusTree(root);
}

int hargaMaks(Obat *data, int n) {
    int maks = data[0].harga;
    for (int i = 1; i < n; i++) {
        if (data[i].harga > maks) {
            maks = data[i].harga;
        }
    }
    return maks;
}

void countingSortByExp(Obat *data, int n, int exp) {
    Obat output[100];
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        int digit = (data[i].harga / exp) % 10;
        count[digit]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int digit = (data[i].harga / exp) % 10;
        output[count[digit] - 1] = data[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++) {
        data[i] = output[i];
    }
}

void radixSortHarga(Obat *data, int n) {
    int maks = hargaMaks(data, n);
    for (int exp = 1; maks / exp > 0; exp *= 10) {
        countingSortByExp(data, n, exp);
    }
}

int binarySearchNama(Obat *data, int n, string target) {
    int kiri = 0;
    int kanan = n - 1;

    while (kiri <= kanan) {
        int tengah = kiri + (kanan - kiri) / 2;

        if (data[tengah].nama == target) {
            return tengah;
        }
        if (data[tengah].nama < target) {
            kiri = tengah + 1;
        } else {
            kanan = tengah - 1;
        }
    }
    return -1;
}

int interpolationSearchHarga(Obat *data, int n, int target) {
    int low = 0;
    int high = n - 1;

    while (low <= high && target >= data[low].harga && target <= data[high].harga) {
        if (data[low].harga == data[high].harga) {
            return (data[low].harga == target) ? low : -1;
        }

        long long pembilang = static_cast<long long>(target - data[low].harga) * (high - low);
        long long penyebut = data[high].harga - data[low].harga;
        int pos = low + static_cast<int>(pembilang / penyebut);

        if (pos < low || pos > high) {
            return -1;
        }

        if (data[pos].harga == target) {
            return pos;
        }
        if (data[pos].harga < target) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }

    return -1;
}

int fibonacciSearchHarga(Obat *data, int n, int target) {
    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;

    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = minInt(offset + fibMMm2, n - 1);

        if (data[i].harga < target) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (data[i].harga > target) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            return i;
        }
    }

    if (fibMMm1 && offset + 1 < n && data[offset + 1].harga == target) {
        return offset + 1;
    }

    return -1;
}

void tampilSatuData(Obat item) {
    cout << "Kode: " << item.kode
         << " | Nama: " << item.nama
         << " | Harga: " << item.harga
         << " | Stok: " << item.stok << '\n';
}

void menuSorting(Obat *dataAsli, int n) {
    if (n == 0) {
        cout << "Data masih kosong!\n";
        return;
    }

    int pilihanSort;
    do {
        cout << "\n=== MENU SORTING ===\n";
        cout << "1. Bubble Sort (Stok Naik - cek stok menipis)\n";
        cout << "2. Exchange Sort (Nama)\n";
        cout << "3. Insertion Sort (Nama)\n";
        cout << "4. Shell Sort (Nama)\n";
        cout << "5. Merge Sort (Nama)\n";
        cout << "6. Quick Sort (Nama)\n";
        cout << "7. Heap Sort (Nama)\n";
        cout << "8. Tree Sort (Nama)\n";
        cout << "9. Radix Sort (Harga)\n";
        cout << "0. Kembali\n";
        pilihanSort = bacaIntDenganBatas("Pilih metode sorting: ", 0, 9);

        Obat temp[100];
        salinData(dataAsli, temp, n);

        switch (pilihanSort) {
            case 1:
                bubbleSortStokNaik(temp, n);
                cout << "\nHasil Bubble Sort (Stok Naik):\n";
                tampilData(temp, n);
                break;
            case 2:
                exchangeSortNama(temp, n);
                cout << "\nHasil Exchange Sort (Nama):\n";
                tampilData(temp, n);
                break;
            case 3:
                insertionSortNama(temp, n);
                cout << "\nHasil Insertion Sort (Nama):\n";
                tampilData(temp, n);
                break;
            case 4:
                shellSortNama(temp, n);
                cout << "\nHasil Shell Sort (Nama):\n";
                tampilData(temp, n);
                break;
            case 5:
                mergeSortNama(temp, n);
                cout << "\nHasil Merge Sort (Nama):\n";
                tampilData(temp, n);
                break;
            case 6:
                quickSortNama(temp, 0, n - 1);
                cout << "\nHasil Quick Sort (Nama):\n";
                tampilData(temp, n);
                break;
            case 7:
                heapSortNama(temp, n);
                cout << "\nHasil Heap Sort (Nama):\n";
                tampilData(temp, n);
                break;
            case 8:
                treeSortNama(temp, n);
                cout << "\nHasil Tree Sort (Nama):\n";
                tampilData(temp, n);
                break;
            case 9:
                radixSortHarga(temp, n);
                cout << "\nHasil Radix Sort (Harga):\n";
                tampilData(temp, n);
                break;
            case 0:
                cout << "Kembali ke menu utama.\n";
                break;
            default:
                break;
        }
    } while (pilihanSort != 0);
}

void menuSearching(Obat *dataAsli, int n) {
    if (n == 0) {
        cout << "Data masih kosong!\n";
        return;
    }

    int pilihanCari;
    do {
        cout << "\n=== MENU SEARCHING ===\n";
        cout << "1. Binary Search (Nama)\n";
        cout << "2. Interpolation Search (Harga)\n";
        cout << "3. Fibonacci Search (Harga)\n";
        cout << "0. Kembali\n";
        pilihanCari = bacaIntDenganBatas("Pilih metode searching: ", 0, 3);

        Obat temp[100];
        salinData(dataAsli, temp, n);

        switch (pilihanCari) {
            case 1: {
                quickSortNama(temp, 0, n - 1);
                string targetNama;
                cout << "Nama obat yang dicari: ";
                getline(cin, targetNama);
                int idx = binarySearchNama(temp, n, targetNama);
                if (idx != -1) {
                    cout << "Data ditemukan (Binary Search):\n";
                    tampilSatuData(temp[idx]);
                } else {
                    cout << "Data tidak ditemukan.\n";
                }
                break;
            }
            case 2: {
                radixSortHarga(temp, n);
                int targetHarga = bacaIntDenganBatas("Harga yang dicari: ", 0, 1000000000);
                int idx = interpolationSearchHarga(temp, n, targetHarga);
                if (idx != -1) {
                    cout << "Data ditemukan (Interpolation Search):\n";
                    tampilSatuData(temp[idx]);
                } else {
                    cout << "Data tidak ditemukan.\n";
                }
                break;
            }
            case 3: {
                radixSortHarga(temp, n);
                int targetHarga = bacaIntDenganBatas("Harga yang dicari: ", 0, 1000000000);
                int idx = fibonacciSearchHarga(temp, n, targetHarga);
                if (idx != -1) {
                    cout << "Data ditemukan (Fibonacci Search):\n";
                    tampilSatuData(temp[idx]);
                } else {
                    cout << "Data tidak ditemukan.\n";
                }
                break;
            }
            case 0:
                cout << "Kembali ke menu utama.\n";
                break;
            default:
                break;
        }
    } while (pilihanCari != 0);
}

int main() {
    Obat dataObat[100];
    int jumlahData = 0;

    int penjualanCabang[3][12] = {0};
    bool sudahInputPenjualan = false;

    int pilihan;
    do {
        cout << "\n=== MENU SISTEM APOTEKER ===\n";
        cout << "1. Input Data Obat (Array 1D + Struct)\n";
        cout << "2. Tampilkan Data Obat\n";
        cout << "3. Hitung Total Stok (Pointer + Fungsi)\n";
        cout << "4. Input Penjualan Cabang (Array Multidimensi)\n";
        cout << "5. Tampilkan Rekap Penjualan Cabang\n";
        cout << "6. Menu Sorting\n";
        cout << "7. Menu Searching\n";
        cout << "0. Keluar\n";
        pilihan = bacaIntDenganBatas("Pilih menu: ", 0, 7);

        switch (pilihan) {
            case 1:
                inputData(dataObat, jumlahData);
                break;
            case 2:
                tampilData(dataObat, jumlahData);
                break;
            case 3:
                if (jumlahData == 0) {
                    cout << "Data obat masih kosong.\n";
                } else {
                    cout << "Total stok semua obat: " << totalStok(dataObat, jumlahData) << '\n';
                }
                break;
            case 4:
                inputPenjualanCabang(penjualanCabang, 3);
                sudahInputPenjualan = true;
                break;
            case 5:
                if (!sudahInputPenjualan) {
                    cout << "Data penjualan belum diinput.\n";
                } else {
                    tampilRekapPenjualan(penjualanCabang, 3);
                }
                break;
            case 6:
                menuSorting(dataObat, jumlahData);
                break;
            case 7:
                menuSearching(dataObat, jumlahData);
                break;
            case 0:
                cout << "Program selesai.\n";
                break;
            default:
                break;
        }
    } while (pilihan != 0);

    return 0;
}
