#include "eau.h"

namespace TOWERDEFENSE{

Eau::Eau(const int niveau):Defense(niveau,3+niveau/2,(4-niveau/2),5*pow(niveau,1.5),20,45,40)
{
}

double Eau::attaquer()
{
    return frappe;
}

void Eau::ameliorer()
{
    niveau++;
    portee = 3 + niveau/2;
    cadence = 4 - niveau/2;
    frappe = 5 * pow(niveau,1.5);
}

}
