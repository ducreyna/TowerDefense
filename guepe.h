#ifndef GUEPE_H
#define GUEPE_H

#include "insecte.h"

namespace TOWERDEFENSE{

class Guepe: public Insecte
{
public:
    Guepe();
    Guepe(const int taille,const int x, const int y, QGraphicsItem *parent=0);

    /*!
      * Methode permettant de traiter les degats recus par une guepe
      * \param degats les degats subis par l'attaque
      */
    void recevoirDegats(int degats);

    /*!
     * Methode retournant les dommages causees lors de la mort d'une guepe
     * \return double les degats causes
     */
    double degatsCauses();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
}

#endif // GUEPE_H
