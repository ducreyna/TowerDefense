#ifndef EAU_H
#define EAU_H

#include "defense.h"

namespace TOWERDEFENSE{

class Eau : public Defense
{
public:
    Eau();
    Eau(const int niveau);

    double attaquer();
    void ameliorer();
};
}

#endif // EAU_H
