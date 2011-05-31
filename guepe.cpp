#include "guepe.h"

namespace TOWERDEFENSE{

Guepe::Guepe(){}

Guepe::Guepe(const double taille,const int x, const int y,QGraphicsPixmapItem *parent):Insecte(taille,7*pow(taille,2),4*pow(taille,2),3,VOLANT,parent)
{
    for(int i = 0; i < 2; ++i)
    {
        QPixmap* animTemp = new QPixmap("data/guepe" + QString::number(i+1) + ".png");
        *animTemp = animTemp->scaled(taille*32,taille*32);
        animPixmap.push_back(animTemp);
    }
    animState = 0; // Première frame de l'animation à 0

    // Image et taille
    this->setPixmap(*animPixmap.first());

    // Position
    this->setPos(x,y);
    this->setData(0,"GUEPE");
}

void Guepe::recevoirDegats(double degats)
{
    Insecte::recevoirDegats(degats);
    if(this->vitalite <= 0) emit this->degatsCrash(5*pow(taille,2),this);
}

void Guepe::advance(int phase)
{
    Insecte::advance(phase);
}
}
