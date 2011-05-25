#include "cafard.h"

namespace TOWERDEFENSE{

Cafard::Cafard(){}

Cafard::Cafard(const double taille,const int x, const int y, QGraphicsPixmapItem *parent):Insecte(taille,10*pow(taille,2),5*pow(taille,2),2,RAMPANT,parent)
{
    for(int i = 0; i < 3; ++i)
    {
        QPixmap* animTemp = new QPixmap("data/cafard" + QString::number(i+1) + ".png");
        *animTemp = animTemp->scaled(taille*32,taille*32);
        animPixmap.push_back(animTemp);
    }
    animState = 0; // Première frame de l'animation à 0

    // Image et taille
    this->setPixmap(*animPixmap.first());

    // Position
    this->setPos(x,y);
    this->setData(0,"CAFARD");
}

Cafard::~Cafard(){}

void Cafard::recevoirDegats(double degats){
    vitalite = vitalite - (degats-resistance);
}

void Cafard::advance(int phase)
{
// Si 'phase' vaut 0, rien ne se passe
    if(!phase)
        return;
    // ...sinon, on met à jour l'item

    // Met à jour l'image de l'animation
    this->setPixmap(*animPixmap[animState]);
    this->increaseAnimationStep();

    // deprecated


    // Oriente l'image dans le bon sens
    // (nb : transformation par rapport au centre de l'image)
    //this->setTransformOriginPoint(this->boundingRect().center().x(),this->boundingRect().center().y());
    //this->setRotation(1*90);

    Insecte::advance(phase);

}
}
