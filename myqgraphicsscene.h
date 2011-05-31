#ifndef MYQGRAPHICSSCENE_H
#define MYQGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QList>

#include "insecte.h"
#include "joueur.h"

using namespace TOWERDEFENSE;

class MyQGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

private:
    std::string tourDemandee;
    QGraphicsItem *precedent;
    QGraphicsItem *precedent2;
    QGraphicsItem *tourPortee;
    QGraphicsItem *tourAmelioration;
    Joueur *J;

public:
    /*!
      * Constructeur parametre
      * \param parent la QGraphicsView parente
      * \param *J le joueur de la partie
      */
    MyQGraphicsScene(QGraphicsView *parent,Joueur *J);

    /*!
      * Methode gerant les cliques de la souris sur la scene
      * \param mouseEvent l'evenement de la souris
      */
    void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );

    /*!
      * Methode gerant les mouvements de la souris sur la scene
      * \param mouseEvent l'evenement de la souris
      */
    void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent );

    /*!
      * Methode permettant de charger les graphiques sur la scene
      * \param **carte tableau a 2 dimensions contenant la carte du jeu
      */
    void chargerGraphiques(int **carte);

    /*!
      * Methode permettant de supprimer un insecte d'envoyer le bon signal au Joueur
      * \param *insecte l'insecte a supprimer
      * \param vivant true = l'insecte est arrive au but    false = l'insecte a ete detruit par une tour
      */
    void removeInsecte(QGraphicsItem *insecte,bool vivant=false);

    /*!
      * Accesseur modifiant la valeur de la tour demandee
      * \param tour type de tour demande
      */
    void setTourDemandee(std::string tour);

    /*!
      * Accesseur constant renvoyant l'item "precedent"
      * \return QGraphicsItem* item "precedent"
      */
    QGraphicsItem* getPrecedent()const;

    /*!
      * Accesseur constant renvoyant l'item "precedent2"
      * \return QGraphicsItem* item "precedent2"
      */
    QGraphicsItem* getPrecedent2()const;

    /*!
      * Accesseur constant renvoyant l'item de portee de la tour
      * \return QGraphicsItem* la portee de la tour
      */
    QGraphicsItem* getTourPortee()const;

    /*!
      * Accesseur constant renvoyant la nouvelle portee suite a l'amelioration de la tour
      * \return QGraphicsItem* la nouvelle amelioration de la tour
      */
    QGraphicsItem* getTourAmelioration()const;

    /*!
      * Accesseur modifiant l'item "precedent2"
      * \param *I item remplacant "precedent2"
      */
    void setPrecedent2(QGraphicsItem *I);

    /*!
      * Accesseur modifiant l'item de portee de la tour
      * \return *I la nouvelle portee de la tour
      */
    void setTourPortee(QGraphicsItem *I);

    /*!
      * Accesseur modifiant la nouvelle portee suite a l'amelioration de la tour
      * \return *I la nouvelle amelioration de la tour
      */
    void setTourAmelioration(QGraphicsItem *I);

signals:
    /*!
      * Signal permettant d'ajouter une tour sur la scene
      * \param x l'emplacement de la tour suivant l'axe x
      * \param y l'emplacement de la tour suivant l'axe y
      * \param type le type de tour que l'on veut creer
      */
    void ajouterTour(int x, int y, std::string type);

    /*!
      * Signal permettant d'ajouter une tour temporairement reproduisant le mouseTracking
      * \param x l'emplacement de la tour suivant l'axe x
      * \param y l'emplacement de la tour suivant l'axe y
      * \param type le type de tour que l'on veut creer
      */
    void tourMouseTracking(int x, int y,std::string type);

    /*!
      * Signal permettant de renseigner la fenetre principale sur la tour selectionnee sur la scene
      * \param x l'emplacement de la tour suivant l'axe x
      * \param y l'emplacement de la tour suivant l'axe y
      * \param *tour pointeur sur la tour selectionnee
      */
    void tourSelectionnee(int x, int y, QGraphicsItem *tour);

    /*!
      * Signal envoye quand l'insecte a ete detruit par une tour
      */
    void augmenterArgent();

    /*!
      * Signal envoye quand l'insecte a atteint le but
      */
    void perdreVie();
};

#endif // MYQGRAPHICSSCENE_H
