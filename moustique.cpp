#include "moustique.h"

namespace TOWERDEFENSE{

Moustique::Moustique(){}

Moustique::Moustique(const int taille,const int x, const int y,QGraphicsItem *parent):Insecte(taille,6*pow(taille,2),pow(taille,2),2+(taille/2),VOLANT,parent)
{
    setX(x);
    setY(y);
}

void Moustique::recevoirDegats(int degats) {
    vitalite = vitalite - (degats-resistance);
    toRampant();
}

void Moustique::toRampant(){
    resistance = 15*taille;
    vitesse = 1 + taille/2;
    deplacement = RAMPANT;
}

void Moustique::toVolant(){
    resistance = pow(taille,2);
    vitesse = 2 + taille/2;
    deplacement = VOLANT;
}

QRectF Moustique::boundingRect() const
{
    return QRectF(0,0,32,32); // A Modifier suivant l'image je pense
}

void Moustique::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
}
