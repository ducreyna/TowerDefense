#ifndef GUEPE_H
#define GUEPE_H

#include "insecte.h"

namespace TOWERDEFENSE{

class Guepe: public Insecte
{
public:
    Guepe();
    Guepe(const int taille);

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
};
}

#endif // GUEPE_H
