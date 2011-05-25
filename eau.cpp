#include "eau.h"

namespace TOWERDEFENSE{

Eau::Eau(const double niveau,const int x, const int y,QGraphicsPixmapItem *parent):Defense(niveau,2+niveau/2,(4-niveau/2),5*pow(niveau,(double)1.5),8,20,45,40,parent)
{
    setData(0,"EAU");

    QPixmap* tour = new QPixmap("data/Tour/tourEau.png");

    // Image et taille
    this->setPixmap(*tour);

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

void Eau::setTarget(double cibleX,double cibleY) {
    // Sauvegarde la position de la cible courante
    this->cibleX = cibleX;
    this->cibleY = cibleY;
}

void Eau::setIsShooting(bool state) {

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

void Eau::advance(int phase)
{
    if(!phase)
            return;

        // Détection des ennemis aux alentours
        QVector<Insecte*> insectes = vagueEnCours->getInsectes();

        // Recherche des ennemis de la map
        for(int i = 0 ; i < insectes.size() ; ++i) {

                double _cibleX = insectes.at(i)->x();
                double _cibleY = insectes.at(i)->y();

                if(sqrt(pow(fabs(this->x() - _cibleX),2) + pow(fabs(this->y() - _cibleY),2))  <= this->portee*32)
                {
                    // Si le défenseur ne tirait pas encore
                    if(!isShooting)
                    {
                        this->setIsShooting(true); // Modification via la méthode pour les effets visuels
                    }
                    // Actualise la position de la cible

                    this->setTarget(_cibleX+insectes.at(i)->getTaille()*16,_cibleY+insectes.at(i)->getTaille()*16);

                    return; // On vise la première cible rencontrée

                } // end distanceTest

        } //eof

        // Si aucun monstre n'a été rencontré
        this->setIsShooting(false);  // Modification via la méthode pour les effets visuels
}

void Eau::shootTarget()
{
    Projectile *shot = new Projectile(vitesse,frappe,this->x()+14,this->y()+14,cibleX,cibleY,vagueEnCours);
    this->scene()->addItem(shot);
}

}
