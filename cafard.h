#ifndef CAFARD_H
#define CAFARD_H

#include "insecte.h"
#include <iostream>

namespace TOWERDEFENSE{

class Cafard : public Insecte
{   
public:
    Cafard();
    Cafard(const double taille,const int x, const int y, QGraphicsPixmapItem *parent=0);
    ~Cafard();

    /*!
      * Methode permettant de traiter les degats recus par un cafard
      * \param degats les degats subis par l'attaque
      */
    void recevoirDegats(double degats);

protected:
    void advance(int phase);
};
}

#endif // CAFARD_H
