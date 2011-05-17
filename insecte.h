#ifndef INSECTE_H
#define INSECTE_H

#include "math.h"

namespace TOWERDEFENSE{

enum Type_deplacement {RAMPANT,VOLANT};

class Insecte
{
protected:
    int taille;
    int vitalite;
    int resistance;
    int vitesse;
    Type_deplacement deplacement;

public:
    Insecte();
    Insecte(const int taille, const int vitalite, const int resistance, const int vitesse, const Type_deplacement deplacement);

    /*!
      * Accesseur modifiant l'attribut vitalite
      * \param vitalite la nouvelle vitalite de l'insecte
      */
    void setVitalite(int vitalite);

    /*!
     * Accesseur modifiant l'attribut resistance
     *\param resistance la nouvelle resistante de l'insecte
     */
    void setResistance(int resistance);

    /*!
      * Accesseur modifiant l'attribut vitesse
      * \param vitesse la nouvelle vitesse de l'insecte
      */
    void setVitesse(int vitesse);

    /*!
      * Accesseur modifiant l'attribut deplacement
      * \param deplacement le nouveau type de deplacement de l'insecte
      */
    void setDeplacement(Type_deplacement deplacement);

    /*!
      * Methode virtuelle pure permettant de traiter les degats recus par un insecte
      * \param degats les degats subis par l'attaque
      */
    virtual void recevoirDegats(int degats) = 0;
};
}

#endif // INSECTE_H
