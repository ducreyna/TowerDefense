#ifndef MUSICIEN_H
#define MUSICIEN_H

#include "defense.h"
#include <QList>

namespace TOWERDEFENSE{

    class Musicien : public Defense
{
        Q_OBJECT
private:
        QList<Defense*> defenses;
        double renforcement;

    public:

        /*!
          * Constructeur par defaut
          */
        Musicien();

        /*!
          * Constructeur parametre
          * \param niveau le niveau de la tour cree
          * \param x placement de la tour suivant l'axe x
          * \param y placement de la tour suivant l'axe y
          * \param parent l'item parent initialise a 0
          */
        Musicien(const double niveau,const int x,const int y,QList<Defense*> defenses,QGraphicsPixmapItem *parent=0);

        /*!
          * Accesseur modifiant la liste des defenses a portee de la tour musique
          * \param defenses liste des defenses
          */
        void setDefenses(QList<Defense*> defenses);

        /*!
          * Methode distribuant le bonus aux defenses a portee
          */
        void bonus();

        /*!
          * Methode heritee de Defense, inutile ici
          */
        double attaquer();

        /*!
          * Methode permettant l'amelioration de la tour
          * \return bool true = amelioration reussie    false = amelioration interdite
          */
        bool ameliorer();

protected:
        void advance(int phase);
};

}

#endif // MUSICIEN_H
