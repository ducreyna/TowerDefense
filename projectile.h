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
    /*!
      * Constructeur parametre
      * \param *tour recuperation des parametres de la tour afin de creer le bon projectile
      */
    Projectile(Defense * tour);

    /*!
      * Methode constante definissant les bords de l'item comme un rectangle
      * \return QRectF le rectangle cree
      */
    QRectF boundingRect() const;

    /*!
      * Methode peignant le contenu d'un item
      */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

}

#endif // PROJECTILE_H
