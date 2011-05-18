#include "petanque.h"

namespace TOWERDEFENSE{

Petanque::Petanque()
{
}

Petanque::Petanque(const int niveau,const int x,const int y,QGraphicsItem *parent):Defense(niveau,3+niveau,0.5,15*pow(niveau,1.5),40,80,20,parent,RAMPANT,BOULE)
{

}

double Petanque::attaquer()
{
    return frappe;
}

void Petanque::ameliorer()
{
    niveau++;
    portee = 3 + niveau;
    frappe = 15 * pow(niveau,1.5);
}

}