#include <iostream>
#include <memory>
#include <list>
#include "Lazik.hh"
#include "ProbkaRegolitu.hh"

class LazikSFR: public Lazik
{
private:
    std::list<std::shared_ptr<ProbkaRegolitu>> _ListaProbek;

public:
    LazikSFR(const char*  sNazwaObiektu, int KolorID);
    void dodajProbkeDoListy(std::shared_ptr<ProbkaRegolitu> probka);
    void wyswietlListeProbek() const;

    virtual void informacje() const override;
    virtual int ID() const override {return OG_LazikSFR;}
//    virtual TypKolizji CzyKolizja(const std::shared_ptr<Lazik> &Wsk_Lazik) const override;
};
