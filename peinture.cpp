#include "peinture.h"

namespace TOWERDEFENSE{

Peinture::Peinture()
{
}

Peinture::Peinture(const double niveau,const int x,const int y,QGraphicsItem *parent):Defense(niveau,4+niveau/2,2,4*pow(niveau,1.5),12,25,60,30,PEINTURE,parent)
{
    this->projectile = PEINTURE;
    setData(0,"PEINTURE");

    for(int i = 0; i < 3; ++i)
    {
        QPixmap* tour = new QPixmap("data/Tour/tourPeintureGrade" + QString::number(i+1) + ".png");
        this->etatTour.push_back(tour);
    }

    // Image et taille
    this->setPixmap(*etatTour.first());

    // Position
    this->setPos(x,y);

    shootTimer = new QTimer();
    QObject::connect(shootTimer,SIGNAL(timeout()),this,SLOT(shootTarget()));
}

double Peinture::attaquer()
{
    return frappe;
}

bool Peinture::ameliorer()
{
    try
    {
        if(niveau == 1)
        {
            niveau++;
            portee = 4 + niveau/2;
            frappe = 4 * pow(niveau,1.5);
            cout += amelioration_1;
            this->setPixmap(*etatTour.at(1));
            return true;
        }
        else if(niveau == 2)
        {
            niveau++;
            portee = 4 + niveau/2;
            frappe = 4 * pow(niveau,1.5);
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
