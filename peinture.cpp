#include "peinture.h"

namespace TOWERDEFENSE{

Peinture::Peinture()
{
}

Peinture::Peinture(const int niveau):Defense(niveau,4+niveau/2,2,4*pow(niveau,1.5),25,60,30,VIDE,PEINTURE)
{

}

double Peinture::attaquer()
{
    return frappe;
}

void Peinture::ameliorer()
{
    niveau++;
    portee = 4 + niveau/2;
    frappe = 4 * pow(niveau,1.5);
}

}
