#include <iostream>
#include "Scena.hh"
#include "Kolory.hh"

#include <termios.h>
#include <unistd.h>

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
        double odleglosc = 10;
        // cout << "Podaj odleglosc, na ktora ma sie przemiescic lazik (w jednostkach sceny)." << endl
        //      << "Odleglosc: ";
        // cin >> odleglosc;
        scena.przemiesc(odleglosc);
    }

    void zmien_orientacje(Scena &scena)
    {
        double kat = 15;
        // cout << "Podaj kat obrotu w stopniach." << endl
        //      << "Wartosc kata: ";
        // cin >> kat;
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

namespace MENU {

    void wyswietl_menu(Scena &scena)
    {
        cout << endl<< "Aktywny lazik" << endl;
        scena.informacje();
        cout << "1,2,3 - wybor lazika" << endl
             << "w - jedz do przodu" << endl
             << "s - jedz do tylu" << endl
             << "a - obroc w lewo" << endl
             << "d - obroc w prawo" << endl
             << "p - podejmij probke (tylko dla SFR)" << endl
             << "p - zostaw probke (tylko dla SFR)" << endl
             << "k - koniec dzialania programu" << endl << endl;

        Wektor3D::iloscObiektow();
    }


    void menu(Scena &scena)
    {
        bool koniec = false;
        char opcja;

        static struct termios oldt, newt;
        tcgetattr( STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr( STDIN_FILENO, TCSANOW, &newt);


        do {
            wyswietl_menu(scena);

            cin >> opcja;

            switch(opcja) {
            case '1': scena.zmienAktywnyLazik(0);  break;
            case '2': scena.zmienAktywnyLazik(1);  break;
            case '3': scena.zmienAktywnyLazik(2);  break;
            case 'w': scena.przemiesc(1);          break;
            case 's': scena.przemiesc(-1);         break;
            case 'a': scena.obroc(-1);             break;
            case 'd': scena.obroc(1);              break;
            case 'p': scena.podniesProbke();       break;
            case 'z': scena.zostawProbke();        break;
            case 'k': koniec = true;               break;


            }

        } while(!koniec);
        tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
    }

}



int main()
{
    {
        Scena mars;
        int opcja;

        Inicjalizuj_Obiekty_Sceny(mars);

        cout << "Wybierz tryb menu: " << endl
             << "\t1. menu tradycyjne" << endl
             << "\t2. menu ze sterowaniem WASD" << endl;
        cin >> opcja;
        if (opcja == 1)
            menu::menu(mars);
        else if (opcja == 2)
            MENU::menu(mars);
    }
    Wektor3D::iloscObiektow();
}


