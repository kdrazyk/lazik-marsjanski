#include "Scena.hh"

Scena::Scena()
{
    Inicjalizuj_Lacze();
    _AktywnyLazik = nullptr;
}

Scena::Scena(const char*  sNazwaPliku_BrylaWzorcowa, const char*  sNazwaObiektu, int KolorID, double X, double Y, double Z)
{
    Inicjalizuj_Lacze();
    _AktywnyLazik = std::make_shared<Lazik>(sNazwaPliku_BrylaWzorcowa, sNazwaObiektu, KolorID);
    _ObiektySceny.push_front(_AktywnyLazik);
    _AktywnyLazik->_Polozenie[0] = X;
    _AktywnyLazik->_Polozenie[1] = Y;
    _AktywnyLazik->_Polozenie[2] = Z;
    _AktywnyLazik->Przelicz_i_Zapisz_Wierzcholki();
    _AktywnyLazik->informacje();
    DodajDoListyRysowania(*_AktywnyLazik);
}

void Scena::dodajLazik(const char*  sNazwaPliku_BrylaWzorcowa, const char*  sNazwaObiektu, int KolorID, double X, double Y, double Z)
{
    if (_AktywnyLazik != nullptr) _ObiektySceny.push_front(_AktywnyLazik);
    _AktywnyLazik = std::make_shared<Lazik>(sNazwaPliku_BrylaWzorcowa, sNazwaObiektu, KolorID);
    _AktywnyLazik->_Polozenie[0] = X;
    _AktywnyLazik->_Polozenie[1] = Y;
    _AktywnyLazik->_Polozenie[2] = Z;
    _AktywnyLazik->Przelicz_i_Zapisz_Wierzcholki();
    _AktywnyLazik->informacje();
    DodajDoListyRysowania(*_AktywnyLazik);
}

/*!
 *  \brief Inicjalizuje połączenie z programem gnuplot oraz rozmiar świata.
 *
 *  Inicjalizuje podstawowe parametry "swiata", tzn. jego wymiary,
 *  które będą widoczne jako obszar objęty układem współrzędnych.
 *  Następnie w tle uruchamiany jest program gnuplot.
 *  \param[in] rLacze - nieaktywne łącze do gnuplota.
 */

void Scena::Inicjalizuj_Lacze()
{
    Lacze.ZmienTrybRys(PzG::TR_3D);
    Lacze.UstawZakresX(-ROMIAR_POWIERZCHNI_X/2, ROMIAR_POWIERZCHNI_X/2);
    Lacze.UstawZakresY(-ROMIAR_POWIERZCHNI_Y/2, ROMIAR_POWIERZCHNI_Y/2);
    Lacze.UstawZakresZ(-0, 90);
    Lacze.UstawRotacjeXZ(40,60); // Tutaj ustawiany jest widok

    Lacze.Inicjalizuj();  // Tutaj startuje gnuplot.
}

void Scena::DodajDoListyRysowania(const Lazik  &rOb)
{
    PzG::InfoPlikuDoRysowania *wInfoPliku;

    wInfoPliku = &Lacze.DodajNazwePliku(rOb.WezNazwePliku_BrylaRysowana());
    wInfoPliku->ZmienKolor(rOb.WezKolorID());
}
