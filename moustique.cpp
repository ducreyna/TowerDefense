#include "moustique.h"

namespace TOWERDEFENSE{

Moustique::Moustique(){}

Moustique::Moustique(const int taille):Insecte(taille,6*pow(taille,2),pow(taille,2),2+(taille/2),VOLANT){}

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
}
