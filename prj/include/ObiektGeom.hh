#ifndef OBIEKTGEOM_HH
#define OBIEKTGEOM_HH

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <cmath>
#include "Kolory.hh"
#include "Wektor3D.hh"
#include "Wektor2D.hh"
#include "MacierzRotacji3D.hh"
#include "ObrysXY.hh"
#include "TypKolizji.hh"

#define NAZWA_KARTOTEKI_PLIKOW_DO_RYSOWANIA    "pliki_do_rysowania"

enum ObiektyGeom {OG_Lazik, OG_LazikSFR, OG_ProbkaRegolitu};

class Lazik; // dla metody CzyKolizja()

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
    virtual void informacje() const {cout << _NazwaObiektu << " " << _Polozenie << endl;}
    virtual int ID() const = 0;
    virtual TypKolizji CzyKolizja(const std::shared_ptr<Lazik> &Wsk_Lazik) const = 0;

    int WezKolorID() const { return _KolorID; }
    const ObrysXY & WezObrys() const {return _Obrys;}
    const Wektor3D & WezPolozenie() const {return _Polozenie;}
    double WezSzerokosc() const {return _Skala[wsp::Y];}
    double WezWysokosc() const {return _Skala[wsp::Z];}
    const std::string & WezNazweObiektu() const { return _NazwaObiektu; }
    const std::string & WezNazwePliku_BrylaRysowana() const { return _NazwaPliku_BrylaRysowana; }
    MacierzRotacji3D & WezMacierzRotacji() {return _MacierzRotacji;}
    double odlegloscOdOsi(const shared_ptr<ObiektGeom> &obiektt) const;


    void UstawPolozenie(double X, double Y, double Z) {_Polozenie[wsp::X] = X; _Polozenie[wsp::Y] = Y; _Polozenie[wsp::Z] = Z;}
    void ZmienKolorID(Kolory kolor) { _KolorID = kolor; }
    void ZmienSkale(double X, double Y, double Z) {_Skala[wsp::X] = X; _Skala[wsp::Y] = Y; _Skala[wsp::Z] = Z;}
    void Przelicz_i_Zapisz_Wierzcholki();
    void Przelicz_i_Zapisz_Wierzcholki(std::istream &StrmWe, std::ostream &StrmWy);
};



#endif
