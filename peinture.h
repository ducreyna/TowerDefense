#ifndef PEINTURE_H
#define PEINTURE_H

#include "defense.h"

namespace TOWERDEFENSE{

class Peinture : public Defense
{
public:
    Peinture();
    Peinture(const int niveau);

    double attaquer();
    void ameliorer();
};
}

#endif // PEINTURE_H
