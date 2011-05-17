#ifndef DEFENSE_H
#define DEFENSE_H

#include <math.h>

namespace TOWERDEFENSE{

enum Type_deplacement {RAMPANT,VOLANT,VIDE};
enum Type_projectile {EAU,PIERRE,PEINTURE,BOULE};

class Defense
{
protected:
    Type_deplacement cible;
    int niveau;
    double portee;
    double cadence;
    double frappe;
    int amelioration_1;
    int amelioration_2;
    Type_projectile projectile;
    int vitesse;

public:
    Defense();
    Defense(const int niveau,const double portee,const double cadence, const double frappe,const int amelioration_1,const int amelioration_2, const int vitesse,const Type_deplacement cible = VIDE,const Type_projectile projectile = EAU);

    virtual double attaquer() = 0;
    virtual void ameliorer() = 0;
};
}

#endif // DEFENSE_H
