#ifndef GUEPE_H
#define GUEPE_H

#include "insecte.h"

namespace TOWERDEFENSE{

class Guepe: public Insecte
{
    Q_OBJECT
public:
    Guepe();
    Guepe(const double taille,const int x, const int y, QGraphicsPixmapItem *parent=0);

    /*!
      * Methode permettant de traiter les degats recus par une guepe
      * \param degats les degats subis par l'attaque
      */
    void recevoirDegats(double degats);

protected:
    void advance(int phase);

signals:
    void degatsCrash(double degats,Guepe *g);
};
}

#endif // GUEPE_H
