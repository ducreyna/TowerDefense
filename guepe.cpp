#include "guepe.h"

namespace TOWERDEFENSE{

Guepe::Guepe(){}

Guepe::Guepe(const int taille,const int x, const int y,QGraphicsItem *parent):Insecte(taille,7*pow(taille,2),4*pow(taille,2),3,VOLANT,parent)
{
    setX(x);
    setY(y);
}

void Guepe::recevoirDegats(int degats)
{
    vitalite = vitalite - (degats-resistance);
}

double Guepe::degatsCauses()
{
    if(deplacement == RAMPANT)
    {
        return 0;
    }
    else
    {
        return 5*pow(taille,2);
    }
}

QRectF Guepe::boundingRect() const
{
    return QRectF(0,0,32,32); // A Modifier suivant l'image je pense
}

void Guepe::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
}
