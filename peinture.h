#ifndef PEINTURE_H
#define PEINTURE_H

#include "defense.h"

namespace TOWERDEFENSE{

class Peinture : public Defense
{
public:
    Peinture();
    Peinture(const double niveau,const int x,const int y,QGraphicsItem *parent=0);

    double attaquer();
    void ameliorer();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
}

#endif // PEINTURE_H
