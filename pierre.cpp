#include "pierre.h"

namespace TOWERDEFENSE{

Pierre::Pierre()
{
}

Pierre::Pierre(const double niveau,const int x,const int y,QGraphicsItem *parent)//:Defense(niveau,3+(niveau/2),1,10*pow(niveau,1.5),12,25,60,25,parent,VOLANT,PIERRE)
{
    setData(0,"PIERRE");

    QPixmap* tour = new QPixmap("data/Tour/tourPierre.png");

    // Image et taille
    this->setPixmap(*tour);

    // Position
    this->setPos(x,y);
}

double Pierre::attaquer()
{
    return frappe;
}

bool Pierre::ameliorer()
{
    try
    {
        if(niveau == 1)
        {
            niveau++;
            portee = 3 + niveau/2;
            frappe = 10 * pow(niveau,1.5);
            cout += amelioration_1;
            return true;
        }
        else if(niveau == 2)
        {
            niveau++;
            portee = 3 + niveau/2;
            frappe = 10 * pow(niveau,1.5);
            cout += amelioration_2;
            return true;
        }
        else throw std::exception();
    }
    catch(std::exception& e)
    {
        QMessageBox(QMessageBox::Information,"Amelioration impossible","La tour est de niveau maximal").exec();
        return false;
    }
}
}
