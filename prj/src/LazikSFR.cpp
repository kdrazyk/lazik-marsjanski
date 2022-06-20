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
