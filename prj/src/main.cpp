#include <iostream>
#include "Scena.hh"
#include "Kolory.hh"

using namespace std;

void Inicjalizuj_Laziki(Scena &scena)
{
    scena.dodajLazik("bryly_wzorcowe/szescian3.dat","FSR"         ,  0,  0, 0);
    scena.dodajLazik("bryly_wzorcowe/szescian3.dat","Perseverance", 60, 60, 0);
    scena.dodajLazik("bryly_wzorcowe/szescian3.dat","Curiosity"   ,-20, 70, 0);
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

    void wyswietl_menu(Scena &scena)
    {
        cout << endl<< "Aktywny lazik" << endl;
        scena.informacje();
        cout << "j - jazda na wprost" << endl
             << "o - zmien orientacje" << endl
             << "w - wybor lazika" << endl
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

        Inicjalizuj_Laziki(mars);


        menu::menu(mars);
    }
    Wektor3D::iloscObiektow();
}


