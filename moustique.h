#ifndef MOUSTIQUE_H
#define MOUSTIQUE_H

#include "insecte.h"

namespace TOWERDEFENSE{

class Moustique : public Insecte
{
private:
    int counterTempsVol;
    int counterTempsSol;

public:
    /*!
      * Constructeur par defaut
      */
    Moustique();

    /*!
      * Construteur parametre appele par la factory
      * \param taille la taille du moustique
      * \param x la position du moustique suivant l'axe x
      * \param y la position du moustique suivant l'axe y
      * \param parent l'item parent du moustique initialise a 0
      */
    Moustique(const double taille,const int x, const int y, QGraphicsPixmapItem *parent=0);

    /*!
      * Methode permettant de traiter les degats recus par un moustique
      * \param degats les degats subis par l'attaque
      */
    void recevoirDegats(double degats);

    /*!
      * Methode permettant le passage du deplacement de type VOLANT vers RAMPANT
      */
    void toRampant();

    /*!
      * Methode permettant le passage du deplacement de type RAMPANT vers VOLANT
      */
    void toVolant();

protected:
    /*!
      * Methode permettant l'animation de l'item sur la scene
      * \param phase la phase d'appel de l'item
      */
    void advance(int phase);
};
}

#endif // MOUSTIQUE_H
