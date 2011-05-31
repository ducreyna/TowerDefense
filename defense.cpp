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

Vague* Defense::getCurrentWave()const { return currentWave; }

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
        shootTimer->stop();
    }
}

void Defense::advance(int phase)
{
    // si la vague courante n'est pas initialisée...
    if(!phase || this->currentWave == 0)
            return;

        // Recherche des ennemis de la map
        for(int i = 0 ; i < this->currentWave->getInsectes().size() ; ++i)
        {

            double _cibleX = currentWave->getInsectes().at(i)->x();
            double _cibleY = currentWave->getInsectes().at(i)->y();

            Guepe* g = dynamic_cast<Guepe*>(currentWave->getInsectes().at(i));
            if(g != 0)
            {
                QObject::connect(g,SIGNAL(degatsCrash(double,Guepe*)),this,SLOT(degatsCrashGuepe(double,Guepe*)));
            }

            if((sqrt(pow(fabs(this->x() - _cibleX),2) + pow(fabs(this->y() - _cibleY),2))  <= this->portee*32) &&
                _cibleX != 0 && _cibleX != 512 && _cibleY != 0 && _cibleY != 512)
            {
                if((this->projectile == PIERRE  && currentWave->getInsectes().at(i)->getDeplacement() == VOLANT) ||
                    (this->projectile == BOULE && currentWave->getInsectes().at(i)->getDeplacement() == RAMPANT) ||
                    (this->projectile == EAU  && currentWave->getInsectes().at(i)->getDeplacement() == VOLANT) ||
                    (this->projectile == EAU && currentWave->getInsectes().at(i)->getDeplacement() == RAMPANT) ||
                    (this->projectile == PEINTURE  && currentWave->getInsectes().at(i)->getDeplacement() == VOLANT && currentWave->getInsectes().at(i)->getVitesse() > 1) ||
                    (this->projectile == PEINTURE && currentWave->getInsectes().at(i)->getDeplacement() == RAMPANT && currentWave->getInsectes().at(i)->getVitesse() > 1)
                    )
                    {
                        // Si le défenseur ne tirait pas encore
                        if(!isShooting)
                        {
                            this->setIsShooting(true); // Modification via la méthode pour les effets visuels
                        }
                        // Actualise la position de la cible
                        this->setCurrentTarget(this->currentWave->getInsectes().at(i));

                        return; // On vise la première cible rencontrée
                    }

            }

        }
        // Si aucun monstre n'a été rencontré
        this->setIsShooting(false);  // Modification via la méthode pour les effets visuels
}

void Defense::degatsCrashGuepe(double degats, Guepe *g)
{
    for(int i = 0 ; i < this->currentWave->getInsectes().size() ; ++i)
    {
        double _cibleX = currentWave->getInsectes().at(i)->x();
        double _cibleY = currentWave->getInsectes().at(i)->y();

        if((sqrt(pow(fabs(g->x() - _cibleX),2) + pow(fabs(g->y() - _cibleY),2))  <= 1.5*32) &&
            currentWave->getInsectes().at(i)->getDeplacement() == RAMPANT)
        {
            currentWave->getInsectes().at(i)->recevoirDegats(degats);
        }

    }
}

}
