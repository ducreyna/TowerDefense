#ifndef PIERRE_H
#define PIERRE_H

#include <QObject>
#include "defense.h"

namespace TOWERDEFENSE{

class Pierre : public Defense
{
    Q_OBJECT
public:
    /*!
      * Constructeur par defaut
      */
    Pierre();

    /*!
      * Constructeur parametre
      * \param niveau le niveau de la tour cree
      * \param x placement de la tour suivant l'axe x
      * \param y placement de la tour suivant l'axe y
      * \param parent l'item parent initialise a 0
      */
    Pierre(const double niveau,const int x,const int y,QGraphicsItem *parent=0);

    /*!
      * Methode renvoyant la frappe de la tour
      * \return double la valeur de la frappe
      */
    double attaquer();

    /*!
      * Methode permettant l'amelioration de la tour
      * \return bool true = amelioration reussie    false = amelioration interdite
      */
    bool ameliorer();
};

}

#endif // PIERRE_H
