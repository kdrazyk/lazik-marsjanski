#include "ProbkaRegolitu.hh"

ProbkaRegolitu::ProbkaRegolitu(const char*  sNazwaObiektu, int KolorID):
    ObiektGeom("bryly_wzorcowe/szescian2.dat", sNazwaObiektu, KolorID)
{
    ZmienSkale(2,6,2);
}

TypKolizji ProbkaRegolitu::CzyKolizja(const std::shared_ptr<Lazik> &Wsk_Lazik) const
{
    const double maksOdlOdOsi = Wsk_Lazik->WezSzerokosc() * 0.2;
    if (_Obrys.NalozenieObrysow(Wsk_Lazik->WezObrys())) {
        if (this->odlegloscOdOsi(Wsk_Lazik) < maksOdlOdOsi) {
            return TK_PrzejazdNadProbka;
        }

        else {
            return TK_Kolizja;
        }

    }
    return TK_BrakKolizji;

}

void ProbkaRegolitu::informacje() const {
    const int szerokosc = 14;
    cout << setw(szerokosc) << left << _NazwaObiektu   << "Polozenie: " << _Polozenie << right;
}
