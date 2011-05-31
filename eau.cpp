#include "eau.h"

namespace TOWERDEFENSE{

Eau::Eau(const double niveau,const int x, const int y,QGraphicsPixmapItem *parent):Defense(niveau,2+niveau/2,(4-niveau/2),5*pow(niveau,(double)1.5),8,20,45,40,EAU,parent)
{
    this->projectile = EAU;
    setData(0,"EAU");

    for(int i = 0; i < 3; ++i)
    {
        QPixmap* tour = new QPixmap("data/Tour/tourEauGrade" + QString::number(i+1) + ".png");
        this->etatTour.push_back(tour);
    }

    // Image et taille
    this->setPixmap(*etatTour.first());

    // Position
    this->setPos(x,y);

    shootTimer = new QTimer();
    QObject::connect(shootTimer,SIGNAL(timeout()),this,SLOT(shootTarget()));
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
            this->setPixmap(*etatTour.at(1));
            return true;
        }
        else if(niveau == 2)
        {
            niveau++;
            portee = 3 + niveau/2;
            cadence = 4 - niveau/2;
            frappe = 5 * pow(niveau,1.5);
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
