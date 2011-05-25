#ifndef EAU_H
#define EAU_H

#include "defense.h"
#include "vague.h"
#include <QObject>

#include <iostream>
#include "insecte.h"
#include "projectile.h"

namespace TOWERDEFENSE{

class Eau : public Defense
{
    Q_OBJECT
public:
    Eau();
    Eau(const double niveau,const int x,const int y,QGraphicsPixmapItem *parent=0);

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

#endif // EAU_H
