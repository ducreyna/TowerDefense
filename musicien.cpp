#include "musicien.h"

namespace TOWERDEFENSE{

Musicien::Musicien()
{
}

Musicien::Musicien(const double niveau, const int x, const int y,QList<Defense*> defenses, QGraphicsPixmapItem *parent):Defense(niveau,1.5,0,0,15,40,80,0,RIEN,parent),defenses(defenses),renforcement(0.2)
{
    setData(0,"MUSICIEN");

    for(int i = 0; i < 3; ++i)
    {
        QPixmap* tour = new QPixmap("data/Tour/tourMusiqueGrade" + QString::number(i+1) + ".png");
        this->etatTour.push_back(tour);
    }

    // Image et taille
    this->setPixmap(*etatTour.first());

    // Position
    this->setPos(x,y);
}

void Musicien::setDefenses(QList<Defense *> defenses)
{
    this->defenses = defenses;
}

void Musicien::bonus()
{
    for(int i = 0; i < defenses.size(); ++i)
    {
        double _cibleX = defenses.at(i)->x();
        double _cibleY = defenses.at(i)->y();

        if(sqrt(pow(fabs(this->x() - _cibleX),2) + pow(fabs(this->y() - _cibleY),2))  <= this->portee*32)
        {
            double frappe = defenses.at(i)->getFrappe() + (defenses.at(i)->getFrappe()*renforcement);
            defenses.at(i)->setFrappe(frappe);
        }
    }
}

double Musicien::attaquer(){}

void Musicien::advance(int phase){}

bool Musicien::ameliorer()
{
    try
    {
        if(niveau == 1)
        {
            niveau++;
            renforcement = 0.4;
            cout += amelioration_1;
            this->setPixmap(*etatTour.at(1));
            this->bonus();
            return true;
        }
        else if(niveau == 2)
        {
            niveau++;
            renforcement = 0.6;
            cout += amelioration_2;
            this->setPixmap(*etatTour.at(2));
            this->bonus();
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
