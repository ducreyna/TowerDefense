#ifndef FOURMI_H
#define FOURMI_H

#include "insecte.h"

namespace TOWERDEFENSE{

class Fourmi : public Insecte
{
public:
    Fourmi();
    Fourmi(const int taille,const int x, const int y, QGraphicsItem *parent=0);

    /*!
      * Methode permettant de traiter les degats recus par une fourmi
      * \param degats les degats subis par l'attaque
      */
    void recevoirDegats(int degats);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
}
#endif // FOURMI_H
