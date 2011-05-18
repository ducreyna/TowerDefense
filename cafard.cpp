#include "cafard.h"

namespace TOWERDEFENSE{

Cafard::Cafard(){}

Cafard::Cafard(const int taille,const int x, const int y, QGraphicsItem *parent):Insecte(taille,10*pow(taille,2),5*pow(taille,2),2,RAMPANT,parent)
{
    setX(x);
    setY(y);
}

void Cafard::recevoirDegats(int degats){
    vitalite = vitalite - (degats-resistance);
}

QRectF Cafard::boundingRect() const
{
    return QRectF(0,0,32,32); // A Modifier suivant l'image je pense
}

void Cafard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
}
