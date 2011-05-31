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
    Moustique();
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
    void advance(int phase);
};
}

#endif // MOUSTIQUE_H
