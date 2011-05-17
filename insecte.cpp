#include "insecte.h"

namespace TOWERDEFENSE{

Insecte::Insecte(){}

Insecte::Insecte(const int taille, const int vitalite, const int resistance, const int vitesse, const Type_deplacement deplacement):taille(taille),vitalite(vitalite),resistance(resistance),vitesse(vitesse),deplacement(deplacement){
}

void Insecte::setDeplacement(Type_deplacement deplacement){
    this->deplacement = deplacement;
}

void Insecte::setResistance(int resistance){
    this->resistance = resistance;
}

void Insecte::setVitalite(int vitalite){
    this->vitalite = vitalite;
}

void Insecte::setVitesse(int vitesse){
    this->vitesse = vitesse;
}

}
