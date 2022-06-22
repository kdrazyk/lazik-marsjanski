#include "Scena.hh"

// PRIVATE --------------------------------------------------------------------------------//

void Scena::Inicjalizuj_Lacze()
{
    Lacze.ZmienTrybRys(PzG::TR_3D);
    Lacze.UstawZakresX(-ROMIAR_POWIERZCHNI_X/2, ROMIAR_POWIERZCHNI_X/2);
    Lacze.UstawZakresY(-ROMIAR_POWIERZCHNI_Y/2, ROMIAR_POWIERZCHNI_Y/2);
    Lacze.UstawZakresZ(-0, 90);
    Lacze.UstawRotacjeXZ(40,60); // Tutaj ustawiany jest widok
    Lacze.Inicjalizuj();  // Tutaj startuje gnuplot.
}

void Scena::DodajDoListyRysowania(std::shared_ptr<ObiektGeom> rOb)
{
    PzG::InfoPlikuDoRysowania *wInfoPliku;
    wInfoPliku = &Lacze.DodajNazwePliku(rOb->WezNazwePliku_BrylaRysowana());
    wInfoPliku->ZmienKolor(rOb->WezKolorID());
}

void Scena::UsunZListyRysowania(std::shared_ptr<ObiektGeom> Ob)
{
    Lacze.UsunNazwePliku(Lacze.ZnajdzNazwePliku(Ob->WezNazwePliku_BrylaRysowana()));
    Lacze.Rysuj();
}

int Scena::dodajElementDoListy(std::shared_ptr<ObiektGeom> el, Obiekt typ)
{
    int i;
    for (i=MAKS_ILOSC_OBIEKTOW * typ; _ObiektySceny.count(i); ++i);
    _ObiektySceny.emplace(i,el);
    return i;
    // _ObiektyScenyB.push_front(el);
    // return 0;
}

// PUBLIC --------------------------------------------------------------------------------//

Scena::Scena()
{
    Inicjalizuj_Lacze();
    Inicjalizuj_PowierzchnieMarsa(Lacze);
    _AktywnyLazik = nullptr;
    Lacze.Rysuj();
}

/*!
 *  \brief Inicjalizuje połączenie z programem gnuplot oraz rozmiar świata.
 *
 *  Inicjalizuje podstawowe parametry "swiata", tzn. jego wymiary,
 *  które będą widoczne jako obszar objęty układem współrzędnych.
 *  Następnie w tle uruchamiany jest program gnuplot.
 *  \param[in] rLacze - nieaktywne łącze do gnuplota.
 */


void Scena::dodajLazik(const char*  sNazwaObiektu, double X, double Y, double Z)
{
    std::shared_ptr<Lazik> lazik = std::make_shared<Lazik>(sNazwaObiektu, NIEAKTYWNY_LAZIK_KOLOR);
    lazik->UstawPolozenie(X, Y, Z);
    lazik->Przelicz_i_Zapisz_Wierzcholki();
    DodajDoListyRysowania(lazik);
    dodajElementDoListy(lazik, Lazik_t);
    Lacze.Rysuj();
}

void Scena::dodajLazikSFR(const char*  sNazwaObiektu, double X, double Y, double Z)
{
    std::shared_ptr<Lazik> lazik = std::make_shared<LazikSFR>(sNazwaObiektu, NIEAKTYWNY_LAZIK_KOLOR);
    lazik->UstawPolozenie(X, Y, Z);
    lazik->Przelicz_i_Zapisz_Wierzcholki();
    DodajDoListyRysowania(lazik);
    dodajElementDoListy(lazik, Lazik_t);
    Lacze.Rysuj();
}


void Scena::dodajProbkeRegolitu(const char*  sNazwaObiektu, int KolorID, double X, double Y, double Z)
{
    std::shared_ptr<ProbkaRegolitu> probka = std::make_shared<ProbkaRegolitu>(sNazwaObiektu, KolorID);
    probka->UstawPolozenie(X, Y, Z);
    probka->Przelicz_i_Zapisz_Wierzcholki();
    DodajDoListyRysowania(probka);
    dodajElementDoListy(probka, Probka_t);
    Lacze.Rysuj();
}


void Scena::dodajProbkeRegolitu(std::shared_ptr<ProbkaRegolitu> probka)
{
    using namespace wsp;
    Wektor3D polozenie;
    polozenie = probka->WezPolozenie();
    probka->UstawPolozenie(polozenie[X],polozenie[Y],0);
    probka->Przelicz_i_Zapisz_Wierzcholki();
    dodajElementDoListy(probka, Probka_t);
    Lacze.Rysuj();
}



void Scena::dostepneLaziki()
{
    for (int i = Lazik_t * MAKS_ILOSC_OBIEKTOW; _ObiektySceny.count(i); ++i) {
        std::shared_ptr<Lazik> lazik = std::static_pointer_cast<Lazik>(_ObiektySceny[i]);
        cout << i << ((lazik == _AktywnyLazik) ? ". AKTYWNY" : ". NIEAKTYWNY") << endl;
        lazik->informacje();
    }

}

