#include "resep.hpp"
#include <list>
#include <iterator>
#include <iostream>

using namespace std;

Resep::Resep()
{
    this->namaBarang = "-";
    this->jumlahBarang = 0;
    this->resepPembuatan = "-";
}

Resep::Resep(string isi_resep)
{
    list<string> templist;
    list<string>::iterator frontptr;
    list<string>::iterator backptr;
    string temp = "";
    for (auto x : isi_resep)
    {
        if (x == ' ')
        {
            templist.push_back(temp);
            temp = "";
        }
        else
        {
            temp += x;
        }
    }
    templist.push_back(temp);
    // for (std::list<string>::iterator it = templist.begin(); it != templist.end(); ++it)
    // {
    //     cout<<*it<<" ";
    // }
    // cout<<""<<endl;
    frontptr = templist.begin();
    frontptr++;
    frontptr++;
    backptr = templist.end();
    backptr--;
    backptr--;
    this->jumlahBarang = std::stoi(*backptr);
    backptr--;
    this->namaBarang = *backptr;
    backptr--;
    while (*frontptr=="-")
    {
        frontptr++;
    }
    while (*backptr=="-")
    {
       backptr--;
    }
    backptr++;
    for ( frontptr; frontptr != backptr; frontptr++)
    {
        this->resepPembuatan+=*frontptr;
    }
    this->resepPembuatan;
}

string Resep::getResep() const{
    return this->resepPembuatan;
}
void Resep::showResep(){
    cout<<this->resepPembuatan<<" "<<this->namaBarang<<" "<<this->jumlahBarang<<endl;
}

string Resep::getNamaBarang() const{
    return this->namaBarang;
}