#ifndef CAFARD_H
#define CAFARD_H

#include "insecte.h"
#include <iostream>

namespace TOWERDEFENSE{

class Cafard : public Insecte
{   
public:
    /*!
      * Constructeur par defaut
      */
    Cafard();

    /*!
      * Construteur parametre appele par la factory
      * \param taille la taille du cafard
      * \param x la position du cafard suivant l'axe x
      * \param y la position du cafard suivant l'axe y
      * \param parent l'item parent du cafard initialise a 0
      */
    Cafard(const double taille,const int x, const int y, QGraphicsPixmapItem *parent=0);

    /*!
      * Methode permettant de traiter les degats recus par un cafard
      * \param degats les degats subis par l'attaque
      */
    void recevoirDegats(double degats);

protected:
    /*!
      * Methode permettant l'animation de l'item sur la scene
      * \param phase la phase d'appel de l'item
      */
    void advance(int phase);
};
}

#endif // CAFARD_H
