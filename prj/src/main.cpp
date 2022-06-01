#include <iostream>
#include <fstream>
#include <cstdlib>
#include "lacze_do_gnuplota.hh"
#include "PowierzchniaMarsa.hh"
#include "Scena.hh"
#include "Kolory.hh"



using namespace std;

/*!
 *  \brief Inicjalizuje połączenie z programem gnuplot oraz rozmiar świata.
 *
 *  Inicjalizuje podstawowe parametry "swiata", tzn. jego wymiary,
 *  które będą widoczne jako obszar objęty układem współrzędnych.
 *  Następnie w tle uruchamiany jest program gnuplot.
 *  \param[in] rLacze - nieaktywne łącze do gnuplota.
 */
void Inicjalizuj_Lacze(PzG::LaczeDoGNUPlota  &rLacze)
{
    rLacze.ZmienTrybRys(PzG::TR_3D);
    rLacze.UstawZakresX(-ROMIAR_POWIERZCHNI_X/2, ROMIAR_POWIERZCHNI_X/2);
    rLacze.UstawZakresY(-ROMIAR_POWIERZCHNI_Y/2, ROMIAR_POWIERZCHNI_Y/2);
    rLacze.UstawZakresZ(-0, 90);
    rLacze.UstawRotacjeXZ(40,60); // Tutaj ustawiany jest widok

    rLacze.Inicjalizuj();  // Tutaj startuje gnuplot.
}

void DodajDoListyRysowania(PzG::LaczeDoGNUPlota &rLacze, const Lazik  &rOb)
{
    PzG::InfoPlikuDoRysowania *wInfoPliku;
  
    wInfoPliku = &rLacze.DodajNazwePliku(rOb.WezNazwePliku_BrylaRysowana());
    wInfoPliku->ZmienKolor(rOb.WezKolorID());
}




void exiting()
{
    Wektor3D::iloscObiektow();
}


int main()
{
    PzG::LaczeDoGNUPlota  Lacze;
    double x,y;

    std::atexit(exiting);

    Inicjalizuj_Lacze(Lacze);
    if (!Inicjalizuj_PowierzchnieMarsa(Lacze)) return 1;

    Scena  Ob1("bryly_wzorcowe/szescian3.dat","FSR",Kolor_JasnoNiebieski);
    DodajDoListyRysowania(Lacze,*Ob1._AktywnyLazik);
    Ob1._AktywnyLazik->_Polozenie[0] = 0;
    Ob1._AktywnyLazik->_Polozenie[1] = 0;
    Ob1._AktywnyLazik->_Polozenie[2] = 0;
    Ob1._AktywnyLazik->Przelicz_i_Zapisz_Wierzcholki();
    Ob1._AktywnyLazik->informacje();

    Ob1.dodajLazik("bryly_wzorcowe/szescian3.dat","Perseverance",Kolor_Czerwony);
    DodajDoListyRysowania(Lacze,*Ob1._AktywnyLazik);
    Ob1._AktywnyLazik->_Polozenie[0] = 60;
    Ob1._AktywnyLazik->_Polozenie[1] = 60;
    Ob1._AktywnyLazik->_Polozenie[2] = 0;
    Ob1._AktywnyLazik->Przelicz_i_Zapisz_Wierzcholki();
    Ob1._AktywnyLazik->informacje();

    Ob1.dodajLazik("bryly_wzorcowe/szescian3.dat","Curiosity",Kolor_Czerwony);
    DodajDoListyRysowania(Lacze,*Ob1._AktywnyLazik);
    Ob1._AktywnyLazik->_Polozenie[0] = -20;
    Ob1._AktywnyLazik->_Polozenie[1] = 70;
    Ob1._AktywnyLazik->_Polozenie[2] = 0;
    Ob1._AktywnyLazik->Przelicz_i_Zapisz_Wierzcholki();
    Ob1._AktywnyLazik->informacje();

    cout << endl << "Start programu gnuplot" << endl << endl;
    Lacze.Rysuj();

    Wektor3D::iloscObiektow();

    //WYSLIJ ZAPROSZENIE DO GITHUBA
    ////WYSLIJ ZAPROSZENIE DO GITHUBA
    //////WYSLIJ ZAPROSZENIE DO GITHUBA
    ////////WYSLIJ ZAPROSZENIE DO GITHUBA
    //////////WYSLIJ ZAPROSZENIE DO GITHUBA
    ////////////WYSLIJ ZAPROSZENIE DO GITHUBA
    //////////////WYSLIJ ZAPROSZENIE DO GITHUBA

    while(1) {
        x = y = 0;
        cout << "Przemieszczenie: ";
        cin >> x;
        if (x==999) break;
        cout << "Obrot: ";
        cin >> y;
        Ob1._AktywnyLazik->przemiesc(x);
        Ob1._AktywnyLazik->obroc(y);
        Ob1._AktywnyLazik->informacje();
        Lacze.Rysuj();
    }
}
