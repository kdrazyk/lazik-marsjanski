#include <iostream>
#include <fstream>
#include <cstdlib>
#include "PowierzchniaMarsa.hh"
#include "Scena.hh"
#include "Kolory.hh"

using namespace std;

void exiting(){ Wektor3D::iloscObiektow(); }


int main()
{
    Scena  scena;
    double x,y;

    std::atexit(exiting);
    if (!Inicjalizuj_PowierzchnieMarsa(scena.Lacze)) return 1;

    scena.dodajLazik("bryly_wzorcowe/szescian3.dat","FSR"         ,Kolor_JasnoNiebieski,  0,  0, 0);
    scena.dodajLazik("bryly_wzorcowe/szescian3.dat","Perseverance",Kolor_Czerwony      , 60, 60, 0);
    scena.dodajLazik("bryly_wzorcowe/szescian3.dat","Curiosity"   ,Kolor_Czerwony      ,-20, 70, 0);

    cout << endl << "Start programu gnuplot" << endl << endl;
    scena.Lacze.Rysuj();

    Wektor3D::iloscObiektow();

    while(1) {
        x = y = 0;
        cout << "Przemieszczenie: ";
        cin >> x;
        if (x==999) break;
        cout << "Obrot: ";
        cin >> y;
        scena._AktywnyLazik->przemiesc(x);
        scena._AktywnyLazik->obroc(y);
        scena._AktywnyLazik->informacje();
        scena.Lacze.Rysuj();
        Wektor3D::iloscObiektow();
    }
}
