#include "cafard.h"

namespace TOWERDEFENSE{

Cafard::Cafard(){}

Cafard::Cafard(const int taille):Insecte(taille,10*pow(taille,2),5*pow(taille,2),2,RAMPANT){}

void Cafard::recevoirDegats(int degats){
    vitalite = vitalite - (degats-resistance);
}
}
