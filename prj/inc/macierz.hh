#pragma once

#include <iostream>
#include <iomanip>
#include "wektor.hh"

#define RZAD_WIELK 6

using namespace std;

template<typename T, int Rozmiar>
class macierz {
protected:
    wektor<T,Rozmiar> _kol[Rozmiar];

public:
    const wektor<T,Rozmiar> & operator[] (int el) const {return this->_kol[el];}
    wektor<T,Rozmiar> & operator[] (int el) {return this->_kol[el];}
    macierz<T, Rozmiar> operator= (const macierz<T, Rozmiar> & mKopiowana);
    wektor<T, Rozmiar> operator* (const wektor<T, Rozmiar> &wek) const;
    void do_jednostkowej();
    macierz<T,Rozmiar> odwrotna() const;
};

template<typename T, int Rozmiar>
istream & operator >> (istream &istr, macierz<T, Rozmiar> &mac)
{
    for (int i=0; i < Rozmiar; ++i)
        istr >> mac[i];
    return istr;
}

template<typename T, int Rozmiar>
ostream & operator << (ostream &ostr, const macierz<T, Rozmiar> &mac)
{
    int i,j;
    for (i=0; i < Rozmiar; ++i) {
        for (j=0; j < Rozmiar; ++j)
            ostr << setw(RZAD_WIELK) << setprecision(2) << mac[j][i];
        ostr << endl;
    }
    return ostr;
}

template<typename T, int Rozmiar>
macierz<T, Rozmiar> macierz<T, Rozmiar>::operator= (const macierz<T, Rozmiar> & mKopiowana)
{
    for (int i=0; i < Rozmiar; ++i)
        for (int j=0; j < Rozmiar; ++j)
            this->_kol[i][j] = mKopiowana[i][j];
    return *this;
}

template<typename T, int Rozmiar>
wektor<T,Rozmiar> macierz<T, Rozmiar>::operator* (const wektor<T,Rozmiar> &wek) const
{
    wektor<T,Rozmiar> wynik;
    int i,j;
    for (i=0; i < Rozmiar; ++i)
        for (j=0; j < Rozmiar; j++)
            wynik.add(i, wek[j] * this->_kol[j][i]);
    return wynik;
}

template<typename T, int Rozmiar>
void macierz<T,Rozmiar>::do_jednostkowej()
{
    int i,j;
    for (i=0; i < Rozmiar; ++i)
        for (j=0; j < Rozmiar; ++j) {
            if (i == j)
                this->_kol[i][j] = 1;
            else
                this->_kol[i][j] = 0;
        }
}

template<typename T, int Rozmiar>
macierz<T,Rozmiar> macierz<T,Rozmiar>::odwrotna() const
{
    macierz<T,Rozmiar> mOdwrotna, mKopia;
    int i,j,k;
    T mnoznik;
    mKopia = *this;
    mOdwrotna.do_jednostkowej();

    for (j=0; j < Rozmiar; ++j)
        for (i=0; i < Rozmiar; ++i) {
            k = (i+j)%Rozmiar;
            if (mKopia[k][j] != 0) {
                swap(mKopia[k],mKopia[j]);
                swap(mOdwrotna[k],mOdwrotna[j]);
                break;
            }
            else if (i==Rozmiar-1) {
                cout << "BLAD: nie udalo sie ulozyc macierzy" << endl;
                exit(-1);
            }
        }
    for (i=0; i < Rozmiar; ++i) {
        mnoznik = mKopia[i][i];
        mKopia[i] = mKopia[i] / mnoznik;
        mOdwrotna[i] = mOdwrotna[i] / mnoznik;
        for (j=1; j < Rozmiar; ++j) {
            k = (i+j)%Rozmiar;
            mnoznik = mKopia[k][i];
            mKopia[k] = mKopia[k] - (mKopia[i] * mnoznik);
            mOdwrotna[k] = mOdwrotna[k] - (mOdwrotna[i] * mnoznik);
        }
    }
    return mOdwrotna;
}
