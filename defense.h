#ifndef DEFENSE_H
#define DEFENSE_H

#include <QGraphicsItem>
#include <QPainter>

#include "constantes.h"

#include <math.h>

namespace TOWERDEFENSE{

class Defense : public QGraphicsItem
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
    Defense(const int niveau,const double portee,const double cadence, const double frappe,const int amelioration_1,const int amelioration_2, const int vitesse, QGraphicsItem *parent=0, const Type_deplacement cible = VIDE,const Type_projectile projectile = EAU);

    virtual double attaquer() = 0;
    virtual void ameliorer() = 0;

    double getPortee()const;
};
}

#endif // DEFENSE_H
