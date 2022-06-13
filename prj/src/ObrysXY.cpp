#include "ObrysXY.hh"



/*

  Y
  |
  #---X

  #---------GP
  |          |
  |   this   |
  |          |
  DL---------#

  #---------GP
  |          |
  |    O2    |
  |          |
  DL---------#

*/


bool ObrysXY::NalozenieObrysow(const ObrysXY &O2) const
{
    using namespace wsp;
    return ((this->_WierzGornyPrawy[X] >    O2._WierzDolnyLewy[X]) &&
            (   O2._WierzGornyPrawy[X] > this->_WierzDolnyLewy[X]) &&
            (this->_WierzGornyPrawy[Y] >    O2._WierzDolnyLewy[Y]) &&
            (   O2._WierzGornyPrawy[Y] > this->_WierzDolnyLewy[Y]) );
}
