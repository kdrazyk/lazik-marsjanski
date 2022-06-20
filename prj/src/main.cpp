#include <iostream>
#include "Scena.hh"
#include "Kolory.hh"

using namespace std;

#define KOLOR_PROBKI 18

void Inicjalizuj_Obiekty_Sceny(Scena &scena)
{
    scena.dodajLazikSFR("FSR"         , -5,  0, 0);
    scena.dodajLazik("Perseverance", 50, 60, 0);
    scena.dodajLazik("Curiosity"   ,-20, 70, 0);

    scena.dodajProbkeRegolitu("Coulettes"   , KOLOR_PROBKI,  0,  90, 0);
    scena.dodajProbkeRegolitu("Salette"     , KOLOR_PROBKI,  0,  85, 0);
    scena.dodajProbkeRegolitu("Dourbes"     , KOLOR_PROBKI, 10,  80, 0);
    scena.dodajProbkeRegolitu("Robine"      , KOLOR_PROBKI, 70,  60, 0);
    scena.dodajProbkeRegolitu("Quartier"    , KOLOR_PROBKI, 70,  50, 0);
    scena.dodajProbkeRegolitu("Bellegarde"  , KOLOR_PROBKI,-70,  55, 0);
    scena.dodajProbkeRegolitu("Montdenier"  , KOLOR_PROBKI,-80,  65, 0);
    scena.dodajProbkeRegolitu("Montagnac"   , KOLOR_PROBKI,-60,  50, 0);
    scena.dodajProbkeRegolitu("Guillaumes"  , KOLOR_PROBKI, 10,   0, 0);
    scena.dodajProbkeRegolitu("Roubion"     , KOLOR_PROBKI, 50, -60, 0);
}


namespace menu {
    void jazda_na_wprost(Scena &scena)
    {
        double odleglosc;
        cout << "Podaj odleglosc, na ktora ma sie przemiescic lazik (w jednostkach sceny)." << endl
             << "Odleglosc: ";
        cin >> odleglosc;
        scena.przemiesc(odleglosc);
    }

    void zmien_orientacje(Scena &scena)
    {
        double kat;
        cout << "Podaj kat obrotu w stopniach." << endl
             << "Wartosc kata: ";
        cin >> kat;
        scena.obroc(kat);
    }

    void wybor_lazika(Scena &scena)
    {
        int numer;
        scena.dostepneLaziki();
        cout << "Podaj numer lazika > ";
        cin >> numer;
        scena.zmienAktywnyLazik(numer);
    }

    void podejmij_probke(Scena &scena)
    {
        scena.podniesProbke();
    }

    void wyswietl_menu(Scena &scena)
    {
        cout << endl<< "Aktywny lazik" << endl;
        scena.informacje();
        cout << "j - jazda na wprost" << endl
             << "o - zmien orientacje" << endl
             << "w - wybor lazika" << endl
             << "l - lista probek na scenie" << endl
             << "p - podejmij probke (tylko dla SFR)" << endl
             << "m - wyswietl menu" << endl
             << "k - koniec dzialania programu" << endl << endl;

        Wektor3D::iloscObiektow();
    }

    void wyjscie(bool &koniec)
    {
        cout << "Koniec programu" << endl << endl;
        koniec = true;
    }

    void bledna_opcja()
    {
        cout << "Nieznana opcja" << endl;
        cin.ignore(1000, '\n');
    }

    void menu(Scena &scena)
    {
        bool koniec = false;
        char opcja;
        do {
            wyswietl_menu(scena);

            cout << "Twoj wybor: ";
            cin >> opcja;

            switch(opcja) {
            case 'j': jazda_na_wprost(scena);  break;
            case 'o': zmien_orientacje(scena); break;
            case 'w': wybor_lazika(scena);     break;
            case 'l': scena.WyswietlProbki();  break;
            case 'p': podejmij_probke(scena);  break;
            case 'm': wyswietl_menu(scena);    break;
            case 'k': wyjscie(koniec);         break;
            default:  bledna_opcja();
            }

        } while(!koniec);
    }
}

int main()
{
    {
        Scena mars;

        Inicjalizuj_Obiekty_Sceny(mars);

        menu::menu(mars);
    }
    Wektor3D::iloscObiektow();
}


