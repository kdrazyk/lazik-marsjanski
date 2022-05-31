#ifndef LAZIK_HH
#define LAZIK_HH

#include <iostream>
#include "ObiektGeom.hh"

class Lazik: public ObiektGeom
{
    //using ObiektGeom::ObiektGeom;

private:
    double _KatOrientacji;
    double _Szybkosc;
    double _OdlegloscDoPrzejechania;
public:
    Lazik( const char*  sNazwaPliku_BrylaWzorcowa, const char*  sNazwaObiektu, int KolorID);
    void obroc(double kat);
    void przemiesc(double odleglosc);

};



#endif
