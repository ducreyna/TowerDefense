#include "fourmi.h"

namespace TOWERDEFENSE{

Fourmi::Fourmi(){}

Fourmi::Fourmi(const int taille):Insecte(taille,5*pow(taille,2),pow(taille,2),2+(taille/2),RAMPANT){}

void Fourmi::recevoirDegats(int degats){
    vitesse = vitesse  * 1.5;
    vitalite = vitalite - (degats-resistance);
}
}
