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

int Scena::dodajElementDoListy(std::shared_ptr<ObiektGeom> el, Obiekt typ)
{
    int i;
    for (i=MAKS_ILOSC_OBIEKTOW * typ; _ObiektySceny.count(i); ++i);
    _ObiektySceny.emplace(i,el);
    return i;
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


void Scena::dodajLazik(const char*  sNazwaPliku_BrylaWzorcowa, const char*  sNazwaObiektu, double X, double Y, double Z)
{
    std::shared_ptr<Lazik> lazik = std::make_shared<Lazik>(sNazwaPliku_BrylaWzorcowa, sNazwaObiektu, NIEAKTYWNY_LAZIK_KOLOR);
    lazik->UstawPolozenie(X, Y, Z);
    lazik->Przelicz_i_Zapisz_Wierzcholki();
    DodajDoListyRysowania(lazik);
    dodajElementDoListy(lazik, Lazik_t);
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
    for (i = _ObiektySceny.cbegin(); i != _ObiektySceny.cend(); ++i)
            if (i->second->CzyKolizja(_AktywnyLazik)) _AktywnyLazik->cofnij();
}

void Scena::informacje() const
{
    if (_AktywnyLazik)
        _AktywnyLazik->informacje();
    else
        cout << "Brak aktywnego lazika" << endl;
}










// Scena::Scena(const char*  sNazwaPliku_BrylaWzorcowa, const char*  sNazwaObiektu, int KolorID, double X, double Y, double Z)
// {
//     Inicjalizuj_Lacze();
//     Inicjalizuj_PowierzchnieMarsa(Lacze);
//     dodajLazik(sNazwaPliku_BrylaWzorcowa, sNazwaObiektu, KolorID, X, Y, Z);
// }
