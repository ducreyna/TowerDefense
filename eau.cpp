#include "eau.h"

namespace TOWERDEFENSE{

Eau::Eau(const double niveau,const int x, const int y,QGraphicsItem *parent):Defense(niveau,2+niveau/2,(4-niveau/2),5*pow(niveau,1.5),20,45,40,parent)
{
    setX(x);
    setY(y);
    setData(0,"EAU");
}

double Eau::attaquer()
{
    return frappe;
}

void Eau::ameliorer()
{
    niveau++;
    portee = 3 + niveau/2;
    cadence = 4 - niveau/2;
    frappe = 5 * pow(niveau,1.5);
}

QRectF Eau::boundingRect()const
{
    return QRectF(0,0,32,32);
}

void Eau::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::NoPen));
    painter->setBrush(Qt::blue);
    painter->drawEllipse(0,0,32,32);
}

}
