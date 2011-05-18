#ifndef PETANQUE_H
#define PETANQUE_H

#include "defense.h"

namespace TOWERDEFENSE{

class Petanque : public Defense
{
public:
    Petanque();
    Petanque(const int niveau);

    double attaquer();
    void ameliorer();
};

}

#endif // PETANQUE_H
