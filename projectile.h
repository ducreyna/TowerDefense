#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPointF>
#include <vague.h>
#include <math.h>

#include "constantes.h"

namespace TOWERDEFENSE{

class Defense; // à cause du problème d'entrecroisement des includes

class Projectile : public QGraphicsPixmapItem
{
private:
    QPointF mouvementVecteur;
    Defense * tour;
    virtual void advance(int phase);

public:
    Projectile(Defense * tour);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

}

#endif // PROJECTILE_H
