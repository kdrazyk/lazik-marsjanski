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
    std::shared_ptr<ProbkaRegolitu> zdejmijProbke();
    void wyswietlListeProbek() const;

    virtual bool obroc() override;
    virtual bool przemiesc() override;

    virtual void informacje() const override;
    virtual int ID() const override {return OG_LazikSFR;}
};
