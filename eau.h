#ifndef EAU_H
#define EAU_H

#include <QObject>
#include "defense.h"

namespace TOWERDEFENSE{

class Eau : public Defense
{
    Q_OBJECT

public:
    Eau();
    Eau(const double niveau,const int x,const int y,QGraphicsPixmapItem *parent=0);

    double attaquer();
    bool ameliorer();
};
}

#endif // EAU_H
