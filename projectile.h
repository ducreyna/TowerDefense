#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPointF>
#include <vague.h>
#include <math.h>
#include "insecte.h"
#include <iostream>

namespace TOWERDEFENSE{

    class Projectile : public QGraphicsItem
{
private:
        double vitesse;
        double frappe;
        double cibleX;
        double cibleY;
        QPointF mouvementVecteur;
        Vague *vagueEnCours;

    virtual void advance(int phase);

public:
    Projectile(const double vitesse,const double frappe,const int x,const int y,const double cibleX,const double cibleY,Vague* vague=0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

}

#endif // PROJECTILE_H
