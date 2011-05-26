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

void Guepe::advance(int phase)
{
// Si 'phase' vaut 0, rien ne se passe
    if(!phase)
        return;
    // ...sinon, on met à jour l'item

    // Met à jour l'image de l'animation
    this->setPixmap(*animPixmap[animState]);
    this->increaseAnimationStep();


    //deprecated

    //this->setPos(x()+vitesse*+1,y()+vitesse*+1);

    // Oriente l'image dans le bon sens
    // (nb : transformation par rapport au centre de l'image)
    //this->setTransformOriginPoint(this->boundingRect().center().x(),this->boundingRect().center().y());
    //this->setRotation(1*90);

    Insecte::advance(phase);
}
}
