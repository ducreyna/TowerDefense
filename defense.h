#ifndef DEFENSE_H
#define DEFENSE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <exception>
#include <QMessageBox>
#include <QTimer>
#include <QList>
#include <QObject>
#include <math.h>

#include "constantes.h"
#include "insecte.h"
#include "vague.h"
#include "entite.h"
#include "projectile.h"

namespace TOWERDEFENSE{

class Defense : public Entite
{
    Q_OBJECT
protected:
    Type_deplacement cible;
    double niveau;
    double  portee;
    double cadence;
    double frappe;
    int cout;
    int amelioration_1;
    int amelioration_2;
    Type_projectile projectile;
    double vitesse;

    bool isShooting;
    QTimer *shootTimer;

    Vague * currentWave;
    Insecte * currentTarget;

    void advance(int phase);

public:
    Defense();
    Defense(const double niveau,const double portee,const double cadence, const double frappe,const int cout,const int amelioration_1,const int amelioration_2, const double vitesse,QGraphicsItem *parent=0,const Type_deplacement cible = VIDE,const Type_projectile projectile = EAU);
    virtual ~Defense();

    virtual double attaquer() = 0;
    virtual bool ameliorer() = 0;

    double getNiveau()const;
    double getPortee()const;
    inline double getFrappe() const { return this->frappe; }
    inline double getVitesseProjectile() const { return this->vitesse; }
    inline Type_projectile getTypeProjectile() const { return this->projectile; }
    int getCout()const;
    int getAmelioration_1()const;
    int getAmelioration_2()const;
    inline void setCurrentWave(Vague * currWave) { this->currentWave = currWave; }
    inline void setCurrentTarget(Insecte * target) { this->currentTarget = target; }
    inline Insecte * getCurrentTarget() const { return this->currentTarget; }

    void setIsShooting(bool state);

protected:


public slots:
    void shootTarget();
};
}

#endif // DEFENSE_H
