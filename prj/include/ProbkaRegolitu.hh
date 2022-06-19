#ifndef PROBKAREGOLITU_HH
#define PROBKAREGOLITU_HH

#include <iostream>
#include "ObiektGeom.hh"
#include "Lazik.hh"

class ProbkaRegolitu: public ObiektGeom
{
    private:

    public:
    ProbkaRegolitu(const char*  sNazwaObiektu, int KolorID);
    virtual void informacje() const override;
    virtual int ID() const override {return OG_ProbkaRegolitu;}
    virtual TypKolizji CzyKolizja(const std::shared_ptr<Lazik> &Wsk_Lazik) const override;
};

#endif // PROBKAREGOLITU_HH
