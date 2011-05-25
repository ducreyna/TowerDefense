#ifndef FICHIER_H
#define FICHIER_H

#include <string>
#include <fstream>
#include <iostream>
#include <QTextStream>
#include "vague.h"
#include <stdexcept>

using namespace std;

namespace TOWERDEFENSE{
class Fichier
{
    int** carte;
    QVector<Vague *> vagues;
    QList<int> * path;

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
      * \return QVector<Vague *> un vecteur de Vague
      */
    QVector<Vague *> getVagues() const;

    QList<int> * getPath() const;

    bool chargerPath();

    QList<int> buildPathRecursively(int currX, int currY, int prevX, int prevY);

    /*!
      * Methode chargant la carte du jeu a partir d'un fichier et effectuant un parsing de celui-ci afin de le traduire dans un tableau a 2 dimensions
      * \param chemin le chemin PATH du fichier texte
      * \return bool true si la carte a bien ete charge, false sinon
      */
    bool chargerCarte(const std::string& chemin);

    /*!
      * Methode chargant les differentes vagues d'ennemis a partir d'un fichier et effectuant un parsing de celui-ci
      * \return QVector<Vague*> La liste des vagues
      */
    bool chargerVague(const std::string& chemin);
};
}

#endif // FICHIER_H
