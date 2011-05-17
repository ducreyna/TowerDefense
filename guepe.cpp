#include "guepe.h"

namespace TOWERDEFENSE{

Guepe::Guepe(){}

Guepe::Guepe(const int taille):Insecte(taille,7*pow(taille,2),4*pow(taille,2),3,VOLANT){}

void Guepe::recevoirDegats(int degats)
{
    vitalite = vitalite - (degats-resistance);
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
}
