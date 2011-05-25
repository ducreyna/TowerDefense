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

        static Insecte* create(int type, int size, QList<int> * path);
};

}

#endif // INSECTEFACTORY_H
