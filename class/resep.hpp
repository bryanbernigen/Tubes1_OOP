#ifndef _RESEP_HPP_
#define _RESEP_HPP_

#include <string>

using namespace std;

class Resep
{
private:
    string namaBarang;
    int jumlahBarang;
    string resepPembuatan;
public:
    Resep();
    /*Membuat resep dari sebuah file txt  dengan format
    panjang_matrix lebar_matrix
    x x x
    x x x
    x x x
    nama_item jumlah_item
    File tesebut sudah dibuat menjadi sebuah string yang tiap barisnya diappend dengan +=
    *Catatan: jumlah x tergantung panjang_matrix dan lebar_matrix
    */
    Resep(string isi_resep);
    string getNamaBarang() const;
    string getResep () const;
    int getJumlah() const;
    void showResep();
};


#endif