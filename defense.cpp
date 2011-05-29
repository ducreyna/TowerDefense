#include "defense.h"

namespace TOWERDEFENSE{

Defense::Defense()
{
}

Defense::Defense(const double niveau,const double portee,const double cadence, const double frappe,const int cout,const int amelioration_1,const int amelioration_2, const double vitesse, QGraphicsItem *parent,const Type_deplacement cible,const Type_projectile projectile):cible(cible),niveau(niveau),portee(portee),cadence(cadence),frappe(frappe),cout(cout),amelioration_1(amelioration_1),amelioration_2(amelioration_2),projectile(projectile),vitesse(vitesse)
{
    this->currentWave = 0;
}

Defense::~Defense(){}

double Defense::getNiveau()const { return niveau; }

double Defense::getPortee()const { return portee; }

int Defense::getCout()const { return cout; }

int Defense::getAmelioration_1()const { return amelioration_1; }

int Defense::getAmelioration_2()const { return amelioration_2; }

void Defense::shootTarget()
{
    Projectile *shot = new Projectile(this);
    this->scene()->addItem(shot);
}

void Defense::setIsShooting(bool state) {

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

void Defense::advance(int phase)
{
    // si la vague courante n'est pas initialisée...
    if(!phase || this->currentWave == 0)
            return;

        // Recherche des ennemis de la map
        for(int i = 0 ; i < this->currentWave->getInsectes().size() ; ++i) {

                double _cibleX = currentWave->getInsectes().at(i)->x();
                double _cibleY = currentWave->getInsectes().at(i)->y();

                if(sqrt(pow(fabs(this->x() - _cibleX),2) + pow(fabs(this->y() - _cibleY),2))  <= this->portee*32)
                {
                    // Si le défenseur ne tirait pas encore
                    if(!isShooting)
                    {
                        this->setIsShooting(true); // Modification via la méthode pour les effets visuels
                    }
                    // Actualise la position de la cible
                    this->setCurrentTarget(this->currentWave->getInsectes().at(i));

                    return; // On vise la première cible rencontrée

                } // end distanceTest

        } //eof

        // Si aucun monstre n'a été rencontré
        this->setIsShooting(false);  // Modification via la méthode pour les effets visuels
}

}
