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
    Fourmi();
    Fourmi(const double taille,const int x, const int y, QGraphicsPixmapItem *parent=0);

    /*!
      * Methode permettant de traiter les degats recus par une fourmi
      * \param degats les degats subis par l'attaque
      */
    void recevoirDegats(double degats);

protected:
    void advance(int phase);
};
}
#endif // FOURMI_H
