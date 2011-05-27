#ifndef PIERRE_H
#define PIERRE_H

#include "defense.h"
#include "projectile.h"
#include <QObject>

namespace TOWERDEFENSE{

class Pierre : public Defense
{
    Q_OBJECT
public:
    Pierre();
    Pierre(const double niveau,const int x,const int y,QGraphicsItem *parent=0);

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

#endif // PIERRE_H
