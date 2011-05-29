#include "joueur.h"

namespace TOWERDEFENSE{

Joueur::Joueur(int vies, int argent):vies(vies),argent(argent)
{
}

int Joueur::getArgent()const { return this->argent; }

int Joueur::getVies()const { return this->vies; }

void Joueur::gagnerArgent()
{
    argent++;
    emit this->argentModifie(argent);
}

void Joueur::perdreVie()
{
    vies--;
    if(vies == 0)
    {
        emit this->viesModifiees(vies);
        emit this->finDuJeu();
    }
    emit this->viesModifiees(vies);
}

void Joueur::achatTour(int prix)
{
    argent -= prix;
    emit this->argentModifie(argent);
}

void Joueur::venteTour(int gain)
{
    argent += gain;
    emit this->argentModifie(argent);
}

}
