#include "moustique.h"

namespace TOWERDEFENSE{

Moustique::Moustique(){}

Moustique::Moustique(const double taille,const int x, const int y,QGraphicsPixmapItem *parent):Insecte(taille,6*pow(taille,2),pow(taille,2),2+(taille/2),VOLANT,parent)
{
    for(int i = 0; i < 2; ++i)
    {
        QPixmap* animTemp = new QPixmap("data/moustiquevolant" + QString::number(i+1) + ".png");
        *animTemp = animTemp->scaled(taille*32,taille*32);
        animPixmap.push_back(animTemp);
    }
    animState = 0;

    this->setPixmap(*animPixmap.first());

    this->setPos(x,y);
    this->setData(0,"MOUSTIQUE");

    this->counterTempsVol = 350;
    this->counterTempsSol = 150;
}

void Moustique::recevoirDegats(double degats) {
    Insecte::recevoirDegats(degats);
    if(this->deplacement == VOLANT) this->toRampant();
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

void Moustique::advance(int phase)
{
    if(this->deplacement == VOLANT)
    {
        this->counterTempsVol--;
        if(this->counterTempsVol == 0) // si le moustique a epuise son temps de vol
        {
            this->toRampant();
            this->counterTempsVol = 350;
        }
    }
    else
    {
        this->counterTempsSol--;
        if(this->counterTempsSol == 0) // si le moustique a epuise le temps au sol
        {
            this->toVolant();
            this->counterTempsSol = 150;
        }
    }
    Insecte::advance(phase);
}
}
