#ifndef GUEPE_H
#define GUEPE_H

#include "insecte.h"

namespace TOWERDEFENSE{

class Guepe: public Insecte
{
    Q_OBJECT
public:

    /*!
      * Constructeur par defaut
      */
    Guepe();

    /*!
      * Constructeur parametre appele par la factory
      * \param taille la taille de la guepe
      * \param x la position de la guepe suivant l'axe x
      * \param y la position de la guepe suivant l'axe y
      * \param parent l'item parent du cafard initialise a 0
      */
    Guepe(const double taille,const int x, const int y, QGraphicsPixmapItem *parent=0);

    /*!
      * Methode permettant de traiter les degats recus par une guepe
      * \param degats les degats subis par l'attaque
      */
    void recevoirDegats(double degats);

protected:
    /*!
      * Methode permettant l'animation de l'item sur la scene
      * \param phase la phase d'appel de l'item
      */
    void advance(int phase);

signals:
    /*!
      * Signal envoye quand la guepe meurt et qu'elle se crash au sol
      * \param degats les degats a causer
      * \param *g la guepe qui se crash
      */
    void degatsCrash(double degats,Guepe *g);
};
}

#endif // GUEPE_H
