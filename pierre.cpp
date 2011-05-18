#include "pierre.h"

namespace TOWERDEFENSE{

Pierre::Pierre()
{
}

Pierre::Pierre(const int niveau,const int x,const int y,QGraphicsItem *parent):Defense(niveau,3+niveau/2,1,10*pow(niveau,1.5),25,60,25,parent,VOLANT,PIERRE)
{
}

double Pierre::attaquer()
{
    return frappe;
}

void Pierre::ameliorer()
{
    niveau++;
    portee = 3 + niveau/2;
    frappe = 10 * pow(niveau,1.5);
}

}