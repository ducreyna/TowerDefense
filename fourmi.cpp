#include "fourmi.h"

namespace TOWERDEFENSE{

Fourmi::Fourmi(){}

Fourmi::Fourmi(const int taille,const int x, const int y,QGraphicsItem *parent):Insecte(taille,5*pow(taille,2),pow(taille,2),2+(taille/2),RAMPANT,parent)
{
    setX(x);
    setY(y);
}

void Fourmi::recevoirDegats(int degats){
    vitesse = vitesse  * 1.5;
    vitalite = vitalite - (degats-resistance);
}

QRectF Fourmi::boundingRect() const
{
    return QRectF(0,0,32,32); // A Modifier suivant l'image je pense
}

void Fourmi::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
}
