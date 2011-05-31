#ifndef PETANQUE_H
#define PETANQUE_H

#include <QObject>
#include "defense.h"

namespace TOWERDEFENSE{

class Petanque : public Defense
{
    Q_OBJECT
public:
    /*!
      * Constructeur par defaut
      */
    Petanque();

    /*!
      * Constructeur parametre
      * \param niveau le niveau de la tour cree
      * \param x placement de la tour suivant l'axe x
      * \param y placement de la tour suivant l'axe y
      * \param parent l'item parent initialise a 0
      */
    Petanque(const double niveau,const int x,const int y,QGraphicsItem *parent=0);

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

#endif // PETANQUE_H
