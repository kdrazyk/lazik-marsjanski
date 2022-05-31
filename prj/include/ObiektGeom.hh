#ifndef OBIEKTGEOM_HH
#define OBIEKTGEOM_HH

#include <iostream>
#include <fstream>
#include <string>
#include "Wektor3D.hh"
#include "MacierzRotacji3D.hh"

#define NAZWA_KARTOTEKI_PLIKOW_DO_RYSOWANIA    "pliki_do_rysowania"

class ObiektGeom {
protected:
    std::string   _NazwaPliku_BrylaWzorcowa;
    std::string   _NazwaPliku_BrylaRysowana;
    std::string   _NazwaObiektu;
    int           _KolorID;
    Wektor3D      _Skala;
    MacierzRotacji3D _MacierzRotacji;

public:
    Wektor3D      _Polozenie;

    ObiektGeom(const char* sNazwaPliku_BrylaWzorcowa, const char* sNazwaObiektu, int KolorID);

    int WezKolorID() const { return _KolorID; }
  
    const std::string & WezNazweObiektu() const { return _NazwaObiektu; }
  
    const std::string & WezNazwePliku_BrylaRysowana() const
    { return _NazwaPliku_BrylaRysowana; }

    void Przelicz_i_Zapisz_Wierzcholki() const;
    void Przelicz_i_Zapisz_Wierzcholki(std::istream &StrmWe, std::ostream &StrmWy) const;
};


#endif
