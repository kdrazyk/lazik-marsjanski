#ifndef OBRYSXY_HH
#define OBRYSXY_HH

#include <iostream>
#include "Wektor2D.hh"

class ObrysXY
{
    private:
    Wektor2D _WierzDolnyLewy;
    Wektor2D _WierzGornyPrawy;
    public:

    const Wektor2D & WezWDL() const {return _WierzDolnyLewy;}
    const Wektor2D & WezWGP() const {return _WierzGornyPrawy;}

    Wektor2D & ZmienWDL() {return _WierzDolnyLewy;}
    Wektor2D & ZmienWGP() {return _WierzGornyPrawy;}

    bool NalozenieObrysow(const ObrysXY &Obrys2) const;
};


#endif // OBRYSXY_H_
