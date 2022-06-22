#include "LazikSFR.hh"

LazikSFR::LazikSFR(const char*  sNazwaObiektu, int KolorID):
    Lazik(sNazwaObiektu, KolorID)
{}

void LazikSFR::dodajProbkeDoListy(std::shared_ptr<ProbkaRegolitu> probka)
{
    _ListaProbek.push_front(probka);
}

void LazikSFR::wyswietlListeProbek() const
{
    int indeks = 1;
    std::list<std::shared_ptr<ProbkaRegolitu>>::const_iterator i;
    cout << "Lista probek:" << endl;
    if (_ListaProbek.empty()) {
        cout << "(brak probek)" << endl;
        return;
    }

    for (i = _ListaProbek.cbegin(); i != _ListaProbek.cend(); ++i)
        if ((*i)->ID() == OG_ProbkaRegolitu) {
            cout << setw(5) << indeks++ << ". ";
            cout << (*i)->WezNazweObiektu() << endl;
        }
}

void LazikSFR::informacje() const
{
    const int odstep = 20;
    cout << setw(odstep) << "Nazwa: " <<  _NazwaObiektu << endl
         << setw(odstep) <<"Polozenie [x,y,z]: " << _Polozenie << endl
         << setw(odstep) <<"Orientacja [st]: " << _KatOrientacji << endl
         << endl;
    wyswietlListeProbek();
    cout << endl;
}



bool LazikSFR::obroc()
{
    double kat;
    int i = 0;
    const int katObProbek = 45;
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
        for (std::shared_ptr<ProbkaRegolitu> &probka : _ListaProbek) {
        probka->WezMacierzRotacji().obrotOZ(_KatOrientacji + katObProbek*i++);
        probka->Przelicz_i_Zapisz_Wierzcholki();
    }
    this->Przelicz_i_Zapisz_Wierzcholki();

    std::this_thread::sleep_for(std::chrono::microseconds(sen));
    return _KatDoObrotu;
}

bool LazikSFR::przemiesc()
{
    using namespace wsp;
    Wektor3D kierunek;
    double odleglosc;
    int i=1;
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
    for (std::shared_ptr<ProbkaRegolitu> &probka : _ListaProbek) {
        probka->UstawPolozenie(_Polozenie[X],_Polozenie[Y],_Skala[Z] + probka->WezWysokosc()*i++);
        probka->Przelicz_i_Zapisz_Wierzcholki();
    }
    this->Przelicz_i_Zapisz_Wierzcholki();

    std::this_thread::sleep_for(std::chrono::microseconds(sen));
    return _OdlegloscDoPrzejechania;
}

std::shared_ptr<ProbkaRegolitu> LazikSFR::zdejmijProbke()
{
    std::shared_ptr<ProbkaRegolitu> probka;
    if (!_ListaProbek.empty()) {
        probka = _ListaProbek.front();
        _ListaProbek.pop_front();
    }
    else {
        probka = NULL;
    }
    return probka;
}
