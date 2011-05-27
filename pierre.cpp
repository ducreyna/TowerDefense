#include "pierre.h"

namespace TOWERDEFENSE{

Pierre::Pierre()
{
}

Pierre::Pierre(const double niveau,const int x,const int y,QGraphicsItem *parent):Defense(niveau,3+(niveau/2),1,10*pow(niveau,1.5),12,25,60,25,parent,VOLANT,PIERRE)
{
    this->projectile = PIERRE;
    setData(0,"PIERRE");

    QPixmap* tour = new QPixmap("data/Tour/tourPierre.png");

    // Image
    this->setPixmap(*tour);

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

void Pierre::setTarget(double cibleX,double cibleY) {
    // Sauvegarde la position de la cible courante
    this->cibleX = cibleX;
    this->cibleY = cibleY;
}

void Pierre::setIsShooting(bool state) {

    isShooting = state;

    // MODE TIR ACTIVÉ
    if(state)
    {
        shootTimer->start(1000/cadence);
    }
    else
    {
        // Désactive le timer
        shootTimer->stop();
    }
}

void Pierre::advance(int phase)
{
    if(!phase)
            return;

        // Recherche des ennemis de la map
        for(int i = 0 ; i < vagueEnCours.size() ; ++i) {

                double _cibleX = vagueEnCours.at(i)->x();
                double _cibleY = vagueEnCours.at(i)->y();

                if(sqrt(pow(fabs(this->x() - _cibleX),2) + pow(fabs(this->y() - _cibleY),2))  <= this->portee*32)
                {
                    // Si le défenseur ne tirait pas encore
                    if(!isShooting)
                    {
                        this->setIsShooting(true); // Modification via la méthode pour les effets visuels
                    }
                    // Actualise la position de la cible

                    this->setTarget(_cibleX+vagueEnCours.at(i)->getTaille()*16,_cibleY+vagueEnCours.at(i)->getTaille()*16);

                    return; // On vise la première cible rencontrée

                } // end distanceTest

        } //eof

        // Si aucun monstre n'a été rencontré
        this->setIsShooting(false);  // Modification via la méthode pour les effets visuels
}

void Pierre::shootTarget()
{
    Projectile *shot = new Projectile(vitesse,frappe,this->x()+16,this->y()+16,cibleX,cibleY,vagueEnCours,this->projectile);
    this->scene()->addItem(shot);
}
}
