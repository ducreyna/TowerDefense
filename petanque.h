#ifndef PETANQUE_H
#define PETANQUE_H

#include "defense.h"

namespace TOWERDEFENSE{

class Petanque : public Defense
{
public:
    Petanque();
    Petanque(const int niveau,const int x,const int y,QGraphicsItem *parent=0);

    double attaquer();
    void ameliorer();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

}

#endif // PETANQUE_H
