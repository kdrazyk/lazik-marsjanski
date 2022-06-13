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



void ObiektGeom::Przelicz_i_Zapisz_Wierzcholki()
{
    ifstream  StrmWe(_NazwaPliku_BrylaWzorcowa);
    ofstream  StrmWy(_NazwaPliku_BrylaRysowana);

    if (!(StrmWe.is_open() && StrmWy.is_open())) {
        cerr << endl << "Nie mozna otworzyc jednego z plikow:" << endl
             << "    " << _NazwaPliku_BrylaWzorcowa << endl
             << "    " << _NazwaPliku_BrylaRysowana << endl
             << endl;
        std::exit(-1);
    }

    this->Przelicz_i_Zapisz_Wierzcholki(StrmWe, StrmWy);
}

void ObiektGeom::Przelicz_i_Zapisz_Wierzcholki(std::istream &StrmWe, std::ostream &StrmWy)
{
    using namespace wsp;
    Wektor3D wspolrzedne;
    int Indeks_Wiersza = 0;
    int i=0;
    Wektor2D WDL, WGP;
    StrmWe >> wspolrzedne;

    if (StrmWe.fail()) std::exit(-1);

    do {

        i=0;
        for (i=0; i<3; ++i)
            wspolrzedne[i] = wspolrzedne[i] * _Skala[i];

        wspolrzedne = _MacierzRotacji * wspolrzedne + _Polozenie;

        if (WDL.iloczynSkalarny(WDL) == 0 && WGP.iloczynSkalarny(WGP) == 0) {
            WDL[X] = WGP[X] = wspolrzedne[X];
            WDL[Y] = WGP[Y] = wspolrzedne[Y];
        }
        else {
            if      (wspolrzedne[X] < WDL[X]) WDL[X] = wspolrzedne[X];
            else if (wspolrzedne[X] > WGP[X]) WGP[X] = wspolrzedne[X];
            if      (wspolrzedne[Y] < WDL[Y]) WDL[Y] = wspolrzedne[Y];
            else if (wspolrzedne[Y] > WGP[Y]) WGP[Y] = wspolrzedne[Y];
        }


        StrmWy << wspolrzedne[X] << " " << wspolrzedne[Y] << " " << wspolrzedne[Z] << endl;
        ++Indeks_Wiersza;

        if (Indeks_Wiersza >= 4) {
            StrmWy << endl;
            Indeks_Wiersza = 0;
        }

        StrmWe >> wspolrzedne;
    } while (!StrmWe.fail());

    _Obrys.ZmienWDL() = WDL;
    _Obrys.ZmienWGP() = WGP;

    cout << "WDL: " << _Obrys.WezWDL() << endl;
    cout << "WGP: " << _Obrys.WezWGP() << endl;

    if (!StrmWe.eof()) std::exit(-1);

    if (!(Indeks_Wiersza == 0 && !StrmWy.fail())) std::exit(-1);
}
