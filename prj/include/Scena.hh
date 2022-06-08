#ifndef SCENA_HH
#define SCENA_HH

#include <iostream>
#include <memory>
#include <list>
#include "Lazik.hh"
#include "lacze_do_gnuplota.hh"
#include "PowierzchniaMarsa.hh"

class Scena
{
private:
    std::list<std::shared_ptr<ObiektGeom>> _ObiektySceny;


public:
    PzG::LaczeDoGNUPlota  Lacze;
    std::shared_ptr<Lazik> _AktywnyLazik;
    Scena();
    Scena(const char*  sNazwaPliku_BrylaWzorcowa, const char*  sNazwaObiektu, int KolorID, double X, double Y, double Z);
    void dodajLazik(const char*  sNazwaPliku_BrylaWzorcowa, const char*  sNazwaObiektu, int KolorID, double X, double Y, double Z);
    void wyborLazika(int numer);
    void Inicjalizuj_Lacze();
    void DodajDoListyRysowania(const Lazik  &rOb);
};

#endif
