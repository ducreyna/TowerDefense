#ifndef EAU_H
#define EAU_H

#include "defense.h"

#include <iostream>

namespace TOWERDEFENSE{

class Eau : public Defense
{
public:
    Eau();
    Eau(const int niveau,const int x,const int y,QGraphicsItem *parent=0);

    double attaquer();
    void ameliorer();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
}

#endif // EAU_H
