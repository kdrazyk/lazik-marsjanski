#include "Lazik.hh"

Lazik::Lazik( const char*  sNazwaPliku_BrylaWzorcowa, const char*  sNazwaObiektu, int KolorID):
    ObiektGeom(sNazwaPliku_BrylaWzorcowa, sNazwaObiektu, KolorID)
{
    _KatOrientacji = 0;
    _Szybkosc = 100;
    _OdlegloscDoPrzejechania = 0;
}

void Lazik::obroc(double kat)
{
    _KatOrientacji += kat;
    _MacierzRotacji.obrotOZ(_KatOrientacji);
    this->Przelicz_i_Zapisz_Wierzcholki();
}


void Lazik::przemiesc(double odleglosc)
{
    Wektor3D kierunek;
    kierunek[0] = 1;
    kierunek = _MacierzRotacji * kierunek;
    _Polozenie = _Polozenie + kierunek * odleglosc;
    this->Przelicz_i_Zapisz_Wierzcholki();
}
