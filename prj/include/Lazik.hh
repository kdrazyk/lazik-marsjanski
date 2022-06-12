#ifndef LAZIK_HH
#define LAZIK_HH

#include <unistd.h>
#include <iostream>
#include "ObiektGeom.hh"

#define KROK 0.5
#define SZYBKOSC 30000

class Lazik: public ObiektGeom
{
protected:
    double _KatOrientacji;
    double _Szybkosc;
    double _OdlegloscDoPrzejechania;
    double _KatDoObrotu;

public:
    Lazik(const char*  sNazwaPliku_BrylaWzorcowa, const char*  sNazwaObiektu, int KolorID);
    bool obroc();
    bool przemiesc();
    void informacje() const;
    void UstawOdlegloscDoPrzejechania(double odleglosc) {_OdlegloscDoPrzejechania = odleglosc;}
    void UstawKatDoObrotu(double kat) {_KatDoObrotu = kat;}
};



#endif
