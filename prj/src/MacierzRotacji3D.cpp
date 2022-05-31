#include "MacierzRotacji3D.hh"

MacierzRotacji3D::MacierzRotacji3D()
{
    int i,j;
    for (i=0; i<3; ++i)
        for (j=0; j<3; ++j)
            _kol[i][j] = (i==j);
}

void MacierzRotacji3D::obrotOX(double kat)
{
    _kol[1][1] =  std::cos(kat);
    _kol[2][2] = _kol[1][1];
    _kol[2][1] = std::sin(kat);
    _kol[1][2] = -_kol[1][0];
}

void MacierzRotacji3D::obrotOY(double kat)
{
    _kol[0][0] =  std::cos(kat);
    _kol[2][2] = _kol[0][0];
    _kol[2][0] = std::sin(kat);
    _kol[0][2] = -_kol[1][0];
}

void MacierzRotacji3D::obrotOZ(double kat)
{
    _kol[0][0] =  std::cos(kat);
    _kol[1][1] = _kol[0][0];
    _kol[1][0] = std::sin(kat);
    _kol[0][1] = -_kol[1][0];
}
