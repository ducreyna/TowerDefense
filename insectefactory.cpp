#include "insectefactory.h"

namespace TOWERDEFENSE {

int const InsecteFactory::TYPE_CAFARD       = 1;
int const InsecteFactory::TYPE_FOURMI       = 2;
int const InsecteFactory::TYPE_GUEPE        = 3;
int const InsecteFactory::TYPE_MOUSTIQUE    = 4;


Insecte* InsecteFactory::create(int type, int size)
{
    Insecte * insecteToCreate;

    switch(type)
    {
        case InsecteFactory::TYPE_CAFARD:
            insecteToCreate = new Cafard(size);
            break;
        case InsecteFactory::TYPE_FOURMI:
            insecteToCreate = new Fourmi(size);
            break;
        case InsecteFactory::TYPE_GUEPE:
            insecteToCreate = new Guepe(size);
            break;
        case InsecteFactory::TYPE_MOUSTIQUE:
            insecteToCreate = new Moustique(size);
            break;
        default:
            throw invalid_argument(0);
            break;
    }

    return insecteToCreate;
}


}
