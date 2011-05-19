#include "petanque.h"

namespace TOWERDEFENSE{

Petanque::Petanque()
{
}

Petanque::Petanque(const double niveau,const int x,const int y,QGraphicsItem *parent):Defense(niveau,3+niveau,0.5,15*pow(niveau,1.5),40,80,20,parent,RAMPANT,BOULE)
{
    setX(x);
    setY(y);
    setData(0,"PETANQUE");
}

double Petanque::attaquer()
{
    return frappe;
}

void Petanque::ameliorer()
{
    niveau++;
    portee = 3 + niveau;
    frappe = 15 * pow(niveau,1.5);
}

QRectF Petanque::boundingRect()const
{
    return QRectF(0,0,32,32);
}

void Petanque::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::NoPen));
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(0,0,32,32);
}

}
