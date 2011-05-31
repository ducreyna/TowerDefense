#ifndef INSECTE_H
#define INSECTE_H

#include <QList>
#include <QString>

#include "math.h"
#include "entite.h"

#include "constantes.h"
#include <iostream>

namespace TOWERDEFENSE{

class Insecte : public Entite
{
    Q_OBJECT
protected:
    double taille;
    double vitalite;
    double resistance;
    double vitesse;
    double vitesseStandard;
    QList<int> *path;
    Type_deplacement deplacement;
    QList<QPixmap*> animPixmap;
    int animState;
    int counter;
    int counterTempsRalentissement;

public:
    /*!
      * Constructeur par defaut
      */
    Insecte();

    /*!
      * Constructeur parametre
      * \param taille la taille de l'insecte
      * \param vitalite la vitalite de l'insecte
      * \param resistance la resistance de l'insecte
      * \param vitesse la vitesse de l'insecte
      * \param deplacement le type de deplacement de l'insecte (RAMPANT OU VOLANT)
      * \param parent l'item parent initialise a 0
      */
    Insecte(const double taille, const double vitalite, const double resistance, const double vitesse, const Type_deplacement deplacement, QGraphicsPixmapItem *parent=0);

    /*!
      * Methode permettant l'animation de l'item sur la scene
      * \param phase la phase d'appel de l'item
      */
    void advance(int phase);

    /*!
      * Accesseur modifiant la liste contenant le path(chemin)
      * \param *path le nouveau path(chemin)
      */
    void setPath(QList<int> *path);

    /*!
      * Accesseur modifiant le compteur du path afin de se placer au bon endroit sur le chemin
      * \param counter le compteur permettant de se placer au bon endroit dans le path
      */
    void setCounter(int counter);

    /*!
      * Methode virtuelle pure permettant de traiter les degats recus par un insecte
      * \param degats les degats subis par l'attaque
      */
    virtual void recevoirDegats(double degats);

    /*!
      * Methode permettant de ralentir un insecte notamment lorsque celui-ci est touche par la tour Peinture
      */
    void ralentir();

    /*!
      * Accesseur constant renvoyant la taille de l'insecte
      * \return double la taille de l'insecte
      */
    double getTaille()const;

    /*!
      * Accesseur constant renvoyant la vitalite de l'insecte
      * \return double la vitalite de l'insecte
      */
    double getVitalite()const;

    /*!
      * Accesseur constant renvoyant la vitesse de l'insecte
      * \return double la vitesse de l'insecte
      */
    double getVitesse()const;

    /*!
      * Accesseur constant renvoyant le type de deplacement de l'insecte
      * \return Type_deplacement le type de deplacement de l'insecte
      */
    Type_deplacement getDeplacement()const;

    /*!
      * Accesseur constant renvoyant le path(chemin) suivi par l'insecte
      * \return QList<int>* pointeur sur la liste contenant le path
      */
    QList<int>* getPath()const;

    /*!
      * Accesseur constant renvoyant la compteur du path(chemin)
      * \return int le compteur du path(chemin)
      */
    int getCounter() const;

    /*!
      * Methode incrementant l'etat de l'animation afin de simuler le mouvement du moustique
      */
    void increaseAnimationStep();

signals:
    /*!
      * Signal envoye quand l'insecte est mort
      * \param *I l'insecte a supprimer
      * \param vivant true = l'insecte est arrive au but    false = l'insecte est tue par une tour
      */
    void supprimerInsecte(Insecte* I,bool vivant);

    /*!
      * Signal permettant d'ajouter des insectes enfants (notamment pour les cafards) quand l'insecte courant est detruit
      * \param type type de l'insecte a creer (passage par la factory)
      * \param taille la taille de l'insecte
      * \param x emplacement de l'insecte sur l'axe x
      * \param y emplacement de l'insecte sur l'axe y
      * \param *path une liste contenant le path(chemnin)
      * \param counter compteur du path(chemin)
      * \param numEnfant numero de l'enfant cree
      */
    void ajouterInsecteEnfant(int type,double taille,int x, int y,QList<int> *path,int counter,int numEnfant);
};
}

#endif // INSECTE_H
