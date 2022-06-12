#ifndef SCENA_HH
#define SCENA_HH

#include <iostream>
#include <memory>
#include <list>
#include <map>

#include "Lazik.hh"
#include "lacze_do_gnuplota.hh"
#include "PowierzchniaMarsa.hh"

#define MAKS_ILOSC_OBIEKTOW 100
#define AKTYWNY_LAZIK_KOLOR Kolor_JasnoNiebieski
#define NIEAKTYWNY_LAZIK_KOLOR Kolor_Czerwony

enum Obiekt {Lazik_t, Przeszkoda_t};

class Scena
{
private:
    PzG::LaczeDoGNUPlota  Lacze;
    std::shared_ptr<Lazik> _AktywnyLazik;
    std::map<int, std::shared_ptr<ObiektGeom>> _ObiektySceny;
    void Inicjalizuj_Lacze();
    void DodajDoListyRysowania(std::shared_ptr<ObiektGeom>  rOb);
    int dodajElementDoListy(std::shared_ptr<ObiektGeom> el, Obiekt typ);
public:
    Scena();
    void dodajLazik(const char*  sNazwaPliku_BrylaWzorcowa,
                    const char*  sNazwaObiektu,
                    double X, double Y, double Z);

    void wyborLazika(int numer);
    void obroc(double kat) {
        _AktywnyLazik->UstawKatDoObrotu(kat);
        while (_AktywnyLazik->obroc()) Lacze.Rysuj();}


    void przemiesc(double odleglosc) {
        _AktywnyLazik->UstawOdlegloscDoPrzejechania(odleglosc);
        while (_AktywnyLazik->przemiesc()) Lacze.Rysuj(); }



    void informacje() const          {if (_AktywnyLazik) _AktywnyLazik->informacje(); else cout << "Brak aktywnego lazika" << endl; }
    void dostepneLaziki();
    void zmienAktywnyLazik(int numer);
    void ZmienKolorObiektu(std::shared_ptr<ObiektGeom> rOb, Kolory kolor);
};

#endif


//Scena(const char*  sNazwaPliku_BrylaWzorcowa, const char*  sNazwaObiektu, int KolorID, double X, double Y, double Z);
