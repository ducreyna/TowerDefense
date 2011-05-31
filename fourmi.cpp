#include "fourmi.h"

namespace TOWERDEFENSE{

Fourmi::Fourmi(){}

Fourmi::Fourmi(const double taille,const int x, const int y,QGraphicsPixmapItem *parent):Insecte(taille,5*pow(taille,2),pow(taille,2),2+(taille/2),RAMPANT,parent)
{
    for(int i = 0; i < 3; ++i)
    {
        QPixmap* animTemp = new QPixmap("data/fourmi" + QString::number(i+1) + ".png");
        *animTemp = animTemp->scaled(taille*32,taille*32);
        animPixmap.push_back(animTemp);
    }
    animState = 0;

    this->setPixmap(*animPixmap.first());

    this->setPos(x,y);
    this->setData(0,"FOURMI");

    this->vitesseBase = vitesse;
    this->counterTempsAcceleration = 250; //nombre d'appel de la methode advance qui correspond a 5 secondes
}

void Fourmi::recevoirDegats(double degats){
    Insecte::recevoirDegats(degats);
    vitesse = vitesse  * 1.5;
    this->counterTempsAcceleration = 250;
}

void Fourmi::advance(int phase)
{
    this->counterTempsAcceleration--;
    if(this->counterTempsAcceleration == 0)
    {
        this->vitesse = this->vitesseBase;
        this->counterTempsAcceleration = 250;
    }
    Insecte::advance(phase);
}
}
