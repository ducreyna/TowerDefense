#ifndef PEINTURE_H
#define PEINTURE_H

#include "defense.h"
#include "projectile.h"

namespace TOWERDEFENSE{

class Peinture : public Defense
{
    Q_OBJECT
public:
    Peinture();
    Peinture(const double niveau,const int x,const int y,QGraphicsItem *parent=0);

    double attaquer();
    bool ameliorer();

    void setTarget(double cibleX,double cibleY);
    void setIsShooting(bool state);

protected:
    void advance(int phase);

public slots:
    void shootTarget();
};
}

#endif // PEINTURE_H
