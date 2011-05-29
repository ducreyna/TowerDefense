#ifndef PETANQUE_H
#define PETANQUE_H

#include <QObject>
#include "defense.h"

namespace TOWERDEFENSE{

class Petanque : public Defense
{
    Q_OBJECT
public:
    Petanque();
    Petanque(const double niveau,const int x,const int y,QGraphicsItem *parent=0);

    double attaquer();
    bool ameliorer();
};

}

#endif // PETANQUE_H
