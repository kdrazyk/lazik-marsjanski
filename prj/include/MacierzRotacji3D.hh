#ifndef MACIERZROTACJI3D_HH
#define MACIERZROTACJI3D_HH

#include <iostream>
#include <cmath>
#include "macierz.hh"

class MacierzRotacji3D: public macierz<double, 3>
{
public:
    MacierzRotacji3D();
    void obrotOX(double kat);
    void obrotOY(double kat);
    void obrotOZ(double kat);
};

#endif
