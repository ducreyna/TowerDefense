#ifndef FOURMI_H
#define FOURMI_H

#include "insecte.h"

namespace TOWERDEFENSE{

class Fourmi : public Insecte
{
public:
    Fourmi();
    Fourmi(const int taille);

    /*!
      * Methode permettant de traiter les degats recus par une fourmi
      * \param degats les degats subis par l'attaque
      */
    void recevoirDegats(int degats);
};
}
#endif // FOURMI_H
