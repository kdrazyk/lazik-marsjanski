#ifndef SCENA_HH
#define SCENA_HH

#include <iostream>
#include <memory>
#include <list>
#include <map>

#include "Lazik.hh"
#include "lacze_do_gnuplota.hh"
#include "PowierzchniaMarsa.hh"

#define MAKS_ILOSC_OBIEKTOW 100

class Scena
{
private:
    PzG::LaczeDoGNUPlota  Lacze;
    std::shared_ptr<Lazik> _AktywnyLazik;
    std::list<std::shared_ptr<ObiektGeom>> _ObiektySceny;
    //std::map<int, std::shared_ptr<ObiektGeom>> _ObiektySceny;
    void Inicjalizuj_Lacze();
    void DodajDoListyRysowania(const Lazik  &rOb);
    //void dodajElementDoListy(std::shared_ptr<ObiektGeom> el, Obiekty typ);
public:
    Scena();
    void dodajLazik(const char*  sNazwaPliku_BrylaWzorcowa,
                    const char*  sNazwaObiektu, int KolorID,
                    double X, double Y, double Z);

    void wyborLazika(int numer);
    void obroc(double kat)           {_AktywnyLazik->obroc(kat);}
    void przemiesc(double odleglosc) {_AktywnyLazik->przemiesc(odleglosc);}
    void informacje() const          {_AktywnyLazik->informacje();}

    void dostepneLaziki();
    
};

//enum Obiekty {Lazik, Przeszkoda};

#endif


//Scena(const char*  sNazwaPliku_BrylaWzorcowa, const char*  sNazwaObiektu, int KolorID, double X, double Y, double Z);
