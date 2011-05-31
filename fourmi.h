#ifndef FOURMI_H
#define FOURMI_H

#include "insecte.h"

namespace TOWERDEFENSE{

class Fourmi : public Insecte
{
private:
    int counterTempsAcceleration;
    double vitesseBase;

public:

    /*!
      * Constructeur par defaut
      */
    Fourmi();

    /*!
      * Constructeur parametre appele par la factory
      * \param taille la taille de la fourmi
      * \param x la position de la fourmi suivant l'axe x
      * \param y la position de la fourmi suivant l'axe y
      * \param parent l'item parent du cafard initialise a 0
      */
    Fourmi(const double taille,const int x, const int y, QGraphicsPixmapItem *parent=0);

    /*!
      * Methode permettant de traiter les degats recus par une fourmi
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
#endif // FOURMI_H
