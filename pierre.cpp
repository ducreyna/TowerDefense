#include "pierre.h"

namespace TOWERDEFENSE{

Pierre::Pierre()
{
}

Pierre::Pierre(const double niveau,const int x,const int y,QGraphicsItem *parent):Defense(niveau,3+(niveau/2),1,10*pow(niveau,1.5),12,25,60,25,parent,VOLANT,PIERRE)
{
    this->projectile = PIERRE;
    setData(0,"PIERRE");

    for(int i = 0; i < 3; ++i)
    {
        QPixmap* tour = new QPixmap("data/Tour/tourPierreGrade" + QString::number(i+1) + ".png");
        this->etatTour.push_back(tour);
    }

    // Image et taille
    this->setPixmap(*etatTour.first());

    // Position
    this->setPos(x,y);

    shootTimer = new QTimer();
    QObject::connect(shootTimer,SIGNAL(timeout()),this,SLOT(shootTarget()));
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
            this->setPixmap(*etatTour.at(1));
            return true;
        }
        else if(niveau == 2)
        {
            niveau++;
            portee = 3 + niveau/2;
            frappe = 10 * pow(niveau,1.5);
            cout += amelioration_2;
            this->setPixmap(*etatTour.at(2));
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
