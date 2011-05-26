#include "defense.h"

namespace TOWERDEFENSE{

Defense::Defense()
{
}

Defense::Defense(const double niveau,const double portee,const double cadence, const double frappe,const int cout,const int amelioration_1,const int amelioration_2, const double vitesse, QGraphicsItem *parent,const Type_deplacement cible,const Type_projectile projectile):cible(cible),niveau(niveau),portee(portee),cadence(cadence),frappe(frappe),cout(cout),amelioration_1(amelioration_1),amelioration_2(amelioration_2),projectile(projectile),vitesse(vitesse)
{
}

Defense::~Defense(){}

double Defense::getNiveau()const { return niveau; }

double Defense::getPortee()const { return portee; }

int Defense::getCout()const { return cout; }

int Defense::getAmelioration_1()const { return amelioration_1; }

int Defense::getAmelioration_2()const { return amelioration_2; }

void Defense::setVague(QVector<Insecte*> vague)
{
    this->vagueEnCours = vague;
}
}
