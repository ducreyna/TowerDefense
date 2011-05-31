#include "petanque.h"

namespace TOWERDEFENSE{

Petanque::Petanque()
{
}

Petanque::Petanque(const double niveau,const int x,const int y,QGraphicsItem *parent):Defense(niveau,3+niveau,0.5,15*pow(niveau,1.5),15,40,80,20,BOULE,parent)
{
    this->projectile = BOULE;
    setData(0,"PETANQUE");

    for(int i = 0; i < 3; ++i)
    {
        QPixmap* tour = new QPixmap("data/Tour/tourPetanqueGrade" + QString::number(i+1) + ".png");
        this->etatTour.push_back(tour);
    }

    // Image et taille
    this->setPixmap(*etatTour.first());

    // Position
    this->setPos(x,y);

    shootTimer = new QTimer();
    QObject::connect(shootTimer,SIGNAL(timeout()),this,SLOT(shootTarget()));
}

double Petanque::attaquer()
{
    return frappe;
}

bool Petanque::ameliorer()
{
    try
    {
        if(niveau == 1)
        {
            niveau++;
            portee = 3 + niveau;
            frappe = 15 * pow(niveau,1.5);
            cout += amelioration_1;
            this->setPixmap(*etatTour.at(1));
            return true;
        }
        else if(niveau == 2)
        {
            niveau++;
            portee = 3 + niveau;
            frappe = 15 * pow(niveau,1.5);
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
