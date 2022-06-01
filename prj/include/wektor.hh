#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

#define SZEROKOSC 6
#define PRECYZJA  1

template <typename T, int Rozmiar>
class wektor {
private:
    inline static int _AktualnaIlosc;
    inline static int _LacznaIlosc;
    T _wsp[Rozmiar];

public:
    wektor();
    ~wektor();

    const T & operator[] (int el) const {return this->_wsp[el];}
    T & operator[] (int el) {return this->_wsp[el];}
    void add(int x, T y) {_wsp[x] += y;}
    T iloczynSkalarny(const wektor<T, Rozmiar> &wek2) const;
    double dlugosc();
    static void iloscObiektow();

    wektor<T,Rozmiar> operator + (const wektor<T, Rozmiar> &wektor2) const;
    wektor<T,Rozmiar> operator - (const wektor<T, Rozmiar> &wektor2) const;
    wektor<T,Rozmiar> operator * (T liczba) const;
    wektor<T,Rozmiar> operator / (T liczba) const;
};

template <typename T, int Rozmiar>
wektor<T,Rozmiar>::wektor() {
    for (T &wsp: _wsp) wsp = 0;
    ++_AktualnaIlosc;
    ++_LacznaIlosc;
}

template <typename T, int Rozmiar>
wektor<T,Rozmiar>::~wektor() {
    --_AktualnaIlosc;
}

template <typename T, int Rozmiar>
void wektor<T,Rozmiar>::iloscObiektow() {
    cout << "Aktualna ilosc obiektow klasy wektor: " << _AktualnaIlosc << endl
         << "Laczna ilosc obiektow klasy wektor: "   << _LacznaIlosc   << endl;
}




template <typename T, int Rozmiar>
istream & operator >> (istream &istr, wektor<T,Rozmiar> &wek)
{
    for (int i=0; i < Rozmiar; ++i)
        istr >> wek[i];
    return istr;
}

template <typename T, int Rozmiar>
ostream & operator << (ostream &ostr, const wektor<T,Rozmiar> &wek)
{
    int precyzja = ostr.precision();
    ostr << "[";
    for (int i=0; i < Rozmiar; ++i) {
        //ostr  << scientific << setprecision(PRECYZJA) << wek[i];
        ostr   << fixed << setprecision(PRECYZJA) << wek[i];
        ostr << (i==Rozmiar-1 ? "" : ",");
    }
    ostr << "]";
    ostr.precision(precyzja);
    ostr << defaultfloat;
    return ostr;
}

template <typename T, int Rozmiar>
T wektor<T,Rozmiar>::iloczynSkalarny(const wektor<T, Rozmiar> &wek2) const
{
    T wynik;
    wynik = 0;
    for (int i=0; i < Rozmiar; ++i)
        wynik += this->_wsp[i] * wek2._wsp[i];
    return wynik;
}

template <typename T, int Rozmiar>
wektor<T,Rozmiar> wektor<T,Rozmiar>::operator + (const wektor<T, Rozmiar> &wektor2) const
{
    wektor<T,Rozmiar> wynik;
    for (int i=0; i < Rozmiar; ++i)
        wynik[i] = this->_wsp[i] + wektor2._wsp[i];
    return wynik;
}

template <typename T, int Rozmiar>
wektor<T,Rozmiar> wektor<T,Rozmiar>::operator - (const wektor<T, Rozmiar> &wektor2) const
{
    wektor<T,Rozmiar> wynik;
    for (int i=0; i < Rozmiar; ++i)
        wynik[i] = this->_wsp[i] - wektor2._wsp[i];
    return wynik;
}

template <typename T, int Rozmiar>
wektor<T,Rozmiar> wektor<T,Rozmiar>::operator * (T liczba) const
{
    wektor<T,Rozmiar> wynik;
    for (int i=0; i < Rozmiar; ++i)
        wynik[i] = this->_wsp[i] * liczba;
    return wynik;
}

template <typename T, int Rozmiar>
wektor<T,Rozmiar> wektor<T,Rozmiar>::operator / (T liczba) const
{
    wektor<T,Rozmiar> wynik;
    for (int i=0; i < Rozmiar; ++i)
        wynik[i] = this->_wsp[i] / liczba;
    return wynik;
}
