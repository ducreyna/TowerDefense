#include "defense.h"

namespace TOWERDEFENSE{

Defense::Defense()
{
}

Defense::Defense(const int niveau,const double portee,const double cadence, const double frappe,const int amelioration_1,const int amelioration_2, const int vitesse,const Type_deplacement cible,const Type_projectile projectile):cible(cible),niveau(niveau),portee(portee),cadence(cadence),frappe(frappe),amelioration_1(amelioration_1),amelioration_2(amelioration_2),projectile(projectile),vitesse(vitesse)
{

}
}
