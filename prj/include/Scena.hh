#ifndef SCENA_HH
#define SCENA_HH

#include <iostream>
#include <memory>
#include <list>
#include "Lazik.hh"

class Scena
{
private:

    std::list<std::shared_ptr<ObiektGeom>> _ObiektySceny;
public:
    std::shared_ptr<Lazik> _AktywnyLazik;
    Scena();
    Scena(const char*  sNazwaPliku_BrylaWzorcowa, const char*  sNazwaObiektu, int KolorID);
    void dodajLazik(const char*  sNazwaPliku_BrylaWzorcowa, const char*  sNazwaObiektu, int KolorID);
    void wyborLazika(int numer);
};








#endif
