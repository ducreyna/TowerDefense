#ifndef JOUEUR_H
#define JOUEUR_H

#include <QObject>

namespace TOWERDEFENSE{

class Joueur :public QObject
{
    Q_OBJECT
private:
    int argent;
    int vies;

public:
    Joueur(const int vies=10, const int argent=50);

    /*!
      * Accesseur constant renvoyant l'argent du joueur de la partie
      * \return int la valeur de l'argent
      */
    int getArgent()const;

    /*!
      * Accesseur constant renvoyant les vies du joueur
      * \return int la valeur des vies
      */
    int getVies()const;

public slots:
    /*!
      * Slot permettant d'augmenter l'argent du joueur suite a la destruction d'un insecte
      */
    void gagnerArgent();

    /*!
      * Slot permettant de diminuer les vies du joueur suite a l'arrivee de l'insecte au but
      */
    void perdreVie();

    /*!
      * Slot permettant de diminuer l'argent du joueur suite a l'achat d'une tour
      * \param prix le prix de la tour
      */
    void achatTour(int prix);

    /*!
      * Slot permettant d'augmenter l'argent du joueur suite a la vente d'une tour
      * \param gain le gain engendre
      */
    void venteTour(int gain);

signals:
    /*!
      * Signal indiquant que l'argent a ete modifie
      * \param int la nouvelle valeur de l'argent
      */
    void argentModifie(int);

    /*!
      * Signal indiquant que les vies ont ete modifiees
      * \param int la nouvelle valeur de l'argent
      */
    void viesModifiees(int);

    /*!
      * Signal indiquant que la partie est terminee et que le joueur a perdu
      */
    void finDuJeu();
};
}

#endif // JOUEUR_H
