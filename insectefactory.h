#ifndef INSECTEFACTORY_H
#define INSECTEFACTORY_H

#include "insecte.h"
#include "moustique.h"
#include "cafard.h"
#include "guepe.h"
#include "fourmi.h"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

namespace TOWERDEFENSE {

class InsecteFactory
{
    public:

        int static const TYPE_GUEPE;
        int static const TYPE_CAFARD;
        int static const TYPE_FOURMI;
        int static const TYPE_MOUSTIQUE;

        /*!
          * Methode creant un insecte
          * \param type type de l'insecte
          * \param size taille de l'insecte
          * \param *path pointeur sur la liste contenant le path
          * \return Insecte* l'insecte cree
          */
        static Insecte* create(int type, double size, QList<int> * path);
};

}

#endif // INSECTEFACTORY_H
