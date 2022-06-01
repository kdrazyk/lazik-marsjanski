#include "Scena.hh"

Scena::Scena()
{
    _AktywnyLazik = nullptr;
}

Scena::Scena(const char*  sNazwaPliku_BrylaWzorcowa, const char*  sNazwaObiektu, int KolorID)
{
    _AktywnyLazik = std::make_shared<Lazik>(sNazwaPliku_BrylaWzorcowa, sNazwaObiektu, KolorID);
    //_ObiektySceny.push_front(_AktywnyLazik);
}

void Scena::dodajLazik(const char*  sNazwaPliku_BrylaWzorcowa, const char*  sNazwaObiektu, int KolorID)
{
    if (_AktywnyLazik != nullptr) _ObiektySceny.push_front(_AktywnyLazik);
    _AktywnyLazik = std::make_shared<Lazik>(sNazwaPliku_BrylaWzorcowa, sNazwaObiektu, KolorID);
}
