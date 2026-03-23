#include <iostream>
#include <string>
#include <limits>
using namespace std;

const int MAX_DATA = 100;

// STRUCT
struct Obat {
    string nama;
    int harga;
    int stok;
};

// PROSEDUR INPUT DATA
void inputData(Obat *data, int &n) {
    cout << "Jumlah data: ";
    if(!(cin >> n)) {
        cout << "Input jumlah data tidak valid!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if(n < 0 || n > MAX_DATA) {
        cout << "Jumlah data harus antara 0 sampai " << MAX_DATA << "!\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        n = 0;
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for(int i = 0; i < n; i++) {
        cout << "\nData ke-" << i+1 << endl;
        cout << "Nama Obat: ";
        getline(cin, data[i].nama);
        cout << "Harga: ";
        while(!(cin >> data[i].harga) || data[i].harga < 0) {
            cout << "Harga harus angka >= 0. Ulangi: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Stok: ";
        while(!(cin >> data[i].stok) || data[i].stok < 0) {
            cout << "Stok harus angka >= 0. Ulangi: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// PROSEDUR TAMPILKAN DATA
void tampilData(Obat *data, int n) { // array dan pointer
    cout << "\n=== DATA OBAT ===\n";
    for(int i = 0; i < n; i++) {
        cout << i+1 << ". " << data[i].nama
             << " | Harga: " << data[i].harga
             << " | Stok: " << data[i].stok << endl;
    }
}

// FUNGSI TOTAL STOK
int totalStok(Obat *data, int n) {
    int total = 0;
    for(int i = 0; i < n; i++) {
        total += data[i].stok;
    }
    return total;
}


// BUBBLE SORT (berdasarkan nama)
void bubbleSort(Obat *data, int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(data[j].nama > data[j+1].nama) {
                swap(data[j], data[j+1]); // akses array
            }
        }
    }
}

// SELECTION SORT (berdasarkan harga)
void selectionSort(Obat *data, int n) {
    for(int i = 0; i < n-1; i++) {
        int min = i;
        for(int j = i+1; j < n; j++) {
            if(data[j].harga < data[min].harga) {
                min = j;
            }
        }
        swap(data[i], data[min]);
    }
}


// LINEAR SEARCH (cari nama)
void linearSearch(Obat *data, int n, string cari) {
    bool found = false;
    for(int i = 0; i < n; i++) {
        if(data[i].nama == cari) {
            cout << "Ditemukan: " << data[i].nama
                 << " | Harga: " << data[i].harga
                 << " | Stok: " << data[i].stok << endl;
            found = true;
        }
    }
    if(!found) cout << "Data tidak ditemukan!\n";
}

// BINARY SEARCH (lebih cepat)
int binarySearch(Obat *data, int n, string cari) {
    int kiri = 0, kanan = n - 1;

    while(kiri <= kanan) {
        int tengah = (kiri + kanan) / 2;

        if(data[tengah].nama == cari)
            return tengah;
        else if(data[tengah].nama < cari)
            kiri = tengah + 1;
        else
            kanan = tengah - 1;
    }
    return -1;
}

// main
int main() {
    Obat data[MAX_DATA]; // array 1 dimensi
    int n = 0, pilihan;
    string cari;

    do {
        cout << "\n=== MENU APOTEK ===\n";
        cout << "1. Input Data\n";
        cout << "2. Tampilkan Data\n";
        cout << "3. Total Stok\n";
        cout << "4. Sorting Nama (Bubble)\n";
        cout << "5. Sorting Harga (Selection)\n";
        cout << "6. Linear Search\n";
        cout << "7. Binary Search\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        if(!(cin >> pilihan)) {
            cout << "Pilihan harus berupa angka!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(pilihan) {
            case 1: inputData(data, n); break;
            case 2:
                if(n == 0) cout << "Data masih kosong!\n";
                else tampilData(data, n);
                break;
            case 3:
                if(n == 0) cout << "Data masih kosong!\n";
                else cout << "Total Stok: " << totalStok(data, n) << endl;
                break;

            case 4:
                if(n == 0) {
                    cout << "Data masih kosong!\n";
                    break;
                }
                bubbleSort(data, n);
                cout << "Data diurutkan berdasarkan nama!\n";
                break;

            case 5:
                if(n == 0) {
                    cout << "Data masih kosong!\n";
                    break;
                }
                selectionSort(data, n);
                cout << "Data diurutkan berdasarkan harga!\n";
                break;

            case 6:
                if(n == 0) {
                    cout << "Data masih kosong!\n";
                    break;
                }
                cout << "Cari nama: ";
                getline(cin, cari);
                linearSearch(data, n, cari);
                break;

            case 7:
                if(n == 0) {
                    cout << "Data masih kosong!\n";
                    break;
                }
                bubbleSort(data, n); // wajib urut dulu
                cout << "Cari nama: ";
                getline(cin, cari);
                {
                    int hasil = binarySearch(data, n, cari);

                    if(hasil != -1) {
                        cout << "Ditemukan: " << data[hasil].nama
                             << " | Harga: " << data[hasil].harga
                             << " | Stok: " << data[hasil].stok << endl;
                    } else {
                        cout << "Data tidak ditemukan!\n";
                    }
                }
                break;

            case 0:
                cout << "Program selesai.\n";
                break;

            default:
                cout << "Pilihan tidak tersedia!\n";
                break;
        }

    } while(pilihan != 0);

    return 0;
}



// utk di video
// void insertionSort(Obat *data, int n) {
//     for(int i = 1; i < n; i++) {
//         Obat key = data[i];
//         int j = i - 1;

//         while(j >= 0 && data[j].nama > key.nama) {
//             data[j+1] = data[j];
//             j--;
//         }
//         data[j+1] = key;
//     }
// }


// void merge(Obat *data, int l, int m, int r) {
//     int n1 = m - l + 1;
//     int n2 = r - m;

//     Obat L[100], R[100];

//     for(int i = 0; i < n1; i++) L[i] = data[l + i];
//     for(int j = 0; j < n2; j++) R[j] = data[m + 1 + j];

//     int i = 0, j = 0, k = l;

//     while(i < n1 && j < n2) {
//         if(L[i].nama <= R[j].nama) data[k++] = L[i++];
//         else data[k++] = R[j++];
//     }

//     while(i < n1) data[k++] = L[i++];
//     while(j < n2) data[k++] = R[j++];
// }

// void mergeSort(Obat *data, int l, int r) {
//     if(l < r) {
//         int m = (l + r) / 2;
//         mergeSort(data, l, m);
//         mergeSort(data, m+1, r);
//         merge(data, l, m, r);
//     }
// }

// void shellSort(Obat *data, int n) {
//     for(int gap = n/2; gap > 0; gap /= 2) {
//         for(int i = gap; i < n; i++) {
//             Obat temp = data[i];
//             int j;
//             for(j = i; j >= gap && data[j-gap].nama > temp.nama; j -= gap) {
//                 data[j] = data[j-gap];
//             }
//             data[j] = temp;
//         }
//     }
// }

// int partition(Obat *data, int low, int high) {
//     string pivot = data[high].nama;
//     int i = low - 1;

//     for(int j = low; j < high; j++) {
//         if(data[j].nama < pivot) {
//             i++;
//             swap(data[i], data[j]);
//         }
//     }
//     swap(data[i+1], data[high]);
//     return i + 1;
// }

// void quickSort(Obat *data, int low, int high) {
//     if(low < high) {
//         int pi = partition(data, low, high);
//         quickSort(data, low, pi - 1);
//         quickSort(data, pi + 1, high);
//     }
// }

// void heapify(Obat *data, int n, int i) {
//     int terbesar = i;
//     int kiri = 2*i + 1;
//     int kanan = 2*i + 2;

//     if(kiri < n && data[kiri].nama > data[terbesar].nama)
//         terbesar = kiri;

//     if(kanan < n && data[kanan].nama > data[terbesar].nama)
//         terbesar = kanan;

//     if(terbesar != i) {
//         swap(data[i], data[terbesar]);
//         heapify(data, n, terbesar);
//     }
// }

// void heapSort(Obat *data, int n) {
//     for(int i = n/2 - 1; i >= 0; i--)
//         heapify(data, n, i);

//     for(int i = n-1; i > 0; i--) {
//         swap(data[0], data[i]);
//         heapify(data, i, 0);
//     }
// }

// int getMax(Obat *data, int n) {
//     int max = data[0].harga;
//     for(int i = 1; i < n; i++)
//         if(data[i].harga > max)
//             max = data[i].harga;
//     return max;
// }

// void countingSort(Obat *data, int n, int exp) {
//     Obat output[100];
//     int count[10] = {0};

//     for(int i = 0; i < n; i++)
//         count[(data[i].harga / exp) % 10]++;

//     for(int i = 1; i < 10; i++)
//         count[i] += count[i - 1];

//     for(int i = n - 1; i >= 0; i--) {
//         int idx = (data[i].harga / exp) % 10;
//         output[count[idx] - 1] = data[i];
//         count[idx]--;
//     }

//     for(int i = 0; i < n; i++)
//         data[i] = output[i];
// }

// void radixSort(Obat *data, int n) {
//     int max = getMax(data, n);
//     for(int exp = 1; max/exp > 0; exp *= 10)
//         countingSort(data, n, exp);
// }