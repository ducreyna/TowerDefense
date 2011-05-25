#include "insecte.h"

namespace TOWERDEFENSE{

Insecte::Insecte(){}

Insecte::Insecte(const double taille, const double vitalite, const double resistance, const double vitesse, const Type_deplacement deplacement, QGraphicsPixmapItem *parent):QGraphicsPixmapItem(parent),taille(taille),vitalite(vitalite),resistance(resistance),vitesse(vitesse),deplacement(deplacement){
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

double Insecte::getTaille()const { return taille; }

double Insecte::getVitalite()const { return vitalite; }

void Insecte::increaseAnimationStep() {

    // Avance à la frame suivante de l'animation
    animState++;
    if(animState >= animPixmap.size())
        animState = 0;
}

}