void Scena::zmienAktywnyLazik(int numer)
{
    _AktywnyLazik = std::static_pointer_cast<Lazik>(_ObiektySceny[Lazik_t * MAKS_ILOSC_OBIEKTOW
                                                                  + numer]);
    for (int i=MAKS_ILOSC_OBIEKTOW * Lazik_t; _ObiektySceny.count(i); ++i) {
        std::shared_ptr<Lazik> lazik = std::static_pointer_cast<Lazik>(_ObiektySceny[i]);
        ZmienKolorObiektu(lazik, NIEAKTYWNY_LAZIK_KOLOR);
    }
    ZmienKolorObiektu(_AktywnyLazik, AKTYWNY_LAZIK_KOLOR);
}

void Scena::ZmienKolorObiektu(std::shared_ptr<ObiektGeom> rOb, Kolory kolor)
{
    PzG::InfoPlikuDoRysowania *wInfoPliku;
    rOb->ZmienKolorID(kolor);
    wInfoPliku = Lacze.ZnajdzNazwePliku(rOb->WezNazwePliku_BrylaRysowana());
    wInfoPliku->ZmienKolor(rOb->WezKolorID());
    Lacze.Rysuj();
}


void Scena::obroc(double kat)
{
    _AktywnyLazik->UstawKatDoObrotu(kat);
    while (_AktywnyLazik->obroc()) {
        KontrolaKolizji();
        Lacze.Rysuj();
    }
}


void Scena::przemiesc(double odleglosc)
{
    _AktywnyLazik->UstawOdlegloscDoPrzejechania(odleglosc);
    while (_AktywnyLazik->przemiesc()) {
        KontrolaKolizji();
        Lacze.Rysuj();
    }
}

void Scena::KontrolaKolizji() {
    std::map<int, std::shared_ptr<ObiektGeom>>::const_iterator i;
    for (i = _ObiektySceny.cbegin(); i != _ObiektySceny.cend(); ++i) {
        if (i->second->CzyKolizja(_AktywnyLazik) == TK_Kolizja)
            _AktywnyLazik->cofnij();
    }
}

void Scena::informacje() const
{
    if (_AktywnyLazik)
        _AktywnyLazik->informacje();
    else
        cout << "Brak aktywnego lazika" << endl;
}


void Scena::WyswietlProbki() const
{
    int indeks = 1;
    std::map<int, std::shared_ptr<ObiektGeom>>::const_iterator i;
    cout << "Lista probek na scenie:" << endl;
    for (i = _ObiektySceny.cbegin(); i != _ObiektySceny.cend(); ++i)
        if (i->second->ID() == OG_ProbkaRegolitu) {
            cout << setw(5) << indeks++ << ". ";
            i->second->informacje();
            cout << endl;
        }
}


void Scena::podniesProbke()
{
    using namespace wsp;
    Wektor3D wzglednePolozenie;
    std::map<int, std::shared_ptr<ObiektGeom>>::const_iterator i;
    std::map<int, std::shared_ptr<ObiektGeom>>::const_iterator np; //najblizszaProbka
    double odleglosc, odlegloscMin;
    const double zasieg = 30;

    if (_AktywnyLazik->ID() != OG_LazikSFR) {
        cout << "Operacja dostepna tylko dla lazika SFR" << endl;
        return;
    }

    for (i = _ObiektySceny.cbegin(); i->second->ID() != OG_ProbkaRegolitu; ++i)
        np = i;

    wzglednePolozenie = _AktywnyLazik->WezPolozenie() - np->second->WezPolozenie();
    odlegloscMin = odleglosc = wzglednePolozenie.dlugosc();

    for (; i != _ObiektySceny.cend(); ++i) {
        if (i->second->ID() == OG_ProbkaRegolitu) {
            wzglednePolozenie = _AktywnyLazik->WezPolozenie() - i->second->WezPolozenie();
            odleglosc = wzglednePolozenie.dlugosc();
            if (odleglosc < odlegloscMin) {
                odlegloscMin = odleglosc;
                np = i;
            }
        }
    }

    if (odlegloscMin < zasieg) {
        cout << "Podniesiono probke:" << endl;
        np->second->informacje();
        cout << endl;
        std::static_pointer_cast<LazikSFR>(_AktywnyLazik)->dodajProbkeDoListy(std::static_pointer_cast<ProbkaRegolitu>(np->second));
        //UsunZListyRysowania(np->second);
        _ObiektySceny.erase(np);
    }
    else {
        cout << "Nie znaleziono probki w zasiegu" << endl;
    }

}

void Scena::zostawProbke()
{
    using namespace wsp;
    std::shared_ptr<ProbkaRegolitu> probka;
    if (_AktywnyLazik->ID() != OG_LazikSFR) {
        cout << "Operacja dostepna tylko dla lazika SFR" << endl;
        return;
    }
    probka = std::static_pointer_cast<LazikSFR>(_AktywnyLazik)->zdejmijProbke();
    if (probka != NULL)
        dodajProbkeRegolitu(probka);
    else
        cout << "Brak probek na laziku" << endl;
}
