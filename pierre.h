#ifndef PIERRE_H
#define PIERRE_H

#include "defense.h"

namespace TOWERDEFENSE{

class Pierre : public Defense
{
public:
    Pierre();
    Pierre(const int niveau,const int x,const int y,QGraphicsItem *parent=0);

    double attaquer();
    void ameliorer();
};

}

#endif // PIERRE_H
