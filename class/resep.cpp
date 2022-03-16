#include "resep.hpp"
#include <list>
#include <iterator>
#include <iostream>

using namespace std;

Resep::Resep()
{
    this->tipebarang = "-";
    this->jumlahbarang = 0;
    this->reseppembuatan = "-";
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
    this->jumlahbarang = std::stoi(*backptr);
    backptr--;
    this->tipebarang = *backptr;
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
        this->reseppembuatan+=*frontptr;
    }
    this->reseppembuatan;
}

void Resep::showResep(){
    cout<<this->reseppembuatan<<" "<<this->tipebarang<<" "<<this->tipebarang<<endl;
}