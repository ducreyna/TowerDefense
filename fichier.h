#ifndef FICHIER_H
#define FICHIER_H

#include <string>
#include <fstream>
#include <iostream>
#include <QTextStream>

namespace TOWERDEFENSE{
class Fichier
{
    int** carte;
    double** vague; //le nombre d'ennemis est limite lors d'un jeu
    /*
        la premiere case du tableau vague indique le numero
        /!\ Par convention 1 = Fourmi
                           2 = Cafard
                           3 = Guepe
                           4 = Moustique
                           0 = pas de vague
     */
public:
    Fichier();
    virtual ~Fichier();

    /*!
      * Accesseur renvoyant la carte du jeu
      * \return int** tableau 2 dimensions
      */
    int** getCarte() const;

    /*!
      * Accesseur renvoyant les vagues du jeu
      * \return double** tableau 2 dimensions
      */
    double** getVague() const;

    /*!
      * Methode chargant la carte du jeu a partir d'un fichier et effectuant un parsing de celui-ci afin de le traduire dans un tableau a 2 dimensions
      * \param chemin le chemin PATH du fichier texte
      * \return bool true si la carte a bien ete charge, false sinon
      */
    bool chargerCarte(const std::string& chemin);

    /*!
      * Methode chargant les differentes vagues d'ennemis a partir d'un fichier et effectuant un parsing de celui-ci
      * \return bool true si la carte a bien ete charge, false sinon
      */
    bool chargerVague(const std::string& chemin);

    /*!
      * Methode permettant de compter le nombre de vagues chargees
      * \return int le nombre de vagues
      */
    int NombreVagues() const;
};
}

#endif // FICHIER_H
