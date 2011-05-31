#ifndef FICHIER_H
#define FICHIER_H

#include <fstream>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QStringList>
#include "vague.h"

namespace TOWERDEFENSE{
class Fichier
{
    int** carte;
    QVector<Vague *> vagues;
    QList<int> * path;

    /*!
      * Methode privee creant le chemin (path) recursivement
      * \param currX emplacement courant sur l'axe x
      * \param currY emplacement courant sur l'axe y
      * \param prevX emplacement precedent sur l'axe x
      * \param prevY emplacement precedent sur l'axe y
      * \return QList<int> une liste d'entiers contenant le chemin fraichement construit
      */
    QList<int> buildPathRecursively(int currX, int currY, int prevX, int prevY);

public:
    /*!
      * Constructeur par defaut
      */
    Fichier();

    /*!
      * Destructeur de la classe
      */
    virtual ~Fichier();

    /*!
      * Accesseur constant renvoyant la carte du jeu
      * \return int** tableau 2 dimensions
      */
    int** getCarte() const;

    /*!
      * Accesseur constant renvoyant les vagues du jeu
      * \return QVector<Vague *> un vecteur de Vague
      */
    QVector<Vague *> getVagues() const;

    /*!
      * Accesseur constant renvoyant le chemin a suivre pour les insectes
      * \return QList<int>* un pointeur de liste contenant le chemin
      */
    QList<int> * getPath() const;

    /*!
      * Methode permettant de charger le chemin (path)
      * \return true = chargement reussie   false = chargement impossible
      */
    bool chargerPath();

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
