#include <iostream>
#include <fstream>
#include "ObiektGeom.hh"



using namespace std;

ObiektGeom::ObiektGeom( const char*  sNazwaPliku_BrylaWzorcowa,
                        const char*  sNazwaObiektu,
                        int          KolorID
                        ):
    _NazwaPliku_BrylaWzorcowa(sNazwaPliku_BrylaWzorcowa), _KolorID(KolorID)
{
    _NazwaObiektu = sNazwaObiektu;
    _NazwaPliku_BrylaRysowana = NAZWA_KARTOTEKI_PLIKOW_DO_RYSOWANIA;
    _NazwaPliku_BrylaRysowana += "/";
    _NazwaPliku_BrylaRysowana += sNazwaObiektu;
    _NazwaPliku_BrylaRysowana += ".dat";
    _Skala[0] = 20;
    _Skala[1] = 20;
    _Skala[2] = 10;
    _Polozenie[0] = 0;
    _Polozenie[1] = 0;
    _Polozenie[2] = 0;
}



bool ObiektGeom::Przelicz_i_Zapisz_Wierzcholki()
{
    ifstream  StrmWe(_NazwaPliku_BrylaWzorcowa);
    ofstream  StrmWy(_NazwaPliku_BrylaRysowana);

    if (!(StrmWe.is_open() && StrmWy.is_open())) {
        cerr << endl << "Nie mozna otworzyc jednego z plikow:" << endl
             << "    " << _NazwaPliku_BrylaWzorcowa << endl
             << "    " << _NazwaPliku_BrylaRysowana << endl
             << endl;
        return false;
    }

    Wektor3D wspolrzedne;
    int Indeks_Wiersza = 0;
    int i=0;

    StrmWe >> wspolrzedne;

    if (StrmWe.fail()) return false;
  
    do {
        i=0;
        for (i=0; i<3; ++i)
            wspolrzedne[i] = wspolrzedne[i] * this->_Skala[i] + this->_Polozenie[i];

        StrmWy << wspolrzedne[0] << " " << wspolrzedne[1] << " " << wspolrzedne[2] << endl;
        ++Indeks_Wiersza;
    
        if (Indeks_Wiersza >= 4) {
            StrmWy << endl;
            Indeks_Wiersza = 0;
        }

        StrmWe >> wspolrzedne;
    } while (!StrmWe.fail());

    if (!StrmWe.eof()) return false;
  
    return Indeks_Wiersza == 0 && !StrmWy.fail();
}
