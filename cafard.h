#ifndef CAFARD_H
#define CAFARD_H

#include "insecte.h"

namespace TOWERDEFENSE{

class Cafard : public Insecte
{
public:
    Cafard();
    Cafard(const int taille,const int x, const int y, QGraphicsItem *parent=0);

    /*!
      * Methode permettant de traiter les degats recus par un cafard
      * \param degats les degats subis par l'attaque
      */
    void recevoirDegats(int degats);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
}

#endif // CAFARD_H
