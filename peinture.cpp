#include "peinture.h"

namespace TOWERDEFENSE{

Peinture::Peinture()
{
}

Peinture::Peinture(const int niveau,const int x,const int y,QGraphicsItem *parent):Defense(niveau,4+niveau/2,2,4*pow(niveau,1.5),25,60,30,parent,VIDE,PEINTURE)
{
    setX(x);
    setY(y);
    setData(0,"PEINTURE");
}

double Peinture::attaquer()
{
    return frappe;
}

void Peinture::ameliorer()
{
    niveau++;
    portee = 4 + niveau/2;
    frappe = 4 * pow(niveau,1.5);
}

QRectF Peinture::boundingRect()const
{
    return QRectF(0,0,32,32);
}

void Peinture::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::NoPen));
    painter->setBrush(Qt::magenta);
    painter->drawEllipse(0,0,32,32);
}

}
