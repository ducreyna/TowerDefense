#include "pierre.h"

namespace TOWERDEFENSE{

Pierre::Pierre()
{
}

Pierre::Pierre(const double niveau,const int x,const int y,QGraphicsItem *parent):Defense(niveau,3+(niveau/2),1,10*pow(niveau,1.5),25,60,25,parent,VOLANT,PIERRE)
{
    setX(x);
    setY(y);
    setData(0,"PIERRE");
}

double Pierre::attaquer()
{
    return frappe;
}

void Pierre::ameliorer()
{
    niveau++;
    portee = 3 + niveau/2;
    frappe = 10 * pow(niveau,1.5);
}

QRectF Pierre::boundingRect()const
{
    return QRectF(0,0,32,32);
}

void Pierre::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::NoPen));
    painter->setBrush(Qt::lightGray);
    painter->drawEllipse(0,0,32,32);
}

}
