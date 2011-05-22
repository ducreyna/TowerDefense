#ifndef EAU_H
#define EAU_H

#include "defense.h"

#include <iostream>

namespace TOWERDEFENSE{

class Eau : public Defense
{
public:
    Eau();
    Eau(const double niveau,const int x,const int y,QGraphicsItem *parent=0);

    double attaquer();
    bool ameliorer();
};
}

#endif // EAU_H
