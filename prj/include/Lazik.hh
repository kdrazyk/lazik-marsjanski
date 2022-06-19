#ifndef LAZIK_HH
#define LAZIK_HH

#include <unistd.h>
#include <iostream>
#include <cmath>
#include "ObiektGeom.hh"

#define KROK 0.5
#define SZYBKOSC 30000

#define LAZIK_SKALA_X 20
#define LAZIK_SKALA_Y 20
#define LAZIK_SKALA_Z 10



class Lazik: public ObiektGeom
{
protected:
    double _KatOrientacji;
    double _Szybkosc;
    double _OdlegloscDoPrzejechania;
    double _KatDoObrotu;

public:
    Lazik(const char*  sNazwaObiektu, int KolorID);
    bool obroc();
    bool przemiesc();
    void cofnij();
    void UstawOdlegloscDoPrzejechania(double odleglosc) {_OdlegloscDoPrzejechania = odleglosc;}
    void UstawKatDoObrotu(double kat) {_KatDoObrotu = kat;}

    virtual void informacje() const override;
    virtual int ID() const override {return OG_Lazik;}
    virtual TypKolizji CzyKolizja(const std::shared_ptr<Lazik> &Wsk_Lazik) const override;
};


#endif
