#include "insectefactory.h"

namespace TOWERDEFENSE {

int const InsecteFactory::TYPE_CAFARD       = 1;
int const InsecteFactory::TYPE_FOURMI       = 2;
int const InsecteFactory::TYPE_GUEPE        = 3;
int const InsecteFactory::TYPE_MOUSTIQUE    = 4;


Insecte* InsecteFactory::create(int type, double size, QList<int> *path)
{
    Insecte * insecteToCreate;

    switch(type)
    {
        case InsecteFactory::TYPE_CAFARD:
            insecteToCreate = new Cafard(size,0,0);
            break;
        case InsecteFactory::TYPE_FOURMI:
            insecteToCreate = new Fourmi(size,0,0);
            break;
        case InsecteFactory::TYPE_GUEPE:
            insecteToCreate = new Guepe(size,0,0);
            break;
        case InsecteFactory::TYPE_MOUSTIQUE:
            insecteToCreate = new Moustique(size,0,0);
            break;
        default:
            throw invalid_argument(0);
            break;
    }

    insecteToCreate->setPath(path);

    return insecteToCreate;
}


}
