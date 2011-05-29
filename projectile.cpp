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
    }

    // Déplacement du projectile selon le vecteur de déplacement et la vitesse
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
    painter->setBrush(Qt::blue);
    painter->drawRect(0,0,5,5);
}

}
