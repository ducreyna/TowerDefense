#include "projectile.h"
#include "defense.h"

namespace TOWERDEFENSE{

Projectile::Projectile(Defense * tour)
{
    this->tour = tour;

    this->setPos(this->tour->x()+16,this->tour->y()+16);

    double XScaledSize = this->tour->getCurrentTarget()->x()+this->tour->getCurrentTarget()->getTaille()*16;
    double YScaledSize = this->tour->getCurrentTarget()->y()+this->tour->getCurrentTarget()->getTaille()*16;

    double vecteurX = XScaledSize - this->x();
    double vecteurY = YScaledSize - this->y();

    this->mouvementVecteur.setX(vecteurX/sqrt(pow(vecteurX,2) + pow(vecteurY,2)));
    this->mouvementVecteur.setY(vecteurY/sqrt(pow(vecteurX,2) + pow(vecteurY,2)));
}

void Projectile::advance(int phase)
{
    if(!phase)
            return;

    if(this->collidesWithItem(this->tour->getCurrentTarget(),Qt::IntersectsItemBoundingRect))
    {
        this->scene()->removeItem(this);
        this->tour->getCurrentTarget()->recevoirDegats(this->tour->getFrappe());

        if(this->tour->getTypeProjectile() == PEINTURE)
        {
            this->tour->getCurrentTarget()->ralentir();
        }

        if(this->tour->getTypeProjectile() == BOULE)
        {
            for(int i = 0; i < this->tour->getCurrentWave()->getInsectes().size(); ++i)
            {
                double _cibleX = this->tour->getCurrentWave()->getInsectes().at(i)->x();
                double _cibleY = this->tour->getCurrentWave()->getInsectes().at(i)->y();

                if((sqrt(pow(fabs(this->x() - _cibleX),2) + pow(fabs(this->y() - _cibleY),2))  <= 32))
                {
                    this->tour->getCurrentWave()->getInsectes().at(i)->recevoirDegats(10*pow(this->tour->getNiveau(),1.5));
                }
            }
        }
    }

    // Déplacement du projectile selon le vecteur de deplacement et la vitesse
    double newx = this->x() + this->tour->getVitesseProjectile()*mouvementVecteur.x();
    double newy = this->y() + this->tour->getVitesseProjectile()*mouvementVecteur.y();

    // Si le projectile est en dehors de l'écran, on le supprime
    if(newx < 0 || newx > 512 || newy < 0 || newy > 512){
        this->scene()->removeItem(this);
        return;
    }
    this->setPos(newx,newy);
}

QRectF Projectile::boundingRect()const
{
    return QRectF(0,0,5,5);
}

void Projectile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    if(this->tour->getTypeProjectile() == EAU)
    {
        painter->setBrush(Qt::darkBlue);
        painter->drawEllipse(0,0,5,5);
    }
    else if(this->tour->getTypeProjectile() == PIERRE)
    {
        painter->setBrush(Qt::darkRed);
        painter->drawEllipse(0,0,5,5);
    }
    else if(this->tour->getTypeProjectile() == PEINTURE)
    {
        painter->setBrush(Qt::darkRed);
        painter->drawEllipse(0,0,5,5);
    }
    else
    {
        painter->setBrush(Qt::darkCyan);
        painter->drawEllipse(0,0,5,5);
    }
}

}
