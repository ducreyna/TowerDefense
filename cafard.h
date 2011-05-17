#ifndef CAFARD_H
#define CAFARD_H

#include "insecte.h"

namespace TOWERDEFENSE{

class Cafard : public Insecte
{
public:
    Cafard();
    Cafard(const int taille);

    /*!
      * Methode permettant de traiter les degats recus par un cafard
      * \param degats les degats subis par l'attaque
      */
    void recevoirDegats(int degats);
};
}

#endif // CAFARD_H
