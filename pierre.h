#ifndef PIERRE_H
#define PIERRE_H

#include "defense.h"

namespace TOWERDEFENSE{

class Pierre : public Defense
{
public:
    Pierre();
    Pierre(const int niveau);

    double attaquer();
    void ameliorer();
};

}

#endif // PIERRE_H
