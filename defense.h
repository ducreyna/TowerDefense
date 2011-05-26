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

#include "constantes.h"
#include "insecte.h"
#include "projectile.h"
#include "vague.h"

#include <math.h>

namespace TOWERDEFENSE{

class Defense : public QGraphicsPixmapItem,public QObject
{
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
    double cibleX;
    double cibleY;
    bool isShooting;
    QTimer *shootTimer;

    QVector<Insecte*> vagueEnCours;

public:
    Defense();
    Defense(const double niveau,const double portee,const double cadence, const double frappe,const int cout,const int amelioration_1,const int amelioration_2, const double vitesse, QGraphicsItem *parent=0, const Type_deplacement cible = VIDE,const Type_projectile projectile = EAU);
    virtual ~Defense();

    virtual double attaquer() = 0;
    virtual bool ameliorer() = 0;

    double getNiveau()const;
    double getPortee()const;
    int getCout()const;
    int getAmelioration_1()const;
    int getAmelioration_2()const;
    void setVague(QVector<Insecte*> vague);

};
}

#endif // DEFENSE_H
