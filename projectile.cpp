#include "projectile.h"

namespace TOWERDEFENSE{

Projectile::Projectile(const double vitesse, const double frappe, const int x, const int y, const double cibleX, const double cibleY, QVector<Insecte*> vague):vitesse(vitesse),frappe(frappe),cibleX(cibleX),cibleY(cibleY),vagueEnCours(vague)
{
    this->setPos(x,y);

    double vecteurX = cibleX - this->x();
    double vecteurY = cibleY - this->y();

    this->mouvementVecteur.setX(vecteurX/sqrt(pow(vecteurX,2) + pow(vecteurY,2)));
    this->mouvementVecteur.setY(vecteurY/sqrt(pow(vecteurX,2) + pow(vecteurY,2)));
}

void Projectile::advance(int phase)
{
    if(!phase)
            return;

        // . Recherche des ennemis de la map
        QVector<Insecte*> insectes = vagueEnCours;

        for(int i = 0 ; i < insectes.size() ; ++i)
        {
                if(this->collidesWithItem(insectes.at(i),Qt::IntersectsItemBoundingRect))
                {
                    // On retire le projectile de la scène
                    this->scene()->removeItem(this);
                    // Inflige des dommages au monstre
                    insectes[i]->recevoirDegats(frappe);
                    return;
                }
        }



        // Déplacement du projectile selon le vecteur de déplacement et la vitesse
        double newx = this->x() + vitesse*mouvementVecteur.x();
        double newy = this->y() + vitesse*mouvementVecteur.y();

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
