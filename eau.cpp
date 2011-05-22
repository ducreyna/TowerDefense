#include "eau.h"

namespace TOWERDEFENSE{

Eau::Eau(const double niveau,const int x, const int y,QGraphicsItem *parent):Defense(niveau,2+niveau/2,(4-niveau/2),5*pow(niveau,1.5),8,20,45,40,parent)
{
    setData(0,"EAU");

    QPixmap* tour = new QPixmap("data/Tour/tourEau.png");

    // Image et taille
    this->setPixmap(*tour);

    // Position
    this->setPos(x,y);
}

double Eau::attaquer()
{
    return frappe;
}

bool Eau::ameliorer()
{
    try
    {
        if(niveau == 1)
        {
            niveau++;
            portee = 3 + niveau/2;
            cadence = 4 - niveau/2;
            frappe = 5 * pow(niveau,1.5);
            cout += amelioration_1;
            return true;
        }
        else if(niveau == 2)
        {
            niveau++;
            portee = 3 + niveau/2;
            cadence = 4 - niveau/2;
            frappe = 5 * pow(niveau,1.5);
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
