#include "Lazik.hh"

Lazik::Lazik(const char*  sNazwaObiektu, int KolorID):
    ObiektGeom("bryly_wzorcowe/szescian3.dat", sNazwaObiektu, KolorID)
{
    ZmienSkale(LAZIK_SKALA_X, LAZIK_SKALA_Y, LAZIK_SKALA_Z);
    _KatOrientacji = 0;
    _Szybkosc = 20;
    _OdlegloscDoPrzejechania = 0;
}

bool Lazik::obroc()
{
    double kat;
    const int sen = SZYBKOSC*KROK/_Szybkosc;



    if (abs(_KatDoObrotu) < KROK) {
        kat = _KatDoObrotu;
        _KatDoObrotu = 0;
    }
    else if (_KatDoObrotu > 0){
        kat = KROK;
        _KatDoObrotu -= KROK;
    }
    else {
        kat = -KROK;
        _KatDoObrotu += KROK;
    }

    _KatOrientacji += kat;
    _MacierzRotacji.obrotOZ(_KatOrientacji);
    this->Przelicz_i_Zapisz_Wierzcholki();

    std::this_thread::sleep_for(std::chrono::microseconds(sen));
    return _KatDoObrotu;
}

bool Lazik::przemiesc()
{
    Wektor3D kierunek;
    double odleglosc;
    const int sen = SZYBKOSC*KROK/_Szybkosc;

    if (abs(_OdlegloscDoPrzejechania) < KROK) {
        odleglosc = _OdlegloscDoPrzejechania;
        _OdlegloscDoPrzejechania = 0;
    }
    else if (_OdlegloscDoPrzejechania > 0) {
        odleglosc = KROK;
        _OdlegloscDoPrzejechania -= KROK;
    }
    else {
        odleglosc = -KROK;
        _OdlegloscDoPrzejechania += KROK;
    }

    kierunek[0] = 1;
    kierunek = _MacierzRotacji * kierunek;
    _Polozenie = _Polozenie + kierunek * odleglosc;
    this->Przelicz_i_Zapisz_Wierzcholki();

    std::this_thread::sleep_for(std::chrono::microseconds(sen));
    return _OdlegloscDoPrzejechania;
}

void Lazik::informacje() const
{
    const int odstep = 20;
    cout << setw(odstep) << "Nazwa: " <<  _NazwaObiektu << endl
         << setw(odstep) <<"Polozenie [x,y,z]: " << _Polozenie << endl
         << setw(odstep) <<"Orientacja [st]: " << _KatOrientacji << endl
         << endl;
}

TypKolizji Lazik::CzyKolizja(const std::shared_ptr<Lazik> &Wsk_Lazik) const
{
    if (Wsk_Lazik.get() == this) return TK_BrakKolizji;
    if (_Obrys.NalozenieObrysow(Wsk_Lazik->WezObrys())) return TK_Kolizja;
    return TK_BrakKolizji;
}

void Lazik::cofnij()
{
    if (_OdlegloscDoPrzejechania != 0) {
        _OdlegloscDoPrzejechania = -copysign(KROK, _OdlegloscDoPrzejechania);
        przemiesc();
    }
    else if (_KatDoObrotu != 0) {
        _KatDoObrotu = -copysign(KROK, _KatDoObrotu);
        obroc();
    }
}
