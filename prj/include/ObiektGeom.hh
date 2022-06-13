#ifndef OBIEKTGEOM_HH
#define OBIEKTGEOM_HH

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "Kolory.hh"
#include "Wektor3D.hh"
#include "Wektor2D.hh"
#include "MacierzRotacji3D.hh"
#include "ObrysXY.hh"
#include "TypKolizji.hh"

#define NAZWA_KARTOTEKI_PLIKOW_DO_RYSOWANIA    "pliki_do_rysowania"

class Lazik;

class ObiektGeom {
protected:
    std::string   _NazwaPliku_BrylaWzorcowa;
    std::string   _NazwaPliku_BrylaRysowana;
    std::string   _NazwaObiektu;
    int           _KolorID;
    Wektor3D      _Skala;
    MacierzRotacji3D _MacierzRotacji;
    ObrysXY _Obrys;
    Wektor3D      _Polozenie;
public:
    ObiektGeom(const char* sNazwaPliku_BrylaWzorcowa, const char* sNazwaObiektu, int KolorID);
    virtual ~ObiektGeom() {}

    void UstawPolozenie(double X, double Y, double Z) {_Polozenie[wsp::X] = X; _Polozenie[wsp::Y] = Y; _Polozenie[wsp::Z] = Z;}
    int WezKolorID() const { return _KolorID; }
    void ZmienKolorID(Kolory kolor) { _KolorID = kolor; }

    const ObrysXY & WezObrys() const {return _Obrys;}

    const std::string & WezNazweObiektu() const { return _NazwaObiektu; }
  
    const std::string & WezNazwePliku_BrylaRysowana() const
    { return _NazwaPliku_BrylaRysowana; }

    virtual TypKolizji CzyKolizja(const std::shared_ptr<Lazik> &Wsk_Lazik) const = 0;

    void Przelicz_i_Zapisz_Wierzcholki();
    void Przelicz_i_Zapisz_Wierzcholki(std::istream &StrmWe, std::ostream &StrmWy);
};



#endif
