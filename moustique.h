#ifndef MOUSTIQUE_H
#define MOUSTIQUE_H

#include "insecte.h"

namespace TOWERDEFENSE{

class Moustique : public Insecte
{
public:
    Moustique();
    Moustique(const int taille,const int x, const int y, QGraphicsItem *parent=0);

    /*!
      * Methode permettant de traiter les degats recus par un moustique
      * \param degats les degats subis par l'attaque
      */
    void recevoirDegats(int degats);

    /*!
      * Methode permettant le passage du deplacement de type VOLANT vers RAMPANT
      */
    void toRampant();

    /*!
      * Methode permettant le passage du deplacement de type RAMPANT vers VOLANT
      */
    void toVolant();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
}

#endif // MOUSTIQUE_H
