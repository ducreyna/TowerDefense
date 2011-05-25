#include "insecte.h"

namespace TOWERDEFENSE{

Insecte::Insecte(){}

Insecte::Insecte(const double taille, const double vitalite, const double resistance, const double vitesse, const Type_deplacement deplacement,QGraphicsPixmapItem *parent):QGraphicsPixmapItem(parent),taille(taille),vitalite(vitalite),resistance(resistance),vitesse(vitesse),deplacement(deplacement), counter(0){
}

void Insecte::setDeplacement(Type_deplacement deplacement){
    this->deplacement = deplacement;
}

void Insecte::setResistance(double resistance){
    this->resistance = resistance;
}

void Insecte::setVitalite(double vitalite){
    this->vitalite = vitalite;
}

void Insecte::setVitesse(double vitesse){
    this->vitesse = vitesse;
}

void Insecte::increaseAnimationStep() {

    // Avance à la frame suivante de l'animation
    animState++;
    if(animState >= animPixmap.size())
        animState = 0;
}

void Insecte::advance(int phase)
{
// Si 'phase' vaut 0, rien ne se passe
    if(!phase)
        return;
    // ...sinon, on met à jour la position de l'item

    if(path->count() == counter)
        return;

    int dir = path->at(counter), deltaX, deltaY;
    double newX = x(), newY = y();

    double speed = vitesse*32*0.02; // en pixel/20ms

    if(dir == 1)
    {
        newY=newY-speed;
    }
    else if(dir == 2)
    {
        newY=y()+speed;
    }
    else if(dir == 4)
    {
        newX=newX+speed;
    }
    else if(dir == 8)
    {
        newX=newX-speed;
    }
    else if(dir == 5 || dir == 6 || dir == 9 || dir == 10)
    {
        if(path->at(counter+1) == 1)
        {
            newY=newY-speed;
            newX=floor(newX / 32)*32;
        }
        if(path->at(counter+1) == 2)
        {
            newY=y()+speed;
            newX=floor(newX / 32)*32;
        }
        if(path->at(counter+1) == 4)
        {
            newX=newX+speed;
            newY=floor(newY / 32)*32;
        }
        if(path->at(counter+1) == 8)
        {
            newX=newX-speed;
            newY=floor(newY / 32)*32;
        }
    }
    else if(dir == 32)
        return;

    deltaX = abs(floor(x() / 32) - floor(newX / 32));
    deltaY = abs(floor(y() / 32) - floor(newY / 32));

    this->setPos(newX,newY);

    int tempCounter = counter;
    this->resetTransform();

    if(path->at(counter) == 5 || path->at(counter) == 6 || path->at(counter) == 9 || path->at(counter) == 10)
    {
        tempCounter++;
    }

    if(path->at(tempCounter) == 1)
    {
        this->translate(16,16);
        this->rotate(-90);
        this->translate(-16,-16);
    }
    if(path->at(tempCounter) == 2)
    {
        this->translate(16,16);
        this->rotate(90);
        this->translate(-16,-16);
    }
    if(path->at(tempCounter) == 4)
    {
        // défault
    }
    if(path->at(tempCounter) == 8)
    {
        this->translate(16,16);
        this->rotate(180);
        this->translate(-16,-16);
    }

    if(deltaX != 0 || deltaY != 0) {
        counter++;
    }
}

void Insecte::setPath(QList<int> *path)
{
    this->path = path;
}

}
