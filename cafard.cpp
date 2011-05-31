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
    Insecte::recevoirDegats(degats);
    if(this->vitalite <= 0 && this->taille >= 2)
    {
        emit this->ajouterInsecteEnfant(1,this->taille-1,this->x(),this->y(),this->getPath(),this->getCounter(),1);
        emit this->ajouterInsecteEnfant(1,this->taille-1,this->x(),this->y(),this->getPath(),this->getCounter(),2);
    }
}

void Cafard::advance(int phase)
{
    Insecte::advance(phase);
}
}
